/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __layeredTexture_h
#define __layeredTexture_h

/*
begin inputs
	color[] inputs[].color
	float[] inputs[].alpha
	uniform float[] inputs[].blendMode
	uniform float[] inputs[].isVisible
	float alphaIsLuminance
end inputs

begin outputs
	color outColor
	float outAlpha
	color outTransparency
end outputs
*/

#include "utils.h"

void
maya_layeredTexture(
	// Inputs
	color i_inputs_color[];
	float i_inputs_alpha[];
	uniform float i_inputs_blendMode[];
	uniform float i_inputs_isVisible[];
	float i_alphaIsLuminance;

	// Outputs
	output color o_outColor;
	output float o_outAlpha;
	output color o_outTransparency;
	)
{
	uniform float numLayers = arraylength( i_inputs_color );
	uniform float i;
	
	o_outColor = 0;
	o_outAlpha = 0;

	for( i = numLayers - 1; i >= 0; i -= 1 )
	{
		if( i_inputs_isVisible[i] != 1.0 )
			continue;

		color fc = i_inputs_color[i];
		float fa = i_inputs_alpha[i];
		uniform float blend = i_inputs_blendMode[i];

		if( blend == 0.0 ) /* None */
		{
			o_outColor = fc;
			o_outAlpha = fa;
		}
		else if( blend == 1.0 ) /* Over */
		{
			o_outColor = fc * fa + (o_outColor * (1 - fa));
			o_outAlpha = 1 - ((1 - o_outAlpha) * (1 - fa));
		}
		else if( blend == 2.0 ) /* In */
		{
			o_outColor *= fa;
			o_outAlpha *= fa;
		}
		else if( blend == 3.0 ) /* Out */
		{
			o_outColor *= (1 - fa);
			o_outAlpha *= (1 - fa);
		}
		else if( blend == 4.0 ) /* Add */
		{
			o_outColor += fc * fa;
		}
		else if( blend == 5.0 ) /* Subtract */
		{
			o_outColor -= fc * fa;
		}
		else if( blend == 6.0 ) /* Multiply */
		{
			o_outColor *= (fc * fa + 1 - fa);
		}
		else if( blend == 7.0 ) /* Difference */
		{
			o_outColor = (cabs((fc * fa) - o_outColor)) * fa + o_outColor * (1 - fa);
		}
		else if( blend == 8.0 ) /* Lighten */
		{
			o_outColor = (max((fc * fa), o_outColor)) * fa + o_outColor * (1 - fa);
		}
		else if( blend == 9.0 ) /* Darken */
		{
			o_outColor = (min((fc * fa), o_outColor)) * fa + o_outColor * (1 - fa);
		}
		else if( blend == 10.0 ) /* Saturate */
		{
			o_outColor *= (1 + (fc * fa));
		}
		else if( blend == 11.0 ) /* Desaturate */
		{
			o_outColor *= (1 - (fc * fa));
		}
		else /* 12.0 : Illuminate */
		{
			o_outColor *= (2 * fc * fa + 1 - fa);
		}
	}

	if( i_alphaIsLuminance != 0.0 )
	{
		o_outAlpha = luminance( o_outColor );
	}

	o_outTransparency = color( 1.0 - o_outAlpha );
}

#endif /* __layeredTexture_h */

