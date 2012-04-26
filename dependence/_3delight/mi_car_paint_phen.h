#ifndef __mi_car_paint_phen_h
#define __mi_car_paint_phen_h

/*
begin inputs
	color ambient
	color base_color
	color edge_color
	float edge_color_bias
	color lit_color
	float lit_color_bias
	float diffuse_weight
	float diffuse_bias

	color flake_color
	float flake_weight
	float flake_reflect
	float flake_exp
	float flake_density
	float flake_decay
	float flake_strength
	float flake_scale

	color spec
	float spec_weight
	float spec_exp
	color spec_sec
	float spec_sec_weight
	float spec_sec_exp
	float spec_glazing

	color reflection_color
	float edge_factor
	float reflection_edge_weight
	float reflection_base_weight
	float samples
	float glossy_spread
	float max_distance
	float single_env_sample

	color dirt_color
	float dirt_weight

	float irradiance_weight
	float global_weight
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

begin shader_extra_parameters aov_surface_color
#ifdef USE_AOV_aov_surface_color
 output varying color aov_surface_color = 0;
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

#include "shading_utils.h"
#include "mi_metallic_paint.h"
#include "mi_bump_flakes.h"
#include "mib_glossy_reflection.h"

#define bool float
#define true 1
#define false 0

#define cpow(c, n) ( color(pow(comp(c,0),n),pow(comp(c,1),n),pow(comp(c,2),n)) )

void maya_mi_car_paint_phen(
	color i_ambient;
	color i_base_color;
	color i_edge_color;
	float i_edge_color_bias;
	color i_lit_color;
	float i_lit_color_bias;
	float i_diffuse_weight;
	float i_diffuse_bias;

	color i_flake_color;
	float i_flake_weight;
	float i_flake_reflect;
	float i_flake_exp;
	float i_flake_density;
	float i_flake_decay;
	float i_flake_strength;
	float i_flake_scale;

	color i_spec;
	float i_spec_weight;
	float i_spec_exp;
	color i_spec_sec;
	float i_spec_sec_weight;
	float i_spec_sec_exp;
	bool i_spec_glazing;

	color i_reflection_color;
	float i_edge_factor;
	float i_reflection_edge_weight;
	float i_reflection_base_weight;
	uniform float i_samples;
	uniform float i_glossy_spread;
	uniform float i_max_distance;
	bool i_single_env_sample;

	color i_dirt_color;
	float i_dirt_weight;

	float i_irradiance_weight;
	float i_global_weight;
	
	output color o_result;
)
{
	color my_contrast(color a; float b)
	{
		color buf = a-0.5;
		buf *= b;
		buf += 0.5;
		return clamp(buf, color(0.0), color(1.0));
	}
	
	extern vector I;
	extern point P;
	extern normal N;
	vector In = normalize(I);
	vector V = -In;
	normal Nn = normalize(N);
	normal Ns = faceforward(Nn, In);
	
	color metallic_comp;
	maya_mi_metallic_paint(i_ambient,
						   i_base_color,
						   i_edge_color,
						   i_edge_color_bias,
						   i_lit_color,
						   i_lit_color_bias,
						   i_diffuse_weight,
						   i_diffuse_bias,
						   1.0,
						   i_spec,
						   i_spec_weight,
						   i_spec_exp,
						   i_spec_sec,
						   i_spec_sec_weight,
						   i_spec_sec_exp,
						   i_spec_glazing,
						   0.0,
						   0.0,
						   0.0,
						   0.0,
						   0.0,
						   1.0,
						   0.0,
						   "a",
						   metallic_comp );
	
	//It very slow because mib_glossy_reflection have anisotropy
	/*
	color empty_array[] = {};
	color reflection_comp;
	maya_mib_glossy_reflection(0.0,
							   i_reflection_color,
							   0.0,
							   2.0,
							   color(0.0),
							   i_reflection_base_weight,
							   i_reflection_edge_weight,
							   i_edge_factor,
							   i_single_env_sample,
							   i_samples,
							   i_glossy_spread,
							   i_glossy_spread,
							   vector(0,0,0),
							   vector(0,0,0),
							   0.0,
							   empty_array,
							   reflection_comp );
	*/
	//But this shader have not anisotropy, there is ability to make it faster
	float base_edge_mix = pow(-(Nn.In), 1/i_edge_factor);
	base_edge_mix = mix(i_reflection_edge_weight, i_reflection_base_weight, base_edge_mix);
	color reflection_comp = getReflection( Ns, In, i_reflection_color, 1.0,
										color(0.0),	i_max_distance, i_samples,
										i_glossy_spread*1.5, 0.0, 0.0, 20)
							* base_edge_mix;
	
	color cFlakes;
	normal nFlakes;
	float decay = length(I);
	if(i_flake_decay > 0)
	{
		decay = 1 - decay/i_flake_decay;
		decay = clamp(decay, 0, 1);
		decay = pow(decay, 0.75);
	} else
		decay = 1;
	maya_mi_bump_flakes_with_normal(i_flake_density,
									i_flake_strength,
									i_flake_scale,
									nFlakes,
									cFlakes );
	cFlakes = my_contrast(cFlakes, 1.5);
	color flake_spec_comp = cFlakes * i_flake_color	* getPhong(nFlakes, V, i_flake_exp/5, 0.0, 0.0) *
				i_flake_weight * decay;
	color flake_refl_comp = cFlakes * i_flake_color * i_flake_weight * i_flake_reflect * decay;
	if(flake_refl_comp != color(0.0))
		flake_refl_comp *= trace(P, reflect(In, nFlakes));
	
#ifdef USE_AOV_aov_reflection
	extern color aov_reflection;
	aov_reflection = flake_refl_comp;
#endif
#ifdef USE_AOV_aov_specular
	extern color aov_specular;
	aov_specular = flake_spec_comp;
#endif
	
	color dirt = diffuse(Ns) * 0.9 * i_dirt_color + 0.1;
	
	o_result = metallic_comp + flake_spec_comp + flake_refl_comp + reflection_comp;
	o_result *= i_global_weight;
	o_result = mix(o_result, dirt, i_dirt_weight);
						   
}

#undef cpow

#undef bool
#undef true
#undef false

#endif /* __mi_car_paint_phen_h */