/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __stencil_h
#define __stencil_h

/*
begin inputs
	float alphaGain
	float alphaOffset
	color colorGain
	color colorOffset
	color defaultColor
	float invert
	init={ss,tt} float2 uvCoord

	color image
	float mask
	float edgeBlend
	float keyMasking
	float positiveKey
	color colorKey
	float hueRange
	float saturationRange
	float valueRange
	float threshold
end inputs
begin outputs
	float outAlpha
	color outColor
end outputs
*/

#include "utils.h"

void
maya_stencil(
	// Inputs
	float i_alphaGain;
	float i_alphaOffset;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	uniform float i_invert;
	float i_uvCoord[2];

	color i_image;
	float i_mask;
	float i_edgeBlend;
	float i_keyMasking;
	float i_positiveKey;
	color i_colorKey;
	float i_hueRange;
	float i_saturationRange;
	float i_valueRange;
	float i_threshold;

	// Outputs
	output float o_outAlpha;
	output color o_outColor;
)
{
	varying float ss = i_uvCoord[0];
	varying float tt = i_uvCoord[1];

	ss = mod(ss, 1);
	tt = mod(tt, 1);
  
	float mask = i_mask;

	if( i_edgeBlend > 0 )
	{
		float edgeBlend = i_edgeBlend * 0.5;
		float border = smoothstep( 0, edgeBlend, abs(ss) );
		border *= smoothstep( 0, edgeBlend, abs(1 - ss));
		border *= smoothstep( 0, edgeBlend, abs(tt));
		border *= smoothstep( 0, edgeBlend, abs(1 - tt));

		/* Using a max() here looks better (IMO) but we do it the maya way. */
		mask += 1 - border;
	}

	mask = clamp( mask, 0, 1 );

	o_outColor = mix( i_image, i_defaultColor, mask );
	o_outAlpha = mask;

	colorBalance(
		o_outColor, 
		o_outAlpha,
		0,
		i_alphaGain,
		i_alphaOffset,
		i_colorGain,
		i_colorOffset,
		i_invert );

	if( i_keyMasking != 0 )
	{
		color img_hsv = ctransform( "hsv", i_image );
		color key_hsv = ctransform( "hsv", i_colorKey );
		color diff = img_hsv - key_hsv;

		float inKey = i_positiveKey;

		if(
			abs( comp( diff, 0 ) ) <= i_hueRange &&
			abs( comp( diff, 1 ) ) <= i_saturationRange &&
			abs( comp( diff, 2 ) ) <= i_valueRange )
		{
			inKey = 1 - i_positiveKey;
		}

		if( inKey != 0 )
		{
			o_outColor = i_defaultColor;
			o_outAlpha = 1.0;
		}
	}
}

#endif /* __stencil_h */

