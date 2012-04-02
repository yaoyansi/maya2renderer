/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/
#include "shading_utils.h"
#include "utils.h"

/*
	ShadingNormal

	A wrapper for faceforward which avoids faceforward for single-sided
	primitives or when using double-sided shading. This is to prevent artefacts
	around silhouette edges caused by the way "Sides 2" is usually shaded. Note
	that we don't explicitely check for double-sided shading as it also sets
	Sides to 1.
*/
//normal ShadingNormal( normal i_N, const vector& I )
//{
//	normal Nf = i_N;
//
//	const float sides = 2;
//
//	if( sides == 2 )
//	{
//		Nf = faceforward(Nf, I);
//	}
//	//else
//	//{
//	//	/* This mess is to flip the normals of polygon meshes with reversed
//	//	   orientation. We only want it when 'N' is attached to the primitive. */
//	//	uniform float geometricnormal = 1;
//	//	attribute( "geometry:geometricnormal", geometricnormal );
//
//	//	if( geometricnormal == 0 )
//	//	{
//	//		uniform string orientation;
//	//		attribute( "Ri:Orientation", orientation );
//	//		if( orientation == "outside" )
//	//			Nf = -Nf;
//	//	}
//	//}
//
//	return Nf;
//}

/*
	Maya's ambient function
*/
color getAmbient( const normal& i_N )
{
	return color(0.0f, 0.0f, 0.0f);
}

//color getAmbientUnshadowed( normal i_N )
//{
//	extern point P;
//	color amb = 0;
//
//	illuminance( P )
//	{
//		if( L == vector(0) )
//		{
//			color unshadowed_cl = 0;
//			lightsource("__3dfm_unshadowed_cl", unshadowed_cl);
//			amb += unshadowed_cl;
//		}
//	}
//
//	return amb;
//}

/*
	Maya's diffuse function
*/
//color getDiffuse(
//	normal i_N; 
//	uniform float keyLightsOnly; 
//	uniform float unshadowed; )
//{
//	extern point P;
//	color C = 0;
//
//	illuminance( P, i_N, PI/2 )
//	{
//		float isKeyLight = 1;
//		
//		if( keyLightsOnly != 0 )
//		{
//			lightsource( "iskeylight", isKeyLight );
//		}
//		
//		if( isKeyLight != 0 )
//		{
//			float nondiffuse = 0;
//			lightsource( "__nondiffuse", nondiffuse );
//		
//			if( nondiffuse < 1 )
//			{
//				varying color cur_cl;
//				GET_CL(cur_cl);
//				C += cur_cl * normalize(L).i_N * (1-nondiffuse);
//			}
//		}
//	}
//
//	return C;
//}
//
//color getTranslucence(
//	const normal& i_N,
//	const float i_translucence,
//	const float i_translucenceDepth,
//	const float i_translucenceFocus)
//{
//	extern point P;
//	extern vector I;
//
// 	/*
// 		A translucence focus of 1 leads to a division by zero and an effective
// 		focus of 0. Clamping it like this yields about the same result as maya.
// 	*/
// 	float focus = min( i_translucenceFocus, 0.99999 );
// 
//	color C = 0;
//
//	if( i_translucence > 0.0 )
//	{
//		illuminance( P )
//		{
//			float nondiffuse = 0;
//			lightsource( "__nondiffuse", nondiffuse );
//
//			if( nondiffuse < 1 )
//			{
//				float costheta = normalize(L).normalize(I);
// 				float a = (1 + costheta) * 0.5;
//
// 				float trs = pow( pow(a, focus), 1/(1-focus) );
// 
//  				C += Cl * trs * (1-nondiffuse);
//			}
//		}
//	}
//
//	return C * i_translucence;
//}
//
//color
//getBlinn( 
//		normal i_Nf;
//		float i_eccentricity;
//		float i_specularRollOff;
//		uniform float i_keyLightsOnly;
//		uniform float unshadowed;
//		)
//{
//	float E;
//	color C = 0;
//	vector H, Ln, V, Nn;
//	float NH, NH2, NHSQR, Dd, Gg, VN, VH, LN, Ff, tmp;
//	extern point P;
//	extern vector L, I;
//	extern color Cl;
//
//	if(i_eccentricity != 1)
//		E = 1 / (SQR(i_eccentricity) - 1);
//	else
//		E = -1e5;
//
//	V = normalize(-I);
//	VN = V . i_Nf;
//
//	illuminance( P, i_Nf, PI / 2)
//	{
//		float isKeyLight = 1;
//		
//		if( i_keyLightsOnly != 0 )
//		{
//			lightsource( "iskeylight", isKeyLight );
//		}
//		
//		if( isKeyLight != 0 )
//		{
//			float nonspecular = 0;
//			lightsource( "__nonspecular", nonspecular );
//
//			if( nonspecular < 1 )
//			{
//				Ln = normalize(L);
//				H = normalize(Ln + V);
//				NH = i_Nf . H;
//				NHSQR = SQR(NH);
//				NH2 = NH * 2;
//				Dd = (E + 1) / (NHSQR + E);
//				Dd *= Dd;
//				VH = V . H;
//				LN = Ln . i_Nf;
//				if(VN < LN)
//				{
//					if(VN * NH2 < VH)
//						Gg = NH2 / VH;
//					else
//						Gg = 1 / VN;
//				}
//				else
//				{
//					if(LN * NH2 < VH)
//						Gg = (LN * NH2) / (VH * VN);
//					else
//						Gg = 1 / VN;
//				}
//				/* poor man's Fresnel */
//				tmp = pow((1 - VH), 3);
//				Ff = tmp + (1 - tmp) * i_specularRollOff;
//
//				varying color cur_cl;
//				GET_CL(cur_cl);
//				C += cur_cl * Dd * Gg * Ff * (1-nonspecular);
//			}
//		}
//	}
//	return C;
//}
//
//color getAnisotropic(
//		vector i_N, i_I, i_xdir;
//		float i_fresnel, i_roughness, i_spreadx, i_spready;
//		uniform float i_keyLightsOnly, unshadowed;)
//{
//	/* Stam's anisotropic BRDF */
//	float stam_anisotropy( float u, v, w, rx, ry )
//	{
//		float w2 = w * w;
//		float bt = 4 * PI * w2 * w2 * rx * ry;
//		float ex = exp(- u * u / (4 * w2 * rx * rx)) * exp( - v * v / (4 * w2 * ry * ry));
//
//		return ex / bt;
//	}
//
//	extern point P;
//	vector ydir  = i_N ^ i_xdir;
//
//	float costheta2 = i_I.i_N;
//
//	/*float sintheta2 = sin(acos(costheta2));*/
//
//	float rx = i_roughness / i_spreadx;
//	float ry = i_roughness / i_spready;
//
//	float exists, emitspec = 0;
//	color ClnoShadow = 0;
//	color spec = 0;
//
//	illuminance( P, i_N, PI / 2 )
//	{
//		float isKeyLight = 1;
//		
//		if( i_keyLightsOnly != 0 )
//		{
//			lightsource( "iskeylight", isKeyLight );
//		}
//		
//		if( isKeyLight != 0 )
//		{
//			float nonspecular = 0;
//			lightsource( "__nonspecular", nonspecular );
//
//			if( nonspecular<1 && i_N.L>0 )
//			{
//				vector Ln = normalize(L);
//
//				float costheta1 = Ln.i_N;
//				vector V = Ln + i_I;
//
//				float v = V.i_xdir;
//				float u = V.ydir;
//				float w = V.i_N;
//
//				float G = (1 + Ln.i_I);
//				G = clamp( G * G / (costheta1*costheta2), 0, 1);
//
//				float D = stam_anisotropy( u, v, w, rx, ry );
//
//				float factor =  G * D;
//				float HdotI = V.i_I / length(V);
//				HdotI = 1.0 - HdotI;
//				HdotI = HdotI * HdotI * HdotI;
//				factor *= HdotI + (1.0 - HdotI);
//				factor = clamp(factor, 0, 1) * i_fresnel;
//
//				varying color cur_cl;
//				GET_CL(cur_cl);
//				spec += factor * cur_cl * (1-nonspecular);
//			}
//		}
//	}
//	return  spec/4;    
//}

void
computeSurfaceTransparency(
	const eiIndex i_matteOpacityMode,
	const eiScalar i_matteOpacity,
	const color& i_transparency,
	color &o_outTransparency )
{
	if( i_matteOpacityMode == 0 )
	{
		// This is the "Black Hole" Maya setting
		o_outTransparency = 0.0f;
	}
	else if( i_matteOpacityMode == 1 )
	{
		// This is the "Solid Matte" Maya setting
		o_outTransparency = i_matteOpacity;
	}
	else
	{
		// This is the "Opacity Gain" Maya setting (and the default value)
		o_outTransparency = (1.0f - i_transparency) * i_matteOpacity;
	}

	o_outTransparency = 1.0f - o_outTransparency;
}

void computeSurface(
	const color& i_surfaceColor,
	const color& i_transparency,
	const eiIndex i_matteOpacityMode,
	const float i_matteOpacity,
	color &o_outColor,
	color &o_outTransparency
	)
{
	computeSurfaceTransparency(
		i_matteOpacityMode, i_matteOpacity, i_transparency, o_outTransparency );

	o_outColor = i_surfaceColor * (1.0f - o_outTransparency);
	o_outColor = clamp(o_outColor, color(0.0f), color(eiMAX_SCALAR));
}

//float raySpecularDepth()
//{
//	uniform float depth = 0;
//	rayinfo( "speculardepth", depth );
//	return depth;
//}
//
//color getReflection(
//	normal i_N;
//	vector i_I;
//	color i_specularColor;
//	float i_reflectivity;
//	color i_reflectedColor;
//	uniform float i_maxDistance;
//	uniform float i_samples;
//	uniform float i_blur;
//	uniform float i_noiseAmp;
//	uniform float i_noiseFreq;
//	uniform float i_reflectionLimit )
//{
//	extern point P;
//#if defined(USE_AOV_aov_env_reflection) || \
//    defined(USE_AOV_aov_rt_reflection) || \
//    defined(USE_AOV_aov_rt_reflection_alpha) || \
//    defined(USE_AOV_aov_reflection)
//	extern color __transparency;
//#endif
//
//	color ray_coloration = i_specularColor * i_reflectivity;
//	color reflected = i_reflectedColor;
//
//#ifdef USE_AOV_aov_env_reflection
//	extern color aov_env_reflection;
//	aov_env_reflection += __transparency * i_reflectedColor * ray_coloration;
//#endif
//
//	if( ray_coloration != color(0) &&
//	    raySpecularDepth() < i_reflectionLimit )
//	{
//		vector R = reflect( i_I, i_N );
//
//		if( i_noiseAmp != 0 && i_noiseFreq != 0)
//		{
//			point Pobj = transform("object", P);
//			R = mix( R, R * noise( Pobj * i_noiseFreq ), i_noiseAmp );
//		}
//		
//		color trs;
//		color rc = trace(
//				P, R,
//				"subset", "-_3dfm_not_visible_in_reflections",
//				"maxdist", i_maxDistance,
//				"samplecone", i_blur,
//				"samples", i_samples,
//				"transmission", trs );
//
//#ifdef USE_AOV_aov_rt_reflection
//		extern color aov_rt_reflection;
//		aov_rt_reflection += __transparency * rc * ray_coloration;
//#endif
//#ifdef USE_AOV_aov_rt_reflection_alpha
//		extern float aov_rt_reflection_alpha;
//		aov_rt_reflection_alpha += luminance(__transparency * (1 - trs));
//#endif
//
//		reflected *= trs;
//		reflected += rc;
//	}
//
//#ifdef USE_AOV_aov_reflection
//	extern color aov_reflection;
//	aov_reflection += __transparency * reflected * ray_coloration;
//#endif
//
//	return reflected * ray_coloration;
//}
//
//void doRefraction(
//	normal i_N;
//	vector i_I;
//	uniform float i_refractions;
//	float i_refractiveIndex;
//	uniform float i_refractionLimit;
//	float i_lightAbsorbance;
//	float i_shadowAttenuation;
//	output color io_transparency;
//	output color o_refraction )
//{
//	extern point P;
//	uniform string rayType;
//	uniform float isShadowMap;
//
//	if( io_transparency != color(0) )
//	{
//		/* Check for shadows (either raytraced or shadow maps), in which case
//		   we compute a straight opacity instead of tracing refraction rays. */
//	    if( (1 == rayinfo( "type", rayType ) && rayType == "transmission") ||
//		    (1 == attribute( "user:ShadowMapRendering", isShadowMap ) &&
//		     isShadowMap != 0) )
//		{
//			o_refraction = 0;
//			io_transparency *=
//				mix( 1, abs( normalize(i_I) . i_N ), i_shadowAttenuation );
//		}
//		else if( i_refractions != 0 )
//		{
//			color refractionColor = 0;
//
//			if( raySpecularDepth() < i_refractionLimit )
//			{
//				float eta;
//				normal Nf;
//
//				if( i_I . i_N < 0 )
//				{
//					eta = 1.0 / i_refractiveIndex;
//					Nf = i_N;
//				} else {
//					eta = i_refractiveIndex;
//					Nf = -i_N;
//				}
//
//				float Kr = 0;
//				float Kt = 0; 
//				vector reflect;
//				vector refract; 
//				fresnel(normalize(i_I), Nf, eta, Kr, Kt, reflect, refract);
//				Kt = 1 - Kr;
//
//				refractionColor = trace(
//						P, normalize(refract),
//						"subset", "-_3dfm_not_visible_in_refractions" );
//			}
//
//			o_refraction = io_transparency * refractionColor;
//			io_transparency = 0;
//		}
//		else
//		{
//			o_refraction = 0;
//		}
//	}
//	else
//	{
//		o_refraction = 0;
//	}
//}
//
//float computeShadowValue(normal i_N)
//{
//	float shadowValue = 0;
//	varying float totalLightIntensity = 0;
//
//	extern varying point P;
//	illuminance(P)
//	{
//		/* Do this manually instead of specifying i_N, PI/2 to illuminance so
//		   ambient lights are included. */
//		if( L.i_N >= 0 )
//		{
//			float __3dfm_shadowing = 0;
//			color __3dfm_unshadowed_cl = 0;
//
//			lightsource("__3dfm_shadowing", __3dfm_shadowing);
//			lightsource("__3dfm_unshadowed_cl", __3dfm_unshadowed_cl);
//			float unshadowed_intensity = luminance(__3dfm_unshadowed_cl);
//
//			shadowValue += __3dfm_shadowing * unshadowed_intensity;
//			totalLightIntensity += unshadowed_intensity;
//		}
//	}
//
//	shadowValue /= totalLightIntensity;
//  return shadowValue;
//}
//
//void computeShadowPass(normal i_N)
//{
//#ifdef USE_AOV_aov_shadow
//	extern float aov_shadow;
//	aov_shadow = computeShadowValue(i_N);
//#endif
//}
//
//color computeLuminanceDepth()
//{
//	uniform float near_far[2] = {0, 1e3};
//	option( "Clipping", near_far );
//
//	uniform float near = near_far[0];
//	uniform float far = near_far[1];
//	
//	extern varying vector I;
//	float depth = length(I) - near;
//	
//	far -= near;
//	depth = (far - depth) / far;
//
//	return color(depth, depth, depth);
//}
//
//color getPhong(
//	normal i_N; vector i_V; float i_size; 
//	uniform float i_keyLightsOnly, unshadowed)
//{
//	color C = 0;
//	vector R = reflect( -normalize(i_V), normalize(i_N) );
//	extern varying point P;
//	
//	illuminance( P, i_N, PI/2 )
//	{
//		float isKeyLight = 1;
//		
//		if( i_keyLightsOnly != 0 )
//		{
//			lightsource( "iskeylight", isKeyLight );
//		}
//		
//		if( isKeyLight != 0 )
//		{
//			float nonspecular = 0;
//			lightsource( "__nonspecular", nonspecular );
//		
//			if( nonspecular < 1 )
//			{
//				vector Ln = normalize(L);
//				
//				varying color cur_cl;
//				GET_CL(cur_cl);
//				C += cur_cl * pow(max(0.0,R.Ln), i_size) * (1-nonspecular);
//			}
//		}
//	}
//	return C;
//}
//
//color getPhongE(vector i_R; float i_highlight_size, i_roughness;
//	uniform float i_keyLightsOnly, unshadowed)
//{
//	extern point P;
//	varying color C = 0;
//	
//	illuminance( "specular", P, i_R, i_highlight_size * PI/2 )
//	{
//		float isKeyLight = 1;
//		
//		if( i_keyLightsOnly != 0 )
//		{
//			lightsource( "iskeylight", isKeyLight );
//		}
//		
//		if( isKeyLight != 0 )
//		{
//			float nonspecular = 0;
//			lightsource( "__nonspecular", nonspecular );
//		
//			if( nonspecular < 1 )
//			{
//				float cos_angle = normalize(L) . i_R;
//				float angle = acos(cos_angle);
//
//				float spec = pow( cos(angle / i_highlight_size), pow(i_roughness, -2) );
//
//				varying color cur_cl;
//				GET_CL(cur_cl);
//				C += spec * cur_cl * (1-nonspecular);
//			}
//		}
//	}
//	return C;
//}
//
//void do_bump_map(
//	float i_bumpValue;
//	float i_bumpDepth;
//	normal i_normalCamera;
//	output normal o_outNormal )
//{
//	extern vector dPdu, dPdv;
//
//	float depth = abs(i_bumpDepth);
//	float offset = clamp(i_bumpValue * i_bumpDepth, -depth, depth);
//
//	/*
//		These scale factors are a bit experimental. The constant is to roughly
//		match maya's bump mapping. The part about dPdu/dPdv ensures that the
//		bump's scale does not depend on the underlying parametrization of the
//		patch (the use of Du and Dv below introduce that) and that it happens
//		in object space. Note that maya's handling of object space appears to
//		be slightly broken since an enlarged sphere will have the same bump as
//		a sphere with its control points moved outwards by a scale, somehow.
//	*/
//	float uscale = 1.0 / (length(vtransform("object", dPdu)) * 6.0);
//	float vscale = 1.0 / (length(vtransform("object", dPdv)) * 6.0);
//
//	vector gu = vector(1, 0, Du(offset) * uscale);
//	vector gv = vector(0, 1, Dv(offset) * vscale);
//	normal n = normal(gu ^ gv);
//	
//	vector basisz = normalize(i_normalCamera);
//	vector basisx = normalize((basisz ^ dPdu) ^ basisz);
//	vector basisy = normalize((basisz ^ dPdv) ^ basisz);
//
//	o_outNormal = normal(
//		xcomp(n) * basisx + ycomp(n) * basisy + zcomp(n) * basisz);
//
//	o_outNormal = normalize(o_outNormal);
//}

/* Macros to implement a special case for photons in the surface shaders. */

//#define BEGIN_PHOTON_CASE( diffuseColor, specularColor, transparency ) \
//	string rayType; \
//	if( 1 == rayinfo( "type", rayType ) && rayType == "light" ) \
//	{ \
//		string shadingmodel; \
//		if( 1 == attribute( "photon:shadingmodel", shadingmodel ) && \
//		    shadingmodel == "matte" ) \
//		{ \
//			o_outColor = diffuseColor; \
//		} \
//		else \
//		{ \
//			o_outColor = specularColor; \
//		} \
//		o_outTransparency = transparency; \
//	} \
//	else \
//	{ /* This encloses the shader body. */
//
//#define END_PHOTON_CASE } /* This closes the brace above. */

//use reflect(wo,H), where wo=-I, H=N
//// I  - eye to surface point
//// nN - normalized normal at surface point
//vector reflect(const vector& I, const vector& nN)
//{
//	return  I - 2.0f * ((I % nN) * nN);
//}


