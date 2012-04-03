#include "rm_renderer.h"

#include "../common/prerequest_std.h"

// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}

// Maya headers
#include "../common/prerequest_maya.h"
#include "../common/mayacheck.h"
// Liquid headers
#include <liquid.h>
#include <liqRibHT.h>
#include <liqRenderer.h>
#include <liqRibLightData.h>
#include <liqGlobalHelpers.h>
#include <liqProcessLauncher.h>
#include <liqCustomNode.h>
#include <liqShaderFactory.h>
#include <liqExpression.h>
#include <liqRenderScript.h>
#include <liqGlobalVariable.h>
#include <liqJobScriptMgr.h>
#include <liqFrameScriptMgr.h>
#include <liqLightMgr.h>
#include <liqLocatorMgr.h>
#include <liqShadowRibWriterMgr.h>
#include <liqHeroRibWriterMgr.h>
#include <liqRibCamera.h>
#include <liqRibTranslator.h>

#include "../renderermgr.h"
#include "rm_helper.h"

#if defined(_WIN32)/* && !defined(DEFINED_LIQUIDVERSION)*/
// unix build gets this from the Makefile
extern const char *LIQUIDVERSION;
#endif

namespace renderman
{
	Renderer::Renderer()
	{
// 		liquid::RendererMgr::getInstancePtr()->registerRenderer(
// 			"renderman", this
// 		);
	}
	//
	Renderer::~Renderer()
	{

	}
	//
	void Renderer::test()
	{
		liquidMessage2(messageInfo, "this is %s.", "renderman" );
	}
	//
	void Renderer::setRenderScriptFormatAndCompress(const bool bbinary, const bool bcompress)
	{
		CM_TRACE_FUNC("Renderer::setRenderScriptFormatAndCompress("<<bbinary<<","<<bcompress<<")");

		// Rib client file creation options MUST be set before RiBegin
#if defined(PRMAN) || defined(DELIGHT)
		/* THERE IS A RIBLIB BUG WHICH PREVENTS THIS WORKING */
		_RiOption_format_compress(liqglo.liqglo_doBinary, liqglo.liqglo_doCompression);
#endif // PRMAN || DELIGHT
	}
	//
	RtToken g_typeAscii       = tokenCast("Ascii");
	RtToken g_typeBinary      = tokenCast("Binary");
	RtToken g_compressionNone = tokenCast("None");
	RtToken g_compressionGzip = tokenCast("Gzip");
	RtToken g_indentSpace = tokenCast("Space");
	RtToken g_indentTab   = tokenCast("Tab");
	void Renderer::_RiOption_format_compress(bool bBinary, bool bCompress)
	{
		CM_TRACE_FUNC("Renderer::_RiOption_format_compress("<<bBinary<<","<<bCompress<<")");

	 #ifdef RIBLIB_AQSIS
  		LIQDEBUGPRINTF( "-> setting binary option\n" );
  		RtToken binary[1]; binary[0] = g_typeBinary;
  		RtToken ascii[1] ; ascii[0]  = g_typeAscii;
  		RiOption( tokenCast("RI2RIB_Output"), "Type", ( RtPointer )(bBinary?&binary:&ascii),        RI_NULL );
	  
  		LIQDEBUGPRINTF( "-> setting compression option\n" );
  		RtToken gzip[1]; gzip[0] = g_compressionGzip;
  		RtToken none[1]; none[0] = g_compressionNone;
  		RiOption( tokenCast("RI2RIB_Output"), "Compression", ( RtPointer )(bCompress?&gzip:&none), RI_NULL );

  		LIQDEBUGPRINTF( "-> setting indent option\n" );
		RtToken itype[1];			RtInt isize[1];
		//itype[0] = g_indentTab;		isize[0] = 1;
		itype[0] = g_indentSpace;	isize[0] = 4;
		RiOption( tokenCast("RI2RIB_Indentation"), "Type", &itype, RI_NULL );
		RiOption( tokenCast("RI2RIB_Indentation"), "Size", &isize, RI_NULL );

	 #else
		LIQDEBUGPRINTF( "-> setting binary option\n" );
		if( liqglo_doBinary ) 
		{
			RtString format[ 1 ] = { "binary" };
			RiOption( "rib", "format", ( RtPointer )format, RI_NULL );
		}else{
			RtString format[ 1 ] = { "ascii" };
			RiOption( "rib", "format", ( RtPointer )format, RI_NULL );

	#ifdef PRMAN
			RtString style = "indented";
			RiOption( "rib", "string asciistyle", &style, RI_NULL );
			//std::cout <<"[liquid DEBUG] RiOption( rib, string asciistyle, &style, RI_NULL );"<<std::endl;
	#endif
		}

		LIQDEBUGPRINTF( "-> setting compression option\n" );
		if( liqglo_doCompression ) 
		{
			RtString comp[ 1 ] = { "gzip" };
			RiOption( "rib", "compression", ( RtPointer )comp, RI_NULL );
		}else{
			RtString comp[ 1 ] = { "none" };
			RiOption( "rib", "compression", ( RtPointer )comp, RI_NULL );
		}
	#endif
	}
	//
	MStatus Renderer::worldPrologue(const structJob& currentJob)
	{
		CM_TRACE_FUNC("Renderer::worldPrologue("<<currentJob.name<<")");

		MStatus returnStatus = MS::kSuccess;
		LIQDEBUGPRINTF( "-> Writing world prologue.\n" );
		// if this is a readArchive that we are exporting then ingore this header information
		if( !liqglo.m_exportReadArchive )
		{
			MFnDependencyNode globalsNode( liqglo.rGlobalObj );
			MPlug prePostplug( globalsNode.findPlug( "preWorldMel" ) );
			MString melcommand( prePostplug.asString() );
			// put in pre-worldbegin statements
			if(liqglo.m_preWorldRIB != "" || melcommand.length() )
			{
				RiArchiveRecord(RI_COMMENT,  " Pre-WorldBegin RIB from liquid globals");
				MGlobal::executeCommand( melcommand );
				RiArchiveRecord(RI_VERBATIM, ( char* )liqglo.m_preWorldRIB.asChar());
				RiArchiveRecord(RI_VERBATIM, "\n");
			}
			// output the arbitrary clipping planes here /////////////
			//
			boost::shared_ptr< liqRibHT > &htable = liqRibTranslator::getInstancePtr()->htable;
			{
				for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
				{
					LIQ_CHECK_CANCEL_REQUEST;
					liqRibNodePtr   ribNode = (*rniter).second;
					if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_ClipPlane ) 
						continue;
					RiTransformBegin();
					if( liqglo.m_outputComments )
						RiArchiveRecord( RI_COMMENT, "Clipping Plane: %s", ribNode->name.asChar(), RI_NULL );
					RtMatrix ribMatrix;
					MMatrix matrix;
					MDagPath path;

					matrix = ribNode->object(0)->matrix( path.instanceNumber() );
					matrix.get( ribMatrix );
					RiConcatTransform( ribMatrix );

					ribNode->object(0)->writeObject("", currentJob, false);
					ribNode->object(0)->written = 1;

					RiTransformEnd();
				}
			}
			RiWorldBegin();
			// set attributes from the globals
			if( liqglo.rt_useRayTracing )
			{
				RiArchiveRecord(RI_COMMENT,  " Ray-Tracing Attributes from liquid globals");
				RtInt on( 1 );
				RiAttribute("visibility", "int trace", &on, RI_NULL );
				if( liqglo.rt_traceDisplacements )
					RiAttribute("trace", "int displacements", &on, RI_NULL );
				if( liqglo.rt_traceSampleMotion )
					RiAttribute("trace", "int samplemotion", &on, RI_NULL );
				if( liqglo.rt_traceBias != 0 )
					RiAttribute("trace", "float bias", &liqglo.rt_traceBias, RI_NULL );
				RiAttribute("trace", "int maxdiffusedepth", &liqglo.rt_traceMaxDiffuseDepth, RI_NULL);
				RiAttribute("trace", "int maxspeculardepth", &liqglo.rt_traceMaxSpecularDepth, RI_NULL);
				if( liqglo.rt_irradianceMaxError != -1.0 )
					RiAttribute( "irradiance", (RtToken) "float maxerror", &liqglo.rt_irradianceMaxError, RI_NULL );
				if( liqglo.rt_irradianceMaxPixelDist != -1.0 )
					RiAttribute( "irradiance", (RtToken) "float maxpixeldist", &liqglo.rt_irradianceMaxPixelDist, RI_NULL );
			}
			// put in post-worldbegin statements
			prePostplug = globalsNode.findPlug( "postWorldMel" );
			melcommand = prePostplug.asString();
			if(liqglo.m_postWorldRIB != "" || melcommand.length() )
			{
				RiArchiveRecord( RI_COMMENT,  " Post-WorldBegin RIB from liquid globals" );
				MGlobal::executeCommand( melcommand );
				RiArchiveRecord( RI_VERBATIM, ( char* )liqglo.m_postWorldRIB.asChar() );
				RiArchiveRecord( RI_VERBATIM, "\n");
			}
			RiTransformBegin();
			RiCoordinateSystem( "worldspace" );
			RiTransformEnd();

			RiTransformBegin();
			RiRotate( -90., 1., 0., 0. );
			RiCoordinateSystem( "_environment" );
			RiTransformEnd();
		}//if( !m_exportReadArchive )
		RiReverseOrientation();
		return returnStatus;
	}
	//
	MStatus Renderer::worldEpilogue()
	{
		CM_TRACE_FUNC("Renderer::worldEpilogue()");

		MStatus returnStatus = MS::kSuccess;
		LIQDEBUGPRINTF( "-> Writing world epilogue.\n" );
		// If this is a readArchive that we are exporting there's no world block
		if( !liqglo.m_exportReadArchive ) 
			RiWorldEnd();
		return returnStatus;
	}
	//
//	MStatus Renderer::exportLight(const liqRibNodePtr& ribNode, const structJob &currentJob)
//	{
////moved to Renderer::writeLight_pre()
//// 		RtInt on( 1 );
//// 			// We need to enclose lights in attribute blocks because of the
//// 			// new added attribute support
//// 			RiAttributeBegin();
//// 
//// 			// All this stuff below should be handled by a new attribute class
//// 			LIQDEBUGPRINTF( "-> RibNodeName " );
//// 			RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
//// 			LIQDEBUGPRINTF( "= %s.\n", (char *)RibNodeName  );
//// 			RiAttribute( "identifier", "name", &RibNodeName, RI_NULL );
//// 			if( ribNode->trace.sampleMotion )
//// 				RiAttribute( "trace", (RtToken) "samplemotion", &on, RI_NULL );
//// 			if( ribNode->trace.displacements )
//// 				RiAttribute( "trace", (RtToken) "displacements", &on, RI_NULL );
//// 			if( ribNode->trace.bias != 0.01f )
//// 			{
//// 				RtFloat bias = ribNode->trace.bias;
//// 				RiAttribute( "trace", (RtToken) "bias", &bias, RI_NULL );
//// 			}
//// 			if( ribNode->trace.maxDiffuseDepth != 1 )
//// 			{
//// 				RtInt mddepth = ribNode->trace.maxDiffuseDepth;
//// 				RiAttribute( "trace", (RtToken) "maxdiffusedepth", &mddepth, RI_NULL );
//// 			}
//// 			if( ribNode->trace.maxSpecularDepth != 2 )
//// 			{
//// 				RtInt msdepth = ribNode->trace.maxSpecularDepth;
//// 				RiAttribute( "trace", (RtToken) "maxspeculardepth", &msdepth, RI_NULL );
//// 			}
//			ribNode->object(0)->writeObject("", currentJob, false);//call liqRibLightData::_write(...)
//			ribNode->object(0)->written = 1;
////moved to Renderer::writeLight_post()
//// 			// The next line pops the light...
//// 			RiAttributeEnd();
//// 			// close light by default // [1/30/2012 yaoyansi]
//// 			RiIlluminate( ribNode->object(0)->lightHandle(), 0 );//
//			return MStatus::kSuccess;
//	}
	void Renderer::openLog()
	{
		CM_TRACE_FUNC("Renderer::openLog()(but do nothing now)");
	}
	void Renderer::closeLog()
	{
		CM_TRACE_FUNC("Renderer::closeLog()(but do nothing now)");
	}
	liqLightHandle Renderer::exportShadowPassLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqString & shadowName,
		const liqMatrix &transform)
	{
		CM_TRACE_FUNC("Renderer::exportShadowPassLight("<<shadertype<<","<<shaderinstance<<","<<shadowName<<",liqMatrix t)");

		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "liquidshadowpasslight", "string shadowname", &shadowName, RI_NULL );
	}

	void Renderer::transform_(const liqMatrix& transform)
	{
		CM_TRACE_FUNC("Renderer::transform_(liqMatrix transform)");
	}
	MStatus Renderer::liqRibLightData_write(
		const liqRibLightData *lightdata, const structJob &currentJob)
	{
		CM_TRACE_FUNC("Renderer::liqRibLightData_write("<<lightdata->getName()<<","<<currentJob.name<<")");
		return MS::kSuccess;
	}

	//
	void Renderer::exportOneObject_data(
		const liqRibNodePtr &ribNode__, 
		const structJob &currentJob__
		)
	{
		CM_TRACE_FUNC("Renderer::exportOneObject_data("<<ribNode__->name<<","<<currentJob__.name<<")");

		// transform ////////////////////////////////////////////////////////////////////////
		//{// transform motion blur
		MDagPath path = ribNode__->path();
		MObject transform = path.transform();
		// Alf: preTransformMel
//		liqRibTranslator::getInstancePtr()->preTransformMel(transform);

		const bool bMotionBlur =
			ribNode__->motion.transformationBlur &&
			( ribNode__->object( 1 ) ) &&
			//( ribNode__->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !currentJob__.isShadow || currentJob__.deepShadows );

// 		const bool bMatrixMotionBlur = 
// 			liqglo.liqglo_doMotion 
// 			&& bMotionBlur;

//		liqRibTranslator::getInstancePtr()->MaxtrixMotionBlur(ribNode__, path, bMatrixMotionBlur);

		// Alf: postTransformMel
//		liqRibTranslator::getInstancePtr()->postTransformMel(transform);
		//}

		//////////////////////////////////////////////////////////////////////////
// 		if( ribNode__->rib.hasBox() ) 
// 			RiArchiveRecord( RI_COMMENT, " RIB Box:\n%s", ribNode__->rib.box.asChar() );
// 		if( ribNode__->rib.hasGenerator() ){
// 			MGlobal::executeCommand( ribNode__->rib.generator, false, false );
// 		}
// 		if( ribNode__->rib.hasReadArchive() ) 
// 			RiArchiveRecord( RI_VERBATIM, " ReadArchive \"%s\" \n", ribNode__->rib.readArchive.asChar() );
// 		if( ribNode__->rib.hasDelayedReadArchive() ) 
// 		{
// 			RiArchiveRecord( RI_VERBATIM, " Procedural \"DelayedReadArchive\" [ \"%s\" ] [ %f %f %f %f %f %f ] \n", ribNode__->rib.delayedReadArchive.asChar(), ribNode__->bound[0],ribNode__->bound[3],ribNode__->bound[1],ribNode__->bound[4],ribNode__->bound[2],ribNode__->bound[5] );
// 			// should be using the bounding box node - Alf
// 		}

		// Geometry ////////////////////////////////////////////////////////////////////////
		// Alf: preShapeMel
//		liqRibTranslator::getInstancePtr()->preShapeMel(transform);

		if( !ribNode__->ignoreShapes ) 
		{
			liqRIBMsg("ribNode__->object(0)->type= %d, path=%s",ribNode__->object(0)->type, ribNode__->path().fullPathName().asChar() );
			// check to see if we are writing a curve to set the proper basis
			if( ribNode__->object(0)->type == MRT_NuCurve
				|| ribNode__->object(0)->type == MRT_PfxHair
				|| ribNode__->object(0)->type == MRT_PfxTube
				|| ribNode__->object(0)->type == MRT_PfxLeaf
				|| ribNode__->object(0)->type == MRT_PfxPetal 
				|| ribNode__->object(0)->type == MRT_Curves )
			{
//				RiBasis( RiBSplineBasis, 1, RiBSplineBasis, 1 );
			} 
			bool hasRibBoxData=ribNode__->rib.hasGenerator()
				|| ribNode__->rib.hasReadArchive()  
				|| ribNode__->rib.hasDelayedReadArchive();
			if(hasRibBoxData)
			{
				//if ribNode is tagged as readArchive or delayedReadArchive, 
				//we do not output its geometry data.
				liqRIBMsg("%s has ribbox data,so we do not output the deometry.", ribNode__->name.asChar());
			}else{
				bool bGeometryMotion = 
					liqglo.liqglo_doDef 
					&& bMotionBlur
					&& ( ribNode__->object(0)->type != MRT_RibGen );

				if( bGeometryMotion )
				{
//					if(liqglo.liqglo_relativeMotion)
//						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
//					else
//						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

					for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ )
					{ 
						this->_writeObject(ribNode__, currentJob__, bGeometryMotion, msampleOn, false);
						//_writeObject() will call Renderer::exportOneGeometry_Mesh()
					}
//					RiMotionEnd();
				}else{
					this->_writeObject(ribNode__, currentJob__, bGeometryMotion, 0, false);
					//_writeObject() will call Renderer::exportOneGeometry_Mesh()
				}// if(bGeometryMotion)
			}//if(hasRibBoxData)


			// Alf: postShapeMel
//			liqRibTranslator::getInstancePtr()->postShapeMel(transform);
		} // else RiArchiveRecord( RI_COMMENT, " Shapes Ignored !!" );

	}
	void Renderer::exportOneObject_reference(
		const liqRibNodePtr &ribNode__, 
		const structJob &currentJob__
		)
	{
		CM_TRACE_FUNC("Renderer::exportOneObject_reference("<<ribNode__->name<<","<<currentJob__.name<<")");

		// transform ////////////////////////////////////////////////////////////////////////
		//{// transform motion blur
		MDagPath path = ribNode__->path();
		MObject transform = path.transform();
		// Alf: preTransformMel
		liqRibTranslator::getInstancePtr()->preTransformMel(transform);

		const bool bMotionBlur =
			ribNode__->motion.transformationBlur &&
			( ribNode__->object( 1 ) ) &&
			//( ribNode__->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !currentJob__.isShadow || currentJob__.deepShadows );

		const bool bMatrixMotionBlur = 
			liqglo.liqglo_doMotion 
			&& bMotionBlur;

		liqRibTranslator::getInstancePtr()->MaxtrixMotionBlur(ribNode__, path, bMatrixMotionBlur);

		// Alf: postTransformMel
		liqRibTranslator::getInstancePtr()->postTransformMel(transform);
		//}

		//////////////////////////////////////////////////////////////////////////
		if( ribNode__->rib.hasBox() ) 
			RiArchiveRecord( RI_COMMENT, " RIB Box:\n%s", ribNode__->rib.box.asChar() );
		if( ribNode__->rib.hasGenerator() ){
			MGlobal::executeCommand( ribNode__->rib.generator, false, false );
		}
		if( ribNode__->rib.hasReadArchive() ) 
			RiArchiveRecord( RI_VERBATIM, " ReadArchive \"%s\" \n", ribNode__->rib.readArchive.asChar() );
		if( ribNode__->rib.hasDelayedReadArchive() ) 
		{
			RiArchiveRecord( RI_VERBATIM, " Procedural \"DelayedReadArchive\" [ \"%s\" ] [ %f %f %f %f %f %f ] \n", ribNode__->rib.delayedReadArchive.asChar(), ribNode__->bound[0],ribNode__->bound[3],ribNode__->bound[1],ribNode__->bound[4],ribNode__->bound[2],ribNode__->bound[5] );
			// should be using the bounding box node - Alf
			/* {
			// this is a visual display of the archive's bounding box
			RiAttributeBegin();
			RtColor debug;
			debug[0] = debug[1] = 1;
			debug[2] = 0;
			RiColor( debug );
			debug[0] = debug[1] = debug[2] = 0.250;
			RiOpacity( debug );
			RiSurface( "defaultsurface", RI_NULL );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int diffuse\" [0]\n" );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int specular\" [0]\n" );
			RiArchiveRecord( RI_VERBATIM, "Attribute \"visibility\" \"int transmission\" [0]\n" );
			float xmin = ribNode->bound[0];
			float ymin = ribNode->bound[1];
			float zmin = ribNode->bound[2];
			float xmax = ribNode->bound[3];
			float ymax = ribNode->bound[4];
			float zmax = ribNode->bound[5];
			RiSides( 2 );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmin, xmax,ymax,zmin, xmax,ymax,zmax, xmin,ymax,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymin,zmin, xmax,ymin,zmin, xmax,ymin,zmax, xmin,ymin,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmax, xmax,ymax,zmax, xmax,ymin,zmax, xmin,ymin,zmax );
			RiArchiveRecord( RI_VERBATIM, "Polygon \"P\" [ %f %f %f  %f %f %f  %f %f %f  %f %f %f ]\n", xmin,ymax,zmin, xmax,ymax,zmin, xmax,ymin,zmin, xmin,ymin,zmin );
			RiAttributeEnd();
			} */
		}

		// Geometry ////////////////////////////////////////////////////////////////////////
		// Alf: preShapeMel
		liqRibTranslator::getInstancePtr()->preShapeMel(transform);

		if( !ribNode__->ignoreShapes ) 
		{
			liqRIBMsg("ribNode__->object(0)->type= %d, path=%s",ribNode__->object(0)->type, ribNode__->path().fullPathName().asChar() );
			// check to see if we are writing a curve to set the proper basis
			if( ribNode__->object(0)->type == MRT_NuCurve
				|| ribNode__->object(0)->type == MRT_PfxHair
				|| ribNode__->object(0)->type == MRT_PfxTube
				|| ribNode__->object(0)->type == MRT_PfxLeaf
				|| ribNode__->object(0)->type == MRT_PfxPetal 
				|| ribNode__->object(0)->type == MRT_Curves )
			{
				RiBasis( RiBSplineBasis, 1, RiBSplineBasis, 1 );
			} 
			bool hasRibBoxData=ribNode__->rib.hasGenerator()
							|| ribNode__->rib.hasReadArchive()  
							|| ribNode__->rib.hasDelayedReadArchive();
			if(hasRibBoxData)
			{
				//if ribNode is tagged as readArchive or delayedReadArchive, 
				//we do not output its geometry data.
				liqRIBMsg("%s has ribbox data,so we do not output the deometry.", ribNode__->name.asChar());
			}else{
				bool bGeometryMotion = 
					liqglo.liqglo_doDef 
					&& bMotionBlur
					&& ( ribNode__->object(0)->type != MRT_RibGen );

				if( bGeometryMotion )
				{
#define GeometryMotionBlur_SimpleEdition
#ifndef GeometryMotionBlur_SimpleEdition
					// For each grain, open a new motion block...
					for( unsigned i( 0 ); i < ribNode__->object( 0 )->granularity(); i++ ) //granularity() is always 1.
					{
						if( ribNode__->object( 0 )->isNextObjectGrainAnimated() ) //isNextObjectGrainAnimated() is always true.
						{
							if(liqglo.liqglo_relativeMotion)
								RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
							else
								RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

							for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ )
							{ 
								liqRibTranslator::getInstancePtr()->_writeObject(ribNode__, currentJob__, true, msampleOn);
							}
							RiMotionEnd();
						}else {
							RiArchiveRecord( RI_COMMENT, "the the next object grain is not animated" );

							liqRibTranslator::getInstancePtr()->_writeObject(ribNode__, currentJob__, false, 0);
						}
					}
#else
					if(liqglo.liqglo_relativeMotion)
						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimesOffsets );
					else
						RiMotionBeginV( liqglo.liqglo_motionSamples, liqglo.liqglo_sampleTimes );

					for ( unsigned msampleOn( 0 ); msampleOn < liqglo.liqglo_motionSamples; msampleOn++ )
					{ 
						this->_writeObject(ribNode__, currentJob__, true, msampleOn, true);
						//_writeObject() will call Renderer::exportOneGeometry_Mesh()
					}
					RiMotionEnd();
#endif
				}else{
					this->_writeObject(ribNode__, currentJob__, false, 0, true);
					//_writeObject() will call Renderer::exportOneGeometry_Mesh()
				}// if(bGeometryMotion)
			}//if(hasRibBoxData)


			// Alf: postShapeMel
			liqRibTranslator::getInstancePtr()->postShapeMel(transform);
		} // else RiArchiveRecord( RI_COMMENT, " Shapes Ignored !!" );

	}
	//void Renderer::exportOneGeometry_Mesh(
	//	const liqRibMeshData *meshdata,  
	//	const structJob &currentJob
	//	)
	//{
	//	//
	//	//mesh data begin
	//	//
	//	// Each loop has one polygon, so we just want an array of 1's of
	//	// the correct size. Stack version.
	//	//vector< RtInt > nloops( numFaces, 1 );
	//	// Alternatively (heap version):
	//	boost::scoped_array< RtInt > nloops( new RtInt[ meshdata->getNumFaces() ] );
	//	std::fill( nloops.get(), nloops.get() + meshdata->getNumFaces(), ( RtInt )1 );

	//	unsigned numTokens( meshdata->tokenPointerArray.size() );
	//	boost::scoped_array< RtToken > tokenArray( new RtToken[ numTokens ] );
	//	boost::scoped_array< RtPointer > pointerArray( new RtPointer[ numTokens ] );
	//	assignTokenArraysV( meshdata->tokenPointerArray, tokenArray.get(), pointerArray.get() );

	//	RiPointsGeneralPolygonsV( meshdata->getNumFaces(),
	//		&nloops[ 0 ],
	//		meshdata->getNverts().get(),
	//		meshdata->getVerts().get(),
	//		numTokens,
	//		tokenArray.get(),
	//		pointerArray.get() );
	//	//mesh data end
	//}
	//
	void Renderer::ribPrologue_comment(const char* liqversion, 
		const char* scenename, const char* user, const time_t &now)
	{
		CM_TRACE_FUNC("Renderer::ribPrologue_comment("<<liqversion<<","<<scenename<<","<<user<<",time)");

		// general info for traceability
		//
		RiArchiveRecord( RI_COMMENT, "    Generated by Liquid v%s", liqversion );
		RiArchiveRecord( RI_COMMENT, "    Scene : %s", scenename );

		if( user )
			RiArchiveRecord( RI_COMMENT, "    User  : %s", user );

		RiArchiveRecord( RI_COMMENT, "    Time  : %s", ctime(&now) );

	}
	//
	MStatus Renderer::ribPrologue_begin(const structJob& currentJob___)
	{
		CM_TRACE_FUNC("Renderer::ribPrologue_begin("<<currentJob___.name<<")");

#ifndef RENDER_PIPE
		liquidMessage( "Beginning RIB output to '" + std::string( currentJob___.ribFileName.asChar() ) + "'", messageInfo );
		RiBegin( const_cast< RtToken >( currentJob___.ribFileName.asChar() ) );
		liqglo.m_ribFileOpen = true;
#else//RENDER_PIPE
		liqglo___.liqglo_ribFP = fopen( currentJob___.ribFileName.asChar(), "w" );
		if( liqglo___.liqglo_ribFP ) 
		{
			RtInt ribFD = fileno( liqglo___.liqglo_ribFP );
			RiOption( ( RtToken )"rib", ( RtToken )"pipe", &ribFD, RI_NULL );
		} 
		else
		{
			liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
		}

		liquidMessage( "Beginning RI output directly to renderer", messageInfo );
		RiBegin( RI_NULL );
#endif//RENDER_PIPE
		return MS::kSuccess;
	}
	MStatus Renderer::ribPrologue_end(const structJob& currentJob)
	{
		CM_TRACE_FUNC("Renderer::ribPrologue_end("<<currentJob.name<<")");
		
		RiEnd();
		liqglo.m_ribFileOpen = false;

		return MS::kSuccess;
	}
	//
	MStatus Renderer::ribPrologue_options(const structJob& currentJob)
	{
		CM_TRACE_FUNC("Renderer::ribPrologue_options("<<currentJob.name<<")");

		LIQDEBUGPRINTF( "-> beginning to write prologue\n" );


		// set any rib options
		//
		writeStatisticsOptions();

		//limits options
		writeLimitsOptions();

		// set search paths
		ribPrologue_writeSearthPath();

		//RiOrientation( RI_RH ); // Right-hand coordinates
		if( currentJob.isShadow ) 
		{
			tShadowRibWriterMgr::ribPrologue_samples(currentJob.shadowPixelSamples, currentJob.shadowPixelSamples);
			tShadowRibWriterMgr::ribPrologue_shadingrate(currentJob.shadingRateFactor);
			// Need to use Box filter for deep shadows.			
			tShadowRibWriterMgr::ribPrologue_filter( pfBoxFilter, 1, 1);
			tShadowRibWriterMgr::ribPrologue_pass(currentJob.deepShadows? "deepshadow":"shadow");
		} 
		else 
		{
			tHeroRibWriterMgr::ribPrologue_hider(liqglo.liqglo_hider);
			//samples 
			tHeroRibWriterMgr::ribPrologue_samples( liqglo.pixelSamples, liqglo.pixelSamples );
			tHeroRibWriterMgr::ribPrologue_shadingrate( liqglo.shadingRate );
			//filter options
			if( liqglo.m_rFilterX > 1 || liqglo.m_rFilterY > 1 ) 
			{
				tHeroRibWriterMgr::ribPrologue_filter(liqglo.m_rFilter, liqglo.m_rFilterX, liqglo.m_rFilterY);
			}
			tHeroRibWriterMgr::ribPrologue_pass("beauty");
		}

		// RAYTRACING OPTIONS
		if( liqglo.liquidRenderer.supports_RAYTRACE && liqglo.rt_useRayTracing ) 
		{
			RiArchiveRecord( RI_COMMENT, "Ray Tracing : ON" );
			RiOption( "trace",   "int maxdepth",                ( RtPointer ) &liqglo.rt_traceMaxDepth,            RI_NULL );
#if defined ( DELIGHT ) || defined ( PRMAN ) || defined ( GENERIC_RIBLIB )
			RiOption( "trace",   "float specularthreshold",     ( RtPointer ) &liqglo.rt_traceSpecularThreshold, RI_NULL );
			RiOption( "trace",   "int continuationbydefault",   ( RtPointer ) &liqglo.rt_traceRayContinuation,   RI_NULL );
			RiOption( "limits",  "int geocachememory",          ( RtPointer ) &liqglo.rt_traceCacheMemory,       RI_NULL );
			RiOption( "user",    "float traceBreadthFactor",    ( RtPointer ) &liqglo.rt_traceBreadthFactor,     RI_NULL );
			RiOption( "user",    "float traceDepthFactor",      ( RtPointer ) &liqglo.rt_traceDepthFactor,       RI_NULL );
#endif
		} 
		else 
		{
			if( !liqglo.liquidRenderer.supports_RAYTRACE ) 
				RiArchiveRecord( RI_COMMENT, "Ray Tracing : NOT SUPPORTED" );
			else 
			{
				RiArchiveRecord( RI_COMMENT, "Ray Tracing : OFF" );
				RtInt maxDepth = 0;
				RiOption( "trace",   "int maxdepth",                ( RtPointer ) &maxDepth,                  RI_NULL );
			}
		}

		// CUSTOM OPTIONS
		MFnDependencyNode globalsNode( liqglo.rGlobalObj );
		MPlug prePostplug( globalsNode.findPlug( "preFrameBeginMel" ) );
		MString melcommand( prePostplug.asString() );
		if( liqglo.m_preFrameRIB != "" || melcommand.length() )
		{
			RiArchiveRecord(RI_COMMENT,  " Pre-FrameBegin RIB from liquid globals" );
			MGlobal::executeCommand( melcommand );
			RiArchiveRecord(RI_VERBATIM, ( char* )liqglo.m_preFrameRIB.asChar() );
			RiArchiveRecord(RI_VERBATIM, "\n");
		}
		if( liqglo.m_bakeNonRasterOrient || liqglo.m_bakeNoCullHidden || liqglo.m_bakeNoCullBackface ) 
		{
			RiArchiveRecord( RI_COMMENT, "Bake Attributes" );
			RtInt zero( 0 );
			if( liqglo.m_bakeNonRasterOrient )
				RiAttribute( "dice","int rasterorient", &zero, RI_NULL );
			if( liqglo.m_bakeNoCullBackface )
				RiAttribute( "cull","int backfacing", &zero, RI_NULL );
			if( liqglo.m_bakeNoCullHidden )
				RiAttribute( "cull","int hidden", &zero, RI_NULL );
		}

		return MStatus::kSuccess;
	}
	void Renderer::ribPrologue_writeSearthPath()
	{
		CM_TRACE_FUNC("Renderer::ribPrologue_writeSearthPath()");

		if ( liqglo.m_dirmaps.length() )
		{
			using namespace std;
			using namespace boost;

			const string str( liqglo.m_dirmaps.asChar() );
			stringstream ss;
			vector< string > names;
			typedef tokenizer< char_separator< char > > tokenizer;
			char_separator< char > sep("{ }");
			tokenizer tokens(str, sep);
			for ( tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter )
				names.push_back( *tok_iter );
			for ( unsigned i( 0 ); i < names.size(); i+= 3 )
			{
				// names.at(i+2)  - zone
				// names.at(i)    - from
				// names.at(i+1)  - to
				// [\"UNC\" \"/from_path/\" \"//comp/to_path/\"]
				ss << "[\\\"" << names.at(i+2) << "\\\" \\\"" << names.at(i) << "\\\" \\\"" << names.at(i+1) << "\\\"] ";
			}
			printf("%s\n", ss.str().c_str());
			string dirmapsPath ( ss.str() );
			RtString list = const_cast< char* > ( dirmapsPath.c_str() );
			RiOption( "searchpath", "dirmap", &list, RI_NULL );
		}
		RtString list = const_cast< char* > ( liqglo.liqglo_shaderPath.asChar() );
		RiOption( "searchpath", "shader", &list, RI_NULL );

		MString texturePath = liqglo.liqglo_texturePath + ":" + liquidSanitizeSearchPath( liqglo.liqglo_textureDir );
		list = const_cast< char* > ( texturePath.asChar() );
		RiOption( "searchpath", "texture", &list, RI_NULL );

		MString archivePath = liqglo.liqglo_archivePath + ":" + liquidSanitizeSearchPath( liqglo.liqglo_ribDir );
		list = const_cast< char* > ( archivePath.asChar() );
		RiOption( "searchpath", "archive", &list, RI_NULL );

		list = const_cast< char* > ( liqglo.liqglo_proceduralPath.asChar() );
		RiOption( "searchpath", "procedural", &list, RI_NULL );

		// if rendering to the renderview, add a path to the liqmaya display driver
		if( liqglo.m_renderView ) 
		{
			MString home( getenv( "LIQUIDHOME" ) );
			MString displaySearchPath;
			if( (liqglo.liquidRenderer.renderName == MString("Pixie")) || (liqglo.liquidRenderer.renderName == MString("Air")) || (liqglo.liquidRenderer.renderName == MString("3Delight")) )
				displaySearchPath = ".:@::" + liqglo.liquidRenderer.renderHome + "/displays:" + liquidSanitizePath( home ) + "/displayDrivers/" + liqglo.liquidRenderer.renderName + "/";
			else 
				displaySearchPath = ".:@:" + liqglo.liquidRenderer.renderHome + "/etc:" + liquidSanitizePath( home ) +  "/displayDrivers/" + liqglo.liquidRenderer.renderName + "/";

			list = const_cast< char* > ( displaySearchPath.asChar() );
			RiArchiveRecord( RI_VERBATIM, "Option \"searchpath\" \"display\" [\"%s\"]\n", list );
		}
	}
	//
	MStatus Renderer::framePrologue(long lframe, const structJob &currentJob)
	{
		CM_TRACE_FUNC("Renderer::framePrologue("<<lframe<<","<<currentJob.name<<")");

		RiFrameBegin( lframe );

		if( currentJob.isShadow )
		{
			tShadowRibWriterMgr::framePrologue_display(currentJob);
		}//if( liqglo.liqglo_currentJob.isShadow )
		else
		{
			tHeroRibWriterMgr::framePrologue_display(currentJob);
		}

		this->framePrologue_camera(lframe, currentJob);

		return MStatus::kSuccess;
	}
	MStatus Renderer::framePrologue_camera(long lframe, const structJob &currentJob)
	{
		CM_TRACE_FUNC("Renderer::framePrologue_camera("<<lframe<<","<<currentJob.name<<")");

		tRibCameraMgr::framePrologue_camera(lframe, currentJob);

		return MStatus::kSuccess;
	}
	//
	MStatus Renderer::frameEpilogue(const long scanTime)
	{
		CM_TRACE_FUNC("Renderer::frameEpilogue("<<scanTime<<")");

		if( !liqglo.m_exportReadArchive ) 
			RiFrameEnd();
		
		return MStatus::kSuccess;
	}
	//
	MStatus Renderer::doTextures(const std::vector<structJob> &txtList_)
	{ 
		CM_TRACE_FUNC(boost::format("rm::Renderer::doTextures(txtList.size()=%d)") % txtList_.size());

		std::vector<structJob>::const_iterator iter = txtList_.begin();
		while ( iter != txtList_.end() ) 
		{
			if(iter->skip)
			{
				printf("    - skipping '%s'\n", iter->ribFileName.asChar() );
				liquidMessage("     - skipping '"+std::string(iter->ribFileName.asChar())+"'", messageInfo);
				++iter;
				continue;
			}
			liquidMessage( "Making textures '" + std::string( iter->imageName.asChar() ) + "'", messageInfo );
			printf("[!] Making textures '%s'\n", iter->imageName.asChar() );
#ifdef _WIN32
			liqProcessLauncher::execute( iter->renderName, iter->ribFileName, liqglo.liqglo_projectDir, true );
#else
			liqProcessLauncher::execute( iter->renderName, iter->ribFileName, liqglo.liqglo_projectDir, true );
#endif
			++iter;
		}
		return MStatus::kSuccess;
	}
	MStatus Renderer::doShadows(const std::vector<structJob> &shadowList_)
	{
		CM_TRACE_FUNC(boost::format("rm::Renderer::doShadows(shadowList_.size()=%d)")%shadowList_.size());

		liquidMessage( "Rendering shadow maps... ", messageInfo );
		liquidMessage( "[!] Rendering shadow maps... ", messageInfo );
		std::vector<structJob>::const_iterator iter = shadowList_.begin();
		while ( iter != shadowList_.end() ) 
		{
			if( iter->skip ) 
			{
				printf("    - skipping '%s'\n", iter->ribFileName.asChar() );
				liquidMessage( "    - skipping '" + std::string( iter->ribFileName.asChar() ) + "'", messageInfo );
				++iter;
				continue;
			}
			printf( "    + '%s'\n", iter->ribFileName.asChar() );
			liquidMessage( "    + '" + std::string( iter->ribFileName.asChar() ) + "'", messageInfo );
#ifdef _WIN32
			if( !liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, liqglo.liquidRenderer.renderCmdFlags + " \"" + iter->ribFileName + "\"", liqglo.liqglo_projectDir, true ) )
#else
			if( !liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, liqglo.liquidRenderer.renderCmdFlags + " " + iter->ribFileName, liqglo.liqglo_projectDir, true ) )
#endif
				break;
			++iter;
		} // while ( iter != shadowList_.end() )
		return MStatus::kSuccess;
	}
	MStatus Renderer::doRenderView()
	{
		CM_TRACE_FUNC("Renderer::doRenderView()");

		MString local = (liqglo.m_renderViewLocal)? "1":"0";
		std::stringstream tmp;
		tmp << liqglo.m_renderViewTimeOut;
		//=============
		printf(">> m_renderView: m_renderViewTimeOut = %s\n", tmp.str().c_str() );
		MString timeout( tmp.str().c_str() );
		MString displayCmd = "liquidRenderView "+( (liqglo.renderCamera=="")?"":("-c "+liqglo.renderCamera) ) + " -l " + local + " -port " + liqglo.m_renderViewPort + " -timeout " + timeout ;
		if( liqglo.m_renderViewCrop ) 
			displayCmd = displayCmd + " -doRegion";
		displayCmd = displayCmd + ";liquidSaveRenderViewImage();";
		//============= 
		printf(">> m_renderView: m_displayCmd = %s\n", displayCmd.asChar() );
		MGlobal::executeCommand( displayCmd );
		return MStatus::kSuccess;
	}
	MStatus Renderer::renderAll_local(const MString& ribFileName)
	{
		CM_TRACE_FUNC(boost::format("rm::Renderer::renderAll_local(%s)")%ribFileName.asChar());

		printf("    + '%s'\n", ribFileName.asChar() );
		liquidMessage( "    + '" + std::string( ribFileName.asChar() ) + "'", messageInfo );

#ifdef _WIN32
		printf("1.liqProcessLauncher::execute(%s, %s %s \"%s\", \"%s\", %d)\n",
			liqglo.liquidRenderer.renderCommand.asChar(), liqglo.liqglo_rifParams.asChar(), liqglo.liquidRenderer.renderCmdFlags.asChar(), ribFileName.asChar(), liqglo.liqglo_projectDir.asChar(), false);
		liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " \"" + ribFileName + "\"", "\"" + liqglo.liqglo_projectDir + "\"", false );
#else
		liqProcessLauncher::execute( liqglo.liquidRenderer.renderCommand, " "+liqglo.liqglo_rifParams+" "+ liqglo.liquidRenderer.renderCmdFlags + " " + ribFileName, liqglo.liqglo_projectDir, false );
#endif
		/*  philippe: here we launch the liquidRenderView command which will listen to the liqmaya display driver
		to display buckets in the renderview.
		*/
		if( liqglo.m_renderView ) 
		{
			doRenderView();
		}
		return MStatus::kSuccess;
	}
	MStatus Renderer::renderAll_remote(const MString& ribFileName)
	{
		CM_TRACE_FUNC("Renderer::renderAll_remote("<<ribFileName<<")");

		return MStatus::kSuccess;
	}

	void Renderer::exportLightLinks(
		const structJob &currentJob__,
		const liqRibNodePtr mesh, 
		const MStringArray& lightedByWhichLightShapes)
	{
		CM_TRACE_FUNC("Renderer::exportLightLinks("<<currentJob__.name<<","<<mesh->name<<",lightedByWhichLightShapes.size="<<lightedByWhichLightShapes.length()<<")");

		if(lightedByWhichLightShapes.length() == 0){
			_liqRIBMsg((mesh->name+" is not lighted.").asChar());
			return;
		}

		boost::shared_ptr< liqRibHT > &htable = liqRibTranslator::getInstancePtr()->htable;
		for ( RNMAP::iterator rniter( htable->RibNodeMap.begin() ); rniter != htable->RibNodeMap.end(); rniter++ ) 
		{
			liqRibNodePtr   ribNode = (*rniter).second;

			if( ribNode->object(0)->ignore || ribNode->object(0)->type != MRT_Light )
				continue;
			
			if(-1 != find_first_of(ribNode->name.asChar(), lightedByWhichLightShapes) ){
				RiIlluminate( ribNode->object(0)->lightHandle(), 1 );
			}else{
				RiIlluminate( ribNode->object(0)->lightHandle(), 0 );
			}
		}
	}

	void Renderer::_writeObject(
		const liqRibNodePtr& ribNode, 
		const structJob &currentJob,
		const bool bGeometryMotion,
		const unsigned int msampleOn,
		const bool bReference
		)
	{
		CM_TRACE_FUNC("Renderer::_writeObject("<<ribNode->name<<","<<currentJob.name<<","<<bGeometryMotion<<","<<msampleOn<<","<<bReference<<")");

		MStatus status;

		MString MotionPostfix;
		unsigned int sample;
		if( bGeometryMotion ){
			MString MSampleOn;
			MSampleOn.set((int)msampleOn);
			MotionPostfix = ".m"+MSampleOn;
			sample        = msampleOn;
		}else{
			MotionPostfix = "";
			sample        = 0;
		}

		MString geometryRibFile( 
			liquidGetRelativePath( 
			false, 
			getLiquidRibName( ribNode->name.asChar() ), 
			liqglo.liqglo_ribDir 
			) +"."+(int)liqglo.liqglo_lframe+MotionPostfix+".rib" 
			);



		//=====================================================
		// Export rib data
		//=====================================================
		ribNode->object( sample )->writeObject(geometryRibFile, currentJob, bReference);
	}
	//
	bool Renderer::isHeroPassReady(const structJob &currentJob)
	{
		CM_TRACE_FUNC("Renderer::isHeroPassReady("<<currentJob.name<<")");

		return true;
	}
	void Renderer::HeroPassBegin(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::HeroPassBegin("<<currentJob___.name<<")");


	}
	void Renderer::HeroPassEnd(const structJob &currentJob)
	{
		CM_TRACE_FUNC("Renderer::HeroPassEnd("<<currentJob.name<<")");



		//
		if( currentJob.skip ) 
		{
			printf("    - skipping '%s'\n", currentJob.ribFileName.asChar() );
			liquidMessage( "    - skipping '" + std::string( currentJob.ribFileName.asChar() ) + "'", messageInfo );
		}else {
			renderAll_local(currentJob.ribFileName);
		}
	}
	//

	bool Renderer::isBaseShadowReady(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::isBaseShadowReady("<<currentJob___.name<<")");

		return !currentJob___.shadowArchiveRibDone;
	}
	void Renderer::BaseShadowBegin(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::BaseShadowBegin("<<currentJob___.name<<")");

		MString     baseShadowName__(getBaseShadowName(currentJob___));
		//
		//  create the read-archive shadow files
		//
#ifndef RENDER_PIPE
		liquidMessage( "Beginning RIB output to '" + std::string( baseShadowName__.asChar() ) + "'", messageInfo );
		RiBegin( const_cast< RtToken >( baseShadowName__.asChar() ) );
		liqglo.m_ribFileOpen = true;
#else
		liqglo__.liqglo_ribFP = fopen( baseShadowName.asChar(), "w" );
		if( liqglo__.liqglo_ribFP ) {
			LIQDEBUGPRINTF( "-> setting pipe option\n" );
			RtInt ribFD( fileno( liqglo__.liqglo_ribFP ) );
			RiOption( "rib", "pipe", &ribFD, RI_NULL );
		}
		else
		{
			liquidMessage( "Error opening RIB -- writing to stdout.\n", messageError );
		}
		liquidMessage( "Beginning RI output directly to renderer", messageInfo );
		RiBegin( RI_NULL );
#endif
	}
	void Renderer::BaseShadowEnd(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::BaseShadowEnd("<<currentJob___.name<<")");

		RiEnd();
		liqglo.m_ribFileOpen = false;
#ifdef RENDER_PIPE  
		fclose( liqglo.liqglo_ribFP );
#endif
		liqglo.liqglo_ribFP = NULL;
	}

	bool Renderer::isShadowPassReady(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::isShadowPassReady("<<currentJob___.name<<")");

		return true;
	}
	void Renderer::ShadowPassBegin(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::ShadowPassBegin("<<currentJob___.name<<")");

		//move RiBegin() to ribPrologue_begin()
	}
	void Renderer::ShadowPassEnd(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::ShadowPassEnd("<<currentJob___.name<<")");
		
		//move RiEnd() to ribPrologue_end()

		//------------------------------------------------------------
		//rendering
		this->renderAll_local(currentJob___.ribFileName);
		//------------------------------------------------------------
	}
	void Renderer::readBaseShadow(const structJob &currentJob___)
	{
		CM_TRACE_FUNC("Renderer::readBaseShadow("<<currentJob___.name<<")");
		
		//MString realShadowName( liquidSanitizePath( liquidGetRelativePath( liqglo_relativeFileNames, baseShadowName, liqglo_projectDir ) ) );
		MString     baseShadowName__(getBaseShadowName(currentJob___));

		RiArchiveRecord( RI_COMMENT, "Read Archive Data:\n" );
		RiReadArchive( const_cast< RtToken >( baseShadowName__.asChar() ), NULL, RI_NULL );

	}
	//
	void Renderer::oneObjectBlock_reference_attribute_begin(
		const liqRibNodePtr &ribNode,
		const structJob &currentJob )
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_begin("<<ribNode->name<<","<<currentJob.name<<")");

		if( liqglo.m_outputComments ) 
			RiArchiveRecord( RI_COMMENT, "Name: %s", ribNode->name.asChar(), RI_NULL );

		RiAttributeBegin();
	}
	void Renderer::oneObjectBlock_reference_attribute_end(
		const liqRibNodePtr &ribNode,
		const structJob &currentJob )
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_end("<<ribNode->name<<","<<currentJob.name<<")");

		RiAttributeEnd();
	}
	void Renderer::oneObjectBlock_reference_attribute_block0(
		const liqRibNodePtr &ribNode,
		const structJob &currentJob )
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_block0("<<ribNode->name<<","<<currentJob.name<<")");

		RiAttribute( "identifier", "name", &getLiquidRibName( ribNode->name.asChar() ), RI_NULL );

		if( !ribNode->grouping.membership.empty() ) 
		{
			RtString members( const_cast< char* >( ribNode->grouping.membership.c_str() ) );
			RiAttribute( "grouping", "membership", &members, RI_NULL );
		}

		if( ribNode->shading.matte || ribNode->mayaMatteMode ) 
			RiMatte( RI_TRUE );

		// If this is a single sided object, then turn that on (RMan default is Sides 2)
		if( !ribNode->doubleSided ) 
			RiSides( 1 );

		if( ribNode->reversedNormals ) 
			RiReverseOrientation();
	}
	void Renderer::oneObjectBlock_reference_attribute_block1(
		const liqRibNodePtr &ribNode,
		const structJob &currentJob )
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_block1("<<ribNode->name<<","<<currentJob.name<<")");

		// displacement bounds
		liqRibTranslator::getInstancePtr()->displacementBounds(ribNode);

		LIQDEBUGPRINTF( "-> writing node attributes\n" );
		// if the node's shading rate == -1,
		// it means it hasn't been overriden by a liqShadingRate attribute.
		// No need to output it then.
		if( ribNode->shading.shadingRate > 0 )
			RiShadingRate ( ribNode->shading.shadingRate );

		if( currentJob.isShadow ) 
		{
			liqRibTranslator::getInstancePtr()->objectShadowAttribute(ribNode);
		}else{
			liqRibTranslator::getInstancePtr()->objectNonShadowAttribute(ribNode);
		}
	}
	void Renderer::logFrame(const char* msg)
	{
		CM_TRACE_FUNC("Renderer::logFrame("<<msg<<")");

		RiArchiveRecord( RI_COMMENT, "\t\t\t\t[DEBUG] %s", msg );
	}
	void Renderer::oneObjectBlock_reference_attribute_block2_writeShader_RibBox(const char* msg)
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_block2_writeShader_RibBox("<<msg<<")");

		RiArchiveRecord( RI_VERBATIM, ( char* )msg );
		RiArchiveRecord( RI_VERBATIM, "\n" );
	}
	void Renderer::oneObjectBlock_reference_attribute_block2_writeShader_RegularShader(
		const liqRibNodePtr &ribNode__,
		const structJob &currentJob 
		)
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_block2_writeShader_RegularShader("<<ribNode__->name<<","<<currentJob.name<<")");

		//liqShader& currentShader( liqGetShader( ribNode__->assignedShader.object() ) );
		liqShader& currentShader = liqShaderFactory::instance().getShader( ribNode__->assignedShader.object() );

		liqRibTranslator::getInstancePtr()->F1(ribNode__, currentShader);

		liqRIBMsg("[2] liqglo_currentJob.isShadow=%d, currentShader.outputInShadow=%d", currentJob.isShadow, currentShader.outputInShadow );
		// per shader shadow pass override
		if( !currentJob.isShadow || currentShader.outputInShadow )
		{
			//currentShader.write();//use ShadingGroup file reference(e.g. *.erapi/*.rmsg) instead.
		}

		//if( outputSurfaceShader )
		//{
		//	scoped_array< RtToken > tokenArray( new RtToken[ currentShader.tokenPointerArray.size() ] );
		//	scoped_array< RtPointer > pointerArray( new RtPointer[ currentShader.tokenPointerArray.size() ] );
		//	assignTokenArrays( currentShader.tokenPointerArray.size(), &currentShader.tokenPointerArray[ 0 ], tokenArray.get(), pointerArray.get() );

		//	char* shaderFileName;
		//	LIQ_GET_SHADER_FILE_NAME( shaderFileName, liqglo_shortShaderNames, currentShader );

		//	// check shader space transformation
		//	if( currentShader.shaderSpace != "" )
		//	{
		//		RiTransformBegin();
		//		RiCoordSysTransform( ( RtString )currentShader.shaderSpace.asChar() );
		//	}
		//	// output shader
		//	// its one less as the tokenPointerArray has a preset size of 1 not 0
		//	int shaderParamCount = currentShader.tokenPointerArray.size() - 1;
		//	RiSurfaceV ( shaderFileName, shaderParamCount, tokenArray.get(), pointerArray.get() );
		//	if( currentShader.shaderSpace != "" )
		//		RiTransformEnd();
		//}
	}
	void Renderer::oneObjectBlock_reference_attribute_block2_writeShader_HasNoSurfaceShaderORIngoreSurface(
		const liqRibNodePtr &ribNode__, const MDagPath &path__, const bool m_shaderDebug
		)
	{
		CM_TRACE_FUNC("Renderer::oneObjectBlock_reference_attribute_block2_writeShader_HasNoSurfaceShaderORIngoreSurface("
			<<ribNode__->name<<","<<path__.fullPathName()<<","<<m_shaderDebug<<")");

		liqRibTranslator::getInstancePtr()->F2(m_shaderDebug, ribNode__);

		if( !liqRibTranslator::getInstancePtr()->m_ignoreSurfaces ) 
		{
			MObject shadingGroup = ribNode__->assignedShadingGroup.object();
			MObject shader = ribNode__->findShader( shadingGroup );
			//
			// here we check for regular shader nodes first
			// and assign default shader to shader-less nodes.
			//
			if( m_shaderDebug ) {
				liqRIBMsg("shader debug is turned on, so the surface is constant.");
				RiSurface( "constant", RI_NULL );
				LIQDEBUGPRINTF("add more constant parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorBlinn.sl as an example.(?)");
			}
			//else if( shader.apiType() == MFn::kLambert ){ 
			//	RiSurface( "matte", RI_NULL );
			//	LIQDEBUGPRINTF("add more lambert parameters here. take //RMS-1.0.1-Maya2008/lib/shaders/src/mtorLambert.sl as an example.");
			//}else if( shader.apiType() == MFn::kPhong ) {
			//	RiSurface( "plastic", RI_NULL );
			//	LIQDEBUGPRINTF("add more phong parameters here. take /RMS-1.0.1-Maya2008/lib/shaders/src/mtorPhong.sl as an example.");
			//}
			else if( path__.hasFn( MFn::kPfxHair ) ) 
			{
				// get some of the hair system parameters
				RtFloat translucence = 0, specularPower = 0;
				RtColor specularColor;

				liqRibTranslator::getInstancePtr()->getPfxHairData(path__, translucence, specularPower, specularColor);

				RiSurface(  "liquidpfxhair",
					"float specularpower", &specularPower,
					"float translucence",  &translucence,
					"color specularcolor", &specularColor,
					RI_NULL );
			} 
			else if( path__.hasFn( MFn::kPfxToon ) ) {
				RiSurface( "liquidpfxtoon", RI_NULL );
			}else if( path__.hasFn( MFn::kPfxGeometry ) ){
				RiSurface( "liquidpfx", RI_NULL );
			}else {
				//RiSurface( "plastic", RI_NULL );
				//MFnDependencyNode shaderFn(shader);
				//RiSurface( const_cast<char*>(shaderFn.name().asChar()), RI_NULL );//use ShadingGroup file reference(e.g. *.erapi/*.rmsg) instead.
			}
		}

	}
	void Renderer::oneObjectBlock_reference_attribute_block3_ShadingGroup(
		const MString& meshname
		)
	{
		CM_TRACE_FUNC(boost::format("liqRibTranslator::writeShadingGroup(%s)")%meshname.asChar());
		RiArchiveRecord( RI_COMMENT, "use Shading Group reference:" );
		{
			MStringArray shadingGroupNode;
			{
				MString cmd = "listConnections -type \"shadingEngine\" -destination on (\""+meshname+"\" + \".instObjGroups\")";
				IfMErrorWarn(MGlobal::executeCommand( cmd, shadingGroupNode));
			}

			MString shadingGroupFileName(getShaderDirectory()+shadingGroupNode[0]);

			RiReadArchive( const_cast< RtToken >((shadingGroupFileName+".rmsg").asChar()), NULL, RI_NULL );
		}
	}
	//
	bool Renderer::canExport()
	{
		CM_TRACE_FUNC("Renderer::canExport()");

		return true;
	}

}//namespace
