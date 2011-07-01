#include "er_renderer.h"
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


namespace elvishray
{
	//static const char *LogName="d:/script.er";
	static const Renderer dummy; 
	// the only goal to define a Renderer variable is 
	// to run the constructor to register this renderer.

	static const char *RendererName="elvishray";

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
		//todo...
	}
	//
	MStatus Renderer::worldPrologue(const structJob& currentJob)
	{

		_Script("ready to go!");

		if( true )
		{
			_Script("ei_make_texture(\"d:\\lunatexmap.bmp\", \"d:\\lunatexmap.tex\", EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f );");
		}

		return MS::kSuccess;
	}
	//
	MStatus Renderer::worldEpilogue()
	{
		_Script("#Renderer::worldEpilogue()");

		return MS::kSuccess;
	}
	//
	MStatus Renderer::exportLight(const liqRibNodePtr& ribNode, const structJob &currentJob)
	{
		RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
		_Script("# Renderer::exportLight(\""+std::string(RibNodeName)+"\");");
		
		ribNode->object(0)->writeObject("", currentJob);//call liqRibLightData::_write(...)
		ribNode->object(0)->written = 1;
// 		if( liqglo.m_illuminateByDefault )
// 			RiIlluminate( ribNode->object(0)->lightHandle(), 1 );
// 		else
// 			RiIlluminate( ribNode->object(0)->lightHandle(), 0 );
		return MS::kSuccess;
	}
	void Renderer::openLog()
	{
		m_log.open("d:/script.er");
	}
	void Renderer::closeLog()
	{
		m_log.close();
	}

	liqLightHandle Renderer::exportShadowPassLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqString & shadowname,
		const liqMatrix &transform)
	{
		_Script("# Renderer::exportShadowPassLight()");
		_Script(
				"ei_shader( \"shadowpasslight\", \
					\"shadername\", "+std::string(shadowname)+",\
					\"paramter0\", 1.0f,\
					\"paramter1\", 1.0f);"
		);

		_Script(
				"ei_light( light1 );\
					ei_lightsource(	shadowpasslight, ei_end );\
					ei_transform( transform );\
				ei_end_light();"
		);
		_Script(
				"ei_instance( shaderinstance );\
					ei_element(	light1 );\
				ei_end_instance();"
		);
		return (liqLightHandle)(0);
	}
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &transform)
	{
		_Script("# Renderer::exportAmbientLight()");
		_Script(
			"ei_shader( \"ambientlight\", \
			\"intensity\", ToString<liqFloat>(intensity),\
			\"lightcolor\", ToString<liqColor>(color);"
			);

		_Script(
			"ei_light( light1 );\
			ei_lightsource(	shadowpasslight, ei_end );\
			ei_transform( transform );\
			ei_end_light();"
			);
		_Script(
			"ei_instance( shaderinstance );\
			ei_element(	light1 );\
			ei_end_instance();"
			);
		return (liqLightHandle)(0);
	}

	void Renderer::transform_(const liqMatrix& transform)
	{

	}
	MStatus Renderer::liqRibLightData_write(const liqRibLightData *lightdata, const structJob &currentJob)
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
		_Script("# Renderer::exportDistantLight()");
		_Script(
			"ei_shader( \"distantlight\", \
			\"intensity\", ToString<liqFloat>(intensity),\
			\"lightcolor\", ToString<liqColor>(color);"
			);

		_Script(
			"ei_light( "+shadertype+" );\
			ei_lightsource(	distantlight, ei_end );\
			ei_transform( transform );\
			ei_end_light();"
			);
		_Script(
			"ei_instance( "+shaderinstance+" );\
			ei_element(	"+shadertype+" );\
			ei_end_instance();"
			);

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
		const liqMatrix &transform)
	{
		_Script("# Renderer::exportPointLight()");
		_Script(
			"ei_shader( \"pointlight\", \
			\"intensity\", ToString<liqFloat>(intensity),\
			\"lightcolor\", ToString<liqColor>(color);"
			);

		_Script(
			"ei_light( "+shadertype+" );\
				ei_lightsource(	pointlight, ei_end );\
				ei_transform( transform );\
			ei_end_light();"
			);
		_Script(
			"ei_instance( "+shaderinstance+" );\
				ei_element(	"+shadertype+" );\
		   ei_end_instance();"
		   );
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
		const liqMatrix &transform)
	{
		_Script("# Renderer::exportSpotLight()");
		_Script(
			"ei_shader( \"spotlight\", \
			\"intensity\", ToString<liqFloat>(intensity),\
			\"lightcolor\", ToString<liqColor>(color);"
			);

		_Script(
			"ei_light( "+shadertype+" );\
									ei_lightsource(	spotlight, ei_end );\
									ei_transform( transform );\
									ei_end_light();"
									);
		_Script(
			"ei_instance( "+shaderinstance+" );\
										   ei_element(	"+shadertype+" );\
										   ei_end_instance();"
										   );
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
		const liqMatrix &transform)
	{
		_Script("# Renderer::exportAreaLight()");
		_Script(
			"ei_shader( \"arealight\", \
			\"intensity\", ToString<liqFloat>(intensity),\
			\"lightcolor\", ToString<liqColor>(color);"
			);

		_Script(
			"ei_light( "+shadertype+" );\
									ei_lightsource(	arealight, ei_end );\
									ei_transform( transform );\
									ei_end_light();"
									);
		_Script(
			"ei_instance( "+shaderinstance+" );\
										   ei_element(	"+shadertype+" );\
										   ei_end_instance();"
										   );
		return (liqLightHandle)(0);
	}
}
