/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __hsvToRgb_h
#define __hsvToRgb_h

/*
begin inputs
	color inHsv
end inputs

begin outputs
	color outRgb
end outputs
*/

void
maya_hsvToRgb(
	// Inputs:
	//
	color i_inHsv;
	// Outputs:
	//
	output color o_outRgb;)
{
	/* In Maya, 'H' is expressed in degrees */
	float H = comp( i_inHsv, 0 ) / 360.0;
	color tmp = color( H, comp(i_inHsv, 1), comp(i_inHsv, 2) );	
	o_outRgb = ctransform("hsv", "rgb", tmp);
}

#endif /* __hsvToRgb_h */

