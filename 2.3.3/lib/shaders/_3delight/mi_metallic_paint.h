#ifndef __mi_metallic_paint_h
#define __mi_metallic_paint_h

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
	float irradiance_weight

	color spec
	float spec_weight
	float spec_exp
	color spec_sec
	float spec_sec_weight
	float spec_sec_exp
	float spec_glazing

	color flake_color
	float flake_weight
	float flake_reflect
	float flake_exp
	float flake_decay

	float global_weight

    valueof_outValue color flake_bump
	sourcename string flake_bump
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

begin shader_extra_parameters aov_specular
#ifdef USE_AOV_aov_specular
	output varying color aov_specular = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_surface_color
#ifdef USE_AOV_aov_surface_color
	output varying color aov_surface_color = 0;
#endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_reflection
#ifdef USE_AOV_aov_reflection
    output varying color aov_reflection = 0;
#endif
end shader_extra_parameters
*/

#include "shading_utils.h"

#define bool float
#define true 1
#define false 0

#define cpow(c, n) ( color(pow(comp(c,0),n),pow(comp(c,1),n),pow(comp(c,2),n)) )

void maya_mi_metallic_paint(
	color i_ambient;
	color i_base_color;
	color i_edge_color;
	float i_edge_color_bias;
	color i_lit_color;
	float i_lit_color_bias;
	float i_diffuse_weight;
	float i_diffuse_bias;
	float i_iradiance_weight;

	color i_spec;
	float i_spec_weight;
	float i_spec_exp;
	color i_spec_sec;
	float i_spec_sec_weight;
	float i_spec_sec_exp;
	bool i_spec_glazing;
	
	color i_flake_color;
	float i_flake_weight;
	float i_flake_reflect;
	float i_flake_exp;
	float i_flake_decay;

	float i_global_weight;
							
	color i_flake_bump;
	string i_flake_bump_str;
	
	output color o_result;
)
{
	color edgediffuse(vector N; float gamma)
	{
		extern point P;
		float buf;
		color C = 0;
		illuminance( P, N, PI )
		{
			buf = (normalize(L).N) * 0.95;
			C += Cl * pow(buf, gamma);
		}
		return C;
	}
	
	color csmoothstep(float min, max; color value)
	{
		color buf = color(
						  smoothstep(min, max, comp(value, 0)),
						  smoothstep(min, max, comp(value, 1)),
						  smoothstep(min, max, comp(value, 2)) );
		
		return buf;
	}
	
	color my_contrast(color a; float b)
	{
		color buf = a-0.5;
		buf *= b;
		buf += 0.5;
		return clamp(buf, color(0.0), color(1.0));
	}
	
	extern point P;
	extern normal N;	
	extern vector I;
	
	normal Nn = normalize(N);
	normal Ns = ShadingNormal(Nn);
	vector In = normalize(I);
	
	color diffuse_component = diffuse(Ns);
	
	vector tmp_n = reflect(I, Ns);
	
	color edge_multipler = (1-edgediffuse(Ns, 6))*(1-pow(-(Nn.In), i_edge_color_bias));
	color lit_multipler = cpow(diffuse_component, i_lit_color_bias*1.2) * 0.9;
	color color_component = mix(i_base_color, i_edge_color, edge_multipler);
		color_component = mix(color_component, i_lit_color, lit_multipler);
	
	diffuse_component = cpow(diffuse_component, i_diffuse_bias);
	computeShadowPass(Ns);

#ifdef USE_AOV_aov_ambient
	extern color aov_ambient;
	aov_ambient = i_ambient * i_global_weight;
#endif
#ifdef USE_AOV_aov_diffuse
	extern color aov_diffuse;
	aov_diffuse = diffuse_component * i_global_weight;
#endif
#ifdef USE_AOV_aov_surface_color
	extern color aov_surface_color;
	aov_surface_color = color_component;
#endif

	diffuse_component += i_ambient;
	diffuse_component *= color_component;
	
	vector V = normalize(-I);
	color specular_component;
	
	float spec_weight = i_spec_weight;
	float spec_sec_weight = i_spec_sec_weight;
	float flake_weight = i_flake_weight;
	
	if(i_spec_glazing == true)
	{
		specular_component =
			i_spec * 
			csmoothstep(0.6, 0.85, getPhong(Ns, V, i_spec_exp/5, 0.0, 0.0)) *
			spec_weight;
	} else {
		specular_component =
			i_spec * getPhong(Ns, V, i_spec_exp/5, 0.0, 0.0) * spec_weight;
	}
	
	specular_component += 
		i_spec_sec * getPhong(Ns, V, i_spec_sec_exp/5, 0.0, 0.0) * spec_sec_weight;
	
	color flake_mult = color(0.5);
	if(i_flake_bump_str != "")
		flake_mult = my_contrast(i_flake_bump, 1.5);
	
	vector flake_nrml = Ns;
	
	float decay = length(I);
	if(i_flake_decay > 0)
	{
		decay = 1 - decay/i_flake_decay;
		decay = clamp(decay, 0, 1);
		decay = pow(decay, 0.75);
	} else
		decay = 1;

	specular_component += 
		flake_mult * i_flake_color * getPhong(flake_nrml, V, i_flake_exp/5, 0.0, 0.0) *
		flake_weight * decay;

#ifdef USE_AOV_aov_specular
	extern color aov_specular;
	aov_specular = specular_component * i_global_weight;
#endif
	
	color reflection_component = flake_mult * i_flake_color * flake_weight * decay * i_flake_reflect;
	if(reflection_component != color(0.0))
		reflection_component *= trace(P, reflect(In, flake_nrml));
	
#ifdef USE_AOV_aov_reflection
	extern color aov_reflection;
	aov_reflection = reflection_component * i_global_weight;
#endif

	o_result = diffuse_component + specular_component + reflection_component;
	o_result *= i_global_weight;
}

#undef cpow

#undef bool
#undef true
#undef false

#endif /* __mi_metallic_paint_h */