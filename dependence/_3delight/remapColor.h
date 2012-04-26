/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __remapColor_h
#define __remapColor_h

/*
begin inputs
	color color
	float inputMin
	float inputMax
	float outputMin
	float outputMax

	float[] red[].red_Position
	float[] red[].red_FloatValue
	uniform float[] red[].red_Interp

	float[] green[].green_Position
	float[] green[].green_FloatValue
	uniform float[] green[].green_Interp

	float[] blue[].blue_Position
	float[] blue[].blue_FloatValue
	uniform float[] blue[].blue_Interp
end inputs

begin outputs
	color outColor
end outputs
*/

#include "ramp_utils.h"

void
maya_remapColor(
	// Inputs
	color i_color;
	float i_inputMin;
	float i_inputMax;
	float i_outputMin;
	float i_outputMax;

	float i_red_Position[];
	float i_red_FloatValue[];
	uniform float i_red_Interp[];

	float i_green_Position[];
	float i_green_FloatValue[];
	uniform float i_green_Interp[];

	float i_blue_Position[];
	float i_blue_FloatValue[];
	uniform float i_blue_Interp[];

	// Outputs
	output color o_outColor )
{
	// Apply input range
	color c = (i_color - i_inputMin) / (i_inputMax - i_inputMin);

	// Mimic maya's behavior when the input range is empty.
	if( i_inputMin == i_inputMax )
		c = 0;

	// Remap red
	float red = floatRamp(
		comp( c, 0 ),
		i_red_Position,
		i_red_Interp,
		i_red_FloatValue );

	setcomp( c, 0, red );

	// Remap green
	float green = floatRamp(
		comp( c, 1 ),
		i_green_Position,
		i_green_Interp,
		i_green_FloatValue );

	setcomp( c, 1, green );

	// Remap blue
	float blue = floatRamp(
		comp( c, 2 ),
		i_blue_Position,
		i_blue_Interp,
		i_blue_FloatValue );

	setcomp( c, 2, blue );

	// Apply output range
	o_outColor = i_outputMin + c * (i_outputMax - i_outputMin);
}

#endif /* __remapColor_h */

