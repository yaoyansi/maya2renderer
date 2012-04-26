/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __areaLight_h
#define __areaLight_h

/*
begin inputs
	prepare color color
	prepare float intensity
	prepare float decayRate

	prepare color shadowColor
	uniform float dmapFilterSize
	uniform float dmapBias

	uniform float useRayTraceShadows
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
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying float __3dfm_shadowing = 0;
#endif
#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
		output varying color __3dfm_unshadowed_cl = 0;
#endif
 end shader_extra_parameters
*/

#include "light_utils.h"

void
prepare_maya_areaLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	float i_decayRate;

	color i_shadowColor;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;

	uniform float i_useRayTraceShadows;

	// Outputs:
	//
	)
{
}

void
end_maya_areaLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	float i_decayRate;

	color i_shadowColor;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;

	uniform float i_useRayTraceShadows;

	// Outputs:
	//
	)
{
	extern color Cl;
	extern string shadowmapname;
	extern float shadowBlur;
	extern float shadowSamples;
	extern normal N;
	extern vector L;
	extern point P;
	extern point Ps;

	illuminate(P, N, PI/2)
	{
		float atten = 1.0;

		if( i_decayRate == 0.0 )
			/* do nothing */ ;
		else if( i_decayRate == 2.0 )
		{
			atten /= L.L;
		}
		else if( i_decayRate == 1.0 )
		{
			atten /= sqrt(L.L);
		}
		else
		{
			atten /= pow(sqrt(L.L), i_decayRate);
		}

 		color lcolor = computeLightColor(
			i_color, i_shadowColor, shadowmapname,
			shadowBlur, shadowSamples, i_dmapFilterSize, i_dmapBias );

#if defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
		extern color __3dfm_unshadowed_cl;
		__3dfm_unshadowed_cl = atten * i_intensity * i_color;
#endif

		Cl = atten * i_intensity * lcolor;

		if (receive_shadows() == 1 && i_useRayTraceShadows == 1)
		{
			color Cshad = 1.0 - transmission(Ps, P);

#ifdef USE_AOV_aov_shadow
			extern float __3dfm_shadowing;
			__3dfm_shadowing = luminance(Cshad);
#endif

			Cl = mix( Cl, i_shadowColor, Cshad );
		}
	}
}

#endif /* __areaLight_h */

