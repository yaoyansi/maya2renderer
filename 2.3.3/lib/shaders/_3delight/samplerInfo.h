/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __samplerInfo_h
#define __samplerInfo_h

/*
begin inputs
	normal normalCamera
end inputs
begin outputs
	point pointCamera
	point pointObj
	point pointWorld
	normal normalCamera
	float2 uvCoord
	vector rayDirection
	vector tangentUCamera
	vector tangentVCamera
	matrix matrixEyeToWorld
	float2 pixelCenter
	float flippedNormal
	float facingRatio
end outputs
*/

#ifdef SHADER_TYPE_light
#define P Ps
#define N Ns
#define Ng Ngs
#endif

void
maya_samplerInfo(
	varying normal i_normalCamera;
	output point o_pointCamera;
	output point o_pointObj;
	output point o_pointWorld;
	output normal o_normalCamera;
	output float o_uvCoord[2];
	output vector o_rayDirection;
	output vector o_tangentUCamera;
	output vector o_tangentVCamera;
	output matrix o_matrixEyeToWorld; // make uniform
	output float o_pixelCenter[2];
	output float o_flippedNormal;
	output float o_facingRatio )
{
	extern varying point P;
	extern varying normal Ng;
	extern varying vector I;
	extern varying float ss,tt;

	o_pointCamera = transform( "mayaCamera", P );
	o_pointObj = transform( "object", P );
	o_pointWorld = transform( "world", P );
	o_normalCamera = normalize( ntransform( "mayaCamera", i_normalCamera ) );
	o_uvCoord[0] = ss;
	o_uvCoord[1] = tt;
	// According to maya's doc, this should be -I... but reality says otherwise.
	o_rayDirection = normalize( vtransform( "mayaCamera", I ) );
	o_tangentUCamera = normalize( Deriv( transform( "mayaCamera", P ), ss ) );
	o_tangentVCamera = -normalize( Deriv( transform( "mayaCamera", P ), tt ) );
	o_matrixEyeToWorld =
		matrix "camera" (1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1) * matrix "world" 1;

	/* Flip y to match maya's coordinates. */
	float format[3];
	option( "Format", format );
	point rasterP = transform( "raster", P );
	o_pixelCenter[0] = xcomp( rasterP );
	o_pixelCenter[1] = format[1] - ycomp( rasterP );

	float doubleshaded;
	if( attribute( "sides:doubleshaded", doubleshaded ) == 1 &&
	    doubleshaded == 1 )
	{
		attribute( "geometry:backfacing", o_flippedNormal );
	}
	else
	{
		/* We want to know about the geometric backside so we use Ng */
		o_flippedNormal = Ng.(-I) > 0 ? 0 : 1;
	}

	o_facingRatio = abs( normalize(i_normalCamera).normalize(-I) );
}

#ifdef SHADER_TYPE_light
#undef P
#undef N
#undef Ng
#endif

#endif /* __samplerInfo_h */

