/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __envSphere_h
#define __envSphere_h

/*
begin inputs
	prepare color image
	float2 shearUV
	uniform float flip
	normal normalCamera
	matrix placementMatrix

	nonplug float prev_ss
	nonplug float prev_tt
	declare float prev_ss
	declare float prev_tt
end inputs

begin outputs
	color outColor
	float outAlpha
end outputs
*/

#include "utils.h"

void
prepare_maya_envSphere(
	// Inputs
	color i_image;
	float i_shearUV[2];
	uniform float i_flip;
	normal i_normalCamera;
	matrix i_placementMatrix;

	output float o_prev_ss;
	output float o_prev_tt;

	// Outputs
	output color o_outColor;
	output float o_outAlpha )
{
	extern vector I;
	extern varying float ss, tt;

	o_prev_ss = ss;
	o_prev_tt = tt;

	vector R;
	R = reflect(I, normalize(i_normalCamera));
	R = vtransform( "world", R );
	R = vtransform( i_placementMatrix, R );

	float px = xcomp(R);
	float py = ycomp(R);
	float pz = zcomp(R);

	float signed_s = atan( px, pz ) / (2 * PI);
	float signed_t = atan( py, sqrt( px*px + pz*pz ) ) / PI;

	ss = signed_s + 0.5 + i_shearUV[0] * signed_t;
	tt = signed_t + 0.5 + i_shearUV[1] * signed_s;

	if( i_flip != 0 )
	{
		float tmp = ss;
		ss = tt;
		tt = tmp;
	}
}

void
end_maya_envSphere(
	// Inputs
	color i_image;
	float i_shearUV[2];
	uniform float i_flip;
	normal i_normalCamera;
	matrix i_placementMatrix;

	float i_prev_ss;
	float i_prev_tt;

	// Outputs
	output color o_outColor;
	output float o_outAlpha )
{
	extern varying float ss;
	extern varying float tt;

	ss = i_prev_ss;
	tt = i_prev_tt;

	o_outColor = i_image;
	o_outAlpha = luminance( o_outColor );
}

#endif /* __envSphere_h */

