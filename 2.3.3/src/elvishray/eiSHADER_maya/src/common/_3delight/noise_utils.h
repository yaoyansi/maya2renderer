/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef _noise_utils_h
#define _noise_utils_h

#include <eiAPI/ei_shaderx.h>

//#define snoise(p) (2 * (float noise(p)) - 1)
template < typename T>
inline T snoise(T p)
{
	return (2.0f * noise(p) - 1.0f);
}

//#define psnoise(x, y, xperiod, yperiod) (2*(float pnoise(x, y, xperiod, yperiod)-1))
template < typename T>
inline T psnoise(T x, T y, int  xperiod, int yperiod)
{
	return (  2.0f * (/*(float)*/pnoise(x, y, xperiod, yperiod)-1.0f)  );
}

//#define snoisexy(x,y) (2 * (float noise(x,y)) - 1)
template < typename T >
inline float snoisexy(T x, float y)
{
	return (2.0f * noise(x,y) - 1.0f);
}

//#define vsnoise(p) (2 * (vector noise(p)) - 1)
template < typename T >
inline T vsnoise(T p)
{
	return (2.0f * /*(vector)*/noise(p) - 1.0f);
}

//#define filteredsnoise(p,width) (snoise(p) * (1-smoothstep (0.2,0.75,width)))
template < typename T >
inline T filteredsnoise(T p, eiScalar width)
{
	return (snoise(p) * (1-smoothstep (0.2f,0.75f,width)))
}

//#define filterwidth(x)  max(abs(Du(x)*du) + abs(Dv(x)*dv), 1e-6)
//Du Dv must be used in shader.

float
fBrownianNoise(
	point i_point,
	const float i_time,
	const float i_amplitude,
	const float i_lacunarity,
	const float i_frequencyRatio,
	const float i_octaves[2],
	const float i_ratio,
	float i_ripples[3] );


float fBm( 
	point p, 
	float i_time,
	float i_initialAmplitude,
	float i_octaves[2],
	float i_lacunarity, float frequencyRatio, float ratio);


/* A vector-valued fBm. */
vector vfBm(
	point p, 
	const float octaves[2], const float lacunarity, const float ratio,
	const float i_ripples[3] );


float
fTurbulence(
	point i_point,
	const float i_time,
	const float i_lacunarity,
	float i_frequencyRatio,
	float i_octaves[2],
	float i_ratio,
	float i_ripples[3]);


/*
	animatedcellnoise

	This is a mix of cell noise and regular noise. It is cell noise by its
	point parameter but smooth noise by its float parameter. So you can think
	of it as a 3D cell noise which changes smoothly in the 4th dimension.
*/
point animatedcellnoise( point i_p, float i_t );


/*
	SuspendedParticles

	simulates a medium filled with particles of a given radius.

	RETURNS
	total number of particles enclosing "Pn".
	
	NOTES
	- if particle radius is "infinit", this will give a "worley" noise.
	- the 'octave' parameter is needed to make jitter different for all octaves
*/
int
SuspendedParticles(
	point Pn, float i_time,
	float particleradius,
	float jitter,
	float octave,
	float &f1,  point &pos1,
	float &f2,  point &pos2,
	point *particlesPos//array
    );


int
SuspendedParticles2d(
	point Pn, float i_time,
	float particleradius,
	float jitter,
	float octave,
	point *particlesPos//array
    );


/*
	ParticleDensity

	computes particles density at some given point in 
	the particle	
*/
float
ParticleDensity(
	int i_falloff,
	point i_particleCenter, point i_P,
	float i_radius );


float BillowNoise( 
	point p, float i_time,
	const float i_dim,
	float radius, float sizeRand, float jitter, float falloff, float spottyness,
	float octaves, float frequencyRatio, float ratio, float amplitude );


/* 
  cos_waves
  
  A simple sum of cosine waves
*/
float
cos_waves(
	float i_x,
	float i_y,
	float i_time,
	float i_numWaves);


#endif

