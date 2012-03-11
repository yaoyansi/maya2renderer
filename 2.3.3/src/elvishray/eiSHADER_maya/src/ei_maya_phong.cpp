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
		color Kd = color(diffuse(), diffuse(), diffuse());

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
									color_() * Kd * (normalize(L()) % Nf) 
									+ cosinePower() * specularColor() * specularbrdf(normalize(L()), Nf, V, 0.1f/*roughness()*/)
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
		if ( ! almost_zerov( &transparency(), 0.001f ) )
		{//transparent
			Ci() = Ci() * ( 1.0f - transparency() ) + trace_transparent() * transparency();
		}//else{ opacity }
		setOutputForMaya();
	}
	void setOutputForMaya()
	{
		outColor() = Ci();
		outTransparency() = Oi();
	}

END(maya_phong)
