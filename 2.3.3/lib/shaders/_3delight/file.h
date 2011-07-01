/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __file_h
#define __file_h

/*
begin inputs
	float alphaGain
	uniform float alphaIsLuminance
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

#include "utils.h"

void
maya_file(
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
	float ss = i_uvCoord[0];
	float tt = 1 - i_uvCoord[1];

	uniform float num_channels;
	textureinfo( i_fileName, "channels", num_channels );

	if(ISUVDEFINED(ss, tt))
	{
		uniform float filterWidth = i_filterType > 0 ? i_filter : 0;
    
		if( num_channels == 1 )
		{
			/* We must read single-channel files as float or only the red
			   channel will be filled. */
			o_outColor = float texture(i_fileName, ss, tt, "blur", i_filterOffset,
				"width", filterWidth);
		} else {
			o_outColor = texture(i_fileName, ss, tt, "blur", i_filterOffset, 
				"width", filterWidth);
		}

		if( num_channels > 3 )
		{
			o_outAlpha = texture(i_fileName[3], ss, tt, "blur", i_filterOffset,
				"width", filterWidth);
		} else {
			o_outAlpha = luminance( o_outColor );
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
		o_outAlpha = luminance( o_outColor );
	}
	
	o_outTransparency = color(1 - o_outAlpha, 1 - o_outAlpha, 1 - o_outAlpha);
}

#endif /* __file_h */

