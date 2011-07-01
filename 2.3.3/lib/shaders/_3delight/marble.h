/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __marble_h
#define __marble_h

/*
begin inputs
	color fillerColor
	color veinColor
	float veinWidth
	float diffusion
	float contrast
	float amplitude
	float ratio
	uniform float3 ripples
	uniform float2 depth
	color defaultColor
	color colorGain
	color colorOffset
	float alphaGain
	float alphaOffset
	float alphaIsLuminance
	float invert
	float local
	float wrap
	float blend
	matrix placementMatrix
end inputs

begin outputs
	color outColor
	float outAlpha	
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "utils.h"
#include "noise_utils.h"
#include "texture3d.h"

void
maya_marble(
	/* "marble" parameters */
	color i_fillerColor;
	color i_veinColor;
	float i_veinWidth;
	float i_diffusion;
	float i_contrast;

	/* "noise" parameters */
	float i_amplitude;
	uniform float i_ratio;
	uniform float i_ripples[3];
	uniform float i_depth[2];
	
	/* "Color Balance" related parameters */
	color i_defaultColor, i_colorGain, i_colorOffset;
	float i_alphaGain, i_alphaOffset;
	uniform float i_alphaIsLuminance;

	/* "Effects" related parameters */
	uniform float i_invert;
	float i_local, i_wrap, i_blend;

	/* geomtric inputs */
	matrix i_placementMatrix;

	/* outputs */
	output color o_outColor;
	output float o_outAlpha;
)
{
	extern point P;
	extern float du, dv;
	
	float outside;
	float edgeDist;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if(outside < 1)
	{
		/* Perturb P's position */
		pp += vfBm( pp, i_depth, 2, i_ratio, i_ripples ) * i_amplitude;

		float y = ycomp(pp);
		float dy = filterwidth(y);

		/* d = distance to vein center */
		float d = min(1, (y - floor(y)) / (1-i_veinWidth));
		if (d > 0.5)
			d = 1 - d;

		/* The following is taken from mental RIB and seems to give results close
		   to Maya's */
		float mix = (1- filteredpulsetrain(1 - i_veinWidth, 1, y, dy) / (1 - i_veinWidth)) * i_contrast + 
			(1 - i_contrast) *  pow(2*d, i_diffusion) * (1 - i_diffusion * .3);

		o_outColor = mix(i_fillerColor, i_veinColor, 1-mix);
		o_outAlpha = luminance(o_outColor);
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __marble_h */

