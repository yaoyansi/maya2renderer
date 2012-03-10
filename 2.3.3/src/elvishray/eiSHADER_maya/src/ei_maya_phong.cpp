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

SURFACE(maya_phong)
	//Common Material Attributes
	PARAM(color, color_);
	PARAM(color, transparency);
	PARAM(color, ambientColor);
	PARAM(color, incandescence);
	PARAM(color, normalCamera);//bump
	PARAM(scalar,diffuse);//
	PARAM(scalar,translucence);//
	PARAM(scalar,translucenceDepth);//
	PARAM(scalar,translucenceFocus);//
	//Specular Shading
	PARAM(scalar,cosinePower);//
	PARAM(color, specularColor);
	PARAM(scalar,reflectivity);
	PARAM(color, reflectedColor);
	//output
	PARAM(color, outColor);
	PARAM(color, outTransparency);
	//PARAM(eiTag, color_link);
	//PARAM(eiTag, transparency_link);
	//PARAM(eiTag, ambientColor_link);
	//PARAM(eiTag, incandescence_link);
	//PARAM(eiTag, normalCamera_link);
	//PARAM(eiTag, diffuse_link);
	//PARAM(eiTag, translucence_link);
	//PARAM(eiTag, translucenceDepth_link);
	//PARAM(eiTag, translucenceFocus_link);
	//PARAM(eiTag, cosinePower_link);
	//PARAM(eiTag, specularColor_link);
	//PARAM(eiTag, reflectivity_link);
	//PARAM(eiTag, reflectedColor_link);
	//scalar tiling; //for test only.

	void parameters(int pid)
	{
		//Common Material Attributes
		DECLARE_COLOR(	color_,						0.5f, 0.5f, 0.5f); 
		DECLARE_COLOR(	transparency,				0.0f, 0.0f, 0.0f); 
		DECLARE_COLOR(	ambientColor,				0.0f, 0.0f, 0.0f); 
		DECLARE_COLOR(	incandescence,				0.0f, 0.0f, 0.0f); 
		DECLARE_COLOR(	normalCamera,				0.0f, 0.0f, 0.0f); 
		DECLARE_SCALAR(	diffuse,					0.8f);
		DECLARE_SCALAR(	translucence,				0.0f); 
		DECLARE_SCALAR(	translucenceDepth,			0.5f); 
		DECLARE_SCALAR(	translucenceFocus,			0.5f); 
		//Specular Shading
		DECLARE_SCALAR(	cosinePower,				20.0f);
		DECLARE_COLOR(	specularColor,				0.5f, 0.5f, 0.5f);
		DECLARE_SCALAR(	reflectivity,				0.5f);
		DECLARE_COLOR(	reflectedColor,				0.0f, 0.0f, 0.0f);
		//output
		DECLARE_COLOR(	outColor,					0.0f, 0.0f, 0.0f);
		DECLARE_COLOR(	outTransparency,			0.0f, 0.0f, 0.0f);
		//DECLARE_TAG(	color_link,					eiNULL_TAG);
		//DECLARE_TAG(	transparency_link,			eiNULL_TAG);
		//DECLARE_TAG(	ambientColor_link,			eiNULL_TAG);
		//DECLARE_TAG(	incandescence_link,			eiNULL_TAG);
		//DECLARE_TAG(	normalCamera_link,			eiNULL_TAG);
		//DECLARE_TAG(	diffuse_link,				eiNULL_TAG);
		//DECLARE_TAG(	translucence_link,			eiNULL_TAG);
		//DECLARE_TAG(	translucenceDepth_link,		eiNULL_TAG);
		//DECLARE_TAG(	translucenceFocus_link,		eiNULL_TAG);
		//DECLARE_TAG(	cosinePower_link,			eiNULL_TAG);	
		//DECLARE_TAG(	specularColor_link,			eiNULL_TAG);
		//DECLARE_TAG(	reflectivity_link,			eiNULL_TAG);
		//DECLARE_TAG(	reflectedColor_link,		eiNULL_TAG);
	//	tiling = 4.0f;
	}
	void init()	{}
	void exit()	{}
	color specularbrdf(const vector & vL, const normal & vN, const vector & V, scalar roughness)
	{
		vector	H = normalize(vL + V);
		scalar	dotNH = vN % H;
		return pow(max(eiSCALAR_EPS, dotNH), 1.0f / roughness);
	}


	//
	//color sampler2D(const eiTag& tex)
	//{
	//	//const scalar tiling = 4.0f;

	//	scalar s = fmodf(u() * tiling, 1.0f);
	//	scalar t = fmodf(v() * tiling, 1.0f);

	//	scalar dsdx, dsdy, dtdx, dtdy;
	//	Dxy(u, dsdx, dsdy);
	//	Dxy(v, dtdx, dtdy);
	//	dsdx = dsdx * tiling;
	//	dsdy = dsdy * tiling;
	//	dtdx = dtdx * tiling;
	//	dtdy = dtdy * tiling;
	//	
	//	return color_texture(tex, 0, s, t, dsdx, dsdy, dtdx, dtdy, 8.0f);
	//}
	//scalar sampler1D(const eiTag& tex)
	//{
	//	//const scalar tiling = 4.0f;

	//	scalar s = fmodf(u() * tiling, 1.0f);
	//	scalar t = fmodf(v() * tiling, 1.0f);

	//	scalar dsdx, dsdy, dtdx, dtdy;
	//	Dxy(u, dsdx, dsdy);
	//	Dxy(v, dtdx, dtdy);
	//	dsdx = dsdx * tiling;
	//	dsdy = dsdy * tiling;
	//	dtdx = dtdx * tiling;
	//	dtdy = dtdy * tiling;

	//	return scalar_texture(tex, 0, s, t, dsdx, dsdy, dtdx, dtdy, 8.0f);
	//}
	////
	//color get(const color& channel, const eiTag& tex) 
	//{
	//	if( tex != eiNULL_TAG )
	//	{
	//		return sampler2D(tex);
	//	}else{
	//		return channel;
	//	}
	//}
	//scalar get(const scalar& channel, const eiTag& tex)
	//{
	//	if( tex != eiNULL_TAG )
	//	{
	//		return sampler1D(tex);
	//	}else{
	//		return channel;
	//	}
	//}
	//
	//Common Material Attributes
	//color _color()
	//{
	//	return get( color_(), color_link() );
	//}
	//color _transparency()
	//{
	//	return get( transparency(), transparency_link() );
	//}
	//color _ambientColor()
	//{
	//	return get( ambientColor(), ambientColor_link());
	//}
	//color _incandescence()
	//{
	//	return get( incandescence(), incandescence_link());
	//}
	//color _normalCamera()
	//{
	//	return get( normalCamera(), normalCamera_link());
	//}
	//scalar _diffuse()
	//{
	//	return get( diffuse(), diffuse_link());
	//}
	//scalar _translucence()
	//{
	//	return get( translucence(), translucence_link());
	//}
	//scalar _translucenceDepth()
	//{
	//	return get( translucenceDepth(), translucenceDepth_link());
	//}
	//scalar _translucenceFocus()
	//{
	//	return get( translucenceFocus(), translucenceFocus_link());
	//}
	////Specular Shading
	//scalar _cosinePower()
	//{
	//	return get( cosinePower(), cosinePower_link());
	//}
	//color _specularColor()
	//{
	//	return get( specularColor(), specularColor_link());
	//}
	//scalar _reflectivity()
	//{
	//	return get( reflectivity(), reflectivity_link());
	//}
	//color _reflectedColor()
	//{
	//	return get( reflectedColor(), reflectedColor_link());
	//}

	void main(void *arg)
	{
		// cook thee variables here
		color Kd = color(diffuse(), diffuse(), diffuse());
		color  _color         ( color_()         );
		scalar _cosinePower   ( cosinePower()   );
		color  _specularColor ( specularColor() );
		color  _transparency  ( transparency()  );
		//

		normal Nf = faceforward(normalize(N()), I());
		vector V = -normalize(I());



		while (illuminance(P(), Nf, PI / 2.0f))
		{
			color	lastC = 0.0f;
			color	localC = 0.0f;
			int		num_samples = 0;

			while (sample_light())
			{
				localC += Cl() * (
									_color * Kd * (normalize(L()) % Nf) 
									+ _cosinePower * _specularColor * specularbrdf(normalize(L()), Nf, V, 0.1f/*roughness()*/)
					);

				++ num_samples;

				if ((num_samples % 4) == 0)
				{
					color	thisC = localC * (1.0f / (scalar)num_samples);

					if (converged(thisC, lastC)){
						break;
					}
					lastC = thisC;
				}
			}

			localC *= (1.0f / (scalar)num_samples);
			Ci() += localC;
		}

		Ci() += Kd * irradiance();
		if ( len( &_transparency ) > 0.0f )
		{
			Ci() = Ci() * ( 1.0f - _transparency ) + trace_transparent() * _transparency;
		}
		setOutputForMaya();
	}
	void setOutputForMaya()
	{
		outColor() = Ci();
		outTransparency() = Oi();
	}

END(maya_phong)
