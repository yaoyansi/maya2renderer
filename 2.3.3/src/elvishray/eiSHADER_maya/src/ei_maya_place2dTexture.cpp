
#include <eiAPI/ei_shaderx.h>


SURFACE(maya_place2dTexture)

	PARAM(vector, repeatUV);
	PARAM(vector, outUV);

	void parameters(int pid)
	{
		DECLARE_VECTOR(repeatUV, 0.0f, 0.0f, 0.0f);
		DECLARE_VECTOR(outUV,    0.0f, 0.0f, 0.0f); 
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main(void *arg)
	{
		//1
		//outUV().x = fmodf( u() * repeatUV().x, 1.0f );
		//outUV().y = fmodf( v() * repeatUV().y, 1.0f );
		
		//2
		outUV().x = repeatUV().x;
		outUV().y = repeatUV().y;
	}

END(maya_place2dTexture)