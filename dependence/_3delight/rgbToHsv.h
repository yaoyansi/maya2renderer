/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __rgbToHsv_h
#define __rgbToHsv_h

/*
begin inputs
	color inRgb
end inputs

begin outputs
	color outHsv
end outputs
*/

void
maya_rgbToHsv(
	// Inputs:
	//
	color i_inRgb;
	// Outputs:
	//
	output color o_outHsv;)
{
	o_outHsv = ctransform("rgb", "hsv", i_inRgb);
	
	/* In Maya, 'H' is expressed in degrees */
	float H = comp( o_outHsv, 0 ) * 360.0;
	setcomp( o_outHsv, 0, H );
}

#endif /* __rgbToHsv_h */

