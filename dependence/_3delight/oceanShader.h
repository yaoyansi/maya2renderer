/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __oceanShader_h
#define __oceanShader_h

/*
begin inputs
	color ambientColor
	float bumpBlur
	float diffuse
	float eccentricity
	float[] environment[].environment_Position
	color[] environment[].environment_Color
	uniform float[] environment[].environment_Interp  
	color foamColor
	float foamEmission
	float foamThreshold
	float foamOffset
	color incandescence
	float matteOpacity
	float matteOpacityMode
	normal normalCamera
	float numFrequencies
	float observerSpeed
	color reflectedColor
	uniform float _3delight_shading_reflectionBlur
	uniform float reflectionLimit
	uniform float _3delight_shading_reflectionMaxDistance
	uniform float _3delight_shading_reflectionNoiseAmplitude
	uniform float _3delight_shading_reflectionNoiseFrequency
	uniform float _3delight_shading_reflectionSamples
	float reflectionSpecularity
	float reflectivity
	float refractionLimit
	float shadowAttenuation
	float refractions
	float refractiveIndex
	float scale
	color specularColor
	float specularity
	float time
	float translucence
	float translucenceDepth
	float translucenceFocus
	color transparency
	float troughShadowing
	color waterColor
	float waveDirSpread
	float[] waveHeight[].waveHeight_Position
	float[] waveHeight[].waveHeight_FloatValue
	uniform float[] waveHeight[].waveHeight_Interp
	float waveHeightOffset
	float waveLengthMin
	float waveLengthMax
	float[] wavePeaking[].wavePeaking_Position
	float[] wavePeaking[].wavePeaking_FloatValue
	uniform float[] wavePeaking[].wavePeaking_Interp
	float[] waveTurbulence[].waveTurbulence_Position
	float[] waveTurbulence[].waveTurbulence_FloatValue
	uniform float[] waveTurbulence[].waveTurbulence_Interp
	float waveSpeed
	float2 windUV
end inputs

begin outputs
	color outColor
	color outTransparency
	float displacement
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

#include "ocean_utils.h"
#ifdef SHADER_TYPE_displacement
#include "displacementShader.h"
#else
#include "shading_utils.h"
#endif

void
maya_oceanShader(
	// Inputs
	//
	color i_ambientColor;
	float i_bumpBlur;
	float i_diffuse;
	float i_eccentricity;
	float i_environment_positions[];
	color i_environment_colors[];
	uniform float i_environment_interp[];  
	color i_foamColor;
	float i_foamEmission;
	float i_foamThreshold;
	float i_foamOffset;
	color i_incandescence;
	float i_matteOpacity;
	float i_matteOpacityMode;
	normal i_normalCamera;
	uniform float i_numFrequencies;
	float i_observerSpeed;
	color i_reflectedColor;
	uniform float i_reflectionBlur;
	uniform float i_reflectionLimit;
	uniform float i_reflectionMaxDistance;
	uniform float i_reflectionNoiseAmplitude;
	uniform float i_reflectionNoiseFrequency;
	uniform float i_reflectionSamples;
	float i_reflectionSpecularity;
	float i_reflectivity;
	uniform float i_refractionLimit;
	float i_shadowAttenuation;
	uniform float i_refractions;
	float i_refractiveIndex;
	float i_scale;
	color i_specularColor;
	float i_specularity;
	float i_time;
	float i_translucence;
	float i_translucenceDepth;
	float i_translucenceFocus;
	color i_transparency;
	float i_troughShadowing;
	color i_waterColor;
	float i_waveDirSpread;
	float i_waveHeight_positions[];
	float i_waveHeight_floatValues[];
	uniform float i_waveHeight_interp[];
	float i_waveHeightOffset;
	float i_waveLengthMin;
	float i_waveLengthMax;
	float i_wavePeaking_positions[];
	float i_wavePeaking_floatValues[];
	uniform float i_wavePeaking_interp[];
	float i_waveTurbulence_positions[];
	float i_waveTurbulence_floatValues[];
	uniform float i_waveTurbulence_interp[];
	float i_waveSpeed;
	float i_windUV[2];

	// Outputs
	//
	output color o_outColor;
	output color o_outTransparency;
	output float o_outDisplacement;)
{
	/* Catch photon shading. */
#ifndef SHADER_TYPE_displacement
	BEGIN_PHOTON_CASE( i_waterColor, i_specularColor, i_transparency )
#endif

	// compute texture
	float waveLengthMin = i_waveLengthMin;
	float waveLengthMax = i_waveLengthMax;

	if(waveLengthMax < waveLengthMin)
	{
		waveLengthMax = waveLengthMin;
		waveLengthMin = i_waveLengthMax;
	}

	float ocean;
	float foam;
	extern point P;
	point Pworld = transform("world", P);

	float time = 0.2 * i_time * i_waveSpeed;

	getOcean(
		xcomp(Pworld), -zcomp(Pworld), time, i_scale, i_windUV, i_observerSpeed,
		i_waveDirSpread, i_numFrequencies, waveLengthMin, waveLengthMax,
		i_waveHeight_positions, i_waveHeight_floatValues, i_waveHeight_interp,
		i_waveTurbulence_positions, i_waveTurbulence_floatValues,
		i_waveTurbulence_interp, i_wavePeaking_positions, i_wavePeaking_floatValues,
		i_wavePeaking_interp, i_foamEmission, i_foamThreshold,
		ocean, foam);

#ifdef SHADER_TYPE_displacement
	o_outDisplacement = ocean + i_waveHeightOffset;
	maya_displacementShader(o_outDisplacement / (i_scale));
#else

	extern color Cs;
	o_outColor = Cs * i_waterColor;
 
	normal Nn = i_normalCamera;
	normal Nf = ShadingNormal(Nn);
	do_bump_map(ocean, 1, Nf, Nf);

	color Cdiffuse = i_diffuse * getDiffuse(Nf, 0, 0);
	color Cambient = i_ambientColor + getAmbient(Nf);

	color Cspecular = getBlinn(Nf, i_eccentricity, 1.0, 0, 0);
	Cspecular *= 0.8 * i_specularity * i_specularColor; 

	color Ctranslucence = getTranslucence(
		Nf, i_translucence, i_translucenceDepth, i_translucenceFocus);

	// Reflections
	extern varying vector I;
	vector In = normalize(I);

	color Creflection = getReflection(
		Nf, In, color(1), i_reflectivity, i_reflectedColor,
		i_reflectionMaxDistance, i_reflectionSamples, i_reflectionBlur,
		i_reflectionNoiseAmplitude, i_reflectionNoiseFrequency,
		i_reflectionLimit );

	// Trough shadowing
	float wlMin = waveLengthMin;
	float wlMax = waveLengthMax;

	wlMin *= floatRamp(0.1, 
		i_waveHeight_positions, i_waveHeight_interp, i_waveHeight_floatValues);
	wlMax *= floatRamp(0.9,
		i_waveHeight_positions, i_waveHeight_interp, i_waveHeight_floatValues);

	wlMax = max( wlMin, wlMax );
	wlMax /= i_scale;

	if(wlMax > EPSILON)
	{
		float displacement = ocean + i_waveHeightOffset;
		displacement = (displacement + wlMax) / (2.5 * wlMax);
		displacement = clamp(displacement, 0, 1);
		displacement *= i_troughShadowing * displacement;
		displacement += 1 - i_troughShadowing;
		o_outColor *= displacement;
	}

	// Foam
	if (foam > 0)
	{
		float underwaterFoam = min(0.5, foam);
		foam = max(0, foam - 0.3);
		float foamInverse = 1 - 0.5 * foam;
		foamInverse = max(0, foamInverse);

		o_outColor += underwaterFoam * i_foamColor * i_waterColor;
		o_outColor = foam * i_foamColor + foamInverse * o_outColor;
	}

	computeSurface(
		o_outColor,
		i_transparency,
		i_matteOpacityMode,
		i_matteOpacity,
		o_outColor,
		o_outTransparency);

	extern color __transparency;
#ifdef USE_AOV_aov_ambient
	extern color aov_ambient;
	if( isoutput(aov_ambient) )
	{
		aov_ambient +=
			__transparency * Cambient * o_outColor * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse
	extern color aov_diffuse;
	if( isoutput(aov_diffuse) )
	{
		aov_diffuse +=
			__transparency * Cdiffuse * o_outColor * (1.0 - o_outTransparency);
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
			__transparency * Ctranslucence * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_ambient_no_shadow
	extern color aov_ambient_no_shadow;
	if( isoutput(aov_ambient_no_shadow) )
	{
		color Ia_nshad = i_ambientColor + getAmbientUnshadowed(Nf);
		aov_ambient_no_shadow +=
			__transparency * Ia_nshad * o_outColor * (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_no_shadow
	extern color aov_diffuse_no_shadow;
	if( isoutput(aov_diffuse_no_shadow) )
	{
		aov_diffuse_no_shadow +=
			__transparency * o_outColor * i_diffuse * getDiffuse(Nf, 0, 1)
				* (1.0 - o_outTransparency);
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity
	extern color aov_diffuse_intensity;
	if( isoutput(aov_diffuse_intensity) )
	{
		aov_diffuse_intensity += __transparency *
			luminance(Cdiffuse * o_outColor * (1.0 - o_outTransparency));
	}
#endif
#ifdef USE_AOV_aov_diffuse_intensity_no_shadow
	extern color aov_diffuse_intensity_no_shadow;
	if( isoutput(aov_diffuse_intensity_no_shadow) )
	{
		aov_diffuse_intensity_no_shadow += __transparency *
			luminance(
				i_diffuse * getDiffuse(Nf, 0, 1) * 
				o_outColor * (1.0 - o_outTransparency) );
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity
	extern color aov_key_lights_diffuse_intensity;
	if( isoutput(aov_key_lights_diffuse_intensity) )
	{
		aov_key_lights_diffuse_intensity += __transparency *
			luminance(
				i_diffuse * getDiffuse(Nf, 1, 0) * 
				o_outColor * (1.0 - o_outTransparency) );
	}
#endif
#ifdef USE_AOV_aov_key_lights_diffuse_intensity_no_shadow
	extern color aov_key_lights_diffuse_intensity_no_shadow;
	if( isoutput(aov_key_lights_diffuse_intensity_no_shadow) )
	{
		aov_key_lights_diffuse_intensity_no_shadow += __transparency *
			luminance(
				i_diffuse * getDiffuse(Nf, 1, 1) 
				* o_outColor * (1.0 - o_outTransparency) );
	}
#endif
#ifdef USE_AOV_aov_specular_no_shadow
	extern color aov_specular_no_shadow;
	if( isoutput(aov_specular_no_shadow) )
	{
		aov_specular_no_shadow +=
			__transparency * getBlinn(Nf, i_eccentricity, 1.0, 0, 1) *
				0.8 * i_specularity * i_specularColor; 
	}
#endif
#ifdef USE_AOV_aov_specular_intensity
	extern color aov_specular_intensity;
	if( isoutput(aov_specular_intensity) )
	{
		aov_specular_intensity +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, 1.0, 0, 0);
	}
#endif
#ifdef USE_AOV_aov_specular_intensity_no_shadow
	extern color aov_specular_intensity_no_shadow;
	if( isoutput(aov_specular_intensity_no_shadow) )
	{
		aov_specular_intensity_no_shadow +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, 1.0, 0, 1);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity
	extern color aov_key_lights_specular_intensity;
	if( isoutput(aov_key_lights_specular_intensity) )
	{
		aov_key_lights_specular_intensity +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, 1.0, 1, 0);
	}
#endif
#ifdef USE_AOV_aov_key_lights_specular_intensity_no_shadow
	extern color aov_key_lights_specular_intensity_no_shadow;
	if( isoutput(aov_key_lights_specular_intensity_no_shadow) )
	{
		aov_key_lights_specular_intensity_no_shadow +=
			__transparency * 0.8 * i_specularity * 
			getBlinn(Nf, i_eccentricity, 1.0, 1, 1);
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

	// Refractions
	color Crefraction;
	doRefraction(
		normalize(i_normalCamera),
		I,
		i_refractions,
		i_refractiveIndex,
		i_refractionLimit,
		0,
		i_shadowAttenuation,
		o_outTransparency,
		Crefraction);

	/*
		Compute environment contribution. This was tested on a flat sphere with
		refractive index both < 1 and > 1 and weird color ramps. Don't touch
		it, it works exactly as maya's.
	*/
	color Cenv = 0;
	if( i_reflectivity > 0 )
	{
		normal Nw = normalize(ntransform("world", reflect( I, Nf )));
		float envRamp = ycomp(Nw) * 0.5 + 0.5;

		Cenv = colorRamp(
			envRamp, 
			i_environment_positions, 
			i_environment_interp, 
			i_environment_colors);

		float kR = 0; 
		float kT = 0;
		fresnel(In, Nf, 1 / i_refractiveIndex, kR, kT);
		Cenv *= i_reflectivity * kR;
	}

#ifdef USE_AOV_aov_color_no_shadow
	extern color aov_color_no_shadow;
	if( isoutput(aov_color_no_shadow) )
	{
		color Cambient_no_shw = i_ambientColor + getAmbientUnshadowed(Nf);
		color Cdiffuse_no_shw =  i_diffuse * getDiffuse(Nf, 0, 1);
		color Cspecular_no_shw =  0.8 * i_specularity * i_specularColor * 
			getBlinn(Nf, i_eccentricity, 1.0, 0, 1);

		color color_no_shadow =
			o_outColor * (Cambient_no_shw + Cdiffuse_no_shw + Ctranslucence)
			* (1.0 - o_outTransparency);
		color_no_shadow +=
			Creflection + Cspecular_no_shw + i_incandescence + Crefraction + Cenv;

		aov_color_no_shadow += __transparency * color_no_shadow;
	}
#endif

	o_outColor *= (Cambient + Cdiffuse + Ctranslucence);
	o_outColor += Cspecular + Creflection + Cenv + i_incandescence;
	o_outColor += Crefraction;
 
#ifdef USE_AOV_aov_refraction
	extern color aov_refraction;
	aov_refraction += __transparency * Crefraction;
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
#endif  

#ifndef SHADER_TYPE_displacement
	END_PHOTON_CASE
#endif
}
 
#endif /* __oceanShader_h */

