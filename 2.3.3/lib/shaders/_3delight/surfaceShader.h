/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __surfaceShader_h
#define __surfaceShader_h

/*
begin inputs
	color outColor
	color outTransparency
	color outMatteOpacity
	color outGlowColor
end inputs

begin outputs
	color outColor
	color outTransparency
	color outMatteOpacity
	color outGlowColor
end outputs
*/
void
maya_surfaceShader(
	color i_outColor, i_outTransparency, i_outMatteOpacity, i_outGlowColor;
	output color o_outColor, o_outTransparency, o_outMatteOpacity, o_outGlowColor;
)
{
	o_outColor = i_outColor;
	o_outTransparency = i_outTransparency;
	o_outMatteOpacity = i_outMatteOpacity;
	o_outGlowColor = i_outGlowColor;
}

#endif /* __surfaceShader_h */

