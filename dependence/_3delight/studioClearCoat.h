/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __studioClearCoat_h
#define __studioClearCoat_h

/*
begin inputs
	float index
	float scale
	float bias
	normal normalCamera
end inputs

begin outputs
	float outValue
end outputs

TODO: we have a slightly different effect than MAYA here probably
du to a difference in fresnel function (I think Maya's one is less
sophisticated).
*/

#include "shading_utils.h"

void
maya_studioClearCoat(
	float i_index, i_scale, i_bias;
	normal i_normalCamera; 
	output float o_outValue; )
{
	extern vector I;

	vector In = normalize( I );
	normal Nn = normalize( ShadingNormal(i_normalCamera) );

	float Kt;
	fresnel( In, Nn, 1/i_index, o_outValue, Kt );

	o_outValue = o_outValue * i_scale + i_bias;
}

#endif /* __studioClearCoat_h */

