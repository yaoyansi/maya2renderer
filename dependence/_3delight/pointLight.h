/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __pointLight_h
#define __pointLight_h

/*
begin inputs
	color color
	float intensity
	float decayRate
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
maya_pointLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	float i_decayRate;
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
	extern color Cl;
	extern vector L;
	extern string shadowmapname;
	extern float shadowBlur;
	extern float shadowSamples;

	point from = point "shader" (0,0,0);

	illuminate( from )
	{
		float distance_squared = L.L;

		Cl = i_intensity;
		float attenuation = 1.0;
    
		if( i_decayRate == 0.0 )
		{
		}
		else if( i_decayRate == 1.0 )
		{
			attenuation = sqrt( distance_squared );
		}
		else if( i_decayRate == 2.0 )
		{
			attenuation = distance_squared;
		}
		else
		{
			attenuation = pow( distance_squared, 0.5 * i_decayRate ); 
		}

		Cl /= attenuation;
    
		color lcolor = computeLightColor(
			i_color, i_shadowColor, shadowmapname,
			shadowBlur, shadowSamples, i_dmapFilterSize, i_dmapBias );

#if	defined(USE_AOV_aov_shadow) || \
	defined(USE_AOV_aov_diffuse_no_shadow) || \
	defined(USE_AOV_aov_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_diffuse_intensity_no_shadow) || \
	defined(USE_AOV_aov_specular_no_shadow) || \
	defined(USE_AOV_aov_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_key_lights_specular_intensity_no_shadow) || \
	defined(USE_AOV_aov_color_no_shadow) || \
	defined(USE_SHADER_usebackground)
			extern color __3dfm_unshadowed_cl;
		__3dfm_unshadowed_cl = i_intensity * i_color / attenuation;
#endif

		Cl *= lcolor;

		Cl = computeRtShadowing(
			Cl, i_shadowColor,
			i_useRayTraceShadows * i_shadowRays, 0, i_lightRadius );
	}
}

#endif /* __pointLight_h */

