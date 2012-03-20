/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/


#include "utils.h"

float
luminance( color i_color )
{
	return
		0.3f * i_color.x + 
		0.59f * i_color.y + 
		0.11f * i_color.z;
}

color
cabs( color i_color )
{
	return color(
		abs(i_color.x), abs(i_color.y), abs(i_color.z));
}

/* Taken from ARMAN */
float filteredpulse (float edge0, float edge1, float x, float dx)
{
    float x0 = x - dx/2;
    float x1 = x0 + dx;
    return max (0.0f, (min(x1,edge1)-max(x0,edge0)) / dx);
}

/* Taken from ARMAN */
	/* Definite integral of normalized pulsetrain from 0 to t */
    float integral (float t, float nedge) { 
        return ((1.0f-nedge)*floor(t) + max(0.0f,t-floor(t)-nedge));
    }
float filteredpulsetrain (float edge,float period,float x,float dx)
{
	/* First, normalize so period == 1 and our domain of interest is > 0 */
    float w = dx/period;
    float x0 = x/period - w/2.0f;
    float x1 = x0+w;
    float nedge = edge / period;



	float result;
	if( x0 == x1 )
	{
		/* Trap the unfiltered case so it doesn't return 0 (when dx << x). */
		result = (x0 - floor(x0) < nedge) ? 0.0f : 1.0f;
	}
	else
	{
    	result = (integral(x1, nedge) - integral(x0, nedge)) / w;
	}

	return result;
}

/*
	Perlin's bias function
*/
float bias(float b, float x)
{
    return pow((float)x, (float)(log(b)/LOG05));
}
	
void
colorBalance(
	/*output*/ color &io_outColor,
	/*output*/ float &io_outAlpha,
	/*uniform*/const eiBool i_alphaIsLuminance,
	float i_alphaGain,
	float i_alphaOffset,
	color i_colorGain,
	color i_colorOffset,
	/*uniform*/const eiBool i_invert )
{
	if(i_invert != eiFALSE)
	{
		io_outColor = 1.0f - io_outColor;
		io_outAlpha = 1.0f - io_outAlpha;
	}

	if(i_alphaIsLuminance != eiFALSE)
	{
		io_outAlpha = luminance( io_outColor );
	}

	io_outColor *= i_colorGain;
	io_outColor += i_colorOffset;

	io_outAlpha *= i_alphaGain;
	io_outAlpha += i_alphaOffset;
}	

