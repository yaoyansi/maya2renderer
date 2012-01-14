
#include <eiAPI/ei_shaderx.h>


SURFACE(maya_file)

	PARAM(eiTag, texture);
	PARAM(scalar, u);
	PARAM(scalar, v);
	PARAM(color, result);

	void parameters(int pid)
	{
		DECLARE_TAG(texture, eiNULL_TAG);
		DECLARE_SCALAR(u, 0.0f);
		DECLARE_SCALAR(v, 0.0f);
		DECLARE_COLOR(result, 0.0f, 0.0f, 0.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main()
	{
		eiTag tex = texture();
		
		if (tex != eiNULL_TAG)
		{
			result() = color_texture(tex, 0, u(), v());
		}
	}

END(maya_file)