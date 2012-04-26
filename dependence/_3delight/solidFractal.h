/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __solidFractal_h
#define __solidFractal_h

/*
begin inputs
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	float amplitude
	float animated
	float bias
	float blend
	color colorGain
	color colorOffset
	color defaultColor
	uniform float2 depth
	float filter
	float filterOffset
	float3 filterSize
	float frequencyRatio
	float inflection
	float invert
	float local
	uniform matrix placementMatrix
	float ratio
	float threshold
	float time
	float timeRatio
	float3 ripples
	float wrap
end inputs

begin outputs
	color outColor
	float outAlpha
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "texture3d.h"
#include "utils.h"
#include "noise_utils.h"

void
maya_solidFractal(
	// Inputs
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	float i_amplitude;
	uniform float i_animated;
	float i_bias;
	float i_blend;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	uniform float i_depth[2];
	float i_filter;
	float i_filterOffset;
	float i_filterSize[3];
	uniform float i_frequencyRatio;
	uniform float i_inflection;
	uniform float i_invert;
	uniform float i_local;
	uniform matrix i_placementMatrix;
	uniform float i_ratio;
	uniform float i_threshold;
	uniform float i_time;
	uniform float i_timeRatio;
	float i_ripples[3];
	uniform float i_wrap;

	// Outputs
	//
	output color o_outColor;
	output float o_outAlpha;)
{
	float edgeDist;
	float outside;
	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside);

	if(outside < 1)
	{
		uniform float time = 0;

		if(i_animated > 0)
		{
			time = i_time * i_timeRatio;
		}

		float fractal;

		if(i_inflection > 0)
		{
			fractal = fTurbulence(
				pp, time, 
				1, i_frequencyRatio, i_depth, i_ratio, i_ripples);
		}
		else
		{
			fractal = fBrownianNoise(
				pp, time, 1, 
				1, i_frequencyRatio, i_depth, i_ratio, i_ripples );
		}

		fractal += i_threshold;
		
		float sn = sign(fractal);

		if(i_bias > 0.0)
		{
			fractal = sn * pow(abs(fractal), 1 - i_bias * 0.5);
		}
		else if(i_bias <  0.0)
		{
			fractal = sn * pow(abs(fractal), 1 / (1 + i_bias));
		}

		fractal *= i_amplitude;
		o_outAlpha = clamp(fractal + i_threshold, 0, 1);
		o_outColor = mix(0, 1, o_outAlpha);

		colorBalance(o_outColor, 
			o_outAlpha, 
			i_alphaIsLuminance, 
			i_alphaGain, 
			i_alphaOffset, 
			i_colorGain, 
			i_colorOffset, 
			i_invert);
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __solidFractal_h */

