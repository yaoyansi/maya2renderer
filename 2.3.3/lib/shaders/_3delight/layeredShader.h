/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __layeredShader_h
#define __layeredShader_h

/*
begin inputs
	float compositingFlag
	color[] inputs[].color
	color[] inputs[].transparency
	float matteOpacityMode
	float matteOpacity
end inputs

begin outputs
	color outColor
	color outTransparency
end outputs
*/

#include "shading_utils.h"

void
maya_layeredShader(
	// Inputs
	uniform float i_compositingFlag;
	color i_inputs_color[];
	color i_inputs_transparency[];
	float i_matteOpacityMode;
	float i_matteOpacity;

	// Outputs
	output color o_outColor;
	output color o_outTransparency;
	)
{
	color transparency;

	uniform float nlayers = arraylength( i_inputs_color );
	uniform float i;

	o_outColor = 0;
	o_outTransparency = 1;

	for( i = 0; i < nlayers; i += 1 )
	{
		color trs = i_inputs_transparency[i];
		color col = i_inputs_color[i];

		if( i_compositingFlag == 1 )
		{
			// Layer texture mode
			col *= (1 - trs);
		}

		o_outColor += col * o_outTransparency;
		o_outTransparency *= trs;
	}

	computeSurfaceTransparency(
		i_matteOpacityMode, i_matteOpacity,
		o_outTransparency, o_outTransparency );
}

#endif /* __layeredShader_h */

