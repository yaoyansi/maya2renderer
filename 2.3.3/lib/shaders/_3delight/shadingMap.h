/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __shadingMap_h
#define __shadingMap_h

/*
begin inputs
	color color
	prepare color shadingMapColor
	prepare color transparency	
	float mapFunctionU
	float mapFunctionV
	float matteOpacityMode
	prepare float matteOpacity
	nonplug float prev_ss
	nonplug float prev_tt
	declare float prev_ss
	declare float prev_tt
end inputs

begin outputs
	color outColor
	color outTransparency
end outputs
*/

#include "shading_utils.h"

float computeMapping(
	uniform float i_func;
	color i_color )
{
  float r = 0;

  if( i_func == 0 )  /* Hue */
    r = comp( ctransform("hsv", i_color),0 );
  else if( i_func == 1 ) /* Saturation */
    r = comp( ctransform("hsv", i_color),1 );
  else if( i_func == 2 ) /* Value */
    r = comp( ctransform("hsv", i_color),2 );
  else if( i_func == 3 ) /* R */
    r = comp(i_color,0);
  else if( i_func == 4 ) /* G */
    r = comp(i_color,1);
  else if( i_func == 5 ) /* B */
    r = comp(i_color,2);
  else if( i_func == 6 ) /* RGB average */
    r = (comp(i_color,0) + comp(i_color,1) + comp(i_color,2)) / 3;

  return clamp(r,0,1);
}

void
prepare_maya_shadingMap(
	color i_color, i_shadingMapColor, i_transparency;
	uniform float i_mapFunctionU, i_mapFunctionV;
	float i_matteOpacityMode, i_matteOpacity;

	output float o_prev_ss;
	output float o_prev_tt;

	output color o_outColor;
	output color o_outTransparency; )
{
	extern varying float ss, tt;

	o_prev_ss = ss;
	o_prev_tt = tt;


	ss = computeMapping( i_mapFunctionU, i_color );
	tt = computeMapping( i_mapFunctionV, i_color );
}

void
end_maya_shadingMap(
	color i_color, i_shadingMapColor, i_transparency; 
	uniform float i_mapFunctionU, i_mapFunctionV;
	float i_matteOpacityMode, i_matteOpacity;

	float i_prev_ss;
	float i_prev_tt;

	output color o_outColor;
	output color o_outTransparency; )
{
	extern varying float ss;
	extern varying float tt;

	ss = i_prev_ss;
	tt = i_prev_tt;

	o_outColor = i_shadingMapColor;

	computeSurfaceTransparency(
		i_matteOpacityMode, i_matteOpacity,
		i_transparency, o_outTransparency );
}

#endif /* __shadingMap_h */

