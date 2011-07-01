#ifndef __mi_bump_flakes_h
#define __mi_bump_flakes_h

/*
 begin inputs
  float flake_density
  float flake_strength
  float flake_scale
 end inputs
 
 begin outputs
  color outValue
 end outputs
 */

#include "noise_utils.h"

void maya_mi_bump_flakes_with_normal(
									 float i_flake_density;
									 float i_flake_strength;
									 float i_flake_scale;

									 output normal o_nrm;
									 output color o_result;
)
{
	void flakes(
				float i_density;
				float i_cellSize;
				
				output float flake_mult;				
				output vector flake_nrml;
				)
	{
		float vtof(vector v)
		{
			return (xcomp(v) + ycomp(v) + zcomp(v))/3;
		}
		
		extern float s;
		extern float t;
		
		float edgeDist;
		float outside;
		
		varying point pp = point(2*s,t,0);
		
		point particle_positions[27];
		
		float mysize = 2.2/i_cellSize;
		
		point Pn = pp * mysize + vector(2*noise(pp*mysize));
		
		float radius = sqrt((0.5*0.5 + 0.5*0.5) * i_density * 2) ; //i_density
		
		point p1, p2;
		float f1, f2;
		float num_particles = SuspendedParticles( 
												 Pn, 0, radius,
												 1.0, 0, f1,
												 p1, f2, p2,
												 particle_positions ); //i_randomness
		
		flake_mult = 0.3;
		flake_nrml = vector(0);
		if( num_particles != 0 )
		{
			flake_nrml = cellnoise ( p1 + vector(1, 7, 1023) ) - 0.5;
			flake_mult += 0.3 * vtof(flake_nrml);
			flake_nrml = normalize(flake_nrml);
		}		
	}
	
	extern normal N;
	
	float flake_mult;
	vector flake_nrml;
	flakes(i_flake_density, i_flake_scale, flake_mult, flake_nrml);
	
	o_nrm = normalize(normalize(N) + flake_nrml * i_flake_strength * 0.15);
	o_result = flake_mult;
}

void maya_mi_bump_flakes(
						 float i_flake_density;
						 float i_flake_strength;
						 float i_flake_scale;

						 output color o_result;
)
{
	normal tmp_nrml;
	maya_mi_bump_flakes_with_normal(i_flake_density,
									i_flake_strength,
									i_flake_scale,
									
									tmp_nrml,
									o_result);
}

#endif /* __mi_bump_flakes_h */