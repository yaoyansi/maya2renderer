#include "er_renderer.h"
#include <liqRibLightData.h>
#include "ercall.h"
#include "log_helper.h"

namespace elvishray
{
	bool Renderer::writeLight_pre(const liqRibNodePtr& ribNode, const structJob &currentJob)
	{
		RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
		_s("\n// Renderer::exportLight(\""+std::string(RibNodeName)+"\");");

		return true;
	}
	//
	void Renderer::writeLight_post(const liqRibNodePtr& ribNode, const structJob &currentJob)
	{

	}
	//
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportAmbientLight()");
		std::string shaderinstanceFullPath( toFullDagPath(shaderinstance) );

		std::string sShaderInstanceName(shaderinstanceFullPath+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "ambientlight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstanceFullPath+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance(  shaderinstanceFullPath.c_str()) );
		_S( ei_element(	 sLightObjectName.c_str()));
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
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
		const liqMatrix &t)
	{
		_s("// Renderer::exportDistantLight()");
		std::string shaderinstanceFullPath( toFullDagPath(shaderinstance) );

		std::string sShaderInstanceName(shaderinstanceFullPath+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "directlight") ); 
		_S( ei_shader_param_vector("lightcolor", i_lightcolor[0], i_lightcolor[1], i_lightcolor[2] ) ); 
		_S( ei_shader_param_scalar("intensity", i_intensity ) );
		_S( ei_shader_param_vector("direction", 0.0f, 0.0f, -1.0f ) ); 
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstanceFullPath+"_object");
		_S( ei_light( sLightObjectName.c_str()) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( 0.0, 0.0, 0.0 ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstanceFullPath.c_str()) );
		_S( ei_element(	sLightObjectName.c_str()) );
		_S( ei_transform( t[0][0], t[0][1], t[0][2], t[0][3],   t[1][0], t[1][1], t[1][2], t[1][3],   t[2][0], t[2][1], t[2][2], t[2][3],   t[3][0], t[3][1], t[3][2], t[3][3] ) );
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
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
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportPointLight()");
		std::string shaderinstanceFullPath( toFullDagPath(shaderinstance) );

		std::string sShaderInstanceName(shaderinstanceFullPath+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "pointlight") ); 
		_S( ei_shader_param_vector("lightcolor", i_lightcolor[0], i_lightcolor[1], i_lightcolor[2] ) );
		_S( ei_shader_param_scalar("intensity", i_intensity) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstanceFullPath+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str()  ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstanceFullPath.c_str() ) );
		_S( ei_element( sLightObjectName.c_str() ) );
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
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
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportSpotLight()");
		std::string shaderinstanceFullPath( toFullDagPath(shaderinstance) );

		std::string sShaderInstanceName(shaderinstanceFullPath+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "spotlight") ); 
		_S( ei_shader_param_vector("lightcolor", i_lightcolor[0], i_lightcolor[1], i_lightcolor[2] ) ); 
		_S( ei_shader_param_scalar("intensity", i_intensity ) );
		_S( ei_shader_param_scalar("deltaangle", (i_penumbraangle*0.5f) ) );
		_S( ei_shader_param_vector("direction", 0.0f, 0.0f, -1.0f ) ); 
		_S( ei_shader_param_scalar("spread", (i_coneangle*0.5f) ) );  
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstanceFullPath+"_object");
		_S( ei_light( sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str()  ) );
		_S( ei_origin( 0.0, 0.0, 0.0 ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstanceFullPath.c_str() ) );
		_S( ei_element(	sLightObjectName.c_str() ) );
		_S( ei_transform( t[0][0], t[0][1], t[0][2], t[0][3],   t[1][0], t[1][1], t[1][2], t[1][3],   t[2][0], t[2][1], t[2][2], t[2][3],   t[3][0], t[3][1], t[3][2], t[3][3] ) );
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
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
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportAreaLight()");
		std::string shaderinstanceFullPath( toFullDagPath(shaderinstance) );

		std::string sShaderInstanceName(shaderinstanceFullPath+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "arealight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstanceFullPath+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2]  ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstanceFullPath.c_str() ) );
		_S( ei_element(	 sLightObjectName.c_str() ) );
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
	}
}//namespace elvishray