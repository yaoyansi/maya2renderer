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

SURFACE(maya_checker)

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
		x = uvCoord().x;
		y = uvCoord().y;
		//2
		//x = fmodf( P().x * uvCoord().x, 1.0f);
		//y = fmodf( P().y * uvCoord().y, 1.0f);

		if ( floor( x * 2 ) == floor( y * 2 ) )
		{
			outColor() = color1();
		}
		else
		{
			outColor() = color2();
		}
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
