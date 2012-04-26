/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __bump3d_h
#define __bump3d_h

/*
begin inputs
	float bumpValue
	float bumpDepth
	float bumpFilter
	float bumpFilterOffset
	normal normalCamera
end inputs

begin outputs
	normal outNormal
end outputs
*/

#include "shading_utils.h"

void
maya_bump3d(
	// Inputs
	float i_bumpValue;
	float i_bumpDepth;
	float i_bumpFilter;
	float i_bumpFilterOffset;
	normal i_normalCamera;

	// Outputs
	output normal o_outNormal;)
{
	do_bump_map(
		i_bumpValue,
		i_bumpDepth,
		i_normalCamera,
		o_outNormal );
}

#endif /* __bump3d_h */

