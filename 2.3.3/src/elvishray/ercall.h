
#ifndef _ER_CALL_
#define _ER_CALL_

namespace elvishray
{
void my_ei_transform(
					 float t00,float t01,float t02,float t03,
					 float t10,float t11,float t12,float t13,
					 float t20,float t21,float t22,float t23,
					 float t30,float t31,float t32,float t33
					 );
void my_ei_scene();
void my_ei_shader(const char* shadertype, const char* param0, const float v);
void my_ei_shading_rate(const float v);

}
#endif