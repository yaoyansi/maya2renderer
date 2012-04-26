/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __rampShader_h
#define __rampShader_h

/*
begin inputs
	color ambientColor
	color[] color[].color_Color
	uniform float[] color[].color_Interp
	float[] color[].color_Position
	float colorInput
	float diffuse
	float eccentricity
	color[] environment[].environment_Color
	uniform float[] environment[].environment_Interp
	float[] environment[].environment_Position
	float forwardScatter
	color[] incandescence[].incandescence_Color
	uniform float[] incandescence[].incandescence_Interp
	float[] incandescence[].incandescence_Position	
	float matteOpacity
	float matteOpacityMode
	normal normalCamera
	color reflectedColor
	uniform float _3delight_shading_reflectionBlur
	uniform float reflectionLimit
	uniform float _3delight_shading_reflectionMaxDistance
	uniform float _3delight_shading_reflectionNoiseAmplitude
	uniform float _3delight_shading_reflectionNoiseFrequency
	uniform float _3delight_shading_reflectionSamples
	uniform float[] reflectivity[].reflectivity_Interp
	float[] reflectivity[].reflectivity_Position
	float[] reflectivity[].reflectivity_FloatValue
	uniform float refractions
	float refractiveIndex
	uniform float refractionLimit
	float lightAbsorbance
	float shadowAttenuation
	color[] specularColor[].specularColor_Color
	uniform float[] specularColor[].specularColor_Interp
	float[] specularColor[].specularColor_Position
	float specularity
	uniform float[] specularRollOff[].specularRollOff_Interp
	float[] specularRollOff[].specularRollOff_Position
	float[] specularRollOff[].specularRollOff_FloatValue
	float translucence
	float translucenceDepth
	float translucenceFocus
	color[] transparency[].transparency_Color
	uniform float[] transparency[].transparency_Interp
	float[] transparency[].transparency_Position
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
#include "ramp_utils.h"
#include "shading_utils.h"

color
old_getTranslucence(normal i_Nf; float i_translucence; )
{
	color outColor = 0;
	extern point P;
	extern color Cl;
	float nondiff;

	if(i_translucence != 0)
	{
		illuminance(P, i_Nf, PI)
		{
			outColor += Cl;
		}

		outColor *= i_translucence;
	}

	return outColor;
}

void
maya_rampShader(
	// Inputs
	//
	color i_ambientColor;
	color i_color_colors[];
	uniform float i_color_interp[];
	float i_color_positions[];
	float i_colorInput;
	float i_diffuse;
	float i_eccentricity;
	color i_environment_colors[];
	uniform float i_environment_interp[];
	float i_environment_positions[];
	float i_forwardScatter;
	color i_incandescence_colors[];
	uniform float i_incandescence_interp[];
	float i_incandescence_positions[];	
	float i_matteOpacity;
	float i_matteOpacityMode;
	normal i_normalCamera;
	color i_reflectedColor;
	uniform float i_reflectionBlur;
	uniform float i_reflectionLimit;
	uniform float i_reflectionMaxDistance;
	uniform float i_reflectionNoiseAmplitude;
	uniform float i_reflectionNoiseFrequency;
	uniform float i_reflectionSamples;
	uniform float i_reflectivity_interp[];
	float i_reflectivity_positions[];
	float i_reflectivity_values[];

	/* Refraction. */
	uniform float i_refractions;
	float i_refractiveIndex;
	uniform float i_refractionLimit;
	float i_lightAbsorbance;
	float i_shadowAttenuation;

	color i_specularColor_colors[];
	uniform float i_specularColor_interp[];
	float i_specularColor_positions[];
	float i_specularity;
	uniform float i_specularRolloff_interp[];
	float i_specularRolloff_positions[];
	float i_specularRolloff_values[];
	float i_translucence;
	float i_translucenceDepth;
	float i_translucenceFocus;
	color i_transparency_colors[];
	uniform float i_transparency_interp[];
	float i_transparency_positions[];

	// Outputs
	//
	output color o_outColor;
	output color o_outTransparency;)
{
	extern varying vector I;
	normal Nn = normalize(i_normalCamera);
	normal Nf = ShadingNormal(Nn);
	vector In = normalize(I);
	extern color Cs;
	
	float input = 0;
	float count = 0;
	float facing = -In . Nf;

	color Ia = getAmbient(Nf) + i_ambientColor;
	color Id = i_diffuse * getDiffuse(Nf, 0, 0) * (1 - i_forwardScatter);
	color Itr = getTranslucence(
		Nf, i_translucence, i_translucenceDepth, i_translucenceFocus);
		
	color Iinc = colorRamp(
		facing,
		i_incandescence_positions, i_incandescence_interp, i_incandescence_colors);

	color transparency = colorRamp(
  	  facing,
    	i_transparency_positions,
    	i_transparency_interp,
    	i_transparency_colors);

 	color br = Id + Ia;
	float brightness = luminance(br);
	
	o_outColor = Cs;
	
	if( i_colorInput==0 )
	{
		/* LightAngle: compute the angle that is closest to surface's normal */
		extern point P;
		float lightangle = 0.5;
		
		/* Note that no ambient lights will be included in here, that is the 
		   way maya works from what I can understend */
		illuminance(P, Nf, PI / 2)
			lightangle = max( 1-acos(normalize(L).Nf)/PI, lightangle);

		o_outColor *= colorRamp(
			lightangle, i_color_positions, i_color_interp, i_color_colors);
	}
	else if(i_colorInput == 1)
	{
		/* FacingAngle */
		o_outColor *= colorRamp(
			facing,
			i_color_positions, i_color_interp, i_color_colors);
	}
	else if( i_colorInput == 2 )
	{
		// Brightness
		o_outColor *= colorRamp(
			brightness,
			i_color_positions, i_color_interp, i_color_colors);
	}
	else
	{
		/* TODO: Normalized brightness */
		o_outColor *= colorRamp(
			brightness,
			i_color_positions, i_color_interp, i_color_colors);
	}
		
	/* Specular shading. */
	float specRolloff = floatRamp(
		facing,
		i_specularRolloff_positions,
		i_specularRolloff_interp,
		i_specularRolloff_values);

	color specColor = getBlinn(Nf, i_eccentricity, specRolloff, 0, 0);
	float specBright = (comp(specColor, 0) + comp(specColor, 1) + comp(specColor, 2)) * brightness / 3;
	color specHue = colorRamp(
		specBright * specBright,
		i_specularColor_positions, i_specularColor_interp, i_specularColor_colors);

	specColor = 0.8 * i_specularity * specColor * specHue;

	/* Reflections */
	float reflectivity = floatRamp(
		facing,
		i_reflectivity_positions,
		i_reflectivity_interp,
		i_reflectivity_values );

	/*
		For some reason, specular rolloff does not affect reflections in
		this shader. In other shaders it multiplies reflectivity here.
	*/
	color Ir = getReflection(
		Nf, In, color(1), reflectivity, i_reflectedColor,
		i_reflectionMaxDistance, i_reflectionSamples, i_reflectionBlur,
		i_reflectionNoiseAmplitude, i_reflectionNoiseFrequency,
		i_reflectionLimit );

	computeSurface(
		o_outColor,
		transparency,
		i_matteOpacityMode,
		i_matteOpacity,
		o_outColor,
		o_outTransparency );

	// FIXME: some of these are probably wrong for this shader
	extern color __transparency;
#ifdef USE_AOV_aov_ambient
	extern color aov_ambient;
	if( isoutput(aov_ambient) )
	{
		aov_ambient += __transparency * Ia * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse
	extern color aov_diffuse;
	if( isoutput(aov_diffuse) )
	{
		color aov_diff = o_outColor;
		if(i_colorInput <= 1)
		{
			aov_diff *= Id;
		}
		aov_diff *= 1.0 - o_outTransparency;

		aov_diffuse += __transparency * aov_diff;
	}
#endif
#ifdef USE_AOV_aov_specular
	extern color aov_specular;
	aov_specular += __transparency * specColor;
#endif
#ifdef USE_AOV_aov_incandescence
	extern color aov_incandescence;
	aov_incandescence += __transparency * Iinc;
#endif
#ifdef USE_AOV_aov_translucence
	extern color aov_translucence;
	if( isoutput(aov_translucence) )
	{
		aov_translucence += __transparency * Itr * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_ambient_no_shadow
	extern color aov_ambient_no_shadow;
	if( isoutput(aov_ambient_no_shadow) )
	{
		color Ia_nshad = getAmbientUnshadowed(Nf) + i_ambientColor;
		aov_ambient_no_shadow +=
			__transparency * Ia_nshad * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_no_shadow
	extern color aov_diffuse_no_shadow;
	if( isoutput(aov_diffuse_no_shadow) )
	{
		color aov_diff_nshad = o_outColor;
	
		if(i_colorInput <= 1)
		{
			aov_diff_nshad *= i_diffuse * getDiffuse(Nf, 0, 1) * 
				(1 - i_forwardScatter) * (1.0 - o_outTransparency);
		}
		aov_diffuse_no_shadow += __transparency * aov_diff_nshad;
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity
	extern color aov_diffuse_intensity;
	if( isoutput(aov_diffuse_intensity) )
	{
		color aov_diff_int;
		if(i_colorInput <= 1)
		{
			aov_diff_int = Id;
		}
		else
		{
			aov_diff_int = luminance(o_outColor);
		}
		aov_diff_int *= 1.0 - o_outTransparency;
		aov_diffuse_intensity += __transparency * aov_diff_int;
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity_no_shadow
	extern color aov_diffuse_intensity_no_shadow;
	if( isoutput(aov_diffuse_intensity_no_shadow) )
	{
		if(i_colorInput <= 1)
		{
			aov_diffuse_intensity_no_shadow +=
				__transparency * i_diffuse * getDiffuse(Nf, 0, 1) * 
				(1 - i_forwardScatter) * (1.0 - o_outTransparency);
		}
		else
		{
			aov_diffuse_intensity_no_shadow +=
				__transparency * luminance(o_outColor) * (1.0 - o_outTransparency);
		}
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity
	extern color aov_key_lights_diffuse_intensity;
	if( isoutput(aov_key_lights_diffuse_intensity) )
	{
		if(i_colorInput <= 1)
		{
			aov_key_lights_diffuse_intensity +=
				__transparency * i_diffuse * getDiffuse(Nf, 1, 0) * 
				(1 - i_forwardScatter) * (1.0 - o_outTransparency);
		}
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity_no_shadow
	extern color aov_key_lights_diffuse_intensity_no_shadow;
	if( isoutput(aov_key_lights_diffuse_intensity_no_shadow) )
	{
		if(i_colorInput <= 1)
		{
			aov_key_lights_diffuse_intensity_no_shadow +=
				__transparency * i_diffuse * getDiffuse(Nf, 1, 1) *
				(1 - i_forwardScatter) * (1.0 - o_outTransparency);
		}
	}
#endif
#ifdef USE_AOV_aov_specular_no_shadow
	extern color aov_specular_no_shadow;
	if( isoutput(aov_specular_no_shadow) )
	{
		aov_specular_no_shadow +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, specRolloff, 0, 1) * specHue;
	}
#endif
#ifdef USE_AOV_aov_specular_intensity
	extern color aov_specular_intensity;
	if( isoutput(aov_specular_intensity) )
	{
		aov_specular_intensity +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, specRolloff, 0, 0);
	}
#endif
#ifdef USE_AOV_aov_specular_intensity_no_shadow
	extern color aov_specular_intensity_no_shadow;
	if( isoutput(aov_specular_intensity_no_shadow) )
	{
		aov_specular_intensity_no_shadow +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, specRolloff, 0, 1);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity
	extern color aov_key_lights_specular_intensity;
	if( isoutput(aov_key_lights_specular_intensity) )
	{
		aov_key_lights_specular_intensity +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, specRolloff,	1, 0);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity_no_shadow
	extern color aov_key_lights_specular_intensity_no_shadow;
	if( isoutput(aov_key_lights_specular_intensity_no_shadow) )
	{
		aov_key_lights_specular_intensity_no_shadow +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, specRolloff, 1, 1);
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
		normalize(i_normalCamera),
		I,
		i_refractions,
		i_refractiveIndex,
		i_refractionLimit,
		i_lightAbsorbance,
		i_shadowAttenuation,
		o_outTransparency,
		refraction );

	normal Nw = normalize(ntransform("world", reflect( I, Nf )));
	float envRamp = (normalize(Nw) . vector(0,1,0)) * 0.5 + 0.5;
	color Cenv = colorRamp(envRamp, 
		i_environment_positions, 
		i_environment_interp, 
		i_environment_colors);

	/* Add the environment ramp to the reflection AOVs. */
#ifdef USE_AOV_aov_reflection
	extern color aov_reflection;
	aov_reflection += __transparency * reflectivity * Cenv;
#endif
#ifdef USE_AOV_aov_env_reflection
	extern color aov_env_reflection;
	aov_env_reflection += __transparency * reflectivity * Cenv;
#endif

#ifdef USE_AOV_aov_color_no_shadow
	extern color aov_color_no_shadow;
	if( isoutput(aov_color_no_shadow) )
	{
		color color_no_shadow = o_outColor;

		if(i_colorInput <= 1)
		{
			color Ia_no_shw = i_ambientColor + getAmbientUnshadowed(Nf);
			color Id_no_shw =
				i_diffuse * getDiffuse(Nf, 0, 1) * (1 - i_forwardScatter);

			color_no_shadow *=
				(Ia_no_shw + Id_no_shw + Itr) * (1.0 - o_outTransparency);
		}

		color Is_no_shw = getBlinn(Nf, i_eccentricity, specRolloff, 0, 1);
		color specColor_no_shw = 0.8 * i_specularity * Is_no_shw * specHue;
		color_no_shadow +=
			Ir + specColor_no_shw + Cenv * reflectivity + Iinc + refraction;

		aov_color_no_shadow += __transparency * color_no_shadow;
	}
#endif

	if(i_colorInput <= 1)
	{
		o_outColor *= (Ia + Id + Itr);
	}

	o_outColor += Ir + specColor;
	o_outColor += Cenv * reflectivity;
	o_outColor += Iinc + refraction;

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
}

#endif /* __rampShader_h */

