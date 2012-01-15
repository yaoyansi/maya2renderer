
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
		outU() = fmodf( u() * repeatU(), 1.0f );
		outV() = fmodf( v() * repeatV(), 1.0f );
	}

END(maya_place2dTexture)