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

SURFACE(maya_mib_amb_occlusion)
	//input
	PARAM(eiIndex,	samples);
	PARAM(color,	bright);
	PARAM(color,	dark);
	PARAM(scalar,	spread);
	PARAM(scalar,	max_distance);
	PARAM(eiBool,	reflective);
	//output
	PARAM(color,	outValue);

	void parameters(int pid)
	{
		//input
		DECLARE_INDEX(	samples,			16); 
		DECLARE_COLOR(	bright,				1.0f, 1.0f, 1.0f); 
		DECLARE_COLOR(	dark,				0.0f, 0.0f, 0.0f); 
		DECLARE_SCALAR(	spread,				0.8f); 
		DECLARE_SCALAR(	max_distance,		0.0f);
		DECLARE_BOOL(	reflective,			eiFALSE); 
		//output
		DECLARE_COLOR(	outValue,			0.0f, 0.0f, 0.0f);
	}
	void init()	{}
	void exit()	{}

	scalar occlusion(const point& p, const normal& N,
		const eiIndex samples, 
		const scalar max_distance,
		const scalar spread)
	{
		uint num_rays = max<eiIndex>(samples, 1);
		int num_hit = 0;
		geoscalar u[2];
		uint count = 0;

		while (sample(u, &count, 2, &num_rays))
		{
			vector dir = sample_cosine_hemisphere(point(0.0f), N, 1.0f, (scalar)u[0], (scalar)u[1]);
			dir = normalize((1.0f - spread) * N + spread * dir);

			if ( trace_probe(p, dir, max_distance ) )
			{
				++ num_hit;
			}
		}

		return (scalar)num_hit / (scalar)num_rays;
	}

	void main_er(void *arg)
	{
		if(max_distance() < eiSCALAR_EPS)//If it is zero, the entire scene is sampled
			max_distance() = eiMAX_SCALAR;

		normal Nf = faceforward(normalize(N()), I());

		uint num_rays = max<int>(samples(), 1);
		int num_misses = 0;
		geoscalar u[2];
		uint count = 0;

		while (sample(u, &count, 2, &num_rays))
		{
			vector dir = sample_cosine_hemisphere(point(0.0f), Nf, 1.0f, (scalar)u[0], (scalar)u[1]);
			if (!trace_probe(P(), dir, max_distance()))
			{
				++ num_misses;
			}
		}

		outValue() = color( (scalar)num_misses / (scalar)num_rays );
		
		//
		Ci() = outValue();
		Oi() = color(1.0f);

	}
	void main_3delight(void *arg)
	{	
		if(max_distance() < eiSCALAR_EPS)//If it is zero, the entire scene is sampled
			max_distance() = eiMAX_SCALAR;

		normal Nf = faceforward(normalize(N()), I());
		normal Nn = normalize(Nf);

		if(reflective() != eiFALSE)
			Nn = reflect( I(), Nn );

		const scalar occ = 1.0f - occlusion(P(), Nn, 
									samples(),
									max_distance(),
									spread()
								);

		outValue() = mix( dark(), bright(), occ );
		//
		Ci() = outValue();
		Oi() = color(1.0f);
	}

	void main(void *arg)
	{
		//main_er(arg);
		main_3delight(arg);
	}

END(maya_mib_amb_occlusion)
