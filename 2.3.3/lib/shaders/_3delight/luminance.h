/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __luminance_h
#define __luminance_h

/*
begin inputs
	color value
end inputs

begin outputs
	float outValue
end outputs
*/

void
maya_luminance(
	// Inputs:
	//
	color i_value;
	// Outputs:
	//
	output float o_outValue;)
{
	o_outValue = 0.3 * comp(i_value, 0) + 
		0.59 * comp(i_value, 1) + 
		0.11 * comp(i_value, 2);
}

#endif /* __luminance_h */

