#include "ercall.h"
#include "../log/prerequest_std.h"
#include "er_renderer.h"

#define _s( _log_ ) dummy.get()<< _log_ <<std::endl;

//#define _USE_ER_LIB_

#ifdef _USE_ER_LIB_
#	include <eray_core.h>
#	pragma comment( lib, "eray_core.lib" )
#	define _er( _call_ )  _call_ 
#else 
#	define _er( _call_ )  
#endif

namespace elvishray
{
	extern Renderer dummy;

void my_ei_transform(
					 float t00,float t01,float t02,float t03,
					 float t10,float t11,float t12,float t13,
					 float t20,float t21,float t22,float t23,
					 float t30,float t31,float t32,float t33
					 )
{
	_s("ei_transform("<< t00<<","<<t01<<","<<t02<<","<<t03<<",   "<<t10<<","<<t11<<","<<t12<<","<<t13<<",   "<<  t20<<","<<t21<<","<<t22<<","<<t23<<",   "<<  t30<<","<<t31<<","<<t32<<","<<t33 <<");");
	_er(ei_transform());
}
void my_ei_scene()
{
	_s("ei_scene();"); 
	_er(ei_scene());
}
void my_ei_shader(const char* shadertype, const char* param0, const float v)
{

}
void my_ei_shading_rate(const float v)
{
	_s("ei_shading_rate("<< v <<");"); 
	_er(ei_shading_rate(v));
}
}