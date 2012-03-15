/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/


#ifndef _utils_h
#define _utils_h

#include <eiAPI/ei_shaderx.h>

#define LOG05 -0.693147180559945  /* log(0.5) */
#define UNDEFINED_UV -10000000

#define ISUVDEFINED(U, V) ( abs(U) < 10000.0f && abs(V) < 10000.0f )

#define WRAPMAX (1.000001f)
//#define EPSILON 1e-6   //we use eiSCALAR_EPS(1.0e-5f) instead.

float
luminance( color i_color );

color
cabs( color i_color );

/* Taken from ARMAN */
float filteredpulse (float edge0, float edge1, float x, float dx);

/* Taken from ARMAN */
float filteredpulsetrain (float edge,float period,float x,float dx);

/*
	Perlin's bias function
*/
float bias(float b, float x);
	
void
colorBalance(
	/*output*/ color &io_outColor,
	/*output*/ float &io_outAlpha,
	/*uniform*/const float i_alphaIsLuminance,
	float i_alphaGain,
	float i_alphaOffset,
	color i_colorGain,
	color i_colorOffset,
	/*uniform*/const float i_invert );


#endif
