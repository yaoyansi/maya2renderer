/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __blendColors_h
#define __blendColors_h

/*
begin inputs
	float blender
	color color1
	color color2
end inputs

begin outputs
	color output
end outputs
*/

void
maya_blendColors(
	// Inputs
	//
	float i_blender;
	color i_color1;
	color i_color2;
	// Outpus
	//
	output color o_output;)
{
	o_output = mix(i_color2, i_color1, i_blender);
}

#endif /* __blendColors_h */

