/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __volumeLight_h
#define __volumeLight_h

/*
begin inputs
	color color
	float intensity
	uniform float lightShape

	color[] colorRange[].colorRange_Color
	uniform float[] colorRange[].colorRange_Interp
	float[] colorRange[].colorRange_Position

	uniform float volumeLightDir
	float arc
	float coneEndRadius
	uniform float emitAmbient

	float[] penumbra[].penumbra_FloatValue
	uniform float[] penumbra[].penumbra_Interp
	float[] penumbra[].penumbra_Position

	color shadowColor
	uniform float dmapFilterSize
	uniform float dmapBias

	uniform float useRayTraceShadows
	uniform float lightRadius
	uniform float shadowRays
end inputs

begin outputs
end outputs

begin shader_extra_parameters lightsource
	string shadowmapname = "";
	float shadowBlur = 0;
	float shadowSamples = 16;
	float __nonspecular = 0;
	float __nondiffuse = 0;
	string __category = "";
	float iskeylight = 0;
#ifdef USE_AOV_aov_shadow
	output varying float __3dfm_shadowing = 0;
#endif
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_ambient_no_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow)
	output varying color __3dfm_unshadowed_cl = 0;
#endif
end shader_extra_parameters
*/

#include "light_utils.h"
#include "ramp_utils.h"

void
maya_volumeLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	uniform float i_lightShape;

	color i_colorRange_Color[];
	uniform float i_colorRange_Interp[];
	float i_colorRange_Position[];

	uniform float i_volumeLightDir;
	float i_arc;
	float i_coneEndRadius;
	uniform float i_emitAmbient;

	float i_penumbra_FloatValue[];
	uniform float i_penumbra_Interp[];
	float i_penumbra_Position[];

	color i_shadowColor;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;

	uniform float i_useRayTraceShadows;
	uniform float i_lightRadius;
	uniform float i_shadowRays;

	// Outputs:
	//
	)
{
	float cube_dist( vector i_P )
	{
		// FIXME: This isn't the right formula.
		float dx = xcomp(i_P);
		float dy = ycomp(i_P);
		float dz = zcomp(i_P);
		float t2 = length(i_P);
		float power = 2 + 64 * (1-pow(1-t2/sqrt(3), 1/32));
		float t3 = pow(pow(abs(dx), power) + pow(abs(dy), power) + pow(abs(dz), power), 1/power);

		return t3;
	}

	extern point Ps;
	extern color Cl;
	extern vector L;
	extern string shadowmapname;
	extern float shadowBlur;
	extern float shadowSamples;

	point from = point "shader" (0,0,0);

	vector lightDir;
	vector realL = Ps - from;

	if( i_volumeLightDir == 0 )
	{
		lightDir = Ps - from;
	}
	else if( i_volumeLightDir == 1 )
	{
		lightDir = from - Ps;
	}
	else
	{
		lightDir = vector "shader" (0,-1,0);
	}

	vector shaderRealL = vtransform( "shader", realL );

	float angle = atan( xcomp(shaderRealL), -zcomp(shaderRealL) );
	if( angle < 0 )
		angle += 2*PI;

	solar( lightDir, 0.0 )
	{
		Cl = i_intensity;

		if( angle > radians(i_arc) )
			Cl = 0.0;

		float colorRampPos;
		float penumbraRampPos;

		if( i_lightShape == 0 )
		{
			/* Box */
			vector shaderL = shaderRealL;
			if( abs(xcomp(shaderL)) > 1.0 ||
			    abs(ycomp(shaderL)) > 1.0 ||
			    abs(zcomp(shaderL)) > 1.0 )
			{
				Cl = 0;
			}
			else
			{
				float d = cube_dist( shaderL );
				colorRampPos = 1.0 - d;
			}
		}
		else if( i_lightShape == 1 )
		{
			/* Sphere */
			float d = length(shaderRealL);
			if( d > 1.0 )
			{
				Cl = 0;
			}
			else
			{
				colorRampPos = 1.0 - d;
			}
		}
		else if( i_lightShape == 2 )
		{
			/* Cylinder */
			float dx = xcomp(shaderRealL);
			float dy = ycomp(shaderRealL);
			float dz = zcomp(shaderRealL);
			float d = sqrt(dx * dx + dz * dz);

			if( d > 1.0 || abs(dy) > 1.0 )
			{
				Cl = 0;
			}
			else
			{
				colorRampPos = 1.0 - abs(dy);
			}

			penumbraRampPos = 1.0 - d;
		}
		else /* i_lightShape == 3 */
		{
			/* Cone */
			float dx = xcomp(shaderRealL);
			float dy = ycomp(shaderRealL);
			float dz = zcomp(shaderRealL);
			float d = sqrt(dx * dx + dz * dz);
			float radius = 1.0 + (i_coneEndRadius - 1.0) * (1.0 + dy);

			if( dy < -1.0 || dy > 0 ||
			    abs(dx) > 1.0 ||
			    abs(dz) > 1.0 ||
			    d > radius )
			{
				Cl = 0;
			}
			else
			{
				if( i_volumeLightDir == 2 )
					colorRampPos = 1.0 - abs(dy);
				else
					colorRampPos = 1.0 - sqrt(dx * dx + dy * dy + dz * dz);
			}

			penumbraRampPos = 1.0 - d;
		}

		if( Cl != color(0) )
		{
			if( i_lightShape >= 2 )
			{
				/* Penumbra, for cylinder and cone only. */
				Cl *= floatRamp(
					penumbraRampPos,
					i_penumbra_Position,
					i_penumbra_Interp,
					i_penumbra_FloatValue );
			}

			/* Color Range */
			Cl *= colorRamp(
				colorRampPos,
				i_colorRange_Position,
				i_colorRange_Interp,
				i_colorRange_Color );

			/* Shadowing. */
			color lcolor = computeLightColor(
				i_color, i_shadowColor, shadowmapname,
				shadowBlur, shadowSamples, i_dmapFilterSize, i_dmapBias );

			Cl *= lcolor;

#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_ambient_no_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow)
			extern color __3dfm_unshadowed_cl;
			__3dfm_unshadowed_cl = Cl;
#endif

			Cl = computeRtShadowing(
				Cl, i_shadowColor,
				i_useRayTraceShadows * i_shadowRays, 0, i_lightRadius );
		}
	}

	if( i_emitAmbient == 1.0 )
	{
		/*
			This will always behave as if neither emit diffuse nor emit
			specular are used. There's no clean & simple way to get a renderman
			light to be both ambient, diffuse and specular. It would require
			more output variables and specially modified surface shaders to
			read them, so it would only work with our own shaders.
		*/
		L = 0;
	}
}

#endif /* __volumeLight_h */

