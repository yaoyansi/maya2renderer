
#include <eiAPI/ei_shaderx.h>


SURFACE(maya_file)

	PARAM(eiTag, fileTextureName);
	PARAM(vector, uvCoord);
	PARAM(color, outColor);

	void parameters(int pid)
	{
		DECLARE_TAG(fileTextureName, eiNULL_TAG);
		DECLARE_VECTOR(uvCoord, 0.0f, 0.0f, 0.0f);
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
		eiTag tex = fileTextureName();
		
		if (tex != eiNULL_TAG)
		{
			outColor() = color_texture(tex, 0, uvCoord().x, uvCoord().y);
			//outColor() = color_texture(tex, 0, get_state()->bary.x, get_state()->bary.y);
			//outColor() = color_texture(tex, 0, u(), v());
		}
	}

END(maya_file)