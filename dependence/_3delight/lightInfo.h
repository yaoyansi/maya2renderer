/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __lightInfo_h
#define __lightInfo_h

/*
begin inputs
	matrix worldMatrix
	uniform float lightDirectionOnly
end inputs
begin outputs
	matrix matrixEyeToWorld
	point pointCamera
	point lightPosition
	vector lightDirection
	float sampleDistance
end outputs
*/

#ifdef SHADER_TYPE_light
#define P Ps
#endif

void
maya_lightInfo(
	// Inputs
	//
	matrix i_worldMatrix;
	uniform float i_lightDirectionOnly;

	// Outputs
	//
	output matrix o_matrixEyeToWorld; // make uniform
	output point o_pointCamera;
	output point o_lightPosition;
	output vector o_lightDirection;
	output float o_sampleDistance )
{
	extern varying point P;

	o_matrixEyeToWorld =
		matrix "camera" (1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1) * matrix "world" 1;

	o_pointCamera = transform( "mayaCamera", P );
	o_lightPosition = transform( i_worldMatrix, point(0) );
	o_lightDirection = normalize( vtransform( i_worldMatrix, vector(0,0,-1) ) );

	point Pw = transform( "world", P );
	vector LP = Pw - o_lightPosition;

	if( i_lightDirectionOnly == 1.0 )
	{
		o_sampleDistance = LP . o_lightDirection;
	}
	else
	{
		o_sampleDistance = length( LP );
	}
}

#ifdef SHADER_TYPE_light
#undef P
#endif

#endif /* __lightInfo_h */

