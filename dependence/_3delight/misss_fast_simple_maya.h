#ifndef __misss_fast_simple_maya_h
#define __misss_fast_simple_maya_h

/*
begin inputs
 color ambient
 color overall_color
 color diffuse_color
 float diffuse_weight
 
 color front_sss_color
 float front_sss_weight
 float front_sss_radius
 color back_sss_color
 float back_sss_weight
 float back_sss_radius
 float back_sss_depth
 
 color specular
 float exponent
 
 float samples
 
 float scale_conversion
 float falloff
 float screen_composit
 
 normal normalCamera
end inputs
 
begin outputs
 color outValue
end outputs
 
 begin shader_extra_parameters aov_ambient
 #ifdef USE_AOV_aov_ambient
 output varying color aov_ambient = 0;
 #endif
 end shader_extra_parameters
 
 begin shader_extra_parameters aov_diffuse
 #ifdef USE_AOV_aov_diffuse
 output varying color aov_diffuse = 0;
 #endif
 end shader_extra_parameters
 
 begin shader_extra_parameters aov_subsurface
 #ifdef USE_AOV_aov_subsurface
 output varying color aov_subsurface = 0;
 #endif
 end shader_extra_parameters
 
 begin shader_extra_parameters aov_specular
 #ifdef USE_AOV_aov_specular
 output varying color aov_specular = 0;
 #endif
 end shader_extra_parameters
 
 begin shader_extra_parameters aov_reflection
 #ifdef USE_AOV_aov_reflection
 output varying color aov_reflection = 0;
 #endif
 end shader_extra_parameters
 */

#include "misss_skin_specular.h"
#include "misss_fast_shader.h"
#include "utils.h"

#define bool float
#define true 1
#define false 0

void maya_misss_fast_simple_maya(
								 color i_ambient;
								 color i_overall_color;
								 color i_diffuse_color;
								 float i_diffuse_weight;
								 
								 color i_front_sss_color;
								 float i_front_sss_weight;
								 float i_front_sss_radius;
								 color i_back_sss_color;
								 float i_back_sss_weight;
								 float i_back_sss_radius;
								 float i_back_sss_depth;
								 
								 color i_specular;
								 float i_exponent;
								 
								 float i_samples;
								 
								 float i_scale_conversion;
								 float i_falloff;
								 bool  i_screen_composit;
								 
								 normal i_normalCamera;
								 
								 output color o_result;
)
{
	color screen_compose(color a, b)
	{
		return 1.0 - (1.0 - a) * (1.0 - b);
	}
	
	//extern point P;
	extern normal N;
	
	normal Nn = normalize(i_normalCamera);
	normal Nbuf = N;
	N = Nn;	
	
		color specular_component;
		maya_misss_skin_specular(
								 1.0,                        // i_overall_weight
								 5.0,                        // i_edge_factor
								 i_specular,				 // i_primary_spec_color
								 1.0,                       // i_primary_weight
								 1.0,                        // i_primary_edge_weight
								 i_exponent,                 // i_primary_shinyness
								 color(0.9, 0.95, 1.0),      // i_secondary_spec_color
								 0.0,                        // i_secondary_weight
								 0.0,                        // i_secondary_edge_weight
								 33.0,                       // i_secondary_shinyness
								 0.0,                        // i_reflect_weight
								 0.0,                        // i_reflect_edge_weight
								 2.0,                        // i_reflect_shinyness
								 false,                      // i_reflect_environment_only
								 
								 specular_component );
		
		maya_misss_fast_shader(
							   0.0,
							   "",
							   i_diffuse_color,
							   0.0,
							   
							   i_diffuse_weight,
							   i_front_sss_color,
							   i_front_sss_weight,
							   i_back_sss_color,
							   i_back_sss_weight,
							   
							   i_front_sss_radius,
							   i_back_sss_radius,
							   i_back_sss_depth,
							   i_scale_conversion,
							   i_falloff,
							   i_samples,
							   i_screen_composit,
							   false,
							   
							   o_result );
		
#ifdef USE_AOV_aov_ambient
		extern varying color aov_ambient;
		if( isoutput(aov_ambient) )
		{
			aov_ambient = i_ambient;
		}
#endif
	
	if(i_screen_composit == 1)
	{
		o_result = i_overall_color * 
			screen_compose(o_result, i_diffuse_color * i_ambient * i_diffuse_weight * 0.5);
		o_result = screen_compose(o_result, specular_component);
	}
	else
	{
		o_result += i_diffuse_color * i_ambient * i_diffuse_weight * 0.5;
		o_result *= i_overall_color;
		o_result += specular_component;
	}
	
	N = Nbuf;
	
}

#undef bool
#undef true
#undef false

#endif /* __misss_fast_simple_maya_h */