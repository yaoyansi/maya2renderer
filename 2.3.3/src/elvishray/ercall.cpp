#include "ercall.h"
#include "er_renderer.h"

#define _USE_ER_LIB_

#ifdef _USE_ER_LIB_
#	include <eiAPI/ei.h>
// set $(ER_ROOT)=E:\dev\render\elvishrender\
// then add  $(ER_ROOT)/build/r990/x86/lib to the lib path
#	pragma comment( lib, "eiAPI.lib" )
#	pragma comment( lib, "eiCORE.lib" )
#	pragma comment( lib, "eiIMG.lib" )
#	pragma comment( lib, "eiSHADER.lib" )
#	define _e( _call_ )  _call_ 
#else 
#	define _e( _call_ )  dummy.get()<< "// "<< #_call_<<" is not called. You should define _USE_ER_LIB_." <<std::endl;
#endif

#define _s( _log_ ) dummy.get()<< _log_ <<";"<<std::endl;



namespace elvishray
{
	extern Renderer dummy;

	//////////////////////////////////////////////////////////////////////////////////
	eiContext *my_ei_create_context()
	{
		_s("eiContext *CONTEXT = ei_create_context()");
#ifdef _USE_ER_LIB_
		return _e( ei_create_context() );
#else
		_e( ei_create_context() );
		return NULL;//dummy value
#endif
	}
	void my_ei_delete_context(eiContext *context)
	{
		_s("ei_delete_context(CONTEXT)");
		_e( ei_delete_context(context) );
	}
	eiContext *my_ei_context(eiContext *context)
	{
		_s("ei_context(CONTEXT)");
#ifdef _USE_ER_LIB_
		return _e( ei_context(context) );
#else
		_e( ei_context(context) );
		return NULL;//dummy value
#endif
	}
	//	Client application connection:
	void my_ei_connection( eiConnection *con )
	{
		_s("//ei_set_connection( &(MayaConnection::getInstance()->connection.base )");
		_e( ei_connection(con) );
	}

	//	Network Rendering:
// 	void my_ei_hosts( const char *host_name, const int port_number, const char *remote_params, ... )
// 	{
// 		_s("ei_hosts( \""<<host_name<<"\", "<<port_number<<", \""<<remote_params<<"\" )");
// 		_e( ei_hosts(host_name, port_number, remote_params) );
// 	}
// 	void my_ei_run_server( const int port_number, const int max_num_clients )
// 	{
// 		_s("ei_run_server( "<<port_number<<","<<max_num_clients<<" )");
// 		_e( ei_run_server(port_number, max_num_clients) );
// 	}

	//	Scene Descriptions:
// 	void my_ei_scene()
// 	{
// 		_s("ei_scene()");
// 		_e( ei_scene());
// 	}
// 	void my_ei_end_scene()
// 	{
// 		_s("ei_end_scene()");
// 		_e( ei_end_scene());
// 	}

	//	Shader Definitions:
// 	void my_ei_shader( const char *instance_name, int end_,  ... )
// 	{
// 		_s("ei_shader(\""<<instance_name<<"\","<< end_<<")");
// 		_e( ei_shader(instance_name, end_));
// 	}
	// void my_ei_incremental_shader( const char *named_shader, ... ){}


	//	Shader Linking:
	void my_ei_link( const char *filename )
	{
		_s("ei_link( \""<<filename<<"\" )");
		_e( ei_link(filename));
	}


	//	Commands:
	void my_ei_verbose( int level )
	{
		_s("ei_verbose( "<<level<<" )");
		_e( ei_verbose(level));
	}
	void my_ei_delete( const char *element_name )
	{
		_s("ei_delete( \""<<element_name<<"\" )");
		_e( ei_delete(element_name));
	}
	void my_ei_render( const char *root_instgroup, const char *camera_inst, const char *options )
	{
		_s("ei_render(\""<<root_instgroup<<"\", \""<<camera_inst<<"\", \""<<options<<"\")");
		_e( ei_render( root_instgroup, camera_inst, options ) );
	}

	eiTag my_ei_tab(const eiInt type, const eiInt items_per_slot)
	{
		_s("ei_tab("<<type<<","<<items_per_slot<<")");
#ifdef _USE_ER_LIB_
		return _e( ei_tab( type, items_per_slot ));
#else
		_e( ei_tab( type, items_per_slot ));
		return NULL;//dummy value
#endif
		
	}
	//void my_ei_tab_add(const void *value);
	//void my_ei_tab_add_int(const eiInt value);
	//void my_ei_tab_add_scalar(const eiScalar value);
	void my_ei_tab_add_vector(const eiScalar x, const eiScalar y, const eiScalar z)
	{
		_s("ei_tab_add_vector("<<x<<","<<y<<","<<z<<")");
		_e( ei_tab_add_vector( x, y, z ));
	}
	//void my_ei_tab_add_vector4(const eiScalar x, const eiScalar y, const eiScalar z, const eiScalar w);
	//void my_ei_tab_add_tag(const eiTag value);
	void my_ei_tab_add_index(const eiIndex value)
	{
		_s("ei_tab_add_index("<<value<<")");
		_e( ei_tab_add_index( value ));
	}
	//void my_ei_tab_add_bool(const eiBool value);
	void my_ei_end_tab()
	{
		_s("ei_end_tab()");
		_e( ei_end_tab());
	}


	//	Options:
	void my_ei_options( const char *name )
	{
		_s("ei_options(\""<<name<<"\")");
		_e( ei_options( name ));
	}

	//	Sampling Quality:
	void my_ei_contrast( float r, float g, float b, float a )
	{
		_s("ei_contrast("<<r<<","<<g<<","<<b<<","<<a<<")");
		_e( ei_contrast(r,g,b,a));
	}
	void my_ei_samples( int _min, int _max )
	{
		_s("ei_samples("<<_min<<","<<_max<<")");
		_e( ei_samples(_min,_max));
	}
	void my_ei_bucket_size( int size )
	{
		_s("ei_bucket_size("<<size<<")");
		_e( ei_bucket_size(size));
	}
	void my_ei_filter( int filter, float size )
	{
		_s("ei_filter("<<filter<<","<<size<<")");
		_e( ei_filter(filter,size));
	}

	//	Tessellation Quality:
// 	void my_ei_shading_rate( float rate )
// 	{
// 		_s("ei_shading_rate("<< rate <<")");
// 		_e( ei_shading_rate(rate));
// 	}
// 	void my_ei_motion_factor( float factor )
// 	{
// 		_s("ei_motion_factor("<<factor<<")");
// 		_e( ei_motion_factor(factor));
// 	}
	void my_ei_max_displace( float dist )
	{
		_s("ei_max_displace("<<dist<<")");
		_e( ei_max_displace(dist));
	}

	//	Motion Blur:
	void my_ei_shutter( float open, float close )
	{
		_s("ei_shutter("<<open<<", "<<close<<")");
		_e( ei_shutter(open, close));
	}
	void my_ei_motion( int type )
	{
		_s("ei_motion("<< type <<")");
		_e( ei_motion(type));
	}
	void my_ei_motion_segments( int num )
	{
		_s("ei_motion_segments("<< num <<")");
		_e( ei_motion_segments(num));
	}

	//	Trace Depth:
	void my_ei_trace_depth( int reflect, int refract, int sum )
	{
		_s("ei_trace_depth("<<reflect<<","<<refract<<","<<sum<<")");
		_e( ei_trace_depth(reflect,refract,sum));
	}

	//	Shadow:
	void my_ei_shadow( int type )
	{
		_s("ei_shadow("<<type<<")");
		_e( ei_shadow(type));
	}

	//	Rendering Algorithms:
// 	void my_ei_trace( int type )
// 	{
// 		_s("ei_trace("<<type<<")");
// 		_e( ei_trace(type));
// 	}
// 	void my_ei_scanline( int type )
// 	{
// 		_s("ei_scanline("<<type<<")");
// 		_e( ei_scanline(type));
// 	}
// 	void my_ei_hardware( int type )
// 	{
// 		_s("ei_hardware("<<type<<")");
// 		_e( ei_hardware(type));
// 	}
	void my_ei_acceleration( int type )
	{
		_s("ei_acceleration("<<type<<")");
		_e( ei_acceleration(type));
	}
// 	void my_ei_simd( int type )
// 	{
// 		_s("ei_simd("<<type<<")");
// 		_e( ei_simd(type));
// 	}
	void my_ei_bsp_size( int size )
	{
		_s("ei_bsp_size("<<size<<")");
		_e( ei_bsp_size(size));
	}
	void my_ei_bsp_depth( int depth )
	{
		_s("ei_bsp_depth("<<depth<<")");
		_e( ei_bsp_depth(depth));
	}
// 	void my_ei_bsp_memory( int size )
// 	{
// 		_s("ei_bsp_memory("<<size<<")");
// 		_e( ei_bsp_memory(size));
// 	}

	//	Feature Disabling:
	void my_ei_lens(eiInt type)
	{
		_s("ei_lens("<<type<<" )");
		_e( ei_lens(type ));
	}
	void my_ei_volume( int type )
	{
		_s("ei_volume("<<type<<")");
		_e( ei_volume(type));
	}
	void my_ei_geometry( int type )
	{
		_s("ei_geometry("<<type<<")");
		_e( ei_geometry(type));
	}
	void my_ei_displace( int type )
	{
		_s("ei_displace("<<type<<")");
		_e( ei_displace(type));
	}
	void my_ei_imager( int type )
	{
		_s("ei_imager("<<type<<")");
		_e( ei_imager(type));
	}

	//	Caustics:
	void my_ei_caustic( int type )
	{
		_s("ei_caustic("<<type<<")");
		_e( ei_caustic(type));
	}
	void my_ei_caustic_photons( int photons )
	{
		_s("ei_caustic_photons("<<photons<<")");
		_e( ei_caustic_photons(photons));
	}
	void my_ei_caustic_accuracy( int samples, float radius )
	{
		_s("ei_caustic_accuracy("<<samples<<","<<radius<<")");
		_e( ei_caustic_accuracy(samples, radius));
	}
	void my_ei_caustic_scale( float r, float g, float b )
	{
		_s("ei_caustic_scale("<<r<<","<<g<<","<<b<<")");
		_e( ei_caustic_scale(r, g, b));
	}
	void my_ei_caustic_filter( int filter, float filter_const )
	{
		_s("ei_caustic_filter("<<filter<<","<<filter_const<<")");
		_e( ei_caustic_filter(filter, filter_const));
	}
	void my_ei_photon_trace_depth( int reflect, int refract, int sum )
	{
		_s("ei_photon_trace_depth("<<reflect<<","<<refract<<","<<sum<<")");
		_e( ei_photon_trace_depth(reflect, refract, sum));
	}
	void my_ei_photon_decay( float decay )
	{
		_s("ei_photon_decay("<<decay<<")");
		_e( ei_photon_decay(decay));
	}
	//	Global Illumination:
	void my_ei_globillum( int type )
	{
		_s("ei_globillum("<<type<<")");
		_e( ei_globillum(type));
	}
	void my_ei_globillum_photons( int photons )
	{
		_s("ei_globillum_photons("<<photons<<")");
		_e( ei_globillum_photons(photons));
	}
	void my_ei_globillum_accuracy( int samples, float radius )
	{
		_s("ei_globillum_accuracy("<<samples<<","<<radius<<")");
		_e( ei_globillum_accuracy(samples, radius));
	}
	void my_ei_globillum_scale( float r, float g, float b )
	{
		_s("ei_globillum_scale("<<r<<","<<g<<","<<b<<")");
		_e( ei_globillum_scale(r, g, b));	
	}
	void my_ei_photonvol_accuracy( int samples, float radius )
	{
		_s("ei_photonvol_accuracy("<<samples<<","<<radius<<")");
		_e( ei_photonvol_accuracy(samples, radius));
	}
	void my_ei_finalgather( int type )	
	{
		_s("ei_finalgather("<<type<<")");
		_e( ei_finalgather(type));
	}
// 	void my_ei_finalgather_precompute( int type )
// 	{
// 		_s("ei_finalgather_precompute("<<type<<")");
// 		_e( ei_finalgather_precompute(type));
// 	}
	void my_ei_finalgather_accuracy( int rays, int samples, float density, float radius )
	{
		_s("ei_finalgather_accuracy("<<rays<<","<<samples<<","<<density<<","<<radius<<")");
		_e( ei_finalgather_accuracy(rays,samples, density, radius));
	}
	void my_ei_finalgather_falloff( int type )
	{
		_s("ei_finalgather_falloff("<<type<<")");
		_e( ei_finalgather_falloff(type));
	}
	void my_ei_finalgather_falloff_range( float start, float stop )
	{
		_s("ei_finalgather_falloff_range("<<start<<","<<stop<<")");
		_e( ei_finalgather_falloff_range(start, stop));
	}
	void my_ei_finalgather_filter( float size )
	{
		_s("ei_finalgather_filter("<<size<<")");
		_e( ei_finalgather_filter(size));
	}
	void my_ei_finalgather_trace_depth( int reflect, int refract, int diffuse, int sum )
	{
		_s("ei_finalgather_trace_depth("<<reflect<<","<<refract<<","<<diffuse<<","<<sum<<")");
		_e( ei_finalgather_trace_depth(reflect,  refract, diffuse, sum));
	}
	void my_ei_finalgather_scale( float r, float g, float b )
	{
		_s("ei_finalgather_scale("<<r<<","<<g<<","<<b<<")");
		_e( ei_finalgather_scale(r,g,b));
	}

	//	Frame Buffer Control:
	void my_ei_exposure( float gain, float gamma )
	{
		_s("ei_exposure("<<gain<<","<<gamma<<")");
		_e( ei_exposure(gain, gamma));
	}
	void my_ei_quantize( float one, float _min, float _max, float dither_amplitude )
	{
		_s("ei_quantize("<<one<<","<<_min<<","<<_max<<","<<dither_amplitude<<")");
		_e( ei_quantize(one,  _min, _max, dither_amplitude));
	}
// 	void my_ei_frame_buffer( const char *name, int datatype, int interpolation )
// 	{
// 		_s("ei_frame_buffer(\""<<name<<"\","<<datatype<<","<<interpolation<<")");
// 		_e( ei_frame_buffer(name, datatype, interpolation));
// 	}

	//	Miscellaneous:
	void my_ei_face( int type )
	{
		_s("ei_face("<< type <<")");
		_e( ei_face(type));
	}
// 	void my_ei_memory( int size )
// 	{
// 		_s("ei_memory("<<size<<")");
// 		_e( ei_memory(size));
// 	}
// 	void my_ei_ambient( float r, float g, float b )
// 	{
// 		_s("ei_ambient("<<r<<","<<g<<","<<b<<")");
// 		_e( ei_ambient(r,g,b));
// 	}

	void my_ei_end_options()
	{
		_s("ei_end_options()");
		_e( ei_end_options());
	}


	//	Cameras:
	void my_ei_camera( const char *name )
	{
		_s("ei_camera(\""<< name <<"\")");
		_e( ei_camera(name));
	}
	// void my_ei_incremental_camera( const char *name ){}

	//	Output Statements:
	void my_ei_output( const char *filename, const char *fileformat, const eiInt datatype)
	{
		_s("ei_output(\""<< filename <<"\",\""<<fileformat<<"\","<<datatype<<")");
		_e( ei_output(filename, fileformat, datatype));
	}

	void my_ei_output_variable(const char *name, const eiInt datatype)
	{
 		_s("ei_output_variable(\""<< name <<"\","<<datatype<<")");
		_e( ei_output_variable(name, datatype));
	}
	void my_ei_end_output()
	{
		_s("ei_end_output()");
		_e( ei_end_output());
	}
 

	//	Other Camera Statements:
	void my_ei_focal( float distance )
	{
		_s("ei_focal("<< distance <<")");
		_e( ei_focal(distance));
	}
	void my_ei_aperture( float aperture )
	{
		_s("ei_aperture("<< aperture <<")");
		_e( ei_aperture(aperture));
	}
	void my_ei_aspect( float aspect )
	{
		_s("ei_aspect("<< aspect <<")");
		_e( ei_aspect(aspect));
	}
	void my_ei_resolution( int x, int y )
	{
		_s("ei_resolution("<< x<<","<<y <<")");
		_e( ei_resolution(x, y));
	}
// 	void my_ei_offset( int x, int y )
// 	{
// 		_s("ei_offset("<< x<<","<<y <<")");
// 		_e( ei_offset(x, y));
// 	}
	void my_ei_window( float xmin, float xmax, float ymin, float ymax )
	{
		_s("ei_window("<< xmin<<","<<xmax<<","<<ymin<<","<<ymax<<")");
		_e( ei_window(xmin, xmax, ymin, ymax ));
	}
	void my_ei_clip( float hither, float yon )
	{
		_s("ei_clip("<<hither<<","<<yon<<")");
		_e( ei_clip(hither,yon));
	}
// 	void my_ei_atmosphere( const char *shader_name, int end_, ... )
// 	{
// 		_s("ei_atmosphere(\""<<shader_name<<"\", "<< end_ <<")");
// 		_e( ei_atmosphere(shader_name, end_));
// 	}
// 	void my_ei_ambience( const char *shader_name,int end_ , ... )
// 	{
// 		_s("ei_ambience(\""<<shader_name<<"\", "<< end_<<")");
// 		_e( ei_ambience(shader_name, end_));
// 	}
// 	void my_ei_frame( int frame, int field )
// 	{
// 		_s("ei_frame("<<frame<<","<<field<<")");
// 		_e( ei_frame(frame,field));
// 	}
// 	void my_ei_dof( int type )
// 	{
// 		_s("ei_dof("<<type<<")");
// 		_e( ei_dof(type));
// 	}
// 	void my_ei_dof( float fstop, float fplane )
// 	{
// 		_s("ei_dof("<<fstop<<","<<fplane<<")");
// 		_e( ei_dof(fstop,fplane));
// 	}

	void my_ei_end_camera()
	{
		_s("ei_end_camera()");
		_e( ei_end_camera());
	}


	//	Textures:
	void my_ei_make_texture( const char *picturename, const char *texturename, 
		int swrap, int twrap, int filter, float swidth, float twidth )
	{
		_s("ei_make_texture(\""<<picturename<<"\", \""<< texturename<<"\","<<swrap<<","<< twrap<<","<<filter<<", "<<swidth<<", "<<twidth<<")");
		_e( ei_make_texture(picturename,  texturename, swrap, twrap, filter, swidth, twidth));
	}


	//	Materials:
	void my_ei_material( const char *name )
	{
		_s("ei_material(\""<<name<<"\")");
		_e( ei_material(name));
	}

	void my_ei_add_surface( const char *shader_name )
	{
		_s("ei_add_surface(\""<<shader_name <<"\")");
		_e( ei_add_surface(shader_name ));
	}
	void my_ei_add_displace( const char *shader_name )
	{
		_s("ei_add_displace(\""<<shader_name <<"\")");
		_e( ei_add_displace(shader_name ));
	}
	void my_ei_add_shadow( const char *shader_name )
	{
		_s("ei_add_shadow(\""<<shader_name <<"\")");
		_e( ei_add_shadow(shader_name ));
	}
	void my_ei_add_volume( const char *shader_name )
	{
		_s("ei_add_volume(\""<<shader_name <<"\")");
		_e( ei_add_volume(shader_name ));
	}
	void my_ei_add_environment( const char *shader_name )
	{
		_s("ei_add_environment(\""<<shader_name <<"\")");
		_e( ei_add_environment(shader_name ));
	}
	void my_ei_add_photon( const char *shader_name )
	{
		_s("ei_add_photon(\""<<shader_name <<"\")");
		_e( ei_add_photon(shader_name ));
	}

	void my_ei_end_material()
	{
		_s("ei_end_material()");
		_e( ei_end_material());
	}


	//	Lights:
	void my_ei_light( const char *name )
	{
		_s("ei_light(\""<<name<<"\")");
		_e( ei_light(name));
	}
	// void my_ei_incremental_light( const char *name ){}

	void my_ei_add_light( const char *shader_name )
	{
		_s("ei_add_light(\""<<shader_name<<"\" )");
		_e( ei_add_light(shader_name));
	}
	void my_ei_origin(eiScalar x, eiScalar y, eiScalar z)
	{
		_s("ei_origin("<<x<<","<<y<<","<<z<<")");
		_e( ei_origin(x,y,z));
	}
// 	void my_ei_photon_emitter( const char *shader_name, int end_, ... )
// 	{
// 		_s("ei_photon_emitter(\""<<shader_name<<"\", "<< end_<<")");
// 		_e( ei_photon_emitter(shader_name, end_));
// 	}
// 	void my_ei_direction( float dx, float dy, float dz )
// 	{
// 		_s("ei_direction( "<<dx<<","<<dy<<","<<dz<<" )");
// 		_e( ei_direction(dx,dy,dz));
// 	}
// 	void my_ei_spread( float spread )
// 	{
// 		_s("ei_spread( "<<spread<<" )");
// 		_e( ei_spread(spread));
// 	}
	void my_ei_energy( float r, float g, float b )
	{
		_s("ei_energy( "<<r<<","<<g<<","<<b<<" )");
		_e( ei_energy(r,g,b));
	}
// 	void my_ei_decay( float exp )
// 	{
// 		_s("ei_decay( "<<exp<<" )");
// 		_e( ei_decay(exp));
// 	}
// 	void my_ei_shadowmap_resolution( int x, int y )
// 	{
// 		_s("ei_shadowmap_resolution( "<<x<<","<<y<<" )");
// 		_e( ei_shadowmap_resolution(x,y));
// 	}
// 	void my_ei_shadowmap_accuracy( int samples, float softness )
// 	{
// 		_s("ei_shadowmap_accuracy( "<<samples<<","<<softness<<" )");
// 		_e( ei_shadowmap_accuracy(samples,softness));
// 	}
// 	void my_ei_shadowmap_bias( float bias )
// 	{
// 		_s("ei_shadowmap_bias( "<<bias<<" )");
// 		_e( ei_shadowmap_bias(bias));
// 	}

	//	Light Source Types:
// 	void my_ei_point()
// 	{
// 		_s("ei_point()");
// 		_e( ei_point());
// 	}
// 	void my_ei_spot(){
// 		_s("ei_spot()");
// 		_e( ei_spot());
// 	}
// 	void my_ei_direct(){
// 		_s("ei_direct()");
// 		_e( ei_direct());
// 	}
// 	void my_ei_rectangle( float x_0, float y_0, float z_0, float x_1, float y_1, float z_1 ){
// 		_s("ei_rectangle("<<x_0<<","<<y_0<<","<<z_0<<","<<x_1<<","<<y_1<<","<<z_1<<" )");
// 		_e( ei_rectangle(x_0,y_0,z_0,x_1,y_1,z_1));
// 	}
// 	void my_ei_disc( float x, float y, float z, float radius ){
// 		_s("ei_disc("<<x<<","<<y<<","<<z<<","<<x<<","<<y<<","<<z<<" )");
// 		_e( ei_disc(x,y,z,radius));
// 	}
// 	void my_ei_sphere( float radius ){
// 		_s("ei_sphere("<<radius<<")");
// 		_e( ei_sphere(radius));
// 	}
// 	void my_ei_cylinder( float x, float y, float z, float radius ){
// 		_s("ei_cylinder("<<x<<","<<y<<","<<z<<","<<x<<","<<y<<","<<z<<" )");
// 		_e( ei_cylinder(x,y,z,radius));
// 	}
// 	void my_ei_area_object( const char *object_inst )
// 	{
// 		_s("ei_area_object(\""<<object_inst<<"\")");
// 		_e( ei_area_object(object_inst));
// 	}
	void my_ei_area_samples( int u_samples, int v_samples, int low_level, int low_u_samples, int low_v_samples )
	{
		_s("ei_area_samples("<<u_samples<<","<<v_samples<<","<<low_level<<","<<low_u_samples<<","<<low_v_samples<<" )");
		_e( ei_area_samples(u_samples,v_samples,low_level,low_u_samples, low_v_samples));
	}

	void my_ei_end_light()
	{
		_s("ei_end_light()");
		_e( ei_end_light());
	}


	//	Objects:
	void my_ei_object( const char *name, const char *type )
	{
		_s("ei_object(\""<< name <<"\",\""<<type<<"\")" ); 
		_e( ei_object(name, type));
	}
	void my_ei_pos_list(const eiTag tab)
	{
		_s("ei_pos_list("<< tab<<")" ); 
		_e( ei_pos_list(tab));
	}
// 	void my_ei_motion_pos_list(const eiTag tab)
// 	{
// 
// 	}
	void my_ei_triangle_list(const eiTag tab)
	{
		_s("ei_triangle_list("<<tab<<")" ); 
		_e( ei_triangle_list(tab));
	}

// 	void my_ei_vector( float x, float y, float z )
// 	{
// 		_s("ei_vector("<<x<<","<<y<<","<<z<<")");
// 		_e( ei_vector(x,y,z));
// 	}
// 	void my_ei_vertex( int index )
// 	{
// 		_s("ei_vertex("<< index <<")" ); 
// 		_e( ei_vertex(index));
// 	}
// 	void my_ei_normal( int index )
// 	{
// 		_s("ei_normal("<< index <<")" ); 
// 		_e( ei_normal(index));
// 	}
// 	void my_ei_derivatives( int dPdu, int dPdv, int d2Pdu2, int d2Pdv2, int d2Pdudv )
// 	{
// 		_s("ei_derivatives("<<dPdu<<","<<dPdv<<","<<d2Pdu2<<","<<d2Pdv2<<","<<d2Pdudv<<" )");
// 		_e( ei_derivatives(dPdu,dPdv,d2Pdu2,d2Pdv2, d2Pdudv));
// 	}
// 	void my_ei_motion_vertex( int index )
// 	{
// 		_s("ei_motion_vertex("<< index <<")" ); 
// 		_e( ei_motion_vertex(index));
// 	}
// 	void my_ei_bake_uv( int index )
// 	{
// 		_s("ei_bake_uv("<< index <<")" ); 
// 		_e( ei_bake_uv(index));
// 	}
	void my_ei_variable(const char *name, const void *value)
	{
		_s("ei_variable(\""<< name<<"\", \""<<value<<"\", ...)" ); 
		_e( ei_variable( name, value));
	}
// 	void my_ei_variable_color( const char *name, const color &c )
// 	{
// 		_s("ei_variable( et_color, \""<<name<<"\", color("<<c.r<<","<<c.g<<","<<c.b<<") )" ); 
// 		_e( ei_variable(et_color, name, c));
// 	}
// 	void my_ei_triangle( int mtl, int v1, int v2, int v3 )
// 	{
// 		_s("ei_triangle("<<mtl<<","<<v1<<","<<v2<<","<<v3<<")"); 
// 		_e( ei_triangle(mtl, v1, v2, v3));
// 	}
// 	void my_ei_polygon( int mtl, ... )
// 	{
// 		_s("ei_polygon("<< mtl <<", ...)" ); 
// 		_e( ei_polygon(mtl));
// 	}
// 
// 	void my_ei_approximate( int param, int end_ , ... )
// 	{
// 		_s("ei_approximate("<< param <<", "<< end_<<")" ); 
// 		_e( ei_approximate(param, end_));
// 	}

	void my_ei_end_object()
	{
		_s("ei_end_object()"); 
		_e( ei_end_object());
	}


	//	Instances:
	void my_ei_instance( const char *name )
	{
		_s("ei_instance(\""<<name<<"\")");
		_e( ei_instance(name));
	}
	// void my_ei_incremental_instance( const char *name ){}

	void my_ei_element( const char *element_name )
	{
		_s("ei_element(\""<<element_name<<"\")");
		_e( ei_element(element_name));
	}

// 	void my_ei_visible( int type )
// 	{
// 		_s("ei_visible( "<<type<<" )");
// 		_e( ei_visible(type));
// 	}
// 	void my_ei_shadowmap( int type )
// 	{
// 		_s("ei_shadowmap("<<type<<")");
// 		_e( ei_shadowmap(type));
// 	}
// 	void my_ei_reflection( int type )
// 	{
// 		_s("ei_reflection("<<type<<")");
// 		_e( ei_reflection(type));
// 	}
// 	void my_ei_refraction( int type )
// 	{
// 		_s("ei_refraction("<<type<<")");
// 		_e( ei_refraction(type));
// 	}
// 	void my_ei_transparency( int type )
// 	{
// 		_s("ei_transparency("<<type<<")");
// 		_e( ei_transparency(type));
// 	}
// 	void my_ei_select( int type )
// 	{
// 		_s("ei_select("<<type<<")");
// 		_e( ei_select(type));
// 	}

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
		)
	{
		_s("ei_motion_transform("<< t00<<","<<t01<<","<<t02<<","<<t03<<",   "<<t10<<","<<t11<<","<<t12<<","<<t13<<",   "<<  t20<<","<<t21<<","<<t22<<","<<t23<<",   "<<  t30<<","<<t31<<","<<t32<<","<<t33 <<")");
		_e( ei_motion_transform(t00,t01,t02,t03,t10,t11,t12,t13,t20,t21,t22,t23,t30,t31,t32,t33));
	}
// 	void my_ei_set_transform(
// 		float t00,float t01,float t02,float t03,
// 		float t10,float t11,float t12,float t13,
// 		float t20,float t21,float t22,float t23,
// 		float t30,float t31,float t32,float t33
// 		)
// 	{
// 		_s("ei_set_transform("<< t00<<","<<t01<<","<<t02<<","<<t03<<",   "<<t10<<","<<t11<<","<<t12<<","<<t13<<",   "<<  t20<<","<<t21<<","<<t22<<","<<t23<<",   "<<  t30<<","<<t31<<","<<t32<<","<<t33 <<")");
// 		_e( ei_set_transform(t00,t01,t02,t03,t10,t11,t12,t13,t20,t21,t22,t23,t30,t31,t32,t33));
// 	}
// 	void my_ei_set_motion_transform( 
// 		float t00,float t01,float t02,float t03,
// 		float t10,float t11,float t12,float t13,
// 		float t20,float t21,float t22,float t23,
// 		float t30,float t31,float t32,float t33
// 		)
// 	{
// 		_s("ei_set_motion_transform("<< t00<<","<<t01<<","<<t02<<","<<t03<<",   "<<t10<<","<<t11<<","<<t12<<","<<t13<<",   "<<  t20<<","<<t21<<","<<t22<<","<<t23<<",   "<<  t30<<","<<t31<<","<<t32<<","<<t33 <<")");
// 		_e( ei_set_motion_transform(t00,t01,t02,t03,t10,t11,t12,t13,t20,t21,t22,t23,t30,t31,t32,t33));
// 	}
	void my_ei_add_material( const char *material_name )
	{
		_s("ei_add_material(\""<<material_name<<"\")");
		_e( ei_add_material(material_name));
	}

	void my_ei_end_instance()
	{
		_s("ei_end_instance()");
		_e( ei_end_instance());
	}


	//	Instance Groups:
	void my_ei_instgroup( const char *name )
	{
		_s("ei_instgroup(\""<<name<<"\")");
		_e( ei_instgroup(name));
	}
// 	void my_ei_incremental_instgroup( const char *name )
// 	{
// 		_s("ei_incremental_instgroup(\""<<name<<"\")");
// 		_e( ei_incremental_instgroup(name));
// 	}

	void my_ei_add_instance( const char *name )
	{
		_s("ei_add_instance(\""<<name<<"\")");
		_e( ei_add_instance(name));
	}
// 	void my_ei_illuminate( const char *light_inst, int type )
// 	{
// 		_s("ei_illuminate(\""<<light_inst<<"\","<<type<<")");
// 		_e( ei_illuminate(light_inst, type));
// 	}

	void my_ei_end_instgroup()
	{
		_s("ei_end_instgroup( )");
		_e( ei_end_instgroup( ));
	}
	//
	//
	void my_ei_shader(const char* instance_name)
	{
		_s("ei_shader(\""<<instance_name<<"\")");
		_e( ei_shader(instance_name) );
	}
	void my_ei_shader_param(
		const char *param_name, 
		const void *param_value)
	{
		_s("ei_shader_param(\""<<param_name<<"\", param_value ) not implemented");
		//_e( ei_shader(shaderInstanceName, shadername, shadertype, param0, ei_var(color(v0x, v0y, v0z)), param1,ei_var(color(v1x, v1y, v1z)), param2,ei_var(v2), param3, ei_var(v3), end_) );

	}
	void my_ei_shader_param_string(
		const char *param_name, 
		const char *param_value)
	{
		_s("ei_shader_param_string(\""<<param_name<<"\",\""<<param_value<<"\")");
		_e( ei_shader_param_string(param_name,param_value));
	}
	void my_ei_shader_param_int(
		const char *param_name, 
		const eiInt param_value)
	{
		_s("ei_shader_param_int(\""<<param_name<<"\","<<param_value<<")");
		_e( ei_shader_param_int(param_name,param_value));
	}
	void my_ei_shader_param_scalar(
		const char *param_name, 
		const eiScalar param_value)
	{
		_s("ei_shader_param_scalar(\""<<param_name<<"\","<<param_value<<")");
		_e( ei_shader_param_scalar(param_name,param_value));
	}
	void my_ei_shader_param_vector(
		const char *param_name, 
		const eiScalar x, const eiScalar y, const eiScalar z)
	{
		_s("ei_shader_param_vector(\""<<param_name<<"\","<<x<<","<<y<<","<<z<<")");
		_e( ei_shader_param_vector(param_name,x,y,z));
	}
	void my_ei_shader_param_vector4(
		const char *param_name, 
		const eiScalar x, const eiScalar y, const eiScalar z, const eiScalar w)
	{
		_s("ei_shader_param_vector4(\""<<param_name<<"\","<<x<<","<<y<<","<<z<<","<<w<<")");
		_e( ei_shader_param_vector4(param_name,x,y,z,w));
	}
	void my_ei_shader_param_tag(
		const char *param_name, 
		const eiTag param_value)
	{
		_s("ei_shader_param_tag(\""<<param_name<<"\","<<param_value<<")");
		_e( ei_shader_param_tag(param_name,param_value));
	}
	void my_ei_shader_param_texture(
		const char *param_name, 
		const char *texture_name)
	{
		_s("ei_shader_param_texture(\""<<param_name<<"\",\""<<texture_name<<"\")");
		_e( ei_shader_param_texture(param_name,texture_name));
	}
	void my_ei_shader_param_index(
		const char *param_name, 
		const eiIndex param_value)
	{
		_s("ei_shader_param_index(\""<<param_name<<"\","<<param_value<<")");
		_e( ei_shader_param_index(param_name,param_value));
	}
	void my_ei_shader_param_bool(
		const char *param_name, 
		const eiBool param_value)
	{
		_s("ei_shader_param_bool(\""<<param_name<<"\","<<param_value<<")");
		_e( ei_shader_param_bool(param_name,param_value));
	}
	void my_ei_shader_link_param(
		const char *param_name, 
		const char *src_shader_name, 
		const char *src_param_name)
	{
		_s("ei_shader_link_param(\""<<param_name<<"\",\""<<src_shader_name<<"\",\""<<src_param_name<<"\")");
		_e( ei_shader_link_param(param_name,src_shader_name,src_param_name));
	}
	void my_ei_end_shader()
	{
		_s("ei_end_shader()");
		_e( ei_end_shader() );
	}
}