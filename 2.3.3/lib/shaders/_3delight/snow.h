/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __snow_h
#define __snow_h

/*
begin inputs
	color snowColor
	color surfaceColor
	float threshold
	float depthDecay
	float thickness
	color defaultColor
	color colorGain
	color colorOffset
	float alphaGain
	float alphaOffset
	float alphaIsLuminance
	float invert
	float local
	float wrap
	float blend
	normal normalCamera
	matrix placementMatrix
end inputs

begin outputs
	color outColor
	float outAlpha	
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "texture3d.h"
#include "utils.h"

void
maya_snow(
	/* "marble" parameters */
	color i_snowColor;
	color i_surfaceColor;
	float i_threshold;
	float i_depthDecay;
	float i_thickness;

	/* "Color Balance" related parameters */
	color i_defaultColor, i_colorGain, i_colorOffset;
	float i_alphaGain, i_alphaOffset;
	uniform float i_alphaIsLuminance;

	/* "Effects" related parameters */
	uniform float i_invert;
	float i_local, i_wrap, i_blend;

	/* geomtric inputs */
	normal i_normalCamera;
	matrix i_placementMatrix;

	/* outputs */
	output color o_outColor;
	output float o_outAlpha;
)
{
	extern point P;
	extern float du, dv;
	
	float outside;
	float edgeDist;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if( outside < 1 )
	{
		normal n;

		if( i_local != 0.0 )
			n = ntransform("object", i_normalCamera);
		else
			n = ntransform("world", i_normalCamera);

		n = ntransform( i_placementMatrix, n );

		float cosangle = normalize(n) . vector(0, 1, 0);		

		if( cosangle < 0 )
		{
			/* In Maya's world, snow cannot stick under objects */
			o_outColor = i_surfaceColor;
		}
		else
		{
			if( cosangle > i_threshold )
			{
				color snow = mix(i_snowColor, i_surfaceColor, 1-i_thickness );
				float mix = (1 - cosangle) / (1-i_threshold);
				mix = pow( mix, i_depthDecay );
				o_outColor = mix(snow, i_surfaceColor, mix);
			}
			else
			{
				o_outColor = i_surfaceColor;
			}
		}

		o_outAlpha = 1;
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __snow_h */

