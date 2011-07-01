/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __wood_h
#define __wood_h

/*
begin inputs
	color fillerColor
	color veinColor
	float veinSpread
	float layerSize
	float randomness
	float age
	color grainColor
	float grainContrast
	float grainSpacing
	float2 center
	float amplitudeX
	float amplitudeY
	float ratio
	uniform float3 ripples
	uniform float2 depth
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

#include "utils.h"
#include "noise_utils.h"
#include "texture3d.h"

void
maya_wood(
	color i_fillerColor,i_veinColor;
	float i_veinSpread, i_layerSize, i_randomness, i_age;
	color i_grainColor;
	float i_grainContrast, i_grainSpacing;
	float i_center[2];

	/* Noise parameters */
	float i_amplitudeX, i_amplitudeY;
	uniform float i_ratio, i_ripples[3], i_depth[2];

	/* "Color Balance" related parameters */
	color i_defaultColor, i_colorGain, i_colorOffset;
	float i_alphaGain, i_alphaOffset;
	uniform float i_alphaIsLuminance;

	/* "Effects" related parameters */
	uniform float i_invert;
	float i_local, i_wrap, i_blend;

	/* geomtric inputs */
	matrix i_placementMatrix;

	/* outputs */
	output color o_outColor;
	output float o_outAlpha; )
{
	extern float du, dv;
	float outside, edgeDist;

	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside );

	if( outside < 1 )
	{
		/* The pattern is defined in the 1x1 square */
		pp = point( mod(xcomp(pp),1), mod(ycomp(pp), 1), zcomp(pp) );

		vector perturb = 0;
		if( (i_amplitudeX>0 || i_amplitudeY>0) )
			perturb = vfBm( pp, i_depth, 2, i_ratio, i_ripples );
	
		/* Perturb P's position */
		float ss = ((xcomp(pp)+xcomp(perturb)*i_amplitudeX) - i_center[0]) / i_layerSize;
		float tt = ((ycomp(pp)+ycomp(perturb)*i_amplitudeY) - i_center[1]) / i_layerSize;

		//ss += i_center[0];
		//tt += i_center[1];

		float r = pow( sqrt( ss*ss + tt*tt ), 1 );
		r += i_randomness * noise(r);
		if( r < 0 )
			r = 0;

		/* d = distance to layer start */
		float d = r - floor( r );

		/* mix vain and fill color together depending on veinSpread. This is an
		   approximation so results are not exactly similar to maya.
		   The 2.5 is a fudge factor to match maya's look. */
		if( d > i_veinSpread*2.5 )
			o_outColor = i_fillerColor;
		else
		{
			d = smoothstep( 0, i_veinSpread * 2.5, d );
			d = sqrt( d );
			o_outColor = mix( i_veinColor, i_fillerColor, d );
		}

		if( i_grainContrast > 0 )
		{
			/* TODO: add grain */
		}

		o_outAlpha = d;
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __wood_h */

