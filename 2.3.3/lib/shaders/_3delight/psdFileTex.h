/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __psdFileTex_h
#define __psdFileTex_h

/*
begin inputs
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	color colorGain
	color colorOffset
	color defaultColor
	texture string fileTextureName
	uniform float filterType
	uniform float filter
	float filterOffset
	float invert
	init={ss,tt} float2 uvCoord
end inputs

begin outputs
	float outAlpha
	color outColor
	color outTransparency
	
end outputs
*/

#include "file.h"

void
maya_psdFileTex(
	// Inputs:
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	uniform string i_fileName;
	uniform float i_filterType;
	uniform float i_filter;
	float i_filterOffset;
	uniform float i_invert;
	float i_uvCoord[2];
	
	// Outputs
	//
	output float o_outAlpha;
	output color o_outColor;
	output color o_outTransparency;
	)
{
	maya_file(
		i_alphaGain, i_alphaIsLuminance, i_alphaOffset,
		i_colorGain, i_colorOffset, i_defaultColor,
		i_fileName, i_filterType, i_filter, i_filterOffset,
		i_invert, i_uvCoord,
		o_outAlpha, o_outColor, o_outTransparency );
}

#endif /* __psdFileTex_h */

