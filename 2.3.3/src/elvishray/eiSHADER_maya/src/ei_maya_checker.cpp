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
#include "common/_3delight/utils.h"

SURFACE(maya_checker)
	// Inputs:
	PARAM(scalar, alphaGain);
	PARAM(eiBool, alphaIsLuminance);
	PARAM(scalar, alphaOffset);
	PARAM(color,  color1);
	PARAM(color,  color2);
	PARAM(color,  colorGain);
	PARAM(color,  colorOffset);
	PARAM(scalar, contrast);
	PARAM(color,  defaultColor);
	PARAM(scalar, filter);
	PARAM(scalar, filterOffset);
	PARAM(eiBool, invert);
	PARAM(vector, uvCoord);//only uvCoord[0],uvCoord[1] are used.
	// Outputs:
	PARAM(scalar, outAlpha);
	PARAM(color,  outColor);

	void parameters(int pid)
	{
 		// Inputs:
 		DECLARE_SCALAR(alphaGain,		1.0f);
 		DECLARE_BOOL(alphaIsLuminance,	eiFALSE);
 		DECLARE_SCALAR(alphaOffset,		0.0f);
 		DECLARE_COLOR(color1,			1.0f, 1.0f, 1.0f);
 		DECLARE_COLOR(color2,			0.0f, 0.0f, 0.0f);
 		DECLARE_COLOR(colorGain,		1.0f, 1.0f, 1.0f);
 		DECLARE_COLOR(colorOffset,		0.0f, 0.0f, 0.0f);
 		DECLARE_SCALAR(contrast,		1.0f);
 		DECLARE_COLOR(defaultColor,		0.5, 0.5f, 0.5f);
 		DECLARE_SCALAR(filter,			1.0f);
 		DECLARE_SCALAR(filterOffset,	0.0f);
 		DECLARE_BOOL(invert,			eiFALSE);
 		DECLARE_VECTOR(uvCoord,			0.0f, 0.0f, 0.0f);
 		// Outputs:
 		DECLARE_SCALAR(outAlpha,		0.5f);
 		DECLARE_COLOR(outColor,			0.5f, 0.5f, 0.5f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		scalar alpha = 0.0f;

		if(ISUVDEFINED(uvCoord().x, uvCoord().y))
		{
			uvCoord().x = fmodf(uvCoord().x, WRAPMAX);
			uvCoord().y = fmodf(uvCoord().y, WRAPMAX);

			/* compute 'ss' and 'tt' filter widths */
			vector dXdu, dXdv, dYdu, dYdv;
			float dss = abs(Du(ss) * du) + abs(Dv(ss) * dv);
			float dtt = abs(Du(tt) * du) + abs(Dv(tt) * dv);


			/* Add in "Effects" filter values. We multiplie the i_filterOffset
			variable by 2 to match Maya's look */ 
			dss = dss * filter() + filterOffset()*2.0f; 
			dtt = dtt * filter() + filterOffset()*2.0f; 

			/* compute separation: 0 for half the squares, 1 for the others. */
			float f = 0.5f - 2.0f *
				(filteredpulsetrain(0.5f, 1.0f, ss, dss) - 0.5f) *
				(filteredpulsetrain(0.5f, 1.0f, tt, dtt) - 0.5f);

			/* contrast interpolates the separation from 0.5 to its normal value. */
			f = 0.5f + (f - 0.5f) * contrast();

			/* Compute final values. */
			alpha = 1.0f - f;
			Ci() = color1() + (color2() - color1()) * f;

			colorBalance(Ci(), 
				alpha,
				alphaIsLuminance(),
				alphaGain(),
				alphaOffset(),
				colorGain(),
				colorOffset(),
				invert() );
		}
		else
		{
			Ci() = defaultColor();
			alpha = luminance( defaultColor() );
		}

		// set output
		outColor() = Ci();
		outAlpha() = alpha;
	}


END(maya_checker)

SURFACE(maya_checker_uv)

	PARAM(color, color1);
	PARAM(color, color2);
	PARAM(vector,uvCoord);
	PARAM(color, outColor);

	void parameters(int pid)
	{
		DECLARE_COLOR(color1, 0.0f, 0.0f, 0.0f);
		DECLARE_COLOR(color2, 1.0f, 1.0f, 1.0f);
		DECLARE_VECTOR(uvCoord, 2.0f, 2.0f, 0.0f);
		DECLARE_COLOR(outColor, 0.0f, 0.0f, 0.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		scalar	x, y;

		//1
		//x = uvCoord().x;
		//y = uvCoord().y;
		//2
		//x = fmodf( u() * uvCoord().x, 1.0f);
		//y = fmodf( v() * uvCoord().y, 1.0f);
		//3
		x =  u() * uvCoord().x;
		y =  v() * uvCoord().y;

		//if ( floor( x * 2 ) == floor( y * 2 ) )
		if ((((eiInt)x + (eiInt)y) % 2) == 0)
		{
			outColor() = color1();
		}
		else
		{
			outColor() = color2();
		}
	}

END(maya_checker_uv)

SURFACE(maya_simple_texture)

	PARAM(eiTag, texture);
	PARAM(color, outColor);

	void parameters(int pid)
	{
		DECLARE_TAG(texture, eiNULL_TAG);
		DECLARE_COLOR(outColor, 0.0f, 0.0f, 0.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		outColor() = color(0.0f, 0.0f, 0.0f);

		eiTag tex = texture();

		if (tex != eiNULL_TAG)
		{
			outColor() = color_texture(tex, 0, get_state()->bary.x, get_state()->bary.y);
		}
	}

END(maya_simple_texture)
