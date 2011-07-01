/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __checker_h
#define __checker_h

/*
begin inputs
	float alphaGain
	float alphaIsLuminance
	float alphaOffset
	color color1
	color color2
	color colorGain
	color colorOffset
	float contrast
	color defaultColor
	float filter
	float filterOffset
	float invert
	init={ss,tt} float2 uvCoord
end inputs

begin outputs
	float outAlpha
	color outColor
end outputs
*/

#include "utils.h"

void
maya_checker(
  // Inputs:
  //
  float i_alphaGain;
  uniform float i_alphaIsLuminance;
  float i_alphaOffset;
  color i_color1;
  color i_color2;
  color i_colorGain;
  color i_colorOffset;
  uniform float i_contrast;
  color i_defaultColor;
  float i_filter;
  float i_filterOffset;
  uniform float i_invert;
  float i_uvCoord[2];

  // Outputs:
  //
  output float o_outAlpha;
  output color o_outColor;
  )
{
	extern float du, dv;

	varying float ss = i_uvCoord[0];
	varying float tt = i_uvCoord[1];
	
	if(ISUVDEFINED(ss, tt))
	{
		ss = mod(ss, WRAPMAX);
		tt = mod(tt, WRAPMAX);
		
		/* compute 'ss' and 'tt' filter widths */
		float dss = abs(Du(ss) * du) + abs(Dv(ss) * dv);
		float dtt = abs(Du(tt) * du) + abs(Dv(tt) * dv);


		/* Add in "Effects" filter values. We multiplie the i_filterOffset
		   variable by 2 to match Maya's look */ 
		dss = dss * i_filter + i_filterOffset*2; 
		dtt = dtt * i_filter + i_filterOffset*2; 

		/* compute separation: 0 for half the squares, 1 for the others. */
		float f = 0.5 - 2 *
			(filteredpulsetrain(0.5, 1, ss, dss) - 0.5) *
			(filteredpulsetrain(0.5, 1, tt, dtt) - 0.5);

		/* contrast interpolates the separation from 0.5 to its normal value. */
		f = 0.5 + (f - 0.5) * i_contrast;

		/* Compute final values. */
		o_outAlpha = 1 - f;
		o_outColor = i_color1 + (i_color2 - i_color1) * f;

		colorBalance(o_outColor, 
			o_outAlpha,
			i_alphaIsLuminance,
			i_alphaGain,
			i_alphaOffset,
			i_colorGain,
			i_colorOffset,
			i_invert);
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = luminance( i_defaultColor );
	}
}

#endif /* __checker_h */

