/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __ambientLight_h
#define __ambientLight_h

/*
begin inputs
	color color
	float intensity
	float ambientShade
	color shadowColor

	uniform float useRayTraceShadows
	uniform float shadowRadius
	uniform float shadowRays
end inputs

begin outputs
end outputs

begin shader_extra_parameters lightsource
	float __nonspecular = 1;
	float __nondiffuse = 0;
	string __category = "ambient";
	float iskeylight = 0;
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying float __3dfm_shadowing = 0;
#endif
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_ambient_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying color __3dfm_unshadowed_cl = 0;
#endif
end shader_extra_parameters
*/

#include "light_utils.h"

void
maya_ambientLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	float i_ambientShade;
	color i_shadowColor;

	uniform float i_useRayTraceShadows;
	uniform float i_shadowRadius;
	uniform float i_shadowRays;

	// Outputs:
	//
	)
{
	extern normal Ns;
	extern vector I;
	extern point Ps;
	extern color Cl;

	normal Nf = normalize( faceforward(Ns, I) );

	/* Do not use "L" and leave it at 0 so that ambient() will catch this light */	
	point from = point "shader" 0;
	vector _L = from-Ps;

	/*
		The ambientShade parameter blends the light source between a true
		ambient light and a diffuse light. The 2/3 exponent was derived
		experimentally.
	*/

	float costheta = normalize(_L).Nf;
	float theta = acos( costheta );
	theta *= pow(i_ambientShade, 0.666666);
	costheta = cos( theta );
	costheta = clamp( costheta, 0, 1 );

	Cl = costheta * i_intensity * i_color;

#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_ambient_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
	extern color __3dfm_unshadowed_cl;
	__3dfm_unshadowed_cl = Cl;
#endif

	/* Shadowing... yes, maya has shadows for ambient lights. */
	Cl = computeRtShadowing(
		Cl, i_shadowColor,
		i_useRayTraceShadows * i_shadowRays, 0, i_shadowRadius );
}

#endif /* __ambientLight_h */

