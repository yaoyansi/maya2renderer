/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#include "noise_utils.h"
#include "utils.h"

//float
//fBrownianNoise(
//			   point i_point,
//			   const float i_time,
//			   const float i_amplitude,
//			   const float i_lacunarity,
//			   const float i_frequencyRatio,
//			   const float i_octaves[2],
//			   const float i_ratio,
//			   float i_ripples[3] )
//{
//	/*const*/ int i = 0;
//	/*const*/ float lacunarity = i_lacunarity;
//	float mix = 0.0f;
//	/*const*/ float amp = i_amplitude;
//	point pp = i_point * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;
//
//	float pixel_size = sqrt( area(pp) );
//	float nyquist = 2 * pixel_size;
//	float pixel = 1.0f;
//
//	while( (i<i_octaves[1] && pixel>nyquist) || i<i_octaves[0] )
//	{
//		mix += amp * snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time);
//		lacunarity *= i_frequencyRatio;
//		amp *= i_ratio;
//		pixel /= i_frequencyRatio;
//
//		i+= 1;
//	}
//
//	if( pixel>pixel_size && i<=i_octaves[1])
//	{
//		float weight = clamp<float>(pixel/pixel_size - 1.0f, 0.0f, 1.0f);
//		mix += weight * amp *
//			snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time);
//	}
//
//	return mix * 0.5f + 0.5f;
//}

//float fBm( 
//		  point p, 
//		  float i_time,
//		  float i_initialAmplitude,
//		  float i_octaves[2],
//		  float i_lacunarity, float frequencyRatio, float ratio)
//{
//	float amp = i_initialAmplitude;
//	point pp = p;
//	float sum = 0;
//	/*const*/ float i = 0;
//
//	/*const*/ float lacunarity = i_lacunarity;
//
//	float pixel_size = sqrt( area(pp) );
//	float nyquist = 2 * pixel_size;
//	float pixel = 1.0;
//
//	while( (i<i_octaves[1] && pixel>nyquist) || (i<i_octaves[0]) )
//	{
//		sum += amp * snoisexy( pp * lacunarity, i_time );
//		amp *= ratio; 
//		lacunarity *= frequencyRatio;
//		pixel /= frequencyRatio;	
//
//		i += 1.0;
//	}
//
//	if( pixel>pixel_size && i<=i_octaves[1] )
//	{
//		float weight = clamp<float>(pixel/pixel_size - 1.0f, 0.0f, 1.0f);
//		sum += weight * amp * snoisexy(pp * lacunarity, i_time );
//	}
//
//	return sum * 0.5f + 0.5f;
//}
//
/* A vector-valued fBm. */
//vector vfBm(
//			point p, 
//			const float octaves[2], const float lacunarity, const float ratio,
//			const float i_ripples[3] )
//{
//	/*varying*/ vector sum = 0;
//	/*const*/ float i = 0;
//	/*const*/ float amp = 1;
//
//	point pp = p * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;
//
//	float pixel_size = sqrt( area(pp) );
//	float nyquist = 2 * pixel_size;
//	float pixel = 1.0;
//
//	while( (i<octaves[1] && pixel>pixel_size) || i<octaves[0] )
//	{
//		sum += amp * vsnoise( pp );
//		amp *= ratio;
//		pp *= lacunarity;
//
//		i += 1.0;
//		pixel /= lacunarity;
//	}
//
//	if( pixel>pixel_size && i<=octaves[1])
//	{
//		float weight = clamp<float>(pixel/pixel_size - 1.0f, 0.0f, 1.0f);
//		sum += weight * amp * vsnoise(pp);
//	}
//
//	return sum;
//}
//

//float
//fTurbulence(
//			point i_point,
//			const float i_time,
//			const float i_lacunarity,
//			float i_frequencyRatio,
//			float i_octaves[2],
//			float i_ratio,
//			float i_ripples[3])
//{
//	/*const*/ float i = 0;
//	/*const*/ float lacunarity = i_lacunarity;
//	float mix = 0;
//	float amp = 1;
//	point pp = i_point * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;
//
//	float pixel_size = sqrt( area(pp) );
//	float nyquist = 2 * pixel_size;
//	float pixel = 1.0;
//
//	while( (i<i_octaves[1] && pixel>nyquist) || i<i_octaves[0] )
//	{
//		mix += amp * abs(snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time));
//		lacunarity *= i_frequencyRatio;
//		amp *= i_ratio;
//		pixel /= i_frequencyRatio;
//
//		i+=1.0;
//	}
//
//	if( pixel>pixel_size && i<=i_octaves[1] )
//	{
//		float weight = clamp<float>(pixel/pixel_size - 1.0f, 0.0f, 1.0f);
//		mix += weight * amp *
//			abs(snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time));
//	}
//
//	return mix;
//}

/*
animatedcellnoise

This is a mix of cell noise and regular noise. It is cell noise by its
point parameter but smooth noise by its float parameter. So you can think
of it as a 3D cell noise which changes smoothly in the 4th dimension.
*/
point animatedcellnoise( point i_p, float i_t )
{
	/* This is so each cell changes direction at a different time. */
	float t = cellnoise(i_p) + i_t;

	float tbase = floor(t);

	point n1 = cellnoise( i_p, tbase );
	float d = t - tbase;
	point n2 = cellnoise( i_p, tbase + 1 );
	n1 += d * (n2 - n1);

	return n1;
}

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
)
{
	point thiscell = 
		point( floor(Pn.x)+0.5f, floor(Pn.y)+0.5f,
		floor(Pn.z)+0.5f);

	f1 = f2 = eiBIG_SCALAR;
	/*const*/ int i, j, k;

	int curr_particle = 0;
	for (i = -1;  i <= 1;  i += 1)
	{
		for (j = -1;  j <= 1;  j += 1)
		{
			for (k = -1;  k <= 1;  k += 1)
			{
				point testcell = thiscell + vector(i,j,k);
				if( jitter > 0 )
				{
					vector jit = animatedcellnoise(
						testcell, i_time + 1000 * octave) - 0.5;
					testcell += jitter * jit;
				}
				float dist = distance( testcell, Pn );
				if( dist < particleradius )
				{
					particlesPos[curr_particle] = testcell;
					curr_particle += 1;
					if (dist < f1)
					{
						f2 = f1;  pos2 = pos1;
						f1 = dist;  pos1 = testcell;
					}
					else if (dist < f2)
					{
						f2 = dist;  pos2 = testcell;
					}
				}
			}
		}
	}

	return curr_particle;
}

int
SuspendedParticles2d(
					 point Pn, float i_time,
					 float particleradius,
					 float jitter,
					 float octave,
					 point *particlesPos//array
)
{
	point thiscell = 
		point( floor(Pn.x)+0.5f, floor(Pn.y)+0.5f, 0.0f );

	/*const*/ int i, j/*, k*/;

	int curr_particle = 0;
	for (i = -1;  i <= 1;  i += 1)
	{
		for (j = -1;  j <= 1;  j += 1)
		{
			point testcell = thiscell + vector(i,j,0);
			if( jitter > 0.0f )
			{
				vector vjit =
					animatedcellnoise(testcell, i_time + 1000 * octave) - 0.5;
				vjit *= jitter;
				vjit.z = 0.0f;
				testcell += vjit;
			}
			float dist = distance( testcell, Pn );
			if( dist < particleradius )
			{
				particlesPos[curr_particle] = testcell;
				curr_particle += 1;
			}
		}
	}

	return curr_particle;
}

/*
ParticleDensity

computes particles density at some given point in 
the particle	
*/
float
ParticleDensity(
				int i_falloff,
				point i_particleCenter, point i_P,
				float i_radius )
{
	float distanceToCenter = distance( i_particleCenter, i_P );
	float fadeout = 0;

	if( i_falloff == 0 ) /* linear */
	{
		fadeout = distanceToCenter / i_radius;
	}
	else if( i_falloff == 1 ) /* smooth */
	{
		fadeout = smoothstep( 0, i_radius, distanceToCenter );
	}
	else
	{
		/* fast and bubble */
		fadeout = distanceToCenter / i_radius;
		fadeout = bias( 0.25, fadeout ); 

		if( i_falloff == 3 ) /* bubble */
		{
			fadeout = clamp<float>( 1.0f - fadeout, 0.0f, 1.0f );
			fadeout += 1.0f - smoothstep( 0.0f, 0.1f, fadeout );
		}
	}

	return 1.0f-fadeout;
}

float BillowNoise( 
				  point p, float i_time,
				  const int i_dim,
				  float radius, float sizeRand, float jitter, int falloff, float spottyness,
				  float octaves, float frequencyRatio, float ratio, float amplitude )
{
	point pp = p + vector(0.425f, 0.6f, i_dim == 3 ? 0.215f : 0.0f);
	/*const*/ int i, j;

	/*const*/ float lacunarity = 1.0f;

	point particles[27];
	float f1, f2;
	point p1, p2;
	int numParticles;
	float sum = 0;
	/*const*/ float amp = 1.0f;
	float ampSum = 0;

	for (i = 0; i<octaves; i+=1 ) 
	{
		if( i_dim == 3 )
		{
			numParticles = SuspendedParticles(
				pp * lacunarity, i_time, radius, jitter, i,
				f1, p2, f2, p2, particles );
		} else {
			numParticles = SuspendedParticles2d(
				pp * lacunarity, i_time, radius, jitter, i, particles );
		}

		if( numParticles > 0 )
		{
			for( j=0; j<numParticles; j+=1 )
			{
				float radiusScale = 1;

				if( sizeRand != 0 )
				{
					radiusScale = (0.5f - clamp<float>( noise( particles[j] ) * 0.75f - 0.25f, 0.0f, 0.5f ) * sizeRand) * 2.0f;
				}

				float density = 
					ParticleDensity( 
					falloff, particles[j],
					pp * lacunarity, radius * radiusScale );

				if( spottyness > 0 )
				{
					float l = spottyness *   
						(cellnoise(particles[j]+vector(1, 7, 1023))*2-1);
					density += density * l;
					density = clamp<float>( density, 0.0f, 1.0f); 
				}

				sum += amp * density;
			}
		}
		ampSum += amp;
		amp *= ratio; 
		lacunarity *= frequencyRatio;
	}

	return amplitude * sum / ampSum;
}

/* 
cos_waves

A simple sum of cosine waves
*/
float
cos_waves(
		  float i_x,
		  float i_y,
		  float i_time,
		  float i_numWaves)
{
	float x = i_x * 2 * PI;
	float y = i_y * 2 * PI;
	float time = i_time * 2 * PI;

	float dirX = 0;
	float dirY = 0;
	float norm = 0;
	float noiseValue = 0;
	float i = 0;

	for(i = 1; i <= i_numWaves; i += 1)
	{
		point noisePoint = noise(i * PI / i_numWaves);

		dirX = 2 * noisePoint.x - 1;
		dirY = 2 * noisePoint.y - 1;
		float offset = 2 * noisePoint.z - 1;
		float freqNoise = noise(50 * dirX * dirY);

		norm = sqrt(dirX * dirX + dirY * dirY);

		if(norm > eiSCALAR_EPS)
		{
			dirX /= norm;
			dirY /= norm;
			noiseValue += cos((dirX * x + dirY * y)  * (PI) / (6 * freqNoise) + 
				offset * time);
		}
	}

	return noiseValue /= i_numWaves;      
}
