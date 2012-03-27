#include "rm_renderer.h"
#include <liqRibLightData.h>
#include "rm_helper.h"

namespace renderman
{
	bool Renderer::writeLight_pre(const liqRibNodePtr& ribNode, const structJob& currentJob)
	{
		CM_TRACE_FUNC("Renderer::writeLight_pre("<<ribNode->name<<","<<currentJob.name<<")");

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
		return true;
	}
	//
	void Renderer::writeLight_post(const liqRibNodePtr& ribNode, const structJob& currentJob)
	{
		CM_TRACE_FUNC("Renderer::writeLight_post("<<ribNode->name<<","<<currentJob.name<<")");

		// The next line pops the light...
		RiAttributeEnd();
		// close light by default // [1/30/2012 yaoyansi]
		RiIlluminate( ribNode->object(0)->lightHandle(), 0 );
	}
	//
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &transform)
	{
		CM_TRACE_FUNC("Renderer::exportAmbientLight("<<shadertype<<","<<shaderinstance<<",...)");

		liqMatrix transformationMatrixScaledZ;
		liqRibLightData::scaleZ_forRenderman(
			transformationMatrixScaledZ, transform
			);
		RiConcatTransform( * const_cast< RtMatrix* >( &transformationMatrixScaledZ ) );
		return RiLightSource( "ambientlight",
			"intensity",  &intensity,
			"lightcolor", color,
			RI_NULL );
	}
	//
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
		CM_TRACE_FUNC("Renderer::exportDistantLight("<<shadertype<<","<<shaderinstance<<",...)");

		liqMatrix transformationMatrixScaledZ;
		liqRibLightData::scaleZ_forRenderman(
			transformationMatrixScaledZ, transform
			);
		RiConcatTransform( * const_cast< RtMatrix* >( &transformationMatrixScaledZ ) );
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
		CM_TRACE_FUNC("Renderer::exportPointLight("<<shadertype<<","<<shaderinstance<<",...)");

		liqMatrix transformationMatrixScaledZ;
		liqRibLightData::scaleZ_forRenderman(
			transformationMatrixScaledZ, transform
			);
		RiConcatTransform( * const_cast< RtMatrix* >( &transformationMatrixScaledZ ) );
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
		CM_TRACE_FUNC("Renderer::exportSpotLight("<<shadertype<<","<<shaderinstance<<",...)");

		liqFloat _i_coneangle     = i_coneangle * 0.5f;
		liqFloat _i_penumbraangle = i_penumbraangle;

		liqMatrix transformationMatrixScaledZ;
		liqRibLightData::scaleZ_forRenderman(
			transformationMatrixScaledZ, transform
			);
		RiConcatTransform( * const_cast< RtMatrix* >( &transformationMatrixScaledZ ) );
		return RiLightSource( "liquidspot",
			"intensity",                    &i_intensity,
			"lightcolor",                   &i_lightcolor,
			"float coneangle",              &_i_coneangle,
			"float penumbraangle",          &_i_penumbraangle,
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
		CM_TRACE_FUNC("Renderer::exportAreaLight("<<shadertype<<","<<shaderinstance<<",...)");

		liqMatrix transformationMatrixScaledZ;
		liqRibLightData::scaleZ_forRenderman(
			transformationMatrixScaledZ, transform
			);
		RiConcatTransform( * const_cast< RtMatrix* >( &transformationMatrixScaledZ ) );
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
}//namespace renderman