/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __reverse_h
#define __reverse_h

/*
begin inputs
	float3 input
end inputs

begin outputs
	float3 output
end outputs
*/

void
maya_reverse(
	// Inputs
	//
	float i_input[3];
	// Outputs
	//
	output float o_output[3];)
{
  o_output[0] = 1 - i_input[0];
  o_output[1] = 1 - i_input[1];
  o_output[2] = 1 - i_input[2];
}

#endif /* __reverse_h */

