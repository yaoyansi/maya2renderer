/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef _noise_utils_h
#define _noise_utils_h

#include "utils.h"

#define snoise(p) (2 * (float noise(p)) - 1)
#define psnoise(x, y, xperiod, yperiod) (2*(float pnoise(x, y, xperiod, yperiod)-1))
#define snoisexy(x,y) (2 * (float noise(x,y)) - 1)
#define vsnoise(p) (2 * (vector noise(p)) - 1)
#define filteredsnoise(p,width) (snoise(p) * (1-smoothstep (0.2,0.75,width)))
#define filterwidth(x)  max(abs(Du(x)*du) + abs(Dv(x)*dv), 1e-6)

float
fBrownianNoise(
	point i_point;
	uniform float i_time;
	uniform float i_amplitude;
	uniform float i_lacunarity;
	uniform float i_frequencyRatio;
	uniform float i_octaves[2];
	uniform float i_ratio;
	float i_ripples[3]; )
{
	uniform float i = 0;
	uniform float lacunarity = i_lacunarity;
	float mix = 0;
	uniform float amp = i_amplitude;
	point pp = i_point * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;

	float pixel_size = sqrt( area(pp) );
	float nyquist = 2 * pixel_size;
	float pixel = 1.0;

	while( (i<i_octaves[1] && pixel>nyquist) || i<i_octaves[0] )
	{
		mix += amp * snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time);
		lacunarity *= i_frequencyRatio;
		amp *= i_ratio;
		pixel /= i_frequencyRatio;

		i+= 1.0;
	}

	if( pixel>pixel_size && i<=i_octaves[1])
	{
		float weight = clamp(pixel/pixel_size - 1, 0, 1);
		mix += weight * amp *
			snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time);
	}

	return mix * 0.5 + 0.5;
}

float fBm( 
	point p; 
	float i_time;
	float i_initialAmplitude;
	float i_octaves[2];
	float i_lacunarity, frequencyRatio, ratio)
{
	float amp = i_initialAmplitude;
	point pp = p;
	float sum = 0;
	uniform float i = 0;

	uniform float lacunarity = i_lacunarity;

	float pixel_size = sqrt( area(pp) );
	float nyquist = 2 * pixel_size;
	float pixel = 1.0;

	while( (i<i_octaves[1] && pixel>nyquist) || (i<i_octaves[0]) )
	{
		sum += amp * snoisexy( pp * lacunarity, i_time );
		amp *= ratio; 
		lacunarity *= frequencyRatio;
		pixel /= frequencyRatio;	

		i += 1.0;
	}

	if( pixel>pixel_size && i<=i_octaves[1] )
	{
		float weight = clamp(pixel/pixel_size - 1, 0, 1);
		sum += weight * amp * snoisexy(pp * lacunarity, i_time );
	}

	return sum * 0.5 + 0.5;
}

/* A vector-valued fBm. */
vector vfBm( point p; uniform float octaves[2], lacunarity, ratio;
	uniform float i_ripples[3] )
{
	varying vector sum = 0;
	uniform float i = 0;
	uniform float amp = 1;

	point pp = p * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;

	float pixel_size = sqrt( area(pp) );
	float nyquist = 2 * pixel_size;
	float pixel = 1.0;

	while( (i<octaves[1] && pixel>pixel_size) || i<octaves[0] )
	{
		sum += amp * vsnoise( pp );
		amp *= ratio;
		pp *= lacunarity;

		i += 1.0;
		pixel /= lacunarity;
	}

	if( pixel>pixel_size && i<=octaves[1])
	{
		float weight = clamp(pixel/pixel_size - 1, 0, 1);
		sum += weight * amp * vsnoise(pp);
	}

	return sum;
}


float
fTurbulence(
	point i_point;
	uniform float i_time;
	uniform float i_lacunarity;
	float i_frequencyRatio;
	float i_octaves[2];
	float i_ratio;
	float i_ripples[3];)
{
	uniform float i = 0;
	uniform float lacunarity = i_lacunarity;
	float mix = 0;
	float amp = 1;
	point pp = i_point * point(i_ripples[0], i_ripples[1], i_ripples[2]) / 2;

	float pixel_size = sqrt( area(pp) );
	float nyquist = 2 * pixel_size;
	float pixel = 1.0;

	while( (i<i_octaves[1] && pixel>nyquist) || i<i_octaves[0] )
	{
		mix += amp * abs(snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time));
		lacunarity *= i_frequencyRatio;
		amp *= i_ratio;
		pixel /= i_frequencyRatio;

		i+=1.0;
	}

	if( pixel>pixel_size && i<=i_octaves[1] )
	{
		float weight = clamp(pixel/pixel_size - 1, 0, 1);
		mix += weight * amp *
			abs(snoisexy((vector(pp) + noise(lacunarity)) * lacunarity, i_time));
	}

	return mix;
}

/*
	animatedcellnoise

	This is a mix of cell noise and regular noise. It is cell noise by its
	point parameter but smooth noise by its float parameter. So you can think
	of it as a 3D cell noise which changes smoothly in the 4th dimension.
*/
point animatedcellnoise( point i_p; float i_t )
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
float
SuspendedParticles(
	point Pn; float i_time;
	float particleradius;
	float jitter;
	float octave;
	output float f1;  output point pos1;
	output float f2;  output point pos2;
	output point particlesPos[];
    )
{
	point thiscell = 
		point( floor(xcomp(Pn))+0.5, floor(ycomp(Pn))+0.5,
		floor(zcomp(Pn))+0.5);

	f1 = f2 = 1e36;
	uniform float i, j, k;

	float curr_particle = 0;
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

float
SuspendedParticles2d(
	point Pn; float i_time;
	float particleradius;
	float jitter;
	float octave;
	output point particlesPos[];
    )
{
	point thiscell = 
		point( floor(xcomp(Pn))+0.5, floor(ycomp(Pn))+0.5, 0 );

	uniform float i, j, k;

	float curr_particle = 0;
	for (i = -1;  i <= 1;  i += 1)
	{
		for (j = -1;  j <= 1;  j += 1)
		{
			point testcell = thiscell + vector(i,j,0);
			if( jitter > 0 )
			{
				vector vjit =
					animatedcellnoise(testcell, i_time + 1000 * octave) - 0.5;
				vjit *= jitter;
				setzcomp( vjit, 0 );
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
	float i_falloff;
	point i_particleCenter, i_P;
	float i_radius; )
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
			fadeout = clamp( 1 - fadeout, 0, 1 );
			fadeout += 1 - smoothstep( 0, 0.1, fadeout );
		}
	}

	return 1-fadeout;
}

float BillowNoise( 
	point p; float i_time;
	uniform float i_dim;
	float radius, sizeRand, jitter, falloff, spottyness;
	float octaves, frequencyRatio, ratio, amplitude )
{
	point pp = p + vector(0.425, 0.6, i_dim == 3 ? 0.215 : 0);
	uniform float i, j;

	uniform float lacunarity = 1;

	point particles[27];
	float f1, f2;
	point p1, p2;
	float numParticles;
	float sum = 0;
	uniform float amp = 1;
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
					radiusScale = (0.5 - clamp( noise( particles[j] ) * 0.75 - 0.25, 0, 0.5 ) * sizeRand) * 2;
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
					density = clamp( density, 0, 1); 
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
	float i_x;
	float i_y;
	float i_time;
	float i_numWaves;)
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
				
		dirX = 2 * xcomp(noisePoint) - 1;
		dirY = 2 * ycomp(noisePoint) - 1;
		float offset = 2 * zcomp(noisePoint) - 1;
		float freqNoise = noise(50 * dirX * dirY);

		norm = sqrt(dirX * dirX + dirY * dirY);
		
		if(norm > EPSILON)
		{
			dirX /= norm;
			dirY /= norm;
			noiseValue += cos((dirX * x + dirY * y)  * (PI) / (6 * freqNoise) + 
				offset * time);
		}
	}

	return noiseValue /= i_numWaves;      
}

#endif

