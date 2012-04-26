/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __phongE_h
#define __phongE_h

/*
begin inputs
	color ambientColor
	color color
	float diffuse
	color incandescence
	float matteOpacity
	float matteOpacityMode
	normal normalCamera
	float translucence
	float translucenceDepth
	float translucenceFocus
	color transparency

	float roughness
	float highlightSize
	color whiteness
	color specularColor
	float reflectivity
	color reflectedColor
	uniform float refractions
	float refractiveIndex
	uniform float refractionLimit
	float lightAbsorbance
	float shadowAttenuation
	uniform float reflectionLimit

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


begin shader_extra_parameters aov_ambient
#ifdef USE_AOV_aov_ambient
	output varying color aov_ambient = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_diffuse
#ifdef USE_AOV_aov_diffuse
	output varying color aov_diffuse = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_specular
#ifdef USE_AOV_aov_specular
	output varying color aov_specular = 0;
#endif
end shader_extra_parameters

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

begin shader_extra_parameters aov_refraction
#ifdef USE_AOV_aov_refraction
	output varying color aov_refraction = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_shadow
#ifdef USE_AOV_aov_shadow
	output varying float aov_shadow = 0;
#endif
end shader_extra_parameters 
 
begin shader_extra_parameters aov_incandescence
#ifdef USE_AOV_aov_incandescence
	output varying color aov_incandescence = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_translucence
#ifdef USE_AOV_aov_translucence
	output varying color aov_translucence = 0;
#endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_ambient_no_shadow
#ifdef USE_AOV_aov_ambient_no_shadow
	output varying color aov_ambient_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_diffuse_no_shadow
#ifdef USE_AOV_aov_diffuse_no_shadow
	output varying color aov_diffuse_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_diffuse_intensity
#ifdef USE_AOV_aov_diffuse_intensity
	output varying color aov_diffuse_intensity = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_diffuse_intensity_no_shadow
#ifdef USE_AOV_aov_diffuse_intensity_no_shadow
	output varying color aov_diffuse_intensity_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_key_lights_diffuse_intensity
#ifdef USE_AOV_aov_key_lights_diffuse_intensity
	output varying color aov_key_lights_diffuse_intensity = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_key_lights_diffuse_intensity_no_shadow
#ifdef USE_AOV_aov_key_lights_diffuse_intensity_no_shadow
	output varying color aov_key_lights_diffuse_intensity_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_luminance_depth
#ifdef USE_AOV_aov_luminance_depth
	output varying color aov_luminance_depth = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_specular_no_shadow
#ifdef USE_AOV_aov_specular_no_shadow
	output varying color aov_specular_no_shadow = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_specular_intensity
#ifdef USE_AOV_aov_specular_intensity
	output varying color aov_specular_intensity = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_specular_intensity_no_shadow
#ifdef USE_AOV_aov_specular_intensity_no_shadow
	output varying color aov_specular_intensity_no_shadow = 0;
#endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_key_lights_specular_intensity
#ifdef USE_AOV_aov_key_lights_specular_intensity
	output varying color aov_key_lights_specular_intensity = 0;
#endif
end shader_extra_parameters
 
begin shader_extra_parameters aov_key_lights_specular_intensity_no_shadow
#ifdef USE_AOV_aov_key_lights_specular_intensity_no_shadow
	output varying color aov_key_lights_specular_intensity_no_shadow = 0;
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
maya_phongE(
	// Inputs:
	//
	color i_ambientColor;
	color i_color;
	float i_diffuse;
	color i_incandescence;
	float i_matteOpacity;
	float i_matteOpacityMode;
	normal i_normalCamera;
	float i_translucence;
	float i_translucenceDepth;
	float i_translucenceFocus;
	color i_transparency;

	float i_roughness;
	float i_highlightSize;
	color i_whiteness;
	color i_specularColor;
	float i_reflectivity;
	color i_reflectedColor;

	/* Refraction. */
	uniform float i_refractions;
	float i_refractiveIndex;
	uniform float i_refractionLimit;
	float i_lightAbsorbance;
	float i_shadowAttenuation;
	/* Reflection. */
	uniform float i_reflectionLimit;

	uniform float i_reflectionMaxDistance;
	uniform float i_reflectionSamples;
	uniform float i_reflectionBlur;
	uniform float i_reflectionNoiseAmplitude;
	uniform float i_reflectionNoiseFrequency;

	// Outputs
	//
	output color o_outColor;
	output color o_outTransparency;
	)
{
	extern vector I;

	/* Catch photon shading. */
	BEGIN_PHOTON_CASE( i_color, i_specularColor, i_transparency )

	normal Nn = normalize(i_normalCamera);
	normal Nf = ShadingNormal(Nn);

	color Cdiffuse = i_diffuse * getDiffuse(Nf, 0, 0);
	color Cambient = i_ambientColor + getAmbient(Nf);

	vector R = normalize( reflect( I, Nn ) );
	color Cspecular = 0;

	float highlight_size = sqrt(i_highlightSize);

	Cspecular = getPhongE(R, highlight_size, i_roughness, 0, 0);
	Cspecular *= i_whiteness;
	Cspecular *= i_specularColor;

	color Creflect = getReflection(
		Nf, I, i_specularColor, i_reflectivity, i_reflectedColor,
		i_reflectionMaxDistance, i_reflectionSamples, i_reflectionBlur,
		i_reflectionNoiseAmplitude, i_reflectionNoiseFrequency,
		i_reflectionLimit );

	color Ctransl = getTranslucence(
		Nf, i_translucence, i_translucenceDepth, i_translucenceFocus);
	
	o_outColor = i_color;

	computeSurface(
		o_outColor,
		i_transparency,
		i_matteOpacityMode,
		i_matteOpacity,
		o_outColor,
		o_outTransparency );

	extern color __transparency;
#ifdef USE_AOV_aov_ambient
	extern color aov_ambient;
	if( isoutput(aov_ambient) )
	{
		aov_ambient +=
			__transparency * Cambient * i_color * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse
	extern color aov_diffuse;
	if( isoutput(aov_diffuse) )
	{
		aov_diffuse +=
			__transparency * Cdiffuse * i_color * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_specular
	extern color aov_specular;
	aov_specular += __transparency * Cspecular;
#endif
#ifdef USE_AOV_aov_incandescence
	extern color aov_incandescence;
	aov_incandescence += __transparency * i_incandescence;
#endif
#ifdef USE_AOV_aov_translucence
	extern color aov_translucence;
	if( isoutput(aov_translucence) )
	{
		aov_translucence +=
			__transparency * Ctransl * i_color * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_ambient_no_shadow
	extern color aov_ambient_no_shadow;
	if( isoutput(aov_ambient_no_shadow) )
	{
		color Ia_nshad = i_ambientColor + getAmbientUnshadowed(Nf);
		aov_ambient_no_shadow +=
			__transparency * Ia_nshad * i_color * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_no_shadow
	extern color aov_diffuse_no_shadow;
	if( isoutput(aov_diffuse_no_shadow) )
	{
		aov_diffuse_no_shadow +=
			__transparency * i_diffuse * getDiffuse(Nf, 0, 1) * i_color * 
			(1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity
	extern color aov_diffuse_intensity;
	if( isoutput(aov_diffuse_intensity) )
	{
		aov_diffuse_intensity +=
			__transparency * Cdiffuse * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity_no_shadow
	extern color aov_diffuse_intensity_no_shadow;
	if( isoutput(aov_diffuse_intensity_no_shadow) )
	{
		aov_diffuse_intensity_no_shadow += __transparency *
			i_diffuse * getDiffuse(Nf, 0, 1) * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity
	extern color aov_key_lights_diffuse_intensity;
	if( isoutput(aov_key_lights_diffuse_intensity) )
	{
		aov_key_lights_diffuse_intensity += __transparency *
			i_diffuse * getDiffuse(Nf, 1, 0) * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity_no_shadow
	extern color aov_key_lights_diffuse_intensity_no_shadow;
	if( isoutput(aov_key_lights_diffuse_intensity_no_shadow) )
	{
		aov_key_lights_diffuse_intensity_no_shadow += __transparency *
			i_diffuse * getDiffuse(Nf, 1, 1) * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_specular_no_shadow
	extern color aov_specular_no_shadow;
	if( isoutput(aov_specular_no_shadow) )
	{
		aov_specular_no_shadow +=
			__transparency * getPhongE(R, highlight_size, i_roughness, 0, 1) *
			i_whiteness * i_specularColor;
	}
#endif
#ifdef USE_AOV_aov_specular_intensity
	extern color aov_specular_intensity;
	if( isoutput(aov_specular_intensity) )
	{
		aov_specular_intensity +=
			__transparency * getPhongE(R, highlight_size, i_roughness, 0, 0);
	}
#endif
#ifdef USE_AOV_aov_specular_intensity_no_shadow
	extern color aov_specular_intensity_no_shadow;
	if( isoutput(aov_specular_intensity_no_shadow) )
	{
		aov_specular_intensity_no_shadow +=
			__transparency * getPhongE(R, highlight_size, i_roughness, 0, 1);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity
	extern color aov_key_lights_specular_intensity;
	if( isoutput(aov_key_lights_specular_intensity) )
	{
		aov_key_lights_specular_intensity +=
			__transparency * getPhongE(R, highlight_size, i_roughness, 1, 0);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity_no_shadow
	extern color aov_key_lights_specular_intensity_no_shadow;
	if( isoutput(aov_key_lights_specular_intensity_no_shadow) )
	{
		aov_key_lights_specular_intensity_no_shadow +=
			__transparency * getPhongE(R, highlight_size, i_roughness, 1, 1);
	}
#endif
#ifdef USE_AOV_aov_surface_color
	extern color aov_surface_color;
	aov_surface_color += __transparency * o_outColor;
#endif
#ifdef USE_AOV_aov_camera_space_normal
	extern normal aov_camera_space_normal;
	aov_camera_space_normal = Nn;
#endif
#ifdef USE_AOV_aov_facing_ratio
	extern varying float aov_facing_ratio;
  aov_facing_ratio = abs( normalize(i_normalCamera).normalize(-I) );
#endif

	color refraction;

	doRefraction(
		Nn,
		I,
		i_refractions,
		i_refractiveIndex,
		i_refractionLimit,
		i_lightAbsorbance,
		i_shadowAttenuation,
		o_outTransparency,
		refraction );

#ifdef USE_AOV_aov_color_no_shadow
	extern varying color aov_color_no_shadow;
	if( isoutput(aov_color_no_shadow) )
	{
		color Ia_no_shw = i_ambientColor + getAmbientUnshadowed(Nf);
		color Id_no_shw = i_diffuse * getDiffuse(Nf, 0, 1);
		color Is_no_shw = getPhongE(R, highlight_size, i_roughness, 0, 1);
		Is_no_shw *= i_whiteness * i_specularColor;

		color color_no_shadow =
			o_outColor * (Id_no_shw + Ia_no_shw + Ctransl)
			+ Creflect + Is_no_shw + i_incandescence + refraction;

		aov_color_no_shadow += __transparency * color_no_shadow;
	}
#endif

	o_outColor *= Cdiffuse + Cambient + Ctransl;
	o_outColor += Creflect + Cspecular + i_incandescence + refraction;

#ifdef USE_AOV_aov_refraction
	extern color aov_refraction;
	aov_refraction += __transparency * refraction;
#endif
    
  computeShadowPass(Nf);
	
#ifdef USE_AOV_aov_luminance_depth
	extern varying color aov_luminance_depth;
	if( isoutput(aov_luminance_depth) )
	{
		aov_luminance_depth = computeLuminanceDepth() * (1.0 - o_outTransparency);
	}
#endif			

	__transparency *= o_outTransparency;

	END_PHOTON_CASE
}

#endif /* __phongE_h */

