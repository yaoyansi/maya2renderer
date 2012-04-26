/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __gammaCorrect_h
#define __gammaCorrect_h

/*
begin inputs
	color value
	color gamma
end inputs

begin outputs
	color outValue
end outputs
*/

void
maya_gammaCorrect(
	// Inputs
	//
	color i_value;
	color i_gamma;
	// Outputs
	//
	output color o_value;)
{
	o_value = color(
		pow(comp(i_value, 0), 1.0 / comp(i_gamma, 0)),
		pow(comp(i_value, 1), 1.0 / comp(i_gamma, 1)),
		pow(comp(i_value, 2), 1.0 / comp(i_gamma, 2)));
}

#endif /* __gammaCorrect_h */

