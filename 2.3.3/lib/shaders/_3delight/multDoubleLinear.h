/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __multDoubleLinear_h
#define __multDoubleLinear_h

/*
begin inputs
	float input1
	float input2
end inputs

begin outputs
	float output
end outputs
*/

void
maya_multDoubleLinear(
	// Inputs
	//
	float i_input1;
	float i_input2;

	// Outputs
	//
	output float o_output;)
{
	o_output = i_input1 * i_input2;
}

#endif /* __multDoubleLinear_h */

