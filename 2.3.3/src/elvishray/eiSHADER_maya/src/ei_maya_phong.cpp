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
	PARAM(eiTag, color_link);
	PARAM(color, transparency);
	PARAM(eiTag, transparency_link);
	PARAM(color, ambientColor);
	PARAM(eiTag, ambientColor_link);
	PARAM(color, incandescence);
	PARAM(eiTag, incandescence_link);
	PARAM(color, normalCamera);//bump
	PARAM(eiTag, normalCamera_link);
	PARAM(scalar,diffuse);//
	PARAM(eiTag, diffuse_link);
	PARAM(scalar,translucence);//
	PARAM(eiTag, translucence_link);
	PARAM(scalar,translucenceDepth);//
	PARAM(eiTag, translucenceDepth_link);
	PARAM(scalar,translucenceFocus);//
	PARAM(eiTag, translucenceFocus_link);
	//Specular Shading
	PARAM(scalar,cosinePower);//
	PARAM(eiTag, cosinePower_link);
	PARAM(color, specularColor);
	PARAM(eiTag, specularColor_link);
	PARAM(scalar,reflectivity);
	PARAM(eiTag, reflectivity_link);
	PARAM(color, reflectedColor);
	PARAM(eiTag, reflectedColor_link);
	//output
	PARAM(color, outColor);
	PARAM(color, outTransparency);

	void parameters(int pid)
	{
		//Common Material Attributes
		DECLARE_COLOR(	color_,						0.5f, 0.5f, 0.5f); 
		DECLARE_TAG(	color_link,					eiNULL_TAG);
		DECLARE_COLOR(	transparency,				0.0f, 0.0f, 0.0f); 
		DECLARE_TAG(	transparency_link,			eiNULL_TAG);
		DECLARE_COLOR(	ambientColor,				0.0f, 0.0f, 0.0f); 
		DECLARE_TAG(	ambientColor_link,			eiNULL_TAG);
		DECLARE_COLOR(	incandescence,				0.0f, 0.0f, 0.0f); 
		DECLARE_TAG(	incandescence_link,			eiNULL_TAG);
		DECLARE_COLOR(	normalCamera,				0.0f, 0.0f, 0.0f); 
		DECLARE_TAG(	normalCamera_link,			eiNULL_TAG);
		DECLARE_SCALAR(	diffuse,					0.8f);
		DECLARE_TAG(	diffuse_link,				eiNULL_TAG);
		DECLARE_SCALAR(	translucence,				0.0f); 
		DECLARE_TAG(	translucence_link,			eiNULL_TAG);
		DECLARE_SCALAR(	translucenceDepth,			0.5f); 
		DECLARE_TAG(	translucenceDepth_link,		eiNULL_TAG);
		DECLARE_SCALAR(	translucenceFocus,			0.5f); 
		DECLARE_TAG(	translucenceFocus_link,		eiNULL_TAG);
		//Specular Shading
		DECLARE_SCALAR(	cosinePower,				20.0f);
		DECLARE_TAG(	cosinePower_link,			eiNULL_TAG);
		DECLARE_COLOR(	specularColor,				0.5f, 0.5f, 0.5f);
		DECLARE_TAG(	specularColor_link,			eiNULL_TAG);
		DECLARE_SCALAR(	reflectivity,				0.5f);
		DECLARE_TAG(	reflectivity_link,			eiNULL_TAG);
		DECLARE_COLOR(	reflectedColor,				0.0f, 0.0f, 0.0f);
		DECLARE_TAG(	reflectedColor_link,		eiNULL_TAG);
		//output
		DECLARE_COLOR(	outColor,					0.0f, 0.0f, 0.0f);
		DECLARE_COLOR(	outTransparency,			0.0f, 0.0f, 0.0f);
	}

	color specularbrdf(const vector & vL, const normal & vN, const vector & V, scalar roughness)
	{
		//vector	H = normalize(vL + V);
		//scalar	dotNH = vN % H;
		//return pow(max(eiSCALAR_EPS, dotNH), 1.0f / roughness);
		return color(0.0f, 1.0f, 0.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		normal Nf = faceforward(normalize(N()), I());
		vector V = -normalize(I());

		Ci() = color(0.0f, 1.0f, 0.0f);
		Oi() = color(1.0f);

		outColor() = Ci();
		outTransparency() = Oi();
	}

END(maya_phong)
