/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __envChrome_h
#define __envChrome_h

/*
begin inputs
	color skyColor
	color zenithColor
	color lightColor
	float lightWidth
	float lightWidthGain
	float lightWidthOffset
	float lightDepth
	float lightDepthGain
	float lightDepthOffset
	uniform float realFloor
	color floorColor
	float floorAltitude
	color horizonColor
	color gridColor
	float gridWidth
	float gridWidthGain
	float gridWidthOffset
	float gridDepth
	float gridDepthGain
	float gridDepthOffset
	normal normalCamera
	matrix placementMatrix
end inputs

begin outputs
	color outColor
	float outAlpha
end outputs
*/

#include "utils.h"

float line_pattern(
	float pos;
	float size, spacing, offset )
{
	float npos = (pos - offset) / spacing;
	float lpos = npos - floor(npos);

	float l = 1 - filterstep( size, lpos );

	// TODO: fade away the lights as they become too small to avoid aliasing.

	return l;
}

void
maya_envChrome(
	// Inputs
	color i_skyColor;
	color i_zenithColor;
	color i_lightColor;
	float i_lightWidth;
	float i_lightWidthGain;
	float i_lightWidthOffset;
	float i_lightDepth;
	float i_lightDepthGain;
	float i_lightDepthOffset;
	uniform float i_realFloor;
	color i_floorColor;
	float i_floorAltitude;
	color i_horizonColor;
	color i_gridColor;
	float i_gridWidth;
	float i_gridWidthGain;
	float i_gridWidthOffset;
	float i_gridDepth;
	float i_gridDepthGain;
	float i_gridDepthOffset;
	normal i_normalCamera;
	matrix i_placementMatrix;

	// Outputs
	output color o_outColor;
	output float o_outAlpha )
{
	extern vector I;

	vector R;
	R = reflect(I, normalize(i_normalCamera));
	R = vtransform( "world", R );
	R = vtransform( i_placementMatrix, R );

	float rx = xcomp(R);
	float ry = ycomp(R);
	float rz = zcomp(R);

	vector Rn = R / abs(ry);

	float elevation = atan( ry, sqrt(rx*rx + rz*rz) );
	float norm_elev = abs(elevation) / (PI / 2 );

	if( ry > 0 )
	{
		float l1 = line_pattern(
			xcomp(Rn), i_lightWidth, i_lightWidthGain, i_lightWidthOffset );

		float l2 = line_pattern(
			zcomp(Rn), i_lightDepth, i_lightDepthGain, i_lightDepthOffset );

		float l = min( l1, l2 );

		color sky = mix( i_skyColor, i_zenithColor, norm_elev );

		o_outColor = mix( sky, i_lightColor, l );
	}
	else
	{
		float f1 = line_pattern(
			xcomp(Rn), i_gridWidth, i_gridWidthGain, i_gridWidthOffset );

		float f2 = line_pattern(
			zcomp(Rn), i_gridDepth, i_gridDepthGain, i_gridDepthOffset );

		float f = max( f1, f2 );

		color floor_color = mix( i_horizonColor, i_floorColor, norm_elev );

		o_outColor = mix( floor_color, i_gridColor, f );
	}

	o_outAlpha = luminance( o_outColor );
}

#endif /* __envChrome_h */

