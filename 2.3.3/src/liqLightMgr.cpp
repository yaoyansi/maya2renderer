#include <liqLightMgr.h>

#include <maya/MItDag.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagModifier.h>
#include <maya/MFnLight.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MDagPathArray.h>


#include <liqRibHT.h>
#include <liqRibTranslator.h>

//
tLightMgr::tLightMgr()
{

}
//
tLightMgr::~tLightMgr()
{

}
//
void tLightMgr::scanScene(const float lframe__, const int sample__,
						  boost::shared_ptr< liqRibHT > &htable__,
						  int &count__,
						  MStatus &returnStatus__)
{
	MItDag dagLightIterator( MItDag::kDepthFirst, MFn::kLight, &returnStatus__);

	for (; !dagLightIterator.isDone(); dagLightIterator.next()) 
	{
#if (Refactoring == 0)
		LIQ_CHECK_CANCEL_REQUEST;
#endif
		MDagPath path;
		MObject currentNode;
		currentNode = dagLightIterator.item();
		MFnDagNode dagNode;
		dagLightIterator.getPath( path );
		if(MS::kSuccess != returnStatus__) 
			continue;
		if(!currentNode.hasFn(MFn::kDagNode)) 
			continue;
		returnStatus__ = dagNode.setObject( currentNode );
		if(MS::kSuccess != returnStatus__) 
			continue;

		// scanScene: if it's a light then insert it into the hash table
		if( currentNode.hasFn( MFn::kLight ) ) 
		{
			if( currentNode.hasFn( MFn::kAreaLight ) ) 
			{
				// add a coordSys node if necessary
				MStatus status;
				bool coordsysExists = false;
				// get the coordsys name
				MFnDependencyNode areaLightDep( currentNode );
				MString coordsysName = areaLightDep.name()+"CoordSys";
				// get the transform
				MObject transform = path.transform();
				// check the coordsys does not exist yet under the transform
				MFnDagNode transformDag( transform );
				int numChildren = transformDag.childCount();
				if( numChildren > 1 ) 
				{
					for ( unsigned int i=0; i<numChildren; i++ ) 
					{
						MObject childObj = transformDag.child( i, &status );
						if( status == MS::kSuccess && childObj.hasFn( MFn::kLocator ) ) 
						{
							MFnDependencyNode test(childObj);
							if( test.name() == coordsysName ) 
								coordsysExists = true;
						}
					}
				}
				if( !coordsysExists ) 
				{
					// create the coordsys
					MDagModifier coordsysNode;
					MObject coordsysObj  = coordsysNode.createNode( "liquidCoordSys", transform, &status );
					if( status == MS::kSuccess ) 
					{
						// rename node to match light name
						coordsysNode.doIt();
						if( status == MS::kSuccess ) 
						{
							MFnDependencyNode coordsysDep( coordsysObj );
							coordsysDep.setName( coordsysName );
						}
					}
				}
			}

			if( ( sample__ > 0 ) && isObjectMotionBlur( path )) 
				htable__->insert( path, lframe__, sample__, MRT_Light,	count__++ );
			else 
				htable__->insert( path, lframe__, 0, MRT_Light, count__++ );
			continue;
		}
	}
}
//
MStatus tLightMgr::buildShadowJob( 
	structJob &thisJob___, bool m_lazyCompute__
	)
{
	MStatus returnStatus__;
	MStatus status__;
	MDagPath lightPath__;

	MItDag dagIterator( MItDag::kDepthFirst, MFn::kLight, &returnStatus__ );
	for (; !dagIterator.isDone(); dagIterator.next()) 
	{
		if( !dagIterator.getPath( lightPath__ ) ) 
			continue;
		bool usesDepthMap = false;
		MFnLight fnLightNode( lightPath__ );
		liquidGetPlugValue( fnLightNode, "useDepthMapShadows", usesDepthMap, status__ );
		if( usesDepthMap && areObjectAndParentsVisible( lightPath__ ) ) 
		{
			// philippe : this is the default and can be overriden
			// by the everyFrame/renderAtFrame attributes.
			//
			thisJob___.renderFrame           = liqglo.liqglo_lframe;
			thisJob___.everyFrame            = true;
			thisJob___.shadowObjectSet       = "";
			thisJob___.shadowArchiveRibDone  = false;
			thisJob___.skip                  = false;
			//
			// We have a shadow job, so find out if we need to use deep shadows,
			// and the pixel sample__ count
			//
			thisJob___.deepShadows                 = false;
			thisJob___.shadowPixelSamples          = 1;
			thisJob___.shadowVolumeInterpretation  = 1;
			thisJob___.shadingRateFactor           = 1.0;
			thisJob___.shadowAggregation			= 0;

			// philippe : we grab the job's resolution now instead of in the output phase
			// that way , we can make sure one light can generate many shadow maps
			// with different resolutions
			thisJob___.aspectRatio = 1.0;
			liquidGetPlugValue( fnLightNode, "dmapResolution", thisJob___.width, status__ );
			thisJob___.height = thisJob___.width;

			// Get to our shader node.
			//
			MPlug liquidLightShaderNodeConnection;
			MStatus liquidLightShaderStatus;
			liquidLightShaderNodeConnection = fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus );
			if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() )
			{
				MPlugArray liquidLightShaderNodePlugArray;
				liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
				MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

				// Now grab the parameters.
				//
				liquidGetPlugValue( fnLightShaderNode, "deepShadows", thisJob___.deepShadows, status__ );

				// Only use the pixel samples and volume interpretation with deep shadows.
				//
				if( thisJob___.deepShadows )
				{
					liquidGetPlugValue( fnLightShaderNode, "pixelSamples", thisJob___.shadowPixelSamples, status__ );
					liquidGetPlugValue( fnLightShaderNode, "volumeInterpretation", thisJob___.shadowVolumeInterpretation, status__ );
				}

				// philippe : check the shadow rendering frequency
				//
				liquidGetPlugValue( fnLightShaderNode, "everyFrame", thisJob___.everyFrame, status__ );

				// philippe : this is crucial, as we rely on the renderFrame to check
				// which frame the scene should be scanned for that job.
				// If the job is a shadow rendering once only at a given frame, we take the
				// renderAtFrame attribute, otherwise, the current time.
				//
				if( !thisJob___.everyFrame ) 
					liquidGetPlugValue( fnLightShaderNode, "renderAtFrame", thisJob___.renderFrame, status__ );  

				// Check if the shadow aggregation option is used
				liquidGetPlugValue( fnLightShaderNode, "aggregateShadowMaps", thisJob___.shadowAggregation, status__ );  

				// philippe : check the shadow geometry set
				//
				liquidGetPlugValue( fnLightShaderNode, "geometrySet", thisJob___.shadowObjectSet, status__ );
				liquidGetPlugValue( fnLightShaderNode, "shadingRateFactor", thisJob___.shadingRateFactor, status__ );
			} 
			else 
			{
				/* Here we support the same options as those found on light shader nodes
				but we look for dynamic attributes, so we need a bit more error checking.
				*/
				//MPlug paramPlug = fnLightNode.findPlug( "deepShadows", &status );
				liquidGetPlugValue( fnLightNode, "deepShadows", thisJob___.deepShadows, status__ );
				if( thisJob___.deepShadows ) 
				{
					liquidGetPlugValue( fnLightNode, "pixelSamples", thisJob___.shadowPixelSamples, status__ );
					liquidGetPlugValue( fnLightNode, "volumeInterpretation", thisJob___.shadowVolumeInterpretation, status__ );
				}
				liquidGetPlugValue( fnLightNode, "everyFrame", thisJob___.everyFrame, status__ );
				if( !thisJob___.everyFrame ) 
					liquidGetPlugValue( fnLightNode, "renderAtFrame", thisJob___.renderFrame, status__ );  

				liquidGetPlugValue( fnLightNode, "geometrySet", thisJob___.shadowObjectSet, status__ );  
				liquidGetPlugValue( fnLightNode, "shadingRateFactor", thisJob___.shadingRateFactor, status__ ); 
			}


			// this will store the shadow camera path and the test's result
			//bool lightHasShadowCam = false;
			MDagPathArray shadowCamPath;

			if( lightPath__.hasFn( MFn::kSpotLight ) || lightPath__.hasFn( MFn::kDirectionalLight ) ) 
			{	
				tLightMgr::buildShadowJob_SpotAndDirectionLight(
					thisJob___, shadowCamPath, fnLightNode, lightPath__,
					m_lazyCompute__
					);
			} 
			else if( lightPath__.hasFn(MFn::kPointLight) ) 
			{
				tLightMgr::buildShadowJob_PointLight(
					thisJob___, shadowCamPath, fnLightNode, lightPath__,
					m_lazyCompute__
					);
			}//else if( lightPath__.hasFn(MFn::kPointLight) )  

			//================= jobs for shadow cameras ==================
			// if the job has shadow cameras, we will store them here
			//
			int isAggregate = thisJob___.shadowAggregation;
			for( unsigned i( 0 ); i < shadowCamPath.length(); i++ )
			{
				if( !i && isAggregate )
					thisJob___.shadowAggregation = 0;
				else if ( isAggregate )
					thisJob___.shadowAggregation = 1;
				else
					thisJob___.shadowAggregation = 0;
				thisJob___.shadowCamPath = shadowCamPath[ i ];
				thisJob___.hasShadowCam = true;

				MFnDependencyNode shadowCamDepNode( shadowCamPath[ i ].node() );
				thisJob___.name = shadowCamDepNode.name();
				if( isAggregate )
					thisJob___.texName = fnLightNode.name(); //MFnDependencyNode( shadowCamPath[ i ].node() ).name();
				//					else
				//						thisJob.texName = "";
				//						thisJob.name = shadowCamDepNode.name();
				if( liquidGetPlugValue( shadowCamDepNode, "liqShadowResolution", thisJob___.width, status__ ) == MS::kSuccess )
					thisJob___.height = thisJob___.width;
				liquidGetPlugValue( shadowCamDepNode, "liqMidPointShadow", thisJob___.isMidPointShadow, status__ );
				thisJob___.midPointRatio = 0;
				liquidGetPlugValue( shadowCamDepNode, "liqMidPointRatio", thisJob___.midPointRatio, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqDeepShadows", thisJob___.deepShadows, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqPixelSamples", thisJob___.shadowPixelSamples, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqVolumeInterpretation", thisJob___.shadowVolumeInterpretation, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqEveryFrame", thisJob___.everyFrame, status__ );
				// as previously : this is important as thisJob.renderFrame corresponds to the
				// scene scanning time.
				if( thisJob___.everyFrame )
					thisJob___.renderFrame = liqglo.liqglo_lframe;
				else
					liquidGetPlugValue( shadowCamDepNode, "liqRenderAtFrame", thisJob___.renderFrame, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqGeometrySet", thisJob___.shadowObjectSet, status__ );
				liquidGetPlugValue( shadowCamDepNode, "liqShadingRateFactor", thisJob___.shadingRateFactor, status__ );
				// test if the file is already on disk...
				if( m_lazyCompute__ )
				{
					MString fileName( liqRibTranslator::getInstancePtr()->generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob___ ) );
					if( fileExists( fileName ) )
						continue;
				}
				liqRibTranslator::getInstancePtr()->jobList.push_back( thisJob___ );
			}//for( unsigned i( 0 ); i < shadowCamPath.length(); i++ )

		} // if( usesDepthMap && areObjectAndParentsVisible( lightPath__ ) ) 
		//cout <<thisJob.name.asChar()<<" -> shd:"<<thisJob.isShadow<<" ef:"<<thisJob.everyFrame<<" raf:"<<thisJob.renderFrame<<" set:"<<thisJob.shadowObjectSet.asChar()<<endl;
	} // light dagIterator
	return returnStatus__;
}
//
//
MStatus tLightMgr::buildShadowCameraJob( 
	structJob &thisJob___, bool m_lazyCompute__
	)
{
	MStatus returnStatus__ = MS::kSuccess;
	MStatus status__;

	MDagPath cameraPath;
	MItDag dagCameraIterator( MItDag::kDepthFirst, MFn::kCamera, &returnStatus__ );
	for ( ; !dagCameraIterator.isDone(); dagCameraIterator.next() ) 
	{
		if( !dagCameraIterator.getPath(cameraPath) ) 
			continue;
		bool usesDepthMap( false );
		MFnCamera fnCameraNode( cameraPath );
		liquidGetPlugValue( fnCameraNode, "useDepthMapShadows", usesDepthMap, status__ );
		if( usesDepthMap && areObjectAndParentsVisible( cameraPath ) ) 
		{
			//
			// We have a shadow job, so find out if we need to use deep shadows,
			// and the pixel sample count
			//
			thisJob___.deepShadows = false;
			thisJob___.shadowPixelSamples = 1;
			thisJob___.shadowVolumeInterpretation = 1;
			fnCameraNode.findPlug( "deepShadows" ).getValue( thisJob___.deepShadows );
			// Only use the pixel samples and volume interpretation with deep shadows.
			//
			if( thisJob___.deepShadows )
			{
				fnCameraNode.findPlug( "pixelSamples" ).getValue( thisJob___.shadowPixelSamples );
				fnCameraNode.findPlug( "volumeInterpretation" ).getValue( thisJob___.shadowVolumeInterpretation );
			}

			thisJob___.hasShadowCam = true;
			thisJob___.shadowCamPath = cameraPath;
			thisJob___.path = cameraPath;
			thisJob___.name = fnCameraNode.name();
			thisJob___.isShadow = true;
			thisJob___.isPoint = false;
			thisJob___.isShadowPass = false;

			// check to see if the minmax shadow option is used
			thisJob___.isMinMaxShadow = false;
			status__.clear();
			MPlug liquidMinMaxShadow = fnCameraNode.findPlug( "liquidMinMaxShadow", &status__ );
			if( status__ == MS::kSuccess ) 
				liquidMinMaxShadow.getValue( thisJob___.isMinMaxShadow );

			// check to see if the midpoint shadow option is used
			thisJob___.isMidPointShadow = false;
			status__.clear();
			MPlug liquidMidPointShadow = fnCameraNode.findPlug( "useMidDistDmap", &status__ );
			if( status__ == MS::kSuccess ) 
				liquidMidPointShadow.getValue( thisJob___.isMidPointShadow );

			bool computeShadow( true );
			if( m_lazyCompute__ ) 
			{
				MString fileName( liqRibTranslator::getInstancePtr()->generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob___ ) );
				if( fileExists( fileName ) ) continue;
			}

			if( computeShadow ) 
				liqRibTranslator::getInstancePtr()->jobList.push_back( thisJob___ );
		}
	} // camera dagIterator

	return returnStatus__;
}
//
void tLightMgr::buildShadowJob_SpotAndDirectionLight(
	structJob &thisJob___, MDagPathArray &shadowCamPath, 
	const MFnLight &fnLightNode, const MDagPath &lightPath__,
	const bool m_lazyCompute__
	)
{
	MStatus status__;

	bool computeShadow = true;
	thisJob___.hasShadowCam = false;
	MPlug liquidLightShaderNodeConnection;
	MStatus liquidLightShaderStatus;
	liquidLightShaderNodeConnection = fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus );

	if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() ) 
	{
		// a shader is connected to the light !
		MPlugArray liquidLightShaderNodePlugArray;
		liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
		MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

		// has the main shadow been disabled ?
		liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status__ ); 

		// look for shadow cameras...
		MStatus stat;
		MPlug shadowCamPlug = fnLightShaderNode.findPlug( "shadowCameras", &stat );
		// find the multi message attribute...
		if( stat == MS::kSuccess ) 
		{
			int numShadowCams = shadowCamPlug.numElements();
			//cout <<">> got "<<numShadowCams<<" shadow cameras"<<endl;
			// iterate through existing array elements
			for ( unsigned int i=0; i<numShadowCams; i++ ) 
			{
				stat.clear();
				MPlug camPlug = shadowCamPlug.elementByPhysicalIndex( i, &stat );
				if( stat != MS::kSuccess ) 
					continue;
				MPlugArray shadowCamPlugArray;

				// if the element is connected, keep going...
				if( camPlug.connectedTo( shadowCamPlugArray, true, false ) ) 
				{
					MFnDependencyNode shadowCamDepNode = shadowCamPlugArray[0].node();
					//cout <<"shadow camera plug "<<i<<" is connected to "<<shadowCamDepNode.name()<<endl;

					MDagPath cameraPath;
					cameraPath.getAPathTo( shadowCamPlugArray[0].node(), cameraPath);
					//cout <<"cameraPath : "<<cameraPath.fullPathName()<<endl;
					shadowCamPath.append( cameraPath );
					//lightHasShadowCam = true;
				}
			}
		}
	}
	thisJob___.path = lightPath__;
	thisJob___.name = fnLightNode.name();
	thisJob___.texName = "";
	thisJob___.isShadow = true;
	thisJob___.isPoint = false;
	thisJob___.isShadowPass = false;

	// check to see if the minmax shadow option is used
	thisJob___.isMinMaxShadow = false;
	liquidGetPlugValue( fnLightNode, "liquidMinMaxShadow", thisJob___.isMinMaxShadow, status__ ); 
	// check to see if the midpoint shadow option is used
	thisJob___.isMidPointShadow = false;
	liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob___.isMidPointShadow, status__ ); 
	// in lazy compute mode, we check if the map is already on disk first.
	if( m_lazyCompute__ && computeShadow ) 
	{
		MString fileName( liqRibTranslator::getInstancePtr()->generateFileName( (fileGenMode) fgm_shadow_tex, thisJob___ ) );
		if( fileExists( fileName ) ) 
			computeShadow = false;
	}
	//
	// store the main shadow map    *****************************
	//
	if( computeShadow )
		liqRibTranslator::getInstancePtr()->jobList.push_back( thisJob___ );
	// We have to handle point lights differently as they need 6 shadow maps!
}
//
void tLightMgr::buildShadowJob_PointLight(
	structJob &thisJob___, MDagPathArray &shadowCamPath, 
	const MFnLight &fnLightNode, 
	const MDagPath &lightPath__,
	const bool m_lazyCompute__
	)
{
	MStatus status__;

	for ( unsigned dirOn( 0 ); dirOn < 6; dirOn++ ) 
	{
		thisJob___.hasShadowCam = false;
		thisJob___.path = lightPath__;
		thisJob___.name = fnLightNode.name();
		thisJob___.isShadow = true;
		thisJob___.isShadowPass = false;
		thisJob___.isPoint = true;
		thisJob___.pointDir = ( PointLightDirection )dirOn;

		// check to see if the midpoint shadow option is used
		thisJob___.isMidPointShadow = false;
		liquidGetPlugValue( fnLightNode, "useMidDistDmap", thisJob___.isMidPointShadow, status__ );

		bool computeShadow = true;
		MStatus liquidLightShaderStatus;
		MPlug liquidLightShaderNodeConnection( fnLightNode.findPlug( "liquidLightShaderNode", &liquidLightShaderStatus ) );

		if( liquidLightShaderStatus == MS::kSuccess && liquidLightShaderNodeConnection.isConnected() ) 
		{
			// a shader is connected to the light !
			MPlugArray liquidLightShaderNodePlugArray;
			liquidLightShaderNodeConnection.connectedTo( liquidLightShaderNodePlugArray, true, true );
			MFnDependencyNode fnLightShaderNode( liquidLightShaderNodePlugArray[0].node() );

			// has the main shadow been disabled ?
			liquidGetPlugValue( fnLightShaderNode, "generateMainShadow", computeShadow, status__ );

			// look for shadow cameras...
			MStatus stat;
			MPlug shadowCamPlug( fnLightShaderNode.findPlug( "shadowCameras", &stat ) );

			// find the multi message attribute...
			if( stat == MS::kSuccess ) 
			{
				int numShadowCams = shadowCamPlug.numElements();
				//cout <<">> got "<<numShadowCams<<" shadow cameras"<<endl;
				// iterate through existing array elements
				for ( unsigned i( 0 ); i < numShadowCams; i++ ) 
				{
					stat.clear();
					MPlug camPlug = shadowCamPlug.elementByPhysicalIndex( i, &stat );
					if( stat != MS::kSuccess ) 
						continue;
					MPlugArray shadowCamPlugArray;

					// if the element is connected, keep going...
					if( camPlug.connectedTo( shadowCamPlugArray, true, false ) ) 
					{
						MFnDependencyNode shadowCamDepNode = shadowCamPlugArray[0].node();
						//cout <<"shadow camera plug "<<i<<" is connected to "<<shadowCamDepNode.name()<<endl;

						MDagPath cameraPath;
						cameraPath.getAPathTo( shadowCamPlugArray[0].node(), cameraPath);
						//cout <<"cameraPath : "<<cameraPath.fullPathName()<<endl;
						shadowCamPath.append( cameraPath );
						//lightHasShadowCam = true;
					}
				}
			}
		}
		MString fileName( liqRibTranslator::getInstancePtr()->generateFileName( ( fileGenMode )fgm_shadow_tex, thisJob___ ) );
		if( m_lazyCompute__ ) 
			if( fileExists( fileName ) ) 
				computeShadow = false;
		if( computeShadow ) 
			liqRibTranslator::getInstancePtr()->jobList.push_back( thisJob___ );
	}//for ( unsigned dirOn( 0 ); dirOn < 6; dirOn++ )  
}