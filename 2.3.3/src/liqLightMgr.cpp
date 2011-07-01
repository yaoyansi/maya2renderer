#include <liqLightMgr.h>

#include <maya/MItDag.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagModifier.h>

#include <liqRibHT.h>


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