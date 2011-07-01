/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __surfaceLuminance_h
#define __surfaceLuminance_h

/*
begin inputs
	normal normalCamera
end inputs
begin outputs
	float outValue
end outputs
*/

#include "utils.h"

void
maya_surfaceLuminance(
	// Inputs
	normal i_normalCamera;

	// Outputs
	output float o_outValue )
{
	o_outValue = luminance( diffuse( normalize(i_normalCamera) ) );
}

#endif /* __surfaceLuminance_h */

