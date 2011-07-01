/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __remapValue_h
#define __remapValue_h

/*
begin inputs
	float inputValue
	float inputMin
	float inputMax
	float outputMin
	float outputMax

	float[] value[].value_Position
	float[] value[].value_FloatValue
	uniform float[] value[].value_Interp

	float[] color[].color_Position
	color[] color[].color_Color
	uniform float[] color[].color_Interp
end inputs

begin outputs
	float outValue
	color outColor
end outputs
*/

#include "ramp_utils.h"

void
maya_remapValue(
	// Inputs
	float i_value;
	float i_inputMin;
	float i_inputMax;
	float i_outputMin;
	float i_outputMax;

	float i_value_Position[];
	float i_value_FloatValue[];
	uniform float i_value_Interp[];

	float i_color_Position[];
	color i_color_Color[];
	uniform float i_color_Interp[];

	// Outputs
	output float o_outValue;
	output color o_outColor )
{
	// Apply input range
	float v = (i_value - i_inputMin) / (i_inputMax - i_inputMin);

	// Mimic maya's behavior when the input range is empty.
	if( i_inputMin == i_inputMax )
		v = 0;

	// Remap to value
	float out_v = floatRamp(
		v,
		i_value_Position,
		i_value_Interp,
		i_value_FloatValue );

	// Remap to color
	color out_c = colorRamp(
		v,
		i_color_Position,
		i_color_Interp,
		i_color_Color );

	// Apply output range
	o_outValue = i_outputMin + out_v * (i_outputMax - i_outputMin);
	o_outColor = i_outputMin + out_c * (i_outputMax - i_outputMin);
}

#endif /* __remapValue_h */

