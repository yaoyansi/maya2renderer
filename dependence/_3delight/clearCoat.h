/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __clearCoat_h
#define __clearCoat_h

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
*/

#include "studioClearCoat.h"

void
maya_clearCoat(
	float i_index, i_scale, i_bias;
	normal i_normalCamera; 
	output float o_outValue; )
{
	maya_studioClearCoat( i_index, i_scale, i_bias, i_normalCamera, o_outValue );
}

#endif /* __clearCoat_h */

