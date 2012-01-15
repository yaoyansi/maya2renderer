
#include <eiAPI/ei_shaderx.h>


SURFACE(maya_file)

	PARAM(eiTag, fileTextureName);
	PARAM(scalar, uCoord);
	PARAM(scalar, vCoord);
	PARAM(color, outColor);

	void parameters(int pid)
	{
		DECLARE_TAG(fileTextureName, eiNULL_TAG);
		DECLARE_SCALAR(uCoord, 0.0f);
		DECLARE_SCALAR(vCoord, 0.0f);
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
			outColor() = color_texture(tex, 0, uCoord(), vCoord());
		}
	}

END(maya_file)