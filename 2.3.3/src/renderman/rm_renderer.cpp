#include "rm_renderer.h"

// Renderman Headers
//extern "C" {
#include "ri_interface.h"
//}
// Maya headers
#include <maya/MAnimControl.h>
#include <maya/MFileIO.h>
#include <maya/MFnLight.h>
#include <maya/MFnTransform.h>
#include <maya/MGlobal.h>
#include <maya/MItDag.h>
#include <maya/MItInstancer.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MSelectionList.h>
#include <maya/MSyntax.h>
#include <maya/MDistance.h>
#include <maya/MFnSet.h>
#include <maya/MFnStringArrayData.h>
#include <maya/MFnIntArrayData.h>
#include <maya/MFnPfxGeometry.h>
#include <maya/MDistance.h>
#include <maya/MDagModifier.h>
#include <maya/MPxNode.h>
#include <maya/MRenderLineArray.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MDagPathArray.h>
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


namespace renderman
{
	static const Renderer dummy;
	// the only goal to define a Renderer variable is 
	// to run the constructor to register this renderer.

	static const char *RendererName="renderman";

	Renderer::Renderer()
	{
		liquid::RendererMgr::getInstancePtr()->registerRenderer(
			RendererName, this
		);
	}
	//
	Renderer::~Renderer()
	{

	}
	//
	void Renderer::test()
	{
		liquidMessage2(messageInfo, "this is %s.", RendererName );
	}
	//
	void Renderer::setRenderScriptFormatAndCompress(const bool bbinary, const bool bcompress)
	{
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

					ribNode->object(0)->writeObject("", currentJob);
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
		MStatus returnStatus = MS::kSuccess;
		LIQDEBUGPRINTF( "-> Writing world epilogue.\n" );
		// If this is a readArchive that we are exporting there's no world block
		if( !liqglo.m_exportReadArchive ) 
			RiWorldEnd();
		return returnStatus;
	}
	//
	MStatus Renderer::exportLight(const liqRibNodePtr& ribNode, const structJob &currentJob)
	{

		RtInt on( 1 );
			// We need to enclose lights in attribute blocks because of the
			// new added attribute support
			RiAttributeBegin();

			// All this stuff below should be handled by a new attribute class
			LIQDEBUGPRINTF( "-> RibNodeName " );
			RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
			LIQDEBUGPRINTF( "= %s.\n", (char *)RibNodeName  );
			RiAttribute( "identifier", "name", &RibNodeName, RI_NULL );
			if( ribNode->trace.sampleMotion )
				RiAttribute( "trace", (RtToken) "samplemotion", &on, RI_NULL );
			if( ribNode->trace.displacements )
				RiAttribute( "trace", (RtToken) "displacements", &on, RI_NULL );
			if( ribNode->trace.bias != 0.01f )
			{
				RtFloat bias = ribNode->trace.bias;
				RiAttribute( "trace", (RtToken) "bias", &bias, RI_NULL );
			}
			if( ribNode->trace.maxDiffuseDepth != 1 )
			{
				RtInt mddepth = ribNode->trace.maxDiffuseDepth;
				RiAttribute( "trace", (RtToken) "maxdiffusedepth", &mddepth, RI_NULL );
			}
			if( ribNode->trace.maxSpecularDepth != 2 )
			{
				RtInt msdepth = ribNode->trace.maxSpecularDepth;
				RiAttribute( "trace", (RtToken) "maxspeculardepth", &msdepth, RI_NULL );
			}
			ribNode->object(0)->writeObject("", currentJob);//call liqRibLightData::_write(...)
			ribNode->object(0)->written = 1;
			// The next line pops the light...
			RiAttributeEnd();
			// ...so we have to switch it on again explicitly
			// if exclusive Lightlinking is set
			if( liqglo.m_illuminateByDefault )
				RiIlluminate( ribNode->object(0)->lightHandle(), 1 );
			else
				RiIlluminate( ribNode->object(0)->lightHandle(), 0 );
			return MStatus::kSuccess;
	}
	void Renderer::openLog()
	{

	}
	void Renderer::closeLog()
	{

	}
	liqLightHandle Renderer::exportShadowPassLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqString & shadowName,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "liquidshadowpasslight", "string shadowname", &shadowName, RI_NULL );
	}
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "ambientlight",
			"intensity",  &intensity,
			"lightcolor", color,
			RI_NULL );
	}
	void Renderer::transform_(const liqMatrix& transform)
	{
	}
	MStatus Renderer::liqRibLightData_write(
		const liqRibLightData *lightdata, const structJob &currentJob)
	{
		return MS::kSuccess;
	}
	liqLightHandle Renderer::exportDistantLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat &i_intensity,
		const liqColor &i_lightcolor,
		const liqString &i_shadowname,
		const liqFloat &i_shadowbias,
		const liqFloat &i_shadowblur,
		const liqFloat &i_shadowsamples,
		const liqFloat &i_shadowfiltersize,
		const liqColor &i_shadowcolor,
		const liqFloat  &i_lightID,
		const liqString &o_category,
		const liqFloat &o_shadowF,
		const liqColor &o_shadowC,
		const liqColor &o_unshadowed_Cl,
		const liqFloat &o_nondiffuse,
		const liqFloat &o_nonspecular,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( 
			"liquiddistant",
			"intensity",              &i_intensity,
			"lightcolor",             &i_lightcolor,
			"string shadowname",      &i_shadowname,
			"float shadowbias",       &i_shadowbias,
			"float shadowblur",       &i_shadowblur,
			"float shadowsamples",    &i_shadowsamples,
			"float shadowfiltersize", &i_shadowfiltersize,
			"color shadowcolor",      &i_shadowcolor,
			"float lightID",          &i_lightID,
			"string __category",      &o_category,

			"float __shadowF",			&o_shadowF,
			"color __shadowC",			&o_shadowC,
			"color __unshadowed_Cl",	&o_unshadowed_Cl,
			"float __nondiffuse",		&o_nondiffuse,
			"float __nonspecular",		&o_nonspecular,
			RI_NULL 
			);
	}
	//
	liqLightHandle Renderer::exportPointLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat &i_intensity,
		const liqColor &i_lightcolor,
		const liqFloat &i_decay,
		const liqString &i_shadownamepx,
		const liqString &i_shadownamenx,
		const liqString &i_shadownamepy,
		const liqString &i_shadownameny,
		const liqString &i_shadownamepz,
		const liqString &i_shadownamenz,
		const liqFloat &i_shadowbias,
		const liqFloat &i_shadowblur,
		const liqFloat &i_shadowsamples,
		const liqFloat &i_shadowfiltersize,
		const liqColor &i_shadowcolor,
		const liqFloat  &i_lightID,
		const liqString &o_category,
		const liqFloat &o_shadowF,
		const liqColor &o_shadowC,
		const liqColor &o_unshadowed_Cl,
		const liqFloat &o_nondiffuse,
		const liqFloat &o_nonspecular,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "liquidpoint",
			"intensity",                  &i_intensity,
			"lightcolor",                 &i_lightcolor,
			"float decay",                &i_decay,
			"string shadownamepx",        &i_shadownamepx,
			"string shadownamenx",        &i_shadownamenx,
			"string shadownamepy",        &i_shadownamepy,
			"string shadownameny",        &i_shadownameny,
			"string shadownamepz",        &i_shadownamepz,
			"string shadownamenz",        &i_shadownamenz,
			"float shadowbias",           &i_shadowbias,
			"float shadowblur",           &i_shadowblur,
			"float shadowsamples",        &i_shadowsamples,
			"float shadowfiltersize",     &i_shadowfiltersize,
			"color shadowcolor",          &i_shadowcolor,
			"float lightID",              &i_lightID,
			"string __category",          &o_category,
			"float __shadowF",			&o_shadowF,
			"color __shadowC",			&o_shadowC,
			"color __unshadowed_Cl",	    &o_unshadowed_Cl,
			"float __nondiffuse",         &o_nondiffuse,
			"float __nonspecular",        &o_nonspecular,
			RI_NULL );
	}
	//
	liqLightHandle Renderer::exportSpotLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat &i_intensity,
		const liqColor &i_lightcolor,
		const liqFloat &i_coneangle,
		const liqFloat &i_penumbraangle,
		const liqFloat &i_dropoff,
		const liqFloat &i_decay,

		const liqFloat &i_barndoors,
		const liqFloat &i_leftbarndoor            ,
		const liqFloat &i_rightbarndoor           ,
		const liqFloat &i_topbarndoor             ,
		const liqFloat &i_bottombarndoor          ,

		const liqFloat &i_decayRegions            ,
		const liqFloat &i_startDistance1          ,
		const liqFloat &i_endDistance1            ,
		const liqFloat &i_startDistance2          ,
		const liqFloat &i_endDistance2            ,
		const liqFloat &i_startDistance3          ,
		const liqFloat &i_endDistance3            ,
		const liqFloat &i_startDistanceIntensity1,
		const liqFloat &i_endDistanceIntensity1,
		const liqFloat &i_startDistanceIntensity2,
		const liqFloat &i_endDistanceIntensity2,
		const liqFloat &i_startDistanceIntensity3,
		const liqFloat &i_endDistanceIntensity3,

		const liqString &i_shadowname,
		const liqFloat &i_shadowbias,
		const liqFloat &i_shadowblur,
		const liqFloat &i_shadowsamples,
		const liqFloat &i_shadowfiltersize,
		const liqColor &i_shadowcolor,
		const liqColor &i_shadowcolorsurf,
		const liqFloat &i_shadowcolormix,

		const liqFloat  &i_lightID,
		const liqString &i_category,
		const liqColor &o_shadowC,
		const liqFloat &o_shadowF,
		const liqFloat &o_barn,
		const liqColor &o_unshadowed_Cl,
		const liqFloat &o_nondiffuse,
		const liqFloat &o_nonspecular,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "liquidspot",
			"intensity",                    &i_intensity,
			"lightcolor",                   &i_lightcolor,
			"float coneangle",              &i_coneangle,
			"float penumbraangle",          &i_penumbraangle,
			"float dropoff",                &i_dropoff,
			"float decay",                  &i_decay,

			"float barndoors",              &i_barndoors,
			"float leftbarndoor",           &i_leftbarndoor,
			"float rightbarndoor",          &i_rightbarndoor,
			"float topbarndoor",            &i_topbarndoor,
			"float bottombarndoor",         &i_bottombarndoor,

			"float decayRegions",           &i_decayRegions,
			"float startDistance1",         &i_startDistance1,
			"float endDistance1",           &i_endDistance1,
			"float startDistance2",         &i_startDistance2,
			"float endDistance2",           &i_endDistance2,
			"float startDistance3",         &i_startDistance3,
			"float endDistance3",           &i_endDistance3,
			"float startDistanceIntensity1",&i_startDistanceIntensity1,
			"float endDistanceIntensity1",  &i_endDistanceIntensity1,
			"float startDistanceIntensity2",&i_startDistanceIntensity2,
			"float endDistanceIntensity2",  &i_endDistanceIntensity2,
			"float startDistanceIntensity3",&i_startDistanceIntensity3,
			"float endDistanceIntensity3",  &i_endDistanceIntensity3,

			"string shadowname",            &i_shadowname,
			"float shadowbias",             &i_shadowbias,
			"float shadowblur",             &i_shadowblur,
			"float shadowsamples",          &i_shadowsamples,
			"float shadowfiltersize",       &i_shadowfiltersize,
			"color shadowcolor",            &i_shadowcolor,
			"color shadowcolorSurf",        &i_shadowcolorsurf,
			"float shadowcolorMix",         &i_shadowcolormix,

			"float lightID",                &i_lightID,
			"string __category",            &i_category,

			"color __shadowC",              &o_shadowC,
			"float __shadowF",              &o_shadowF,
			"float __barn",				    &o_barn,
			"color __unshadowed_Cl",        &o_unshadowed_Cl,
			"float __nondiffuse",           &o_nondiffuse,
			"float __nonspecular",          &o_nonspecular,
			RI_NULL );
	}
	//
	liqLightHandle Renderer::exportAreaLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat &i_intensity,
		const liqColor &i_lightcolor,
		const liqFloat &i_decay,
		const liqString  &i_coordsys,
		const liqFloat   &i_lightsamples,
		const liqFloat &i_doublesided,
		const liqString &i_shadowname,
		const liqColor &i_shadowcolor,
		const liqString &i_hitmode,
		const liqString &i_lightmap,
		const liqFloat &i_lightmapsaturation,
		const liqFloat  &i_lightID,
		const liqString &i_category,
		const liqFloat &o_nonspecular,
		const liqFloat &o_shadowF,
		const liqColor &o_shadowC,
		const liqColor &o_unshadowed_Cl,
		const liqFloat &o_arealightIntensity,
		const liqColor &o_arealightColor,
		const liqMatrix &transform)
	{
		RiConcatTransform( * const_cast< RtMatrix* >( &transform ) );
		return RiLightSource( "liquidarea",
			"float intensity",            &i_intensity,
			"color lightcolor",           &i_lightcolor,
			"float decay",                &i_decay,
			"string coordsys",            &i_coordsys,
			"float lightsamples",         &i_lightsamples,
			"float doublesided",          &i_doublesided,
			"string shadowname",          &i_shadowname,
			"color shadowcolor",          &i_shadowcolor,
			"string hitmode",             &i_hitmode,
			"string lightmap",            &i_lightmap,
			"float lightmapsaturation",   &i_lightmapsaturation,
			"float lightID",              &i_lightID,
			"string __category",          &i_category,

			"float __nonspecular",			&o_nonspecular,
			"float __shadowF",				&o_shadowF, 
			"color __shadowC",				&o_shadowC,
			"color __unshadowed_Cl",		&o_unshadowed_Cl,
			"float __arealightIntensity",	&o_arealightIntensity,
			"color __arealightColor",		&o_arealightColor,
			RI_NULL );
	}

}
