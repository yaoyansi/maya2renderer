#ifndef __misss_fast_skin_maya_h
#define __misss_fast_skin_maya_h

/*
 begin inputs
 color ambient
 color overall_color
 color diffuse_color
 float diffuse_weight
 
 color front_sss_color
 float front_sss_weight
 float front_sss_radius
 color mid_sss_color
 float mid_sss_weight
 float mid_sss_radius
 color back_sss_color
 float back_sss_weight
 float back_sss_radius
 float back_sss_depth
 
 float overall_weight
 float edge_factor
 color primary_spec_color
 float primary_weight
 float primary_edge_weight
 float primary_shinyness
 color secondary_spec_color
 float secondary_weight
 float secondary_edge_weight
 float secondary_shinyness
 float reflect_weight
 float reflect_edge_weight
 float reflect_environment_only
 float reflect_shinyness
 
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

#define bool float
#define true 1
#define false 0

void maya_misss_fast_skin_maya(
							   color i_ambient;
							   color i_overall_color;
							   color i_diffuse_color;
							   float i_diffuse_weight;
							   
							   color i_front_sss_color;
							   float i_front_sss_weight;
							   float i_front_sss_radius;
							   color i_mid_sss_color;
							   float i_mid_sss_weight;
							   float i_mid_sss_radius;
							   color i_back_sss_color;
							   float i_back_sss_weight;
							   float i_back_sss_radius;
							   float i_back_sss_depth;
							   
							   float i_overall_weight;
							   float i_edge_factor;
							   color i_primary_spec_color;
							   float i_primary_weight;
							   float i_primary_edge_weight;
							   float i_primary_shinyness;
							   color i_secondary_spec_color;
							   float i_secondary_weight;
							   float i_secondary_edge_weight;
							   float i_secondary_shinyness;
							   float i_reflect_weight;
							   float i_reflect_edge_weight;
							   float i_reflect_environment_only;
							   float i_reflect_shinyness;
							   
							   float i_scale_conversion;
							   float i_falloff;
							   float i_screen_composit;
							   
							   normal i_normalCamera;
							   
							   output color o_result;
)
{
	color screen_compose(color a, b)
	{
		return 1.0 - (1.0 - a) * (1.0 - b);
	}
	
	extern normal N;
	extern vector I;
	normal Nn = normalize(i_normalCamera);
	normal Nbuf = N; N = Nn;	
	normal Nf = faceforward(Nn, I);
	
	// Specular component.
	color specular;
	maya_misss_skin_specular(
							 i_overall_weight,
							 i_edge_factor,
							 i_primary_spec_color,
							 i_primary_weight,
							 i_primary_edge_weight,
							 i_primary_shinyness,
							 i_secondary_spec_color,
							 i_secondary_weight,
							 i_secondary_edge_weight,
							 i_secondary_shinyness,
							 i_reflect_weight,
							 i_reflect_edge_weight,
							 i_reflect_shinyness,
							 i_reflect_environment_only,
							 
							 specular );
	
	uniform string raytype = "unknown";
	rayinfo("type", raytype);
	
	if( raytype == "subsurface" )
	{
		// Subsurface scattering.
		
		color d = diffuse(normalize(N));
		
		if (N . I > 0.0)
		{
			// Back scattering.
			o_result = 0.14 * i_ambient * i_diffuse_weight;
			o_result += 2.0 * i_back_sss_color * i_back_sss_weight * d;
			o_result *= i_overall_color;
		}
		else
		{
			// Front scattering.
			o_result = 0.14 * i_ambient * i_diffuse_weight;
			o_result += 0.5 * i_front_sss_color * i_front_sss_weight * d;
			o_result += 0.75 * i_mid_sss_color * i_mid_sss_weight * d;
			o_result *= i_overall_color;
		}
	}
	else
	{
		float i_samples = 1.0;
		
		// Surface shading.
		color shallow_scatter;
		maya_misss_fast_shader(
							   0.0,
							   "",
							   i_diffuse_color,
							   0.0,
							   
							   i_diffuse_weight,
							   i_front_sss_color,
							   i_front_sss_weight,
							   
							   0.0, // i_back_sss_color
							   0.0, // i_back_sss_weight
							   
							   i_front_sss_radius,
							   0.0, // i_back_sss_radius
							   0.0, // i_back_sss_depth
							   
							   i_scale_conversion,
							   i_falloff,
							   i_samples,
							   1.0,
							   false, // i_output_sss_only
							   
							   shallow_scatter );
		
		maya_misss_fast_shader(
							   shallow_scatter,
							   "shallow_scatter",
							   i_diffuse_color,
							   0.0,
							   
							   1.0, //i_diffuse_weight
							   
							   i_mid_sss_color,
							   i_mid_sss_weight,
							   
							   i_back_sss_color,
							   i_back_sss_weight,
							   
							   i_mid_sss_radius,
							   i_back_sss_radius,
							   i_back_sss_depth,
							   
							   i_scale_conversion,
							   i_falloff,
							   i_samples,
							   i_screen_composit,
							   false, // i_output_sss_only
							   
							   o_result );
		
#ifdef USE_AOV_aov_ambient
		extern varying color aov_ambient;
		if( isoutput(aov_ambient) )
		{
			aov_ambient = i_ambient;
		}
#endif
		
		//o_result += i_diffuse_color * i_ambient;
		//o_result += specular;
		
		if(i_screen_composit == 1)
		{
			o_result = i_overall_color * 
			screen_compose(o_result, i_diffuse_color * i_ambient * i_diffuse_weight * 0.5);
			o_result = screen_compose(o_result, specular);
		}
		else
		{
			o_result += i_diffuse_color * i_ambient * i_diffuse_weight * 0.5;
			o_result *= i_overall_color;
			o_result += specular;
		}
	}
	
	N = Nbuf;
}

#undef bool
#undef true
#undef false

#endif /* __misss_fast_skin_maya_h */