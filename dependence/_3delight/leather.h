/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __leather_h
#define __leather_h

/*
begin inputs
	color cellColor
	color creaseColor
	float cellSize
	float density
	float spottyness
	float randomness
	float threshold
	float creases
	color defaultColor
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	color colorGain
	color colorOffset
	float invert
	float local
	float wrap
	float blend
	normal normalCamera
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

/* We use the "granite" function since it englobe the funcionality of
   "leather" */
#include "granite.h"

void
maya_leather(
	// Inputs
	//
	/* leather parameters */
	color i_cellColor;
	color i_creaseColor;
	float i_cellSize;
	float i_density;
	float i_spottyness;
	float i_randomness;
	float i_threshold;
	float i_creases;

	/* color related inputs */
	color i_defaultColor;
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	color i_colorGain;
	color i_colorOffset;
	uniform float i_invert;
	float i_local;
	float i_wrap;
	float i_blend;

	/* geomtric inputs */
	normal i_normalCamera;
	matrix i_placementMatrix;

	// Outputs
	//
	output float o_outAlpha;
	output color o_outColor; )
{
	maya_granite(
		i_cellColor, i_cellColor, i_cellColor, i_creaseColor,
		i_cellSize, i_density, 0.0 /* mixRatio, doesn't matter. */,
		i_spottyness, i_randomness, 
		i_threshold, i_creases,
		i_defaultColor, i_alphaGain, i_alphaIsLuminance, i_alphaOffset,
		i_colorGain, i_colorOffset,
		i_invert, i_local, i_wrap, i_blend,
		i_normalCamera, i_placementMatrix,
		o_outAlpha, o_outColor );
}

#endif /* __leather_h */

