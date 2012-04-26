#ifndef __misss_skin_specular_h
#define __misss_skin_specular_h

/*
 begin inputs
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
 float reflect_shinyness
 float reflect_environment_only
 end inputs
 
 begin outputs
 color outValue
 end outputs
 
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

#define bool float
#define true 1
#define false 0

color misss_skin_specular_edge(
							   normal  Nn;
							   vector  V;
							   float   edge_factor;
							   float   shinyness)
{
	color pow(color c; float exponent)
	{
		return
		color( pow(c[0], exponent), pow(c[1], exponent), pow(c[2], exponent));
	}
	
	extern point P;
	
	float e = 1.0 + 0.5 * edge_factor + 0.1 * shinyness;
	vector R = reflect(-V, Nn);
	color C = 0.0;
	
	illuminance( "specular", P, Nn, PI / 2.0 )
	{
		vector Ln = normalize(L);
		C += Cl
		* pow(max(R . Ln, 0.0), shinyness)
		* pow(1.0 - max(V . Nn, 0.0), e);
	}
	
	return C;
}

void maya_misss_skin_specular(
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
							  float i_reflect_shinyness;
							  float i_reflect_environment_only;
							  
							  output color o_result;
)
{
	extern normal N;
	extern vector I;
	extern point P;
	
	normal Nn = normalize(N);
	normal Nf = faceforward(Nn, I);
	vector V = normalize(-I);
	
	float Eps = 1.0e-4;
	float primary_shinyness = max(i_primary_shinyness, Eps);
	float secondary_shinyness = max(i_secondary_shinyness, Eps);
	
	color primary_spec =
	i_primary_weight
	* i_primary_spec_color
	* getPhong(Nn, V, primary_shinyness, 0, 0);
	primary_spec +=
	i_primary_edge_weight
	* i_primary_spec_color
	* misss_skin_specular_edge(
							   Nn, V,
							   i_edge_factor,
							   primary_shinyness);
	
	color secondary_spec =
	i_secondary_weight
	* i_secondary_spec_color
	* getPhong(Nn, V, secondary_shinyness, 0, 0);
	secondary_spec +=
	i_secondary_edge_weight
	* i_secondary_spec_color
	* misss_skin_specular_edge(
							   Nn, V,
							   i_edge_factor,
							   secondary_shinyness);
	
	vector reflection_dir = reflect(I, Nn);
	
	float angle = i_reflect_shinyness == 0.0
	? 0.0
	: 1.0 / (1.0 + i_reflect_shinyness) * PI / 2.0;
	
	color transmission = 1.0;
	color reflection_color = 0.0;
	
	if( i_reflect_environment_only != true )
	{
		// todo: rendering hangs if "samplecone" is set to anything else than 0.0:
		reflection_color =
		trace(
			  P,
			  reflection_dir,
			  "samplecone", angle,
			  "samples", 1.0,
			  "transmission", transmission);
	}
	
	color reflection = i_reflect_weight * reflection_color;
	reflection +=
	i_reflect_edge_weight
	* reflection_color
	* misss_skin_specular_edge(
							   Nn, V,
							   i_edge_factor,
							   i_reflect_shinyness);
	
#ifdef USE_AOV_aov_specular
	extern varying color aov_specular;
	if( isoutput(aov_specular) )
	{
		aov_specular = primary_spec + secondary_spec;
	}
#endif
	
#ifdef USE_AOV_aov_reflection
	extern varying color aov_reflection;
	if( isoutput(aov_reflection) )
	{
		aov_reflection = reflection;
	}
#endif
	
	o_result = primary_spec + secondary_spec + reflection;
	o_result *= i_overall_weight;
}

#undef bool
#undef true
#undef false

#endif /* __misss_skin_specular_h */
