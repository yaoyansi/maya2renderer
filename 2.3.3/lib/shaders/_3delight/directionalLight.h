/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __directionalLight_h
#define __directionalLight_h

/*
begin inputs
	prepare color color
	prepare float intensity
	prepare color shadowColor
	uniform float dmapFilterSize
	uniform float dmapBias

	uniform float useRayTraceShadows
	uniform float lightAngle
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
prepare_maya_directionalLight(
  // Inputs:
  //
  color i_color;
  float i_intensity;
  color i_shadowColor;
  uniform float i_dmapFilterSize;
  uniform float i_dmapBias;
  
  uniform float i_useRayTraceShadows;
  uniform float i_lightAngle;
  uniform float i_shadowRays;
  
  // Outputs:
  //
  )
{
  extern float ss, tt;
  extern point Ps;
  
  point Pl = transform("shader", Ps);
  ss = xcomp(Pl);
  tt = ycomp(Pl);
}

void
end_maya_directionalLight(
	// Inputs:
	//
	color i_color;
	float i_intensity;
	color i_shadowColor;
	uniform float i_dmapFilterSize;
	uniform float i_dmapBias;

	uniform float i_useRayTraceShadows;
	uniform float i_lightAngle;
	uniform float i_shadowRays;

	// Outputs:
	//
	)
{
	extern color Cl;
	extern string shadowmapname;
	extern float shadowBlur;
	extern float shadowSamples;

	vector dir = vector "shader" (0,0,1);
  
	solar(dir, 0.0)
	{
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
		__3dfm_unshadowed_cl = i_intensity * i_color;
#endif

		Cl = i_intensity * lcolor;

		Cl = computeRtShadowing(
			Cl, i_shadowColor,
			i_useRayTraceShadows * i_shadowRays, 1, i_lightAngle );
	}
}

#endif /* __directionalLight_h */

