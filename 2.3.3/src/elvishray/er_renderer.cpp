#include "er_renderer.h"

#include "boost/format.hpp"

// Maya headers
#include "../log/prerequest_maya.h"
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
#include "../log/mayacheck.h"

namespace elvishray
{
	#define _s(_log_) dummy.get()<< _log_ <<std::endl;

	//static const char *LogName="d:/script.er";
	static /*const*/ Renderer dummy; 
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

		_s("\n//worldPrologue");

		if( true )
		{
			_s("ei_make_texture(\"d:\\lunatexmap.bmp\", \"d:\\lunatexmap.tex\", EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f );");
		}

		return MS::kSuccess;
	}
	//
	MStatus Renderer::worldEpilogue()
	{
		_s("\n//Renderer::worldEpilogue()");

		return MS::kSuccess;
	}
	//
	MStatus Renderer::exportLight(const liqRibNodePtr& ribNode, const structJob &currentJob)
	{
		RtString RibNodeName = getLiquidRibName( ribNode->name.asChar() );
		_s("\n// Renderer::exportLight(\""+std::string(RibNodeName)+"\");");
		
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
		_s("\n// Renderer::exportShadowPassLight()");
		_s("ei_shader( \"shadowlight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	shadowlight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "<<shaderinstance<<" );");
		_s("ei_element(	"<<shadertype<<" );");
		_s("ei_end_instance();");

		return (liqLightHandle)(0);
	}
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &transform)
	{
		_s("\n// Renderer::exportAmbientLight()");
		_s("ei_shader( \"ambientlight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	ambientlight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "<<shaderinstance<<" );");
		_s("ei_element(	"<<shadertype<<" );");
		_s("ei_end_instance();");

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
		_s("// Renderer::exportDistantLight()");
		_s("ei_shader( \"distantlight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	distantlight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "<<shaderinstance<<" );");
		_s("ei_element(	"<<shadertype<<" );");
		_s("ei_end_instance();");

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
		_s("\n// Renderer::exportPointLight()");
		_s("ei_shader( \"pointlight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	pointlight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "<<shaderinstance<<" );");
		_s("ei_element(	"<<shadertype<<" );");
		_s("ei_end_instance();");

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
		_s("\n// Renderer::exportSpotLight()");
		_s("ei_shader( \"spotlight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	spotlight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "<<shaderinstance<<" );");
		_s("ei_element(	"<<shadertype<<" );");
		_s("ei_end_instance();");

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
		_s("\n// Renderer::exportAreaLight()");
		_s( "ei_shader( \"arealight\", ");
		_s("           \"intensity\", ToString<liqFloat>(intensity),");
		_s("           \"lightcolor\", ToString<liqColor>(color)");
		_s(");");

		_s("ei_light( "<<shadertype<<" );");
		_s("ei_lightsource(	arealight, ei_end );");
		_s("ei_transform("<< boost::format("%f,%f,%f,%f,") %transform[0][0]%transform[0][1]%transform[0][2]%transform[0][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[1][0]%transform[1][1]%transform[1][2]%transform[1][3]);
		_s("             "<< boost::format("%f,%f,%f,%f,") %transform[2][0]%transform[2][1]%transform[2][2]%transform[2][3]);
		_s("             "<< boost::format("%f,%f,%f,%f ") %transform[3][0]%transform[3][1]%transform[3][2]%transform[3][3]);
		_s(");");
		_s("ei_end_light();");

		_s("ei_instance( "+shaderinstance+" );");
		_s("ei_element(	"+shadertype+" );");
		_s("ei_end_instance();");

		return (liqLightHandle)(0);
	}
	//
	void Renderer::exportOneObject(
		const liqRibNodePtr *lightdata, 
		const structJob &currentJob
		)
	{

	}
	void Renderer::exportOneGeometry_Mesh(
		const liqRibMeshData *mesh, 
		const structJob &currentJob
		)
	{
		_s("\n// Renderer::exportOneGeometry_Mesh("<<mesh->getName()<<")");
		MStatus status;
		MFnMesh fnMesh(mesh->objDagPath, &status);
		IfMErrorWarn(status);

		MFloatPointArray position;
		IfMErrorWarn(fnMesh.getPoints (position, MSpace::kWorld));

		MIntArray triangleCounts,triangleVertices;
		IfMErrorWarn(fnMesh.getTriangles(triangleCounts, triangleVertices));

		// geometry data (shape)
		_s("\n");
		_s("ei_object(\""<< mesh->getName()<<"\")");
		_s("//### vertex positions");
		for(size_t i=0; i<position.length(); ++i)
		{
			_s("ei_vector("<<position[i][0]<<","<<position[i][1]<<","<<position[i][2]<<")");
		}
		_s("//### vertex color");
		for(int i=0; i<position.length(); i++)
		{
			_s("ei_vertex("<<i<<")");
			_s("ei_variable( et_color, \"Cs\", color( 0.0f, 0.0f, 0.0f ) )");
		}
		_s("//### triangles");
		for(size_t i=0; i<triangleVertices.length(); i=i+3)
		{
			_s("ei_triangle("
				<<0<<","
				<<triangleVertices[i  ]<<","
				<<triangleVertices[i+1]<<"," 
				<<triangleVertices[i+2]<<")");
		}
		_s("ei_end_object()");

		_s("ei_instance("<<"dummy"<<")");//transform
// 		ei_visible( on );
// 		ei_shadow( on );
// 		ei_trace( on );
//		ei_set_material( "mtl", ei_end );
		_s("ei_element(\""<<mesh->getName()<<"\")");
// 		if( motion_transform )
// 		{
// 			ei_transform( 1.0f, 0.0f, 0.0f, 0.0f, 
// 				0.0f, 1.0f, 0.0f, 0.0f, 
// 				0.0f, 0.0f, 1.0f, 0.0f, 
// 				0.0f, 0.0f, 0.0f, 1.0f );
// 			// 			ei_motion_transform( 1.0f, 0.0f, 0.0f, 0.0f, 
// 			// 				0.0f, 1.0f, 0.0f, 0.0f, 
// 			// 				0.0f, 0.0f, 1.0f, 0.0f, 
// 			// 				2.3f, 2.0f, 3.1f, 1.0f );
// 		}
// 		if( motion_transform || motion_deform )
// 		{
// 			_s("ei_motion( on )");
// 		}
		_s("ei_end_instance();");
	}
	//
	MStatus Renderer::ribPrologue_options(const structJob& currentJob)
	{

		return MStatus::kSuccess;
	}
}//namespace
