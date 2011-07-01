/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __projection_h
#define __projection_h

/*
begin inputs
	prepare float alphaGain
	float alphaIsLuminance
	prepare float alphaOffset
	float amplitudeX
	float amplitudeY
	float blend
	prepare color colorGain
	prepare color colorOffset
	prepare color defaultColor
	uniform float2 depth
	sourcename string linkedCamera
	float fitType
	float fitFill
	connectedtexture string image
	prepare color image
	float invert
	float local
	matrix placementMatrix
	float projType
	float ratio
	float3 ripples
	float uAngle
	init={ss,tt} float2 uvCoord
	float vAngle
	float wrap
	nonplug float prev_ss
	nonplug float prev_tt
	declare float prev_ss
	declare float prev_tt
end inputs

begin outputs
	color outColor
	float outAlpha
end outputs


begin shader_extra_parameters Pref_param
	varying point Pref = 0;
end shader_extra_parameters
*/

#include "utils.h"
#include "noise_utils.h"
#include "texture3d.h"

void
prepare_maya_projection(
	// Inputs
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	float i_amplitudeX;
	float i_amplitudeY;
	float i_blend;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	uniform float i_depth[2];
	uniform string i_linkedCamera;
	uniform float i_fitType;
	uniform float i_fitFill;
	uniform string i_imageTextureName;
	color i_image;
	uniform float i_invert;
	float i_local;
	matrix i_placementMatrix;
	uniform float i_projType;
	uniform float i_ratio;
	float i_ripples[3];
	float i_uAngle;
	float i_uvCoord[2];
	float i_vAngle;
	float i_wrap;

	// Outputs
	//
	output float o_prev_ss;
	output float o_prev_tt;

	output color o_outColor;
	output float o_outAlpha;)
{
	extern float ss;
	extern float tt;
	o_prev_ss = ss;
	o_prev_tt = tt;

	float edgeDist;
	float outside;
	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside);

	if(outside < 1)
	{
		if(i_amplitudeX > 0.0 || i_amplitudeY > 0.0)
		{
			color mix = fBrownianNoise(pp, 0, 1, 1, 2, i_depth, i_ratio, i_ripples);
			pp = point(vector(-i_amplitudeX * comp(mix, 0), i_amplitudeY * comp(mix, 1), 0) + vector(pp));
		}

		if(i_projType == 1)
		{
			// planar projection
			ss = xcomp(pp) / 2 + 0.5;
			tt = ycomp(pp) / 2 + 0.5;
		}
		else if(i_projType == 2)
		{
			// spherical projection
			vector v = normalize(vector pp);
			float vx = xcomp(v);
			float vy = ycomp(v);
			float vz = zcomp(v);
			ss = 0.5 * atan(vx, vz) / radians(i_uAngle);
			tt = 0.5 * atan(vy, sqrt(vx * vx + vz * vz)) / radians(i_vAngle);
			ss += 0.5;
			tt += 0.5;
		}
		else if(i_projType == 3)
		{
			// cylindrical projection
			vector v = normalize(vector pp);
			ss = atan(xcomp(v), zcomp(v)) / radians(i_uAngle) + 0.5;
			tt = ycomp(pp) / 2 + 0.5;
		}
		else if(i_projType == 4)
		{
			// ball projection
			vector v = normalize(vector pp);

			float l = 0.5 / length( v + vector(0,0,1) );
			ss = xcomp(v) * l + 0.5;
			tt = ycomp(v) * l + 0.5;
		}
		else if(i_projType == 5)
		{
			// cubic projection
			vector v = normalize(vector pp);
			if(abs(xcomp(pp)) > abs(ycomp(pp)) &&
				abs(xcomp(pp)) > abs(zcomp(pp)))
			{
				ss = zcomp(pp) / xcomp(pp);
				tt = ycomp(pp) / xcomp(pp);

				if(xcomp(pp) < 0.0)
				{
					ss = -ss;
					tt = -tt;
				}
			}
			else if(abs(ycomp(pp)) > abs(xcomp(pp)) &&
				abs(ycomp(pp)) > abs(zcomp(pp)))
			{
				ss = xcomp(pp) / ycomp(pp);
				tt = zcomp(pp) / ycomp(pp);

				if(ycomp(pp) < 0.0)
				{
					ss = -ss;
					tt = -tt;
				}
			}
			else if(abs(zcomp(pp)) > abs(ycomp(pp)) && 
				abs(zcomp(pp)) > abs(xcomp(pp)))
			{
				ss = xcomp(pp) / zcomp(pp);
				tt = ycomp(pp) / zcomp(pp);

				if(zcomp(pp) < 0.0)
				{
					ss = -ss;
					tt = -tt;
				}
			}

			ss = (ss + 1) / 2;
			tt = (tt + 1) / 2;
		}
		else if(i_projType == 6)
		{
			// triplanar projection
			extern normal N;
			normal NN = normalize(ntransform("shader", N));

			if(abs(xcomp(NN)) >= abs(ycomp(NN)) &&
				abs(xcomp(NN)) >= abs(zcomp(NN)))
			{
				ss = zcomp(pp);
				tt = ycomp(pp);
			}
			else if(abs(ycomp(NN)) >= abs(xcomp(NN)) &&
				abs(ycomp(NN)) >= abs(zcomp(NN)))
			{
				ss = xcomp(pp);
				tt = zcomp(pp);
			}
			else
			{
				ss = xcomp(pp);
				tt = ycomp(pp);
			}

			ss = 0.5 * ss + 0.5;
			tt = 0.5 * tt + 0.5;
		}
		else if(i_projType == 7)
		{
			// concentric projection
			// Not quite like maya's but fairly close. Can you do better?
			ss = cellnoise(pp);
			vector dp = pp - point(floor(xcomp(pp)), floor(ycomp(pp)), floor(zcomp(pp))) - 0.5;
			float dx = xcomp(dp);
			float dy = ycomp(dp);
			float dz = zcomp(dp);
			float t2 = 2 * length(dp);
			float power = 2 + 64 * (1-pow(1-t2/sqrt(3), 1/32));
			float t3 = 2 * pow(pow(abs(dx), power) + pow(abs(dy), power) + pow(abs(dz), power), 1/power);

			tt = t3 + cellnoise(pp + vector(42,25,99));
			tt = 1 - tt;
		}
		else if(i_projType == 8)
		{
			// perspective projection
			extern point P;
			extern point Pref;
			if( Pref == point(0) )
			{
				pp = transform( "current", "world", P );
			}
			else
			{
				pp = transform( "current", "world", Pref );
			}

			string cameraSpace = concat( "mayaCamera:", i_linkedCamera );
			point ps = transform( cameraSpace, "current", pp );
			
			float px = xcomp(ps);
			float py = ycomp(ps);

			uniform float imageAR = 1;
			uniform float imageRes[2];
			if( 1 == textureinfo( i_imageTextureName, "resolution", imageRes ) )
			{
				imageAR = imageRes[0] / imageRes[1];
			}

			if( i_fitType > 0 )
			{
				uniform float frameAR;

				if( i_fitType == 1 )
				{
					/* Match Camera Film Gate */
					uniform string option_name =
						concat("user:", i_linkedCamera, "_camera_aspectRatio");
					frameAR = 1;
					option( option_name, frameAR );
				}
				else
				{
					/* Match Camera Resolution */
					uniform float frameFormat[3];
					option( "Format", frameFormat );
					frameAR = frameFormat[0] / frameFormat[1];
				}

				if( i_fitFill == 0 )
				{
					/* Fill */
					py *= frameAR;
				}
				else if( i_fitFill == 1 )
				{
					/* Horizontal */
					py *= imageAR;
				}
				else
				{
					/* Vertical */
					px *= frameAR / imageAR;
					py *= frameAR;
				}
			}

			/* Only project in front of the camera. */
			if( zcomp(ps) < 1 )
			{
				ss = px / 2 + 0.5;
				tt = py / 2 + 0.5;
			}
			else
			{
				ss = tt = UNDEFINED_UV;
			}
		}
	}
}

void
end_maya_projection(
	// Inputs
	//
	float i_alphaGain;
	uniform float i_alphaIsLuminance;
	float i_alphaOffset;
	float i_amplitudeX;
	float i_amplitudeY;
	float i_blend;
	color i_colorGain;
	color i_colorOffset;
	color i_defaultColor;
	uniform float i_depth[2];
	uniform string i_linkedCamera;
	uniform float i_fitType;
	uniform float i_fitFill;
	uniform string i_imageTextureName;
	color i_image;
	uniform float i_invert;
	float i_local;
	matrix i_placementMatrix;
	uniform float i_projType;
	uniform float i_ratio;
	float i_ripples[3];
	float i_uAngle;
	float i_uvCoord[2];
	float i_vAngle;
	float i_wrap;

	// Outputs
	//
	output float o_prev_ss;
	output float o_prev_tt;

	output color o_outColor;
	output float o_outAlpha;)
{
	extern float ss, tt;

	ss = o_prev_ss;
	tt = o_prev_tt;

	float edgeDist;
	float outside;
	varying point pp = transformP(i_blend, 
		i_local, 
		i_placementMatrix, 
		i_wrap, edgeDist, 
		outside);

	if(outside < 1)
	{
		o_outColor = i_image;

		colorBalance(o_outColor, 
			o_outAlpha, 
			1, 
			i_alphaGain, 
			i_alphaOffset, 
			i_colorGain, 
			i_colorOffset, 
			i_invert);
	}
	else
	{
		o_outColor = i_defaultColor;
		o_outAlpha = 0;
	}
}

#endif /* __projection_h */

