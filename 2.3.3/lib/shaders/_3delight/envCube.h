/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __envCube_h
#define __envCube_h

/*
begin inputs
	float infiniteSize
	prepare color right
	prepare color left
	prepare color top
	prepare color bottom
	prepare color front
	prepare color back
	normal normalCamera
	matrix placementMatrix

	nonplug float prev_ss
	nonplug float prev_tt
	nonplug float face_no
	declare float prev_ss
	declare float prev_tt
	declare float face_no
end inputs

begin outputs
	color outColor
	float outAlpha
end outputs
*/

#include "utils.h"

/*
	trace_square

	Traces a ray against a [-1,1] (in x,y) square located at z=1. Returns 1 if
	there is a hit, 0 otherwise. When there is a hit, normalized coordinates of
	the hit are returned.

	NOTES
	- The square is single-sided and will only hit when i_dirz > 0.
*/
float trace_square(
	float i_px, i_py, i_pz;
	float i_dirx, i_diry, i_dirz;
	output float o_s, o_t )
{
	float hit = 0;

	if( i_dirz > 0 )
	{
		float t = (1 - i_pz ) / i_dirz;

		if( t > 0 )
		{
			float phitx = i_px + t * i_dirx;
			float phity = i_py + t * i_diry;

			if( phitx >= -1 && phitx <= 1 &&
			    phity >= -1 && phity <= 1 )
			{ 
				hit = 1;
				o_s = phitx * 0.5 + 0.5;
				o_t = phity * 0.5 + 0.5;
			}
		}
	}

	return hit;
}

	
void
prepare_maya_envCube(
	uniform float i_infiniteSize;
	color i_right, i_left, i_top, i_bottom, i_front, i_back;
	normal i_normalCamera;
	matrix i_placementMatrix;

	output float o_prev_ss;
	output float o_prev_tt;
	output float o_face_no;

	output color o_outColor;
	output float o_outAlpha )
{
	extern vector I;
	extern point P;
	extern varying float ss, tt;

	o_prev_ss = ss;
	o_prev_tt = tt;

	vector R;
	R = reflect(I, normalize(i_normalCamera));
	R = vtransform( "world", R );
	R = vtransform( i_placementMatrix, R );

	point p = transform( "world", P );
	p = transform( i_placementMatrix, p );

	if( i_infiniteSize == 1 )
		p = 0;

	float px = xcomp(p);
	float py = ycomp(p);
	float pz = zcomp(p);
	float rx = xcomp(R);
	float ry = ycomp(R);
	float rz = zcomp(R);

	if( 1 == trace_square( -px, py, pz, -rx, ry, rz, ss, tt ) )
	{
		o_face_no = 4;
	}
	else if( 1 == trace_square( px, py, -pz, rx, ry, -rz, ss, tt ) )
	{
		o_face_no = 5;
	}
	else if( 1 == trace_square( pz, py, px, rz, ry, rx, ss, tt ) )
	{
		o_face_no = 0;
	}
	else if( 1 == trace_square( -pz, py, -px, -rz, ry, -rx, ss, tt ) )
	{
		o_face_no = 1;
	}
	else if( 1 == trace_square( px, pz, py, rx, rz, ry, ss, tt ) )
	{
		o_face_no = 2;
	}
	else if( 1 == trace_square( px, -pz, -py, rx, -rz, -ry, ss, tt ) )
	{
		o_face_no = 3;
	}
	else
	{
		o_face_no = -1;
	}

	/* Don't let anything enter the box from the outside. */
	if( px < -1 || px > 1 || py < -1 || py > 1 || pz < -1 || pz > 1 )
		o_face_no = -1;
}

void
end_maya_envCube(
	uniform float i_infiniteSize;
	color i_right, i_left, i_top, i_bottom, i_front, i_back;
	normal i_normalCamera;
	matrix i_placementMatrix;

	float i_prev_ss;
	float i_prev_tt;
	float i_face_no;

	output color o_outColor;
	output float o_outAlpha )
{
	extern varying float ss;
	extern varying float tt;

	ss = i_prev_ss;
	tt = i_prev_tt;

	if( i_face_no == 0 )
	{
		o_outColor = i_right;
	}
	else if( i_face_no == 1 )
	{
		o_outColor = i_left;
	}
	else if( i_face_no == 2 )
	{
		o_outColor = i_top;
	}
	else if( i_face_no == 3 )
	{
		o_outColor = i_bottom;
	}
	else if( i_face_no == 4 )
	{
		o_outColor = i_front;
	}
	else if( i_face_no == 5 )
	{
		o_outColor = i_back;
	}
	else
	{
		o_outColor = 0;
	}

	o_outAlpha = luminance( o_outColor );
}

#endif /* __envCube_h */

