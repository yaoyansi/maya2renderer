#include "ercall.h"
#include "../log/prerequest_std.h"

#define _USE_ER_LIB_
#ifdef _USE_ER_LIB_
#	include <core/include/eray_core.h>
// set $(ER_ROOT)=E:\dev\render\renderer\elvishrayrenderer\elvishrayrenderer
// then add  $(ER_ROOT)/debug/lib to the lib path
#	pragma comment( lib, "eray_core.lib" )
#	define _e( _call_ )  _call_ 
#else 
#	define _e( _call_ )  
#endif

#include "er_renderer.h"


#define _s( _log_ ) dummy.get()<< _log_ <<std::endl;



namespace elvishray
{
	extern Renderer dummy;

	//////////////////////////////////////////////////////////////////////////////////
	//	Client application connection:
	void my_ei_set_connection( e_Connection *con )
	{

	}

	//	Network Rendering:
	void my_ei_hosts( const char *host_name, const int port_number, const char *remote_params... ){}
	void my_ei_run_server( const int port_number, const int max_num_clients ){}

	//	Scene Descriptions:
	void my_ei_scene()
	{
		_s("ei_scene()");
		_e(ei_scene());
	}
	void my_ei_end_scene(){}

	//	Shader Definitions:
	void my_ei_shader( const char *instance_name,  ... ){}
	// void my_ei_incremental_shader( const char *named_shader, ... ){}


	//	Shader Linking:
	void my_ei_link( const char *filename ){}


	//	Commands:
	void my_ei_verbose( int level ){}
	void my_ei_delete( const char *element_name ){}
	void my_ei_render( const char *root_instgroup, const char *camera_inst, const char *options ){}


	//	Options:
	void my_ei_options( const char *name ){}
	void my_ei_incremental_options( const char *name ){}

	//	Sampling Quality:
	void my_ei_contrast( float r, float g, float b, float a ){}
	void my_ei_samples( int _min, int _max ){}
	void my_ei_bucket_size( int size ){}
	void my_ei_filter( int filter, float size ){}

	//	Tessellation Quality:
	void my_ei_shading_rate( float rate )
	{
		_s("ei_shading_rate("<< rate <<")");
		_e(ei_shading_rate(rate));
	}
	void my_ei_motion_factor( float factor ){}
	void my_ei_max_displace( float dist ){}

	//	Motion Blur:
	void my_ei_shutter( float open, float close ){}
	void my_ei_motion( int type ){}
	void my_ei_motion_segments( int num ){}

	//	Trace Depth:
	void my_ei_trace_depth( int reflect, int refract, int sum ){}

	//	Shadow:
	void my_ei_shadow( int type ){}

	//	Rendering Algorithms:
	void my_ei_trace( int type ){}
	void my_ei_scanline( int type ){}
	void my_ei_hardware( int type ){}
	void my_ei_acceleration( int type ){}
	void my_ei_simd( int type ){}
	void my_ei_bsp_size( int size ){}
	void my_ei_bsp_depth( int depth ){}
	void my_ei_bsp_memory( int size ){}

	//	Feature Disabling:
	void my_ei_lens( int type ){}
	void my_ei_volume( int type ){}
	void my_ei_geometry( int type ){}
	void my_ei_displace( int type ){}
	void my_ei_imager( int type ){}

	//	Caustics:
	void my_ei_caustic( int type ){}
	void my_ei_caustic_photons( int photons ){}
	void my_ei_caustic_accuracy( int samples, float radius ){}
	void my_ei_caustic_scale( float r, float g, float b ){}
	void my_ei_caustic_filter( int filter, float filter_const ){}
	void my_ei_photon_trace_depth( int reflect, int refract, int sum ){}
	void my_ei_photon_decay( float decay ){}

	//	Global Illumination:
	void my_ei_globillum( int type ){}
	void my_ei_globillum_photons( int photons ){}
	void my_ei_globillum_accuracy( int samples, float radius ){}
	void my_ei_globillum_scale( float r, float g, float b ){}
	void my_ei_photonvol_accuracy( int samples, float radius ){}
	void my_ei_finalgather( int type ){}
	void my_ei_finalgather_precompute( int type ){}
	void my_ei_finalgather_accuracy( int rays, int samples, float density, float radius ){}
	void my_ei_finalgather_falloff( int type ){}
	void my_ei_finalgather_falloff( float start, float stop ){}
	void my_ei_finalgather_filter( float size ){}
	void my_ei_finalgather_trace_depth( int reflect, int refract, int diffuse, int sum ){}
	void my_ei_finalgather_scale( float r, float g, float b ){}

	//	Frame Buffer Control:
	void my_ei_exposure( float gain, float gamma ){}
	void my_ei_quantize( float one, float _min, float _max, float dither_amplitude ){}
	void my_ei_frame_buffer( const char *name, int datatype, int interpolation ){}

	//	Miscellaneous:
	void my_ei_face( int type ){}
	void my_ei_memory( int size ){}
	void my_ei_ambient( float r, float g, float b ){}

	void my_ei_end_options(){}


	//	Cameras:
	void my_ei_camera( const char *name ){}
	// void my_ei_incremental_camera( const char *name ){}

	//	Output Statements:
	void my_ei_output( const char *filename, int fileformat, int datatype, ... ){}
	void my_ei_imager( const char *shader_name, ... ){}

	//	Other Camera Statements:
	void my_ei_focal( float distance ){}
	void my_ei_aperture( float aperture ){}
	void my_ei_aspect( float aspect ){}
	void my_ei_resolution( int x, int y ){}
	void my_ei_offset( int x, int y ){}
	void my_ei_window( float xmin, float xmax, float ymin, float ymax ){}
	void my_ei_clip( float hither, float yon ){}
	void my_ei_atmosphere( const char *shader_name, ... ){}
	void my_ei_ambience( const char *shader_name, ... ){}
	void my_ei_lens( const char *shader_name, ... ){}
	void my_ei_frame( int frame, int field ){}
	void my_ei_dof( int type ){}
	void my_ei_dof( float fstop, float fplane ){}

	void my_ei_end_camera(){}


	//	Textures:
	void my_ei_make_texture( const char *picturename, const char *texturename, 
		int swrap, int twrap, int filter, float swidth, float twidth ){}


	//	Materials:
	void my_ei_material( const char *name ){}
	void my_ei_incremental_material( const char *name ){}

	void my_ei_opaque( int type ){}
	void my_ei_surface( const char *shader_name, ... ){}
	void my_ei_displace( const char *shader_name, ... ){}
	void my_ei_shadow( const char *shader_name, ... ){}
	void my_ei_volume( const char *shader_name, ... ){}
	void my_ei_environment( const char *shader_name, ... ){}
	void my_ei_photon( const char *shader_name, ... ){}

	void my_ei_end_material(){}


	//	Lights:
	void my_ei_light( const char *name ){}
	// void my_ei_incremental_light( const char *name ){}

	void my_ei_lightsource( const char *shader_name, ... ){}
	void my_ei_photon_emitter( const char *shader_name, ... ){}
	void my_ei_origin( float x, float y, float z ){}
	void my_ei_direction( float dx, float dy, float dz ){}
	void my_ei_spread( float spread ){}
	void my_ei_energy( float r, float g, float b ){}
	void my_ei_decay( float exp ){}
	void my_ei_shadowmap_resolution( int x, int y ){}
	void my_ei_shadowmap_accuracy( int samples, float softness ){}
	void my_ei_shadowmap_bias( float bias ){}

	//	Light Source Types:
	void my_ei_point(){}
	void my_ei_spot(){}
	void my_ei_direct(){}
	void my_ei_rectangle( float x_0, float y_0, float z_0, float x_1, float y_1, float z_1 ){}
	void my_ei_disc( float x, float y, float z, float radius ){}
	void my_ei_sphere( float radius ){}
	void my_ei_cylinder( float x, float y, float z, float radius ){}
	void my_ei_area_object( const char *object_inst ){}
	void my_ei_area_samples( int u_samples, int v_samples, int low_level, int low_u_samples, int low_v_samples ){}

	void my_ei_end_light(){}


	//	Objects:
	void my_ei_object( const char *name ){}
	void my_ei_incremental_object( const char *name ){}

	void my_ei_vector( float x, float y, float z ){}
	void my_ei_vertex( int index ){}
	void my_ei_normal( int index ){}
	void my_ei_derivatives( int dPdu, int dPdv, int d2Pdu2, int d2Pdv2, int d2Pdudv ){}
	void my_ei_motion_vertex( int index ){}
	void my_ei_bake_uv( int index ){}
	void my_ei_variable( int type, const char *name, ... ){}

	void my_ei_triangle( int mtl, int v1, int v2, int v3 ){}
	void my_ei_polygon( int mtl, ... ){}

	void my_ei_approximate( int param, ... ){}

	void my_ei_end_object(){}


	//	Instances:
	void my_ei_instance( const char *name ){}
	// void my_ei_incremental_instance( const char *name ){}

	void my_ei_element( const char *element_name ){}

	void my_ei_visible( int type ){}
	void my_ei_shadowmap( int type ){}
	void my_ei_reflection( int type ){}
	void my_ei_refraction( int type ){}
	void my_ei_transparency( int type ){}
	void my_ei_select( int type ){}

	void my_ei_transform( 
		float t00,float t01,float t02,float t03,
		float t10,float t11,float t12,float t13,
		float t20,float t21,float t22,float t23,
		float t30,float t31,float t32,float t33 
		)
	{
		_s("ei_transform("<< t00<<","<<t01<<","<<t02<<","<<t03<<",   "<<t10<<","<<t11<<","<<t12<<","<<t13<<",   "<<  t20<<","<<t21<<","<<t22<<","<<t23<<",   "<<  t30<<","<<t31<<","<<t32<<","<<t33 <<")");
		_e( ei_transform(t00,t01,t02,t03,t10,t11,t12,t13,t20,t21,t22,t23,t30,t31,t32,t33));
	}
	void my_ei_motion_transform( 
		float t00,float t01,float t02,float t03,
		float t10,float t11,float t12,float t13,
		float t20,float t21,float t22,float t23,
		float t30,float t31,float t32,float t33
		){}
	void my_ei_set_transform(
		float t00,float t01,float t02,float t03,
		float t10,float t11,float t12,float t13,
		float t20,float t21,float t22,float t23,
		float t30,float t31,float t32,float t33
		){}
	void my_ei_set_motion_transform( 
		float t00,float t01,float t02,float t03,
		float t10,float t11,float t12,float t13,
		float t20,float t21,float t22,float t23,
		float t30,float t31,float t32,float t33
		){}

	void my_ei_set_material( const char *material_name, ... ){}

	void my_ei_end_instance(){}


	//	Instance Groups:
	void my_ei_instgroup( const char *name ){}
	void my_ei_incremental_instgroup( const char *name ){}

	void my_ei_init_instance( const char *name ){}
	void my_ei_illuminate( const char *light_inst, int type ){}

	void my_ei_end_instgroup(){}
	//
	//
void my_ei_shader(const char* shadertype, const char* param0, const float v)
{

}
 
}