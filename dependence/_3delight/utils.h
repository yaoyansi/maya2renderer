/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/


#ifndef _utils_h
#define _utils_h

#define LOG05 -0.693147180559945  /* log(0.5) */
#define UNDEFINED_UV -10000000

#define ISUVDEFINED(U, V) ( abs(U) < 10000 && abs(V) < 10000 )

#define WRAPMAX (1.000001)
#define EPSILON 1e-6

float
luminance( color i_color )
{
	return
		0.3 * comp(i_color, 0) + 
		0.59 * comp(i_color, 1) + 
		0.11 * comp(i_color, 2);
}

color
cabs( color i_color )
{
	return color(
		abs(comp(i_color, 0)), abs(comp(i_color,1)), abs(comp(i_color,2)) );
}

/* Taken from ARMAN */
float filteredpulse (float edge0, edge1, x, dx)
{
    float x0 = x - dx/2;
    float x1 = x0 + dx;
    return max (0, (min(x1,edge1)-max(x0,edge0)) / dx);
}

/* Taken from ARMAN */
float filteredpulsetrain (float edge, period, x, dx)
{
	/* First, normalize so period == 1 and our domain of interest is > 0 */
    float w = dx/period;
    float x0 = x/period - w/2;
    float x1 = x0+w;
    float nedge = edge / period;

	/* Definite integral of normalized pulsetrain from 0 to t */
    float integral (float t) { 
        extern float nedge;
        return ((1-nedge)*floor(t) + max(0,t-floor(t)-nedge));
    }

	float result;
	if( x0 == x1 )
	{
		/* Trap the unfiltered case so it doesn't return 0 (when dx << x). */
		result = (x0 - floor(x0) < nedge) ? 0 : 1;
	}
	else
	{
    	result = (integral(x1) - integral(x0)) / w;
	}

	return result;
}

/*
	Perlin's bias function
*/
float bias(float b, x)
{
    return pow(x, log(b)/LOG05);
}
	
void
colorBalance(
	output color io_outColor;
	output float io_outAlpha;
	uniform float i_alphaIsLuminance;
	float i_alphaGain;
	float i_alphaOffset;
	color i_colorGain;
	color i_colorOffset;
	uniform float i_invert; )
{
	if(i_invert != 0.0)
	{
		io_outColor = 1 - io_outColor;
		io_outAlpha = 1 - io_outAlpha;
	}

	if(i_alphaIsLuminance != 0.0)
	{
		io_outAlpha = luminance( io_outColor );
	}

	io_outColor *= i_colorGain;
	io_outColor += i_colorOffset;

	io_outAlpha *= i_alphaGain;
	io_outAlpha += i_alphaOffset;
}	


#endif
