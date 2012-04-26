/*
	Copyright (c) 2007 TAARNA Studios International.
*/

#ifndef __mia_material_h
#define __mia_material_h

/*
begin inputs
	color additional_color

	color diffuse
	float diffuse_weight
	float diffuse_roughness

	color refl_color
	float reflectivity
	float refl_gloss
	float refl_gloss_samples
	float refl_hl_only
	float refl_is_metal
	
	float refr_ior
	color refr_color
	float transparency
	float refr_gloss
	float refr_gloss_samples
	float thin_walled

	float anisotropy
	float anisotropy_rotation	

	float brdf_fresnel
	float brdf_0_degree_refl
	float brdf_90_degree_refl
	float brdf_curve

	float ao_on
	float ao_samples
	float ao_distance
	color ao_dark
	color ao_ambient

	float hl_vs_refl_balance
end inputs

begin outputs
	color outValue
end outputs

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

begin shader_extra_parameters aov_refraction
#ifdef USE_AOV_aov_refraction
	output varying color aov_refraction = 0;
#endif
end shader_extra_parameters

begin shader_extra_parameters aov_occlusion
#ifdef USE_AOV_aov_occlusion
	output varying color aov_occlusion = 0;
#endif
end shader_extra_parameters
*/

#define bool float
#define true 1
#define false 0

/*
 * Oren and Nayar's generalization of Lambert's reflection model.
 * The roughness parameter gives the standard deviation of angle
 * orientations of the presumed surface grooves.  When roughness=0,
 * the model is identical to Lambertian reflection.
 * Taken from Arman so credits go to Larry Gritz.
 */
color
LocIllumOrenNayar (normal N;  vector V;  float roughness;)
{
    /* Surface roughness coefficients for Oren/Nayar's formula */
    float sigma2 = roughness * roughness;
    float A = 1 - 0.5 * sigma2 / (sigma2 + 0.33);
    float B = 0.45 * sigma2 / (sigma2 + 0.09);
    /* Useful precomputed quantities */
    float  theta_r = acos (V . N);        /* Angle between V and N */
    vector V_perp_N = normalize(V-N*(V.N)); /* Part of V perpendicular to N */

    /* Accumulate incoming radiance from lights in C */
    color  C = 0;
    extern point P;
    illuminance (P, N, PI/2) {
	/* Must declare extern L & Cl because we're in a function */
	extern vector L;  extern color Cl;
	uniform float nondiff = 0;
	lightsource ("__nondiffuse", nondiff);
	if (nondiff == 0) {
	    vector LN = normalize(L);
	    float cos_theta_i = LN . N;
	    float cos_phi_diff = V_perp_N . normalize(LN - N*cos_theta_i);
	    float theta_i = acos (cos_theta_i);
	    float alpha = max (theta_i, theta_r);
	    float beta = min (theta_i, theta_r);
	    C += Cl * cos_theta_i * 
		(A + B * max(0,cos_phi_diff) * sin(alpha) * tan(beta));
	}
    }
    return C;

}


// Compute the square of a given value.
float sq(float x)
{
	return x * x;
}

// Compute the CIE luminance (Rec. 709) of a given color.
float luminance(color c)
{
	return
	      comp(c, 0) * 0.212671
	    + comp(c, 1) * 0.715160
	    + comp(c, 2) * 0.072169;
}

// Compute the roughness corresponding to a given glossiness value.
float roughness(float gloss)
{
	return pow(2.0, 8.0 * gloss);
}

// Compute sampling parameters.
float compute_sampling_angle( float glossiness; )
{
	if( glossiness >= 1.0 )
		return 0.0;
	else

	    return (1.0 - pow(clamp(glossiness, 0.0, 1.0), 0.2)) * PI / 2.0;
}

color trace_reflection(
	vector In;
	normal Nf;
	vector V;
	float i_refl_gloss;
	uniform float i_refl_gloss_samples;)
{
	extern point P;

	// Compute the sampling parameters.
	float sample_angle = compute_sampling_angle( i_refl_gloss );
	float sample_count = (i_refl_gloss == 0) ?
		min(4, i_refl_gloss_samples) : i_refl_gloss_samples;

	// Compute reflected direction.
	vector refl_dir = reflect(In, Nf);

	return trace( P, refl_dir, "samplecone", sample_angle,
		"samples", sample_count );
}

color trace_refraction(
	normal Nn;
	vector In;
	normal Nf;
	vector V;
	float i_refr_ior, i_refr_gloss;
	uniform float i_refr_gloss_samples; )
{
	extern point P;

	// Compute the sampling parameters.
	uniform float sample_angle = compute_sampling_angle( i_refr_gloss );
	uniform float sample_count = (i_refr_gloss == 0) ?
		min(4, i_refr_gloss_samples) : i_refr_gloss_samples;

	// Compute refracted direction.
	float eta = (In . Nn < 0.0) ? 1.0 / i_refr_ior : i_refr_ior;
	vector refr_dir = refract(In, Nf, eta);

	return trace( P, refr_dir, "samplecone", sample_angle,
		"samples", sample_count );
}

/*
	Compute specular highlights.

	NOTES
	- We use the ward anisotropic model. But we sum 3 highlights with decreasing
	roughness and increasing contribution.
*/
color specular_highlight(
	vector In;
	normal Nf;
	vector V;
	float  refl_roughness_u, refl_roughness_v;)
{
	extern color Cl;
	extern vector dPdu, dPdv;
	extern point P;

	vector xdir = normalize( dPdu );
	vector ydir = normalize( dPdv );

	color highlights = 0;

	/* We have three specular higlihgts of diminushing roughness but increasing
	   brightness */
	uniform float component_coefs[3] = {0.5, 1.0, 1.5}; 

	illuminance( P, Nf, PI * 0.5 )
	{
		uniform float nonspecular = 0;
		lightsource( "__nonspecular", nonspecular );

		if( nonspecular == 0 )
		{
			vector Ln = normalize(L);

			float dot_ln = Ln . Nf;
			float dot_vn = V . Nf;

			if( dot_vn*dot_ln>0.0 )
			{
				vector Hn = normalize(V + Ln);
				float dot_hn2 = min(sq(Hn . Nf), 1.0);

				if( dot_hn2>0.0 )
				{
					/* precompute this to get it out of the loop below */
					float k1_devider = 1 / (sqrt(dot_vn * dot_ln) * 4.0 * PI);  
					float smooth_step_ln = smoothstep( 0, 0.25, dot_ln );

					uniform float i=0;
					uniform float roughness_coef = 1;

					for( i=0; i<3; i+=1.0 )
					{
						// Compute the highlight due to this light source.
						float k1 =
							(refl_roughness_u * refl_roughness_v * roughness_coef * roughness_coef )
							* k1_devider;
						float k2 =
							sq(Hn . xdir * refl_roughness_u * roughness_coef)
							+ sq(Hn . ydir * refl_roughness_v * roughness_coef);
						color c =
							k1 * exp(-k2 / dot_hn2)
							* dot_ln
							* smooth_step_ln;

						// Accumulate highlights.
						highlights += Cl * c * component_coefs[i];

						roughness_coef *= 0.5;
					}
				}
			}
		}
	}

	return highlights;
}

#define RGBA_COLOR( x ) color x; float x##_a;

void maya_mia_material(
	color i_ambient;

	// Diffuse reflection parameters.
	color i_diffuse_color;
	float i_diffuse_scale;
	float i_diffuse_roughness;

	// Reflection parameters.
	color reflection_color;
	float reflectivity;
	float reflection_gloss;
	uniform float reflection_gloss_samples;
	bool highights_only;
	bool is_metallic;

	// Transparency/refraction parameters.
	float refraction_ior;
	color refraction_color;
	float transparency;
	float refraction_gloss;
	uniform float refraction_gloss_samples; 
	bool thin_walled;

	float anisotropy;
	float anisotropy_rotation;

	// BRDF parameters.
	bool brdf_fresnel;
	float brdf_0_degree_refl;
	float brdf_90_degree_refl;
	float brdf_curve;

	/* Ambient occlusion. */
	bool enable_ao;
	float ao_samples;
	float ao_distance;
	color ao_dark;
	color ao_ambient;

	// Additional flags
	float hl_vs_refl_balance;

	output color outValue;)
{
	extern normal N;
	extern vector I;
	extern point P;

	normal Nn = normalize(N);
	vector In = normalize(I);
	normal Nf = faceforward(Nn, In);
	vector V = -In;

	uniform string rtype;
	uniform float rdepth;
	rayinfo( "type", rtype ); rayinfo( "depth", rdepth );

	bool shadow_ray = (rtype == "transmission") ? 1 : 0;
	bool photon_ray = (rtype == "light") ? 1 : 0;

	color refl_color = reflection_color;
	color refr_color = refraction_color;
	uniform bool ao_on = enable_ao;

	if( shadow_ray == true )
	{
		/* Disable further refraction and ambient occlusion */
		refr_color = 0;
		ao_on = false;
	}

	if( rdepth >= 2 )
		refl_color = 0;

	float reflectivity_scale = reflectivity;
	float diffuse_scale = i_diffuse_scale;
	float transparency_scale = transparency;

	// Compute the reflection curve.
	if (brdf_fresnel == true)
	{
		// Automatic mode.
		float eta = (In . Nn < 0.0) ? 1.0 / refraction_ior : refraction_ior;
		float kr, kt;
		fresnel( In, Nf, eta, kr, kt);
		reflectivity_scale *= kr;
	}
	else
	{
		// Manual mode.
		reflectivity_scale *=
			mix(
				brdf_0_degree_refl,
				brdf_90_degree_refl,
				pow(1-abs(V . Nf), brdf_curve));
	}

	// Compute component weights.

	RGBA_COLOR(scaled_refl_color);
	scaled_refl_color = refl_color * reflectivity_scale;
	scaled_refl_color_a = luminance(scaled_refl_color);

	if (is_metallic == true)
	{
		diffuse_scale *= 1.0 - luminance(refl_color) * reflectivity_scale;
		diffuse_scale = max(diffuse_scale, 0.0);
		scaled_refl_color *= i_diffuse_color;
	}

	RGBA_COLOR(scaled_refr_color);
	scaled_refr_color = refr_color;
	scaled_refr_color_a = luminance(scaled_refr_color);

#if 0
	if (brdf_conserve_energy == true)
	{
		diffuse_scale *= 1.0 - min(scaled_refr_color_a * transparency, 1.0);
		diffuse_scale *= 1.0 - min(scaled_refl_color_a, 1.0);
		transparency_scale *= 1.0 - min(scaled_refl_color_a, 1.0);
	}
#endif

	scaled_refr_color *= transparency_scale;

	RGBA_COLOR(scaled_diffuse_color);
	scaled_diffuse_color = i_diffuse_color * diffuse_scale;

	// Ambient occlusion.
	color ambient_occlusion = 0;

	if (ao_on == true)   // no AO for secondary reflections and refractions
	{
		// Add in the ambient occlusion term. FIXME: transform distance into
		// world units -- todo: aren't shader inputs (and thus ao_distance)
		// already expressed in world space?

		uniform float adaptive = ao_samples >= 256 ? 1 : 0;
		float occ =
			occlusion(
					P, Nf, ao_samples,
					"adaptive", adaptive,
					"maxdist", ao_distance);

		ambient_occlusion = mix(ao_ambient, ao_dark, occ);
	}

	// Diffuse component.
	color diffuse_component =
		scaled_diffuse_color
		* (ambient_occlusion + LocIllumOrenNayar(Nf, V, i_diffuse_roughness));

	// Reflected component.
	color reflected_component = 0;
	if( scaled_refl_color != 0 && highights_only==false )
	{
		reflected_component = scaled_refl_color *
			trace_reflection(
				In, Nf, V, reflection_gloss, reflection_gloss_samples );
	}

	// Compute reflection roughness values.
	float refl_roughness_u = roughness(reflection_gloss);
	float refl_roughness_v = refl_roughness_u * max(anisotropy, 0.01);

	if (refl_roughness_u >= 80.0)
		refl_roughness_u = 80.0 + sqrt(refl_roughness_u - 80.0);
	if (refl_roughness_v >= 80.0)
		refl_roughness_v = 80.0 + sqrt(refl_roughness_v - 80.0);

	/* Compute specular highlights. In "metal mode" the higlight color is
	   inherited from the diffuse color. */

	color highlights_component = 0;
	color hcolor = (is_metallic == true) ?
		i_diffuse_color*reflectivity : scaled_refl_color; 
	hcolor *= hl_vs_refl_balance;
	if( hcolor != 0 )
	{
		highlights_component = hcolor * 
			specular_highlight(
				In, Nf, V, refl_roughness_u, refl_roughness_v );
	}

	// Refracted component.
	color refracted_component = 0;
	if( scaled_refr_color != 0 )
	{
		refracted_component =  scaled_refr_color *
			trace_refraction(
				Nn, In, Nf, V,
				thin_walled == true ? 1.0 : refraction_ior,
				refraction_gloss,
				refraction_gloss_samples );
	}

	outValue = diffuse_component
		+ reflected_component
		+ highlights_component
		+ refracted_component
		+ i_ambient;
	
#ifdef USE_AOV_aov_occlusion
	extern varying color aov_occlusion;
	if( isoutput(aov_occlusion) )
	{
		aov_occlusion = ambient_occlusion;
	}
#endif

#ifdef USE_AOV_aov_diffuse
	extern varying color aov_diffuse;
	if( isoutput(aov_diffuse) )
	{
		aov_diffuse = diffuse_component;
	}
#endif

#ifdef USE_AOV_aov_specular
	extern varying color aov_specular;
	if( isoutput(aov_specular) )
	{
		aov_specular = highlights_component;
	}
#endif

#ifdef USE_AOV_aov_reflection
	extern varying color aov_reflection;
	if( isoutput(aov_reflection) )
	{
		aov_reflection = reflected_component;
	}
#endif

#ifdef USE_AOV_aov_refraction
	extern varying color aov_refraction;
	if( isoutput(aov_refraction) )
	{
		aov_refraction = refracted_component;
	}
#endif
}

#undef bool
#undef true
#undef false

#endif /* __mia_material_h */

