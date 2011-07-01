/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __bump2d_h
#define __bump2d_h

/*
NOTES
- The bumpNormal parameter is an extension to work around the braindead design
of the bump2d node. It 'magically' receives the color of whatever texture is
connected to its bumpValue input. But put that float connection through some
transformation node and you will see that it's just a quick hack. What we do
instead is require the user to add a 'bumpNormal' vector parameter to the node
and connect the normal map to it.

begin inputs
	float bumpValue
	float bumpDepth
	uniform float bumpInterp
	float bumpFilter
	float bumpFilterOffset
	normal normalCamera
	normal bumpNormal
end inputs

begin outputs
	normal outNormal
end outputs


begin shader_extra_parameters stangent
	varying vector stangent = 0;
end shader_extra_parameters
*/

#include "shading_utils.h"

void
maya_bump2d(
	// Inputs
	//
	float i_bumpValue;
	float i_bumpDepth;
	uniform float i_bumpInterp;
	float i_bumpFilter;
	float i_bumpFilterOffset;
	normal i_normalCamera;
	normal i_bumpNormal;

	// Outputs
	//
	output normal o_outNormal;)
{
	extern varying vector dPdu, dPdv;
	extern varying vector stangent;
	extern float ss, tt;
  
	if( i_bumpInterp == 0 )
	{
		/* Bump. */
		do_bump_map(
			i_bumpValue,
			i_bumpDepth,
			i_normalCamera,
			o_outNormal );

	}
	else if( i_bumpInterp == 1 )
	{
		/* Tangent Space Normals. */
		vector udir, vdir;

		if( stangent != vector(0) )
		{
			vdir = stangent ^ i_normalCamera;
		}
		else
		{
			vdir = Du(tt) * dPdu + Dv(tt) * dPdv;
			vdir = i_normalCamera ^ (vdir ^ i_normalCamera);
		}

		udir = i_normalCamera ^ vdir;
		vector uorient = Du(ss) * dPdu + Dv(ss) * dPdv;
		if( udir.uorient < 0 )
		{
			udir = -udir;
		}

		vector basisx = normalize(udir);
		vector basisy = normalize(vdir);
		vector basisz = normalize(i_normalCamera);

		o_outNormal = normal(
			(xcomp(i_bumpNormal) - 0.5) * basisx +
			(ycomp(i_bumpNormal) - 0.5) * basisy +
			(zcomp(i_bumpNormal) - 0.5) * basisz );

		o_outNormal = normalize(o_outNormal);
	}
	else
	{
		/* Object Space Normals. This needs some work. */
		o_outNormal = ntransform( "object", "current", i_bumpNormal - 0.5 );
		o_outNormal = normalize(o_outNormal);
	}
}

#endif /* __bump2d_h */

