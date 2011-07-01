/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __rock_h
#define __rock_h

/*
begin inputs
	color color1
	color color2
	float grainSize
	float diffusion
	float mixRatio
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
	float outAlpha
	color outColor
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "texture3d.h"
#include "utils.h"

void
maya_rock(
	/* "rock" related parameters */
	color i_color1, i_color2;
	float i_grainSize, i_diffusion, i_mixRatio;

	/* "Color Balance" related parameters */
	color i_defaultColor, i_colorGain, i_colorOffset;
	float i_alphaGain, i_alphaOffset;
	uniform float i_alphaIsLuminance;

	/* "Effects" related parameters */
	uniform float i_invert;
	float i_local;
	float i_wrap;
	float i_blend;

	/* geomtric inputs */
	matrix i_placementMatrix;

	// Outputs
	//
	output float o_outAlpha;
	output color o_outColor; )
{
	extern point P;
	
	float outside;
	float edgeDist;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if(outside < 1)
	{
		/* This is directly taken from mentalRib by Peter Quint and seems to work
		   just fine. */
		float mx = noise( pp / (2*i_grainSize)) + i_mixRatio * 0.8 - 0.4;
		mx = smoothstep( 0.5 * (1-i_diffusion), 1-0.5*(1-i_diffusion), mx );
		mx = clamp( mx, 0, 1 );
 
		o_outColor = mix( i_color1, i_color2, mx );
		o_outAlpha = 1 - mx;
 
		colorBalance( o_outColor, 
			o_outAlpha, 
			i_alphaIsLuminance, 
			i_alphaGain, 
			i_alphaOffset, 
			i_colorGain, 
			i_colorOffset, 
			i_invert );
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __rock_h */

