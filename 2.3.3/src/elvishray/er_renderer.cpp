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
#include "ercall.h"
#include "MayaConnection.h"
#include "er_groupmgr.h"

namespace elvishray
{
#define _s( _log_ ) dummy.get()<< _log_ <<std::endl;

#define _t( _log_or_call_ )  \
	if(0) dummy.get()<< _log_or_call_ <<std::endl; \
	else  dummy.get()<< #_log_or_call_ <<";"<<std::endl; _log_or_call_ ; 

// #define _S(_call_)  \
// 	dummy.get()<<#_call_<<std::endl; my_##_call_ ; 
#define _S(_call_)  my_##_call_ ; 

	//static const char *LogName="d:/script.er";
	/*static const*/ Renderer dummy; 
	// the only goal to define a Renderer variable is 
	// to run the constructor to register this renderer.
	static const char *RendererName="elvishray";

	Renderer::Renderer()
	{
		m_groupMgr = new GroupMgr(this);

		liquid::RendererMgr::getInstancePtr()->registerRenderer(
			RendererName, this
			);
	}
	//
	Renderer::~Renderer()
	{
		delete m_groupMgr; 
		m_groupMgr = 0;

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
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportShadowPassLight()");
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "shadowlight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light( sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance(  shaderinstance.c_str() ) );
		_S( ei_element(	 sLightObjectName.c_str() ) );
		_S( ei_end_instance() );

		return (liqLightHandle)(0);
	}
	liqLightHandle Renderer::exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &t)
	{
		_s("\n// Renderer::exportAmbientLight()");
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "ambientlight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance(  shaderinstance.c_str()) );
		_S( ei_element(	 sLightObjectName.c_str()));
		_S( ei_end_instance() );

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
		const liqMatrix &t)
	{
		_s("// Renderer::exportDistantLight()");
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "distantlight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light( sLightObjectName.c_str()) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstance.c_str()) );
		_S( ei_element(	sLightObjectName.c_str()) );
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
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "pointlight") ); 
		_S( ei_shader_param_vector("lightcolor", 1.0f, 1.0f, 1.0f ) );
		_S( ei_shader_param_scalar("intensity", i_intensity) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str()  ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstance.c_str() ) );
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
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "spotlight") ); 
		_S( ei_shader_param_vector("lightcolor", 1.0f, 1.0f, 1.0f ) ); 
		_S( ei_shader_param_scalar("intensity", i_intensity ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light( sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str()  ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2] ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstance.c_str() ) );
		_S( ei_element(	sLightObjectName.c_str() ) );
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
		std::string sShaderInstanceName(shaderinstance+"_shader");
		_S( ei_shader( sShaderInstanceName.c_str() ) ); 
		_S( ei_shader_param_string("desc", "arealight") ); 
		_S( ei_shader_param_scalar("intensity", 3.0 ) );
		_S( ei_end_shader() );

		std::string sLightObjectName(shaderinstance+"_object");
		_S( ei_light(  sLightObjectName.c_str() ) );
		_S( ei_add_light(	sShaderInstanceName.c_str() ) );
		_S( ei_origin( t[3][0],t[3][1],t[3][2]  ) );
		_S( ei_end_light() );

		_S( ei_instance( shaderinstance.c_str() ) );
		_S( ei_element(	 sLightObjectName.c_str() ) );
		_S( ei_end_instance() );

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
		//
		liqRibNodePtr ribNode = liqRibTranslator::getInstancePtr()->htable->find(
			mesh->objDagPath.fullPathName(), 
			mesh->objDagPath,
			MRT_Unknown
			);
		assert( ribNode!=0 );
		assert( ribNode->path().fullPathName() == mesh->objDagPath.fullPathName() );
	
		liqShader& shader = 
			liqShaderFactory::instance().getShader( ribNode->assignedShader.object() );
		//shader.name;//liquidSurface1
		//shader.file;//"your_shader_dir/test_type2"
		//
		MStatus status;
		MFnMesh fnMesh(mesh->objDagPath, &status);
		IfMErrorWarn(status);

		MFloatPointArray position;
		IfMErrorWarn(fnMesh.getPoints (position, MSpace::kWorld));

		MIntArray triangleCounts,triangleVertices;
		IfMErrorWarn(fnMesh.getTriangles(triangleCounts, triangleVertices));

		// geometry data (shape)
		_s("\n//############################### mesh #");
		std::string sMeshObjectName(std::string(mesh->getName())+"_object");
		_S( ei_object( sMeshObjectName.c_str(), "poly" ) );
		_s("//### vertex positions");
		_s("{");
		_s("eiTag tag;"); eiTag tag;
		_s("tag = "); tag =   
		_S( ei_tab(EI_DATA_TYPE_VECTOR, 1024) ); //_s(";");
		_s("//tag="<<tag);
		_S( ei_pos_list( tag ) );//_s( "ei_pos_list( tag );" );
		for(size_t i=0; i<position.length(); ++i)
		{
			_S( ei_tab_add_vector( position[i][0],position[i][1],position[i][2] ) );
		}
		_S( ei_end_tab() );
// 		_s("//### vertex color");
// 		for(int i=0; i<position.length(); i++)
// 		{
// 			_S( ei_vertex(i) );
// 			//_S( ei_variable_color( "Cs", color( 1.0f, 0.0f, 1.0f ) ) );
// 		}
		_s("//### triangles");
		_s("tag = "); tag = 
		_S( ei_tab(EI_DATA_TYPE_INDEX, 1024) ); //_s(";");
		_s("//tag="<<tag);
		_S( ei_triangle_list( tag ) );//_s( "ei_triangle_list( tag );" );
		for(size_t i=0; i<triangleVertices.length(); i=i+3)
		{
			_S( ei_tab_add_index(triangleVertices[i])); 
			_S( ei_tab_add_index(triangleVertices[i+1])); 
			_S( ei_tab_add_index(triangleVertices[i+2])); 
		}
		_S( ei_end_tab() );
		_s("}");
		_S( ei_end_object() );
		_s("\n//--------------------------");
		_S( ei_instance( mesh->getName() ) );//transform
 		//_S( ei_visible( on ) );
// 		ei_shadow( on );
// 		ei_trace( on );
		{
		//_S( ei_add_material( shader.getName().c_str() ) );
		
		// add test shader,must removed when the shader export is done.
		_S( ei_add_material("phong_mtl_for_test") );
		}
		_S( ei_element( sMeshObjectName.c_str() ) );
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
		int bMotion = (ribNode->doDef || ribNode->doMotion);
		_S( ei_motion( bMotion ) );

		_S( ei_end_instance() );
		_s("//");
		//
		m_groupMgr->addObjectInstance( currentJob.name.asChar(), mesh->getName() );//_S( ei_init_instance( currentJob.camera[0].name.asChar() ) );

	}
	//
	void Renderer::ribPrologue_comment(const char* liqversion, 
		const char* scenename, const char* user, const time_t &now)
	{
		pretest();
		// general info for traceability
		//
		_s("//    Generated by Liquid v"<<liqversion );
		_s("//    Scene : "<< scenename );

		if( user )
			_s("//    User  : "<< user );

		_s("//    Time  : "<< ctime(&now) );

	}
	//
	MStatus Renderer::ribPrologue_begin(const structJob& currentJob)
	{
		if( false )
		{
			_S( ei_make_texture( currentJob.imageName.asChar(), currentJob.texName.asChar() , EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f ) );
		}	
		_s("//### SCENE BEGIN ###");
		CONTEXT =_S( ei_create_context() );

		_S( ei_context(CONTEXT) );

		_S( ei_connection(&(MayaConnection::getInstance()->connection.base)) );

		_S( ei_verbose(	EI_VERBOSE_ALL ) );
		_S( ei_link( "eiIMG" ) );
		_S( ei_link( "eiSHADER" ) );

		m_root_group = currentJob.name.asChar();
		m_groupMgr->createGroup(m_root_group);//

		dummyPhongShader();//for test only, must be removed when the shader export is done.

		return MS::kSuccess;
	}
	MStatus Renderer::ribPrologue_end(const structJob& currentJob)
	{ 
		cookInstanceGroup();

		assert(!m_root_group.empty());
		assert(currentJob.camera[0].name.length());
		assert(!m_option.empty());

		// start render
		if (MayaConnection::getInstance()->startRender( currentJob.width, currentJob.height, false) != MS::kSuccess)
		{
			_s( "//MayaConnection: error occured in startRender." );
			return MS::kFailure;
		}

		_S( ei_render( m_root_group.c_str(), currentJob.camera[0].name.asChar(), m_option.c_str() ) );
		//ei_render( "world",	"caminst1",	"opt" );		
		//dummy.get()<< "ei_render(\""<<m_root_group<<"\", \""<<currentJob.camera[0].name<<"\", \""<<m_option<<"\");"<<std::endl;
		//ei_render( m_root_group.c_str(), currentJob.camera[0].name.asChar(), m_option.c_str() );

		
		_S( ei_delete_context(CONTEXT) );

		// end render
		if (MayaConnection::getInstance()->endRender() != MS::kSuccess)
		{
			_s( "//MayaConnection: error occured in endRender." );
			MayaConnection::delInstance();
			return MS::kFailure;
		}
		MayaConnection::delInstance();

		return MS::kSuccess;
	}
	//
	MStatus Renderer::ribPrologue_options(const structJob& currentJob)
	{
		_s("\n//############################### option #");
		std::string tmp( currentJob.path.fullPathName().asChar() );//_s( (MString("// current job path = ")+).asChar() );

		m_option = std::string(currentJob.name.asChar()) + "_option";
		_S( ei_options( m_option.c_str() ) );
		//ei_incremental_options( const char *name );

		//	Sampling Quality:
		_S( ei_contrast(  0.05f, 0.05f, 0.05f, 0.05f ) );
		if( currentJob.isShadow ){
			_S( ei_samples( currentJob.shadowPixelSamples, currentJob.shadowPixelSamples ) );
			_S( ei_filter( EI_FILTER_BOX, 1 ) );
			//_S( ei_shading_rate( currentJob.shadingRateFactor ) );

		}else{
			_S( ei_samples(0,2) );//_S("ei_Samples("<< liqglo.pixelSamples<<","<<liqglo.pixelSamples<<");");//4,4
			_S( ei_filter( EI_FILTER_GAUSSIAN, 3.0f ) );
			//_S( ei_shading_rate( liqglo.shadingRate ) );
		}
//		_S("ei_bucket_Size( int size );");
		

		//	Tessellation Quality:
// 		_S("ei_Shading_rate( float rate );");
// 		_S("ei_motion_factor( float factor );");
// 		_S("ei_max_displace( float dist );");

		//	Motion Blur:
//		_S("ei_Shutter( float open, float close );");
		//_S( ei_motion( (liqglo.liqglo_doMotion? 1:0) ) );
//		_S("ei_motion_Segments( int num );");

		//	Trace Depth:
		_S( ei_trace_depth(	4,4,4  ) );

		//	Shadow:
//		_S("ei_Shadow( int type );");

		//	Rendering Algorithms:
// 		_S("ei_trace( int type );");
// 		_S("ei_Scanline( int type );");
// 		_S("ei_hardware( int type );");
// 		_S("ei_acceleration( int type );");
// 		_S("ei_Simd( int type );");
// 		_S("ei_bsp_Size( int size );");
// 		_S("ei_bsp_depth( int depth );");
// 		_S("ei_bsp_memory( int size );");

		//	Feature Disabling:
// 		_S("ei_lens( int type );");
// 		_S( ei_volume( name, ei_end );");
// 		_S("ei_geometry( int type );");
// 		_S( ei_displace( name, ei_end ) );
// 		_S("ei_imager( name , ei_end);");
// 		_S("ei_imager( type );");
		//	Caustics:
// 		_S("ei_caustic( int type );");
// 		_S("ei_caustic_photons( int photons );");
// 		_S("ei_caustic_accuracy( int samples, float radius );");
// 		_S("ei_caustic_Scale( float r, float g, float b );");
// 		_S("ei_caustic_filter( int filter, float filter_const );");
// 		_S("ei_photon_trace_depth( int reflect, int refract, int sum );");
// 		_S("ei_photon_decay( float decay );");
// 
		//	Global Illumination:
// 		_S("ei_globillum( int type );");
// 		_S("ei_globillum_photons( int photons );");
// 		_S("ei_globillum_accuracy( int samples, float radius );");
// 		_S("ei_globillum_Scale( float r, float g, float b );");
// 		_S("ei_photonvol_accuracy( int samples, float radius );");
// 		_S("ei_finalgather( int type );");
// 		_S("ei_finalgather_precompute( int type );");
// 		_S("ei_finalgather_accuracy( int rays, int samples, float density, float radius );");
// 		_S("ei_finalgather_falloff( int type );");
// 		_S("ei_finalgather_falloff( float start, float stop );");
// 		_S("ei_finalgather_filter( float size );");
// 		_S("ei_finalgather_trace_depth( int reflect, int refract, int diffuse, int sum );");
// 		_S("ei_finalgather_Scale( float r, float g, float b );");

		//	Frame Buffer Control:
// 		_S("ei_exposure( float gain, float gamma );");
// 		_S("ei_quantize( float one, float _min, float _max, float dither_amplitude );");
// 		_S("ei_frame_buffer( const char *name, int datatype, int interpolation );");

		//	Miscellaneous:
		_S( ei_face( EI_FACE_BOTH ) );
//		_S( ei_memory( int size ) );
		//_S( ei_ambient( 0.12f, 0.13f, 0.05f ) );

		_S( ei_end_options() );

		return MStatus::kSuccess;
	}
	//
	MStatus Renderer::framePrologue(long lframe, const structJob &currentJob)
	{
		framePrologue_camera(lframe, currentJob);

		return MStatus::kSuccess;
	}
	MStatus Renderer::framePrologue_camera(long lframe, const structJob &currentJob)
	{
		MStatus status;
		MFnCamera fnCamera(currentJob.path, &status);
		IfMErrorWarn(status);

		//
		float focal;
		float aperture;
		float aspect;
		float width=currentJob.width, height=currentJob.height;

// 		// use liquid settings
// 		focal = currentJob.camera[0].focalLength;
// 		aperture = 2.0 * focal * tan(currentJob.camera[0].hFOV/2.0);
// 		aspect = currentJob.aspectRatio;
// 		_s("// liquid settings: focal="<<focal <<", aperture = "<<aperture<<", aspect="<<aspect );
// 		//e.g. focal=3.5, aperture = 2.7, aspect=1
		// use maya settings
		//NOTE: we will caculate these setting from structJob data.[yaoyansi]
		focal = fnCamera.focalLength(&status);
		IfMErrorWarn(status);
		double horizontalFOV,verticalFOV;
		fnCamera.getPortFieldOfView(width, height, horizontalFOV,verticalFOV);
		aperture = 2.0f * focal * tan(horizontalFOV /2.0f);
		aspect = aperture / (2.0f * focal * tan(verticalFOV / 2.0f));
		_s("// maya settings: focal="<<focal <<", aperture = "<<aperture<<", aspect="<<aspect );
		//e.g. focal=35, aperture = 36, aspect=1.33333.

		//get camera transform matrix
		//currentJob.camera[0].mat.get( m ) );
		MObject transformNode = currentJob.path.transform(&status );
		IfMErrorWarn(status);
		MFnDagNode transform (transformNode, &status);
		IfMErrorWarn(status);
		MTransformationMatrix   m0(transform.transformationMatrix());
		RtMatrix m;		
		IfMErrorWarn(m0.asMatrix().get(m));

		_s("\n//############################### camera #");
		std::string sCameraObjectName(std::string(currentJob.camera[0].name.asChar())+"_object");
		_S( ei_camera( sCameraObjectName.c_str() ) );
			//_S( ei_frame( lframe, off ) );
	 		if(currentJob.imageName.length()!=0){
	 			_S( ei_output( currentJob.imageName.asChar(), "bmp", EI_IMG_DATA_RGB ) );
				//_S( ei_output( "d:/_cameraShape1.0001.bmp", "bmp", EI_IMG_DATA_RGB ) );
				_S( ei_output_variable("color", EI_DATA_TYPE_VECTOR));
				_S( ei_end_output());
			}
			_S( ei_focal( focal ) );
			_S( ei_aperture( aperture ) );
			_S( ei_aspect( aspect ) );
			if( currentJob.isShadow == false && liqglo.liqglo_rotateCamera  == true ) {
				_S( ei_resolution(height, width) );
			}else{ 
				_S( ei_resolution(width, height) );
			}

			_S( ei_clip( currentJob.camera[0].neardb, currentJob.camera[0].fardb) );
			if(  liqglo.doDof && !currentJob.isShadow  )
			{
				//_S( ei_dof( on ) );
				//_S( ei_dof( currentJob.camera[0].fStop, focal ) );
			}
		_S( ei_end_camera() );
		_s("//----------------------------------");
		_S( ei_instance( currentJob.camera[0].name.asChar()	) );
			_S( ei_element(	sCameraObjectName.c_str() ) );
			_S( ei_transform( m[0][0], m[0][1], m[0][2], m[0][3],   m[1][0], m[1][1], m[1][2], m[1][3],   m[2][0], m[2][1], m[2][2], m[2][3],   m[3][0], m[3][1], m[3][2], m[3][3] ) );
			//_S( ei_transform(  1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  -1.95384,-2.76373,16.1852, 1.0f ) );
		_S( ei_end_instance() );
		_s("//");		
		m_groupMgr->addObjectInstance(currentJob.name.asChar(), currentJob.camera[0].name.asChar());//_S( ei_init_instance( currentJob.camera[0].name.asChar() ) );

		return MStatus::kSuccess;
	}
	//
	MStatus Renderer::frameEpilogue(const long scanTime)
	{
		return MStatus::kSuccess;
	}
	//
	MStatus Renderer::doTextures(const std::vector<structJob> &txtList_)
	{
		return MStatus::kSuccess;
	}
	MStatus Renderer::doShadows(const std::vector<structJob> &shadowList_)
	{
		return MStatus::kSuccess;
	}
	MStatus Renderer::doRenderView()
	{
		return MStatus::kSuccess;
	}
	MStatus Renderer::renderAll_local(const structJob& currentJob____)
	{
		return MStatus::kSuccess;
	}
	MStatus Renderer::renderAll_remote(const structJob& currentJob____)
	{
		return MStatus::kSuccess;
	}
	void Renderer::cookInstanceGroup()
	{
		std::map<GroupID, Group>::iterator group_i = m_groupMgr->groups.begin();
		std::map<GroupID, Group>::iterator group_e = m_groupMgr->groups.end();
		for(; group_i!=group_e; ++group_i)
		{
			//each group
			_S( ei_instgroup( group_i->first.name.c_str() ) );// not id
			
			Group &group = group_i->second;

			//ei_init_instance( all light )
			LightNames lights = group.gatherLights();
			LightNames::iterator light_i = lights.begin();
			LightNames::iterator light_e = lights.end();
			if(lights.empty())
			{
				_s("//[warning]: light links are default and not output here, you must edit light links in Maya.")
			}else{
				for(; light_i!=light_e; ++light_i)
				{
					_S( ei_add_instance( light_i->c_str()) );	
				}
			}
			


			//
			std::map<MeshName, LightNames>::iterator mesh_i 
				= group.lightlink.begin();
			std::map<MeshName, LightNames>::iterator mesh_e 
				= group.lightlink.end();
			for(; mesh_i!=mesh_e; ++mesh_i)
			{
				LightNames::iterator light_i = mesh_i->second.begin();
				LightNames::iterator light_e = mesh_i->second.end();
				for(; light_i!=light_e; ++light_i)// has light link
				{
					//_S( ei_illuminate( light_i->c_str(), on ) );//removed in new eiAPI
				}

				// init object
				_S( ei_add_instance( mesh_i->first.c_str() ) );
				_s("\n");
			}

			_S( ei_end_instgroup() );
		}

	}
	void Renderer::shader_transformBegin(const liqString  shaderSpace)
	{

	}
	void Renderer::shader_transformEnd(const liqString  shaderSpace)
	{

	}
	void Renderer::shader_surface(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		//_s( "// shader_surface("<<shader.getShaderFileName()<<","<<", ...)" );//e.g."your_shader_dir/test_type2"
		_s( "// shader_surface("<<shader.getName()<<","<<", ...)" );//e.g."lambert1", or "liquidSurface1"

		
		size_t parameterNum =  tokenPointerArray.size() - 1;
		for(size_t i=0; i<parameterNum; ++i)
		{
// 			_s("//- "
// 				<<const_cast<liqTokenPointer*>(&tokenPointerArray[i])->
// 				getDetailedTokenName()<<","//uniform float intensity
// 				<<tokenPointerArray[i].getDetailType()<<","
// 				<<"//tokenPointerArray[i].getTokenFloatArray()"<<","
// 				<<"//[error]tokenPointerArray[i].getTokenString()"<<","
// 				<<tokenPointerArray[i].getTokenName()<<","//intensity,
// 				<<tokenPointerArray[i].getParameterType()<<","//rFloat,
// 				<<tokenPointerArray[i].getRiDeclare()<<","//uniform float,
// 				);
// 			_s("// "<<tokenPointerArray[i].getTokenName());
			liqTokenPointer* vp = const_cast< liqTokenPointer* >( &tokenPointerArray[i] );
			switch( tokenPointerArray[i].getParameterType() )
			{
			case rFloat:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]);
				}
				break;
			case rPoint: case rVector: case rNormal: case rColor:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]<<","<<v[1]<<","<<v[2]);
				}
				break;
			case rString: case rShader:
				{
					const std::string &v = vp->getTokenString();
					_s("//     "<<v);
				}
				break; 
			case rHpoint:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]);
				}
				break;
			case rMatrix:
				{
					const liqFloat *v = vp->getTokenFloatArray();
					_s("//     "
						<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]
						<<v[4]<<","<<v[5]<<","<<v[6]<<","<<v[7]
						<<v[8]<<","<<v[9]<<","<<v[10]<<","<<v[11]
						<<v[12]<<","<<v[13]<<","<<v[14]<<","<<v[15]
					);
				}
				;break;
			default :
				assert(0);
			}
		}//for
		const std::string shaderobject(shader.getName()+"_object");
		_S( ei_shader( shaderobject.c_str() ));
		_S( ei_shader_param_string("desc", "plastic") );
		//_S( ei_shader_param_vector("Ka", 1.0f, 1.0f, 1.0f) ); 
		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) ); 
		_S( ei_shader_param_scalar("Ks", 1.0f) );
		_S( ei_shader_param_scalar("roughness", 0.2f ) );
		_S( ei_end_shader() );

		_S( ei_shader("opaque_shadow"));
		_S( ei_shader_param_string("desc", "opaque"));
		_S( ei_end_shader());

		_S( ei_material( shader.getName().c_str() ) );
		_S( ei_add_surface(	shaderobject.c_str() ) );
		//_S( ei_shadow( "opaque_shadow" ) );
		_S( ei_end_material() );
	}
	liqLightHandle Renderer::shader_light(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_light("<<shader.getName()<<","<<", ...)" );

		return (liqLightHandle)0;	
	}
	void Renderer::shader_displacement(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_displacement("<<shader.getName()<<","<<", ...)" );	 
	}
	void Renderer::shader_volume(
		const liqShader &shader,
		const std::vector<liqTokenPointer> &tokenPointerArray
	)
	{
		_s( "// shader_volume("<<shader.getName()<<","<<", ...)" );	
	}

	void Renderer::exportLightLinks(
		const structJob &currentJob__,
		const liqRibNodePtr mesh, 
		const liqRibNodePtr light,
		const bool bIlluminateByDefault)
	{
		m_groupMgr->addLightLink(currentJob__.name.asChar(), 
			mesh->object(0)->getDataPtr()->getName(),
			light->object(0)->getDataPtr()->getName()
			);//_S( ei_init_instance( mesh->getName() ) );
	}
	void Renderer::dummyPhongShader()
	{
		_s("//----------------phong_shader_for_test begin---");
		_S( ei_shader("phong_shader_for_test") );
		_S( ei_shader_param_string("desc", "plastic") );
		_S( ei_shader_param_vector("Cs", 1.0f, 0.2f, 0.3f) );
		_S( ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f) );
		_S( ei_shader_param_scalar("Ks", 1.0f) );
		_S( ei_shader_param_scalar("roughness", 0.2f) );
		_S( ei_end_shader() );

		_S( ei_shader("opaque_shadow_for_test") );
		_S( ei_shader_param_string("desc", "opaque") );
		_S( ei_end_shader() );

		_S( ei_material("phong_mtl_for_test") );
		_S( ei_add_surface("phong_shader_for_test") );
		_S( ei_add_shadow("opaque_shadow_for_test") );
		_S( ei_end_material() );
		_s("//----------------phong_shader_for_test end ---");
	}
	void Renderer::pretest()
	{
		if( !fopen("manager.ini","r") )
		{
			_s("//[ERROR] manager.ini is not found. Please copy manager.ini to MayaRoot/bin/");
			_s("//[Warnning]Make sure searchpath is set to the directory which contains eiIMG.dll and eiSHADER.dll.");
			_s("//e.g. add the following line to manager.ini");
			_s("//searchpath E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/src/elvishray/dependences");
			assert(0&&"[ERROR]manager.ini is not found. Please copy manager.ini to MayaRoot/bin/." 
				"Make sure searchpath is set to the directory which contains eiIMG.dll and eiSHADER.dll.");
		}
	}
}//namespace
