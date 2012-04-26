/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __clamp_h
#define __clamp_h

/*
begin inputs
	color min
	color max
	color input
end inputs

begin outputs
	color output
end outputs
*/

void
maya_clamp(
	// Inputs:

	color i_min;
	color i_max;
	color i_input;
	// Outputs:

	output color o_output )
{
	o_output = clamp( i_input, i_min, i_max );
}

#endif /* __clamp_h */

