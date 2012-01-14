
#include <eiAPI/ei_shaderx.h>


SURFACE(maya_place2dTexture)

	PARAM(scalar, repeatU);
	PARAM(scalar, repeatV);
	PARAM(scalar, outU);
	PARAM(scalar, outV);

	void parameters(int pid)
	{
		DECLARE_SCALAR(repeatU, 0.0f);
		DECLARE_SCALAR(repeatV, 0.0f);
		DECLARE_SCALAR(outU, 0.0f);
		DECLARE_SCALAR(outV, 0.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}

	void main()
	{
		//extern float s, t;
		outU = mod( t * repeatU, 1 );
		outV = mod( s * repeatV, 1 );
	}

END(maya_place2dTexture)