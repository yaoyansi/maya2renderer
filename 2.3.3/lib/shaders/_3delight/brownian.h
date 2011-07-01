/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __brownian_h
#define __brownian_h

/*
begin inputs
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	float blend
	color colorGain
	color colorOffset
	color defaultColor
	float filter
	float filterOffset
	float3 filterSize
	float increment
	float invert
	float local
	float lacunarity
	float octaves
	float3 weight3d
	matrix placementMatrix
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
maya_brownian(
	// Inputs
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	float i_blend;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	float i_filter;
	float i_filterOffset;
	float i_filterSize[3];
	uniform float i_increment;
	uniform float i_invert;
	uniform float i_local;
	uniform float i_lacunarity;
	uniform float i_octaves;
	float i_weight3d[3];
	matrix i_placementMatrix;
	float i_wrap;

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
		varying point pn = pp * point(i_weight3d[0], i_weight3d[1], i_weight3d[2]);

		float i = 1;
		float amp = 1;
		float sum = 0;
		varying point pq = pn;
		float filterWidth = area(pq);
		float inc = (i_increment < 1.0 ? 1.0 - i_increment : i_increment);

		for(i = 0.99; i < i_octaves; i += inc)
		{
			sum += amp * filteredsnoise(pq, filterWidth);
			amp *= inc;
			pq *= i_lacunarity;
			filterWidth *= i_lacunarity;
		}

		o_outAlpha = sum;
		o_outColor = clamp((o_outAlpha + 1) / 2, 0, 1);

		colorBalance(o_outColor, 
			o_outAlpha, 
			i_alphaIsLuminance, 
			i_alphaGain, 
			i_alphaOffset, 
			i_colorGain, 
			i_colorOffset, 
			i_invert);

		if(i_blend > 0 && edgeDist >= 0)
		{
			o_outColor = blendDefaultColor(i_blend, i_defaultColor, edgeDist, o_outColor);
		}
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}
	
#endif /* __brownian_h */

