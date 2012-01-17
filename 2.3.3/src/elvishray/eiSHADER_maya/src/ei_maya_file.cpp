
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

	void main()
	{
		eiTag tex = fileTextureName();
		
		if (tex != eiNULL_TAG)
		{
			outColor() = color_texture(tex, 0, uvCoord().x, uvCoord().y);
		}
	}

END(maya_file)