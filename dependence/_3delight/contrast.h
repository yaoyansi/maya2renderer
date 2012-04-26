/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __contrast_h
#define __contrast_h

/*
begin inputs
	color value
	color contrast
	color bias
end inputs

begin outputs
	color outValue
end outputs
*/

#include "utils.h"

float
mayaContrast(
	float i_value;
	float i_contrast;
	float i_bias;)
{
	// Compute biased value 
	float value = pow(i_value + EPSILON, log(0.5) / log(i_bias));

	float outValue;
	
	if (value < 0.5)
	{
		outValue = 0.5 * pow(2 * value, i_contrast);
	}
	else
	{
		outValue = 1.0 - 0.5 * pow(2 * (1 - value), i_contrast);
	}

	return outValue;
}

void
maya_contrast(
	// Inputs
	//
	color i_value;
	color i_contrast;
	color i_bias;
	// Outputs
	//
	output color o_outputValue;)
{
	float r = mayaContrast(comp(i_value, 0), 
		comp(i_contrast, 0), 
		comp(i_bias, 0));

	float g = mayaContrast(comp(i_value, 1), 
		comp(i_contrast, 1), 
		comp(i_bias, 1));

	float b = mayaContrast(comp(i_value, 2), 
		comp(i_contrast, 2), 
		comp(i_bias, 2));

	o_outputValue = color(r, g, b);
}

#endif /* __contrast_h */

