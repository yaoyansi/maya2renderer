/* 
 * Copyright 2010 elvish render Team
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <eiAPI/ei_shaderx.h>
#include "common/_3delight/shading_utils.h"
#include "common/_3delight/utils.h"
#include "common/my_utils.h"

#define TEST_CASE 1

#if TEST_CASE == 0 
//all is black
#elif TEST_CASE == 1
#	define USE_SAMPLE_LIGHT 
#elif TEST_CASE == 2
#	define RESET_OUTER//all is black
#elif TEST_CASE == 3
#	define RESET_OUTER
#	define USE_SAMPLE_LIGHT 
#endif




#define SAMPLE_LIGHT(value, cmd)	\
	while(my_sample_light( value )){\
		cmd;						\
	}my_sample_light_get( value );

#define SAMPLE_LIGHT_2(T, name, default_value, cmd)	\
	T last_##name = default_value;					\
	int num_samples_##name = 0;						\
	const int sample_slot = 4;						\
	while( sample_light() ){						\
		cmd;										\
		++ num_samples_##name;						\
		if ((num_samples_##name % sample_slot) == 0){		\
			const color current =							\
				name * (1.0f / (scalar)num_samples_##name);	\
			if (converged(current, last_##name))	\
				break;								\
			last_##name = current;					\
		}											\
	}												\
	name *= (1.0f / (scalar)num_samples_##name);





SURFACE(maya_phong)
	//Common Material Attributes
	PARAM(color, color_);
	PARAM(color, transparency);
	PARAM(color, ambientColor);
	PARAM(color, incandescence);
	PARAM(normal, normalCamera);//bump
	PARAM(scalar,diffuse);//
	PARAM(scalar,translucence);//
	PARAM(scalar,translucenceDepth);//
	PARAM(scalar,translucenceFocus);//
	//Specular Shading
	PARAM(scalar,cosinePower);//
	PARAM(color, specularColor);
	PARAM(scalar,reflectivity);
	PARAM(color, reflectedColor);
	//Matte Opacity
	PARAM(eiIndex,matteOpacityMode);
	PARAM(scalar, matteOpacity);
	//Raytrace Options
	PARAM(eiIndex,reflectionLimit);
	//output
	PARAM(color, outColor);
	PARAM(color, outTransparency);

	protected:
		color last_value;
		int num_samples;
	public:

	void parameters(int pid)
	{
		//Common Material Attributes
		DECLARE_COLOR(	color_,						0.5f, 0.5f, 0.5f); 
		DECLARE_COLOR(	transparency,				0.0f, 0.0f, 0.0f); 
		DECLARE_COLOR(	ambientColor,				0.0f, 0.0f, 0.0f); 
		DECLARE_COLOR(	incandescence,				0.0f, 0.0f, 0.0f); 
		DECLARE_NORMAL(	normalCamera,				0.0f, 0.0f, 0.0f); 
		DECLARE_SCALAR(	diffuse,					0.8f);
		DECLARE_SCALAR(	translucence,				0.0f); 
		DECLARE_SCALAR(	translucenceDepth,			0.5f); 
		DECLARE_SCALAR(	translucenceFocus,			0.5f); 
		//Specular Shading
		DECLARE_SCALAR(	cosinePower,				20.0f);
		DECLARE_COLOR(	specularColor,				0.5f, 0.5f, 0.5f);
		DECLARE_SCALAR(	reflectivity,				0.5f);
		DECLARE_COLOR(	reflectedColor,				0.0f, 0.0f, 0.0f);
		//Matte Opacity
		DECLARE_INDEX( matteOpacityMode,			2);
		DECLARE_SCALAR(	matteOpacity,				1.0f);
		//Raytrace Options
		DECLARE_INDEX( reflectionLimit,				1);
		//output
		DECLARE_COLOR(	outColor,					0.0f, 0.0f, 0.0f);
		DECLARE_COLOR(	outTransparency,			0.0f, 0.0f, 0.0f);

		//
		reset_sample_light();
	}
	void reset_sample_light()
	{
		last_value = 0.0f;
		num_samples = 0;
	}
	void init()	{}
	void exit()	{}
	color specularbrdf(const vector & vL, const normal & vN, const vector & V, scalar roughness)
	{
		vector	H = normalize(vL + V);
		scalar	dotNH = vN % H;
		return pow(max(eiSCALAR_EPS, dotNH), 1.0f / roughness);
	}

	void main(void *arg)
	{
		//main1(arg);
		//main1_2(arg);
		main1_3(arg);
		//main2(arg);

	}
	eiBool my_sample_light(const color& value)
	{
		eiBool ret = sample_light();

		++ num_samples;
		if ((num_samples % 4) == 0)
		{
			color	this_value = value * (1.0f / (scalar)num_samples);

			if (converged(this_value, last_value)){
				return eiFALSE;
			}
			last_value = this_value;
		}
		return ret;
	}
	void my_sample_light_get(color& value)
	{
		value *= (1.0f / (scalar)num_samples);
	}
	void main1(void *arg)
	{
		color Kd = color(diffuse(), diffuse(), diffuse());

		normal Nf = faceforward(normalize(N()), I());
		vector V = -normalize(I());

		while (illuminance(P(), Nf, PI / 2.0f))
		{
			color	C = 0.0f;
			color	last = 0.0f;
			int		num_samples = 0;

			while (sample_light())
			{
				C += Cl() * (
					color_() * Kd * (normalize(L()) % Nf) 
					+ cosinePower() * specularColor() * specularbrdf(normalize(L()), Nf, V, 0.1f/*roughness()*/)
					);

				++ num_samples;

				if ((num_samples % 4) == 0)
				{
					color	current = C * (1.0f / (scalar)num_samples);

					if (converged(current, last)){
						break;
					}
					last = current;
				}
			}

			C *= (1.0f / (scalar)num_samples);
			Ci() += C;
		}

		Ci() += Kd * irradiance();
		if ( ! less_than( &transparency(), LIQ_SCALAR_ALMOST_ZERO ) )
		{//transparent
			Ci() = Ci() * ( 1.0f - transparency() ) + trace_transparent() * transparency();
		}//else{ opacity }
		setOutputForMaya();
	}
	void main1_2(void *arg)
	{
		color Kd = color(diffuse(), diffuse(), diffuse());

		normal Nf = faceforward(normalize(N()), I());
		vector V = -normalize(I());

		while (illuminance(P(), Nf, PI / 2.0f))
		{
			reset_sample_light();
			color	localC = 0.0f;

			SAMPLE_LIGHT( localC,
 				localC += Cl() * (
 					color_() * Kd * (normalize(L()) % Nf) 
 					+ cosinePower() * specularColor() * specularbrdf(normalize(L()), Nf, V, 0.1f/*roughness()*/)
 					);
			);

			Ci() += localC;
		}

		Ci() += Kd * irradiance();
		if ( ! less_than( &transparency(), LIQ_SCALAR_ALMOST_ZERO ) )
		{//transparent
			Ci() = Ci() * ( 1.0f - transparency() ) + trace_transparent() * transparency();
		}//else{ opacity }
		setOutputForMaya();
	}
	void main1_3(void *arg)
	{
		color Kd = color(diffuse(), diffuse(), diffuse());

		normal Nf = faceforward(normalize(N()), I());
		vector V = -normalize(I());

		while (illuminance(P(), Nf, PI / 2.0f))
		{
			color C = 0.0f;
			SAMPLE_LIGHT_2(color, C, 0.0f,
				C += Cl() * (
					color_() * Kd * (normalize(L()) % Nf) 
					+ cosinePower() * specularColor() * specularbrdf(normalize(L()), Nf, V, 0.1f/*roughness()*/)
					)
				);

			Ci() += C;
		}

		Ci() += Kd * irradiance();
		if ( ! less_than( &transparency(), LIQ_SCALAR_ALMOST_ZERO ) )
		{//transparent
			Ci() = Ci() * ( 1.0f - transparency() ) + trace_transparent() * transparency();
		}//else{ opacity }
		setOutputForMaya();
	}
	//////////////////////////////////////////////////////////////////////////
	normal ShadingNormal(const normal& i_N)
	{
		normal Nf = i_N;

		//const int sides = 2;
		if( true/*sides == 2*/ )
		{
			Nf = faceforward(Nf, I());
		}
		return Nf;
	}
	color getDiffuse(
		const normal& i_N,
		const eiBool keyLightsOnly,
		const eiBool unshadowed )
	{
		eiBool isKeyLight = eiTRUE;
#ifdef RESET_OUTER
		reset_sample_light();
#endif
		color C = 0;

		while ( illuminance( P(), i_N, PI/2.0f ) )
		{

			//if( keyLightsOnly != eiFALSE )
			//{
			//	lightsource( "iskeylight", isKeyLight );
			//}

			if( isKeyLight != eiFALSE )
			{
				float nondiffuse = 0.0f;
				//lightsource( "__nondiffuse", nondiffuse );

				if( nondiffuse < 1.0f )
				{
#ifndef RESET_OUTER
					reset_sample_light();
#endif
#ifdef USE_SAMPLE_LIGHT
					SAMPLE_LIGHT( C,
						C += Cl() * (normalize(L()) % i_N) * (1.0f-nondiffuse);
					);
#else
						C += Cl() * (normalize(L()) % i_N) * (1.0f-nondiffuse);
#endif
				}
			}
		}

		return C;
	}


	color getPhong(
		const normal& i_N, const vector& i_V, const float cosinePower, 
		const eiBool i_keyLightsOnly, const eiBool unshadowed)
	{
#ifdef RESET_OUTER
		reset_sample_light();
#endif
		color C = 0;
		vector R = reflect( -normalize(i_V), normalize(i_N) );

		while( illuminance( P(), i_N, PI/2.0f ) )
		{
			float isKeyLight = 1;

			//if( i_keyLightsOnly != 0 )
			//{
			//	lightsource( "iskeylight", isKeyLight );
			//}

			if( isKeyLight != 0 )
			{
				const float nonspecular = 0.0f;
				//lightsource( "__nonspecular", nonspecular );

				if( nonspecular < 1 )
				{
#ifndef RESET_OUTER
					reset_sample_light();
#endif
#ifdef USE_SAMPLE_LIGHT
					SAMPLE_LIGHT(C,
						vector Ln = normalize( L() );
						C += Cl() * pow( max<float>(0.0f, R%Ln), cosinePower) * (1.0f-nonspecular);
					);
#else
					vector Ln = normalize( L() );
					C += Cl() * pow( max<float>(0.0f, R%Ln), cosinePower) * (1.0f-nonspecular);
#endif
				}
			}
		}
		return C;
	}
	color getPhong2(
		const vector& i_N, const vector& i_V, const float cosinePower, 
		const eiBool i_keyLightsOnly, const eiBool unshadowed)
	{
#ifdef RESET_OUTER
		reset_sample_light();
#endif
		color C = 0;
		vector R = reflect( -normalize(i_V), normalize(i_N) );
		vector	H = normalize(normalize(L()) + i_V);

		while( illuminance( P(), i_N, PI/2.0f ) )
		{
			float isKeyLight = 1;

			//if( i_keyLightsOnly != 0 )
			//{
			//	lightsource( "iskeylight", isKeyLight );
			//}

			if( isKeyLight != 0 )
			{
				const float nonspecular = 0.0f;
				//lightsource( "__nonspecular", nonspecular );

				if( nonspecular < 1 )
				{
#ifndef RESET_OUTER
					reset_sample_light();
#endif
					vector Ln = normalize(L());
#ifdef USE_SAMPLE_LIGHT
					//SAMPLE_LIGHT(C,
						C += Cl()  * pow( max<float>(0.0f,  i_N%H /* R%Ln */ ), cosinePower) * (1.0f-nonspecular);
					//);
#else
						C += Cl()  * pow( max<float>(0.0f,  i_N%H /* R%Ln */ ), cosinePower) * (1.0f-nonspecular);
#endif
				}
			}
		}
		return C;
	}
	color getTranslucence(const normal& i_N, 
		const float i_translucence,
		const float i_translucenceDepth,
		const float i_translucenceFocus)
	{
		/*
		A translucence focus of 1 leads to a division by zero and an effective
		focus of 0. Clamping it like this yields about the same result as maya.
		*/
		float focus = min( i_translucenceFocus, 0.99999f );

#ifdef RESET_OUTER
		reset_sample_light();
#endif
		color C = 0.0f;

		if( i_translucence > 0.0f )
		{
			while( illuminance( P() ) )
			{
				float nondiffuse = 0.0f;
				//lightsource( "__nondiffuse", nondiffuse );

				if( nondiffuse < 1.0f )
				{
#ifndef RESET_OUTER
					reset_sample_light();
#endif
#ifdef USE_SAMPLE_LIGHT
					SAMPLE_LIGHT( C,
 						float costheta = normalize(L()) % normalize(I());
 						float a = (1.0f + costheta) * 0.5f;
 						float trs = pow( pow(a, focus), 1.0f/(1.0f-focus) );
 						C += Cl() * trs * (1.0f-nondiffuse);
					);
#else
						float costheta = normalize(L()) % normalize(I());
						float a = (1.0f + costheta) * 0.5f;
						float trs = pow( pow(a, focus), 1.0f/(1.0f-focus) );
						C += Cl() * trs * (1.0f-nondiffuse);
#endif
				}
			}
		}

		return C * i_translucence;
	}

	color getReflection(
		const normal& i_N,
		const vector& i_I,
		const color& i_specularColor,
		const float i_reflectivity,
		const color& i_reflectedColor,
		//const float i_maxDistance, const float i_samples, const float i_blur, const float i_noiseAmp, const float i_noiseFreq,
		const eiIndex i_reflectionLimit )
	{
		color ray_coloration = i_specularColor * i_reflectivity;
		color reflected = i_reflectedColor;

		if( /*ray_coloration != color(0)*/!less_than(&ray_coloration, LIQ_SCALAR_ALMOST_ZERO) &&
			/*raySpecularDepth() < i_reflectionLimit*/eiTRUE )
		{
			vector R = reflect( i_I, i_N );

			//if( i_noiseAmp != 0 && i_noiseFreq != 0)
			//{
			//	point Pobj = transform("object", P);
			//	R = mix( R, R * noise( Pobj * i_noiseFreq ), i_noiseAmp );
			//}
			//color rc = trace_probe(P(), R,i_maxDistance);
			color rc = trace_reflection(R);
			color trs = trace_transmission(R);

			reflected *= trs;
			reflected += rc;
		}
		return reflected * ray_coloration;
	}
	void main2(void *arg)
	{
		color Kd = color(diffuse(), diffuse(), diffuse());

		vector In = normalize( I() );
		normal Nn = normalize( normalCamera() );
		normal Nf = ShadingNormal(Nn);
		
		vector V = -In;



		color Cdiffuse = diffuse() * getDiffuse(Nf, eiFALSE, eiFALSE);
		color Cambient = ambientColor() + getAmbient(Nf);
		//color Cspecular = specularColor() * getPhong (Nf, V, cosinePower(), eiFALSE, eiFALSE);
		color Cspecular   = specularColor() * getPhong2(Nf, V, cosinePower(), eiFALSE, eiFALSE);
		
		color Ctransl = getTranslucence(Nf, translucence(), translucenceDepth(), translucenceFocus());
 		color Creflect = getReflection(
 			Nf, In, specularColor(), reflectivity(), reflectedColor(),
 			//i_reflectionMaxDistance, i_reflectionSamples, i_reflectionBlur, i_reflectionNoiseAmplitude, i_reflectionNoiseFrequency,
 			reflectionLimit() );

		//outColor() = color_()  * Ci();
		Ci() = color_();
		Oi() = transparency();	
		computeSurface(
			Ci(),//outColor(),
			Oi(),//transparency(),
			matteOpacityMode(),
			matteOpacity(),
			Ci(),//outColor(),
			Oi()//outTransparency()
		);


		color refraction;
		//doRefraction(
		//	Nn(),
		//	I(),
		//	refractions,
		//	refractiveIndex,
		//	refractionLimit,
		//	lightAbsorbance,
		//	shadowAttenuation,
		//	outTransparency(),
		//	refraction );

		//Ci() += Kd * irradiance();
		Ci() *= (Cdiffuse + Cambient + Ctransl);
		Ci() += Creflect +  Cspecular + incandescence() + refraction;

		if ( ! less_than( &transparency(), LIQ_SCALAR_ALMOST_ZERO ) )
		{//transparent
			Ci() = Ci() * ( 1.0f - transparency() ) + trace_transparent() * transparency();
		}//else{ opacity }

		//computeShadowPass(Nf);

		setOutputForMaya();
	}
	void setOutputForMaya()
	{
		outColor() = Ci();
		outTransparency() = Oi();
	}

END(maya_phong)
