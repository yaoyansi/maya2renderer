/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __remapHsv_h
#define __remapHsv_h

/*
begin inputs
	color color
	float inputMin
	float inputMax
	float outputMin
	float outputMax

	float[] hue[].hue_Position
	float[] hue[].hue_FloatValue
	uniform float[] hue[].hue_Interp

	float[] saturation[].saturation_Position
	float[] saturation[].saturation_FloatValue
	uniform float[] saturation[].saturation_Interp

	float[] value[].value_Position
	float[] value[].value_FloatValue
	uniform float[] value[].value_Interp
end inputs

begin outputs
	color outColor
end outputs
*/

#include "ramp_utils.h"

void
maya_remapHsv(
	// Inputs
	color i_color;
	float i_inputMin;
	float i_inputMax;
	float i_outputMin;
	float i_outputMax;

	float i_hue_Position[];
	float i_hue_FloatValue[];
	uniform float i_hue_Interp[];

	float i_saturation_Position[];
	float i_saturation_FloatValue[];
	uniform float i_saturation_Interp[];

	float i_value_Position[];
	float i_value_FloatValue[];
	uniform float i_value_Interp[];

	// Outputs
	output color o_outColor )
{
	// Apply input range
	color c = (i_color - i_inputMin) / (i_inputMax - i_inputMin);

	// Mimic maya's behavior when the input range is empty.
	if( i_inputMin == i_inputMax )
		c = 0;

	// Convert to hsv
	c = ctransform( "hsv", c );

	// Remap hue
	float hue = floatRamp(
		comp( c, 0 ),
		i_hue_Position,
		i_hue_Interp,
		i_hue_FloatValue );

	setcomp( c, 0, hue );

	// Remap saturation
	float saturation = floatRamp(
		comp( c, 1 ),
		i_saturation_Position,
		i_saturation_Interp,
		i_saturation_FloatValue );

	setcomp( c, 1, saturation );

	// Remap value
	float value = floatRamp(
		comp( c, 2 ),
		i_value_Position,
		i_value_Interp,
		i_value_FloatValue );

	setcomp( c, 2, value );

	// Convert back to rgb
	c = ctransform( "hsv", "rgb", c );

	// Apply output range
	o_outColor = i_outputMin + c * (i_outputMax - i_outputMin);
}

#endif /* __remapHsv_h */

