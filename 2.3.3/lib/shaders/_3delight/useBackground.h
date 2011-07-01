/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __useBackground_h
#define __useBackground_h

/*
begin inputs
	float matteOpacityMode
	float matteOpacity
	color specularColor
	float reflectivity
	uniform float reflectionLimit
	float shadowMask
	normal normalCamera
	uniform float _3delight_shading_reflectionMaxDistance
	uniform float _3delight_shading_reflectionSamples
	uniform float _3delight_shading_reflectionBlur
	uniform float _3delight_shading_reflectionNoiseAmplitude
	uniform float _3delight_shading_reflectionNoiseFrequency
end inputs

begin outputs
	color outColor
	color outTransparency
end outputs


begin shader_extra_parameters aov_reflection
#ifdef USE_AOV_aov_reflection
	output varying color aov_reflection = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_rt_reflection
#ifdef USE_AOV_aov_rt_reflection
	output varying color aov_rt_reflection = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_rt_reflection_alpha
#ifdef USE_AOV_aov_rt_reflection_alpha
	output varying float aov_rt_reflection_alpha = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_env_reflection
#ifdef USE_AOV_aov_env_reflection
	output varying color aov_env_reflection = 0;
#endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_shadow
#ifdef USE_AOV_aov_shadow
	output varying float aov_shadow = 0;
#endif
end shader_extra_parameters 
 
begin shader_extra_parameters aov_luminance_depth
#ifdef USE_AOV_aov_luminance_depth
	output varying color aov_luminance_depth = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_color_no_shadow
#ifdef USE_AOV_aov_color_no_shadow
	output varying color aov_color_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_surface_color
#ifdef USE_AOV_aov_surface_color
	output varying color aov_surface_color = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_normal
#ifdef USE_AOV_aov_camera_space_normal
	output varying normal aov_camera_space_normal = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_facing_ratio
#ifdef USE_AOV_aov_facing_ratio
	output varying float aov_facing_ratio = 0;
#endif
end shader_extra_parameters
*/

#include "utils.h"
#include "shading_utils.h"

void
maya_useBackground(
	// Inputs:
	//
	uniform float i_matteOpacityMode;
	float i_matteOpacity;
	color i_specularColor;
	float i_reflectivity;
	uniform float i_reflectionLimit;
	float i_shadowMask;
	normal i_normalCamera;

	uniform float i_reflectionMaxDistance;
	uniform float i_reflectionSamples;
	uniform float i_reflectionBlur;
	uniform float i_reflectionNoiseAmplitude;
	uniform float i_reflectionNoiseFrequency;

	// Outputs:
	//
	output color o_outColor;
	output color o_outTransparency;
)
{
	normal Nf, Nn;
	color Ir;
	extern vector I;

	/* Catch photon shading. */
	BEGIN_PHOTON_CASE( color(0), i_specularColor, color(0) )

	vector In = normal( I );
	Nn = normalize(i_normalCamera);
	Nf = ShadingNormal(Nn);
	Ir = getReflection(
		Nf, I, i_specularColor,
		i_reflectivity, color(0),
		i_reflectionMaxDistance, i_reflectionSamples, i_reflectionBlur,
		i_reflectionNoiseAmplitude, i_reflectionNoiseFrequency,
		i_reflectionLimit );
	
	o_outColor = color(0);

	computeSurface(
		o_outColor,
		color(0),
		i_matteOpacityMode,
		i_matteOpacity,
		o_outColor,
		o_outTransparency );

	extern color __transparency;
#ifdef USE_AOV_aov_surface_color
	extern color aov_surface_color;
		aov_surface_color += __transparency * Ir;
#endif

#ifdef USE_AOV_aov_color_no_shadow
	extern color aov_color_no_shadow;
		aov_color_no_shadow += __transparency * Ir;
#endif
#ifdef USE_AOV_aov_camera_space_normal
	extern normal aov_camera_space_normal;
	aov_camera_space_normal = Nn;
#endif
#ifdef USE_AOV_aov_facing_ratio
	extern varying float aov_facing_ratio;
  aov_facing_ratio = abs( normalize(i_normalCamera).normalize(-I) );
#endif

	o_outColor += Ir;
	
	float shadowValue =  computeShadowValue(Nf) * i_shadowMask;
	o_outTransparency = 1 - shadowValue;

#ifdef USE_AOV_aov_shadow
	extern float aov_shadow;
	aov_shadow = shadowValue;
#endif

#ifdef USE_AOV_aov_luminance_depth
	extern varying color aov_luminance_depth;
	if( isoutput(aov_luminance_depth) )
	{
		aov_luminance_depth = computeLuminanceDepth();
	}
#endif		

	__transparency *= o_outTransparency;

	END_PHOTON_CASE
}

#endif /* __usebackground_h */

