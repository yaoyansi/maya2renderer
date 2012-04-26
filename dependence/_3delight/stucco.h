/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __stucco_h
#define __stucco_h

/*
begin inputs
	float shaker
	color channel1
	color channel2
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
maya_stucco(
	/* "stucco" parameters */
	float i_shaker;
	color i_channel1;
	color i_channel2;

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
	
	float outside, edgeDist;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if( outside < 1 )
	{
		uniform float depth[2] = {1, 10};
		o_outAlpha = fBm( pp, 0, 2.0, depth, 1, 2, 0.5 );
		o_outAlpha = pow( o_outAlpha, i_shaker/10 );
		o_outAlpha = clamp( o_outAlpha, 0, 1 );
		o_outColor = mix( i_channel1, i_channel2, o_outAlpha );
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __stucco_h */

