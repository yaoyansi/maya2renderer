/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __texture3d_h
#define __texture3d_h

#ifdef SHADER_TYPE_light
#define P Ps
#endif

point
transformP(
	float i_blend;
	float i_local;
	matrix i_placementMatrix;
	float i_wrap;
	output float o_edgeDist;
	output float o_outside;)
{
	extern varying point P;
	extern varying point Pref;
	point pp;

	o_edgeDist = 0.0;

	if(i_local != 0.0)
	{
		if( Pref == point(0) )
			pp = transform("object", P);
		else
			pp = transform("object", Pref);
	}
	else
	{
		if( Pref == point(0) )
			pp = transform("world", P);
		else
			pp = transform("world", Pref);
	}

	point pq = transform(i_placementMatrix, pp);
	
	if(xcomp(pq) > 1 ||
		xcomp(pq) < -1 ||
		ycomp(pq) > 1 ||
		ycomp(pq) < -1 ||
		zcomp(pq) > 1 ||
		zcomp(pq) < -1)
	{
		if(i_wrap != 0.0)
		{
			o_outside = 0.0;
		}
		else
		{
			o_outside = 1.0;
		}
	}
	else
	{
		o_outside = 0.0;

		if(i_wrap == 0.0 && i_blend > 0.0)
		{
			// Todo: improve this
			o_edgeDist = min(abs(xcomp(pq) + 1) / 2, abs(xcomp(pq) - 1) / 2, 
				abs(ycomp(pq) + 1) / 2, abs(ycomp(pq) - 1) / 2, 
				abs(zcomp(pq) + 1) / 2, abs(zcomp(pq) - 1) / 2);
		}
	}

	return pq;
}

#ifdef SHADER_TYPE_light
#undef P
#endif

color
blendDefaultColor(
	float i_blend;
	color i_defaultColor;
	float i_edgeDist;
	color i_outColor;)
{
	return  mix(i_defaultColor, i_outColor, 
		smoothstep(0.1 * i_blend, 0.5 * i_blend, i_edgeDist));
}                                               

#endif /* __texture3d_h */

