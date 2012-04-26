/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __cloud_h
#define __cloud_h

/*
begin inputs
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	float amplitude
	float blend
	float centerThresh
	color color1
	color color2
	color colorGain
	color colorOffset
	float contrast
	color defaultColor
	uniform float2 depth
	float edgeThresh
	float invert
	float local
	normal normalCamera
	matrix placementMatrix
	float ratio
	float3 ripples
	float softEdges
	float transpRange
	float wrap
end inputs

begin outputs
	float outAlpha
	color outColor
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "texture3d.h"
#include "utils.h"
#include "noise_utils.h"

void
maya_cloud(
	// Inputs
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	uniform float i_amplitude;
	float i_blend;
	float i_centerThreshold;
	color i_color1;
	color i_color2;
	color i_colorGain;
	color i_colorOffset;
	float i_contrast;
	color i_defaultColor;
	uniform float i_depth[2];
	float i_edgeThreshold;
	uniform float i_invert;
	float i_local;
	normal i_normalCamera;
	matrix i_placementMatrix;
	uniform float i_ratio;
	float i_ripples[3];
	float i_softEdges;
	float i_transparentRange;
	float i_wrap;

	// Outputs
	//
	output float o_outAlpha;
	output color o_outColor;)
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
		float mix = fBrownianNoise(pp, 0, i_amplitude, 1, 2, i_depth, i_ratio, i_ripples);
		color c1 = i_color1;

		o_outAlpha = mix;
		c1 = mix(i_color2, c1, i_contrast);
		o_outColor = mix(i_color2, c1, 1 - mix);

		if(i_softEdges > 0)
		{
			o_outColor *= 1 - mix;
		}
		
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

#endif /* __cloud_h */

