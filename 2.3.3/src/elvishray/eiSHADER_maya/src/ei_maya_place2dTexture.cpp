
#include <eiAPI/ei_shaderx.h>
#include "common/_3delight/utils.h"

SURFACE(maya_place2dTexture)
	// Inputs
	PARAM(vector, uvCoord);//float2
	PARAM(scalar, coverageU);
	PARAM(scalar, coverageV);
	PARAM(eiBool, mirrorU);
	PARAM(eiBool, mirrorV);
	PARAM(scalar, noiseU);
	PARAM(scalar, noiseV);
	PARAM(scalar, offsetU);
	PARAM(scalar, offsetV);
	PARAM(scalar, repeatU);
	PARAM(scalar, repeatV);
	PARAM(scalar, rotateFrame);//angle(deg)
	PARAM(scalar, rotateUV);//angle(deg)
	PARAM(eiBool, stagger);
	PARAM(scalar, translateFrameU);
	PARAM(scalar, translateFrameV);
	PARAM(eiBool, wrapU);
	PARAM(eiBool, wrapV);
	// Outputs
	PARAM(vector, outUV);//float2

	void parameters(int pid)
	{
		// Inputs
		DECLARE_VECTOR(uvCoord, 0.0f, 0.0f, 0.0f);//float2
		DECLARE_SCALAR(coverageU, 1.0f);
		DECLARE_SCALAR(coverageV, 1.0f);
		DECLARE_BOOL(mirrorU, eiFALSE);
		DECLARE_BOOL(mirrorV, eiFALSE);
		DECLARE_SCALAR(noiseU, 0.0f);
		DECLARE_SCALAR(noiseV, 0.0f);
		DECLARE_SCALAR(offsetU, 0.0f);
		DECLARE_SCALAR(offsetV, 0.0f);
		DECLARE_SCALAR(repeatU, 1.0f);
		DECLARE_SCALAR(repeatV, 1.0f);
		DECLARE_SCALAR(rotateFrame, 0.0f);//angle(deg)
		DECLARE_SCALAR(rotateUV, 0.0f);//angle(deg)
		DECLARE_BOOL(stagger, eiFALSE);
		DECLARE_SCALAR(translateFrameU, 0.0f);
		DECLARE_SCALAR(translateFrameV, 0.0f);
		DECLARE_BOOL(wrapU, eiTRUE);
		DECLARE_BOOL(wrapV, eiTRUE);
		// Outputs
		DECLARE_VECTOR(outUV,    0.0f, 0.0f, -1.0f); //float2
	}

	void init()
	{
	}

	void exit()
	{
	}
	void main(void *arg)
	{
		//main0(arg);
		main1(arg);
	}
	void main0(void *arg)
	{
		outUV().x = fmodf( u() * repeatU(), 1.0f );
		outUV().y = fmodf( v() * repeatV(), 1.0f );
		outUV().y = 1.0f - outUV().y;//adjust v for elvishray
	}
	void main1(void *arg)
	{
		float ss = u();
		float tt = 1.0f - v();//adjust v for elvishray

		float outU = ss;
		float outV = tt;

		if(noiseU() > 0.0f)
		{
			outU += 1.25f * noiseU() * (	pnoise( point(ss * 18.0f, tt * 18.0f, 0.0f), 
													point(18.0f, 18.0f, 18.0f) 
											) 
											* 2.0f - 1.0f
										);
		}

		if(noiseV() > 0.0f)
		{
			outV += 1.25f * noiseV() * (	pnoise(	point(ss * 18.0f, tt * 18.0f, 1.0f), 
													point(18.0f, 18.0f, 18.0f)
											) 
											* 2.0f - 1.0f
										);
		}

		if(rotateFrame() != 0.0f)
		{
			point Q = point(outU, outV, 0.0);
			point P1 = point(0.5, 0.5, 0.0);
			point P2 = point(0.5, 0.5, 1.0);

			matrix rotMatrix = rotate(rotateFrame(), P2-P1 ); //Q = rotate(Q, radians(rotateFrame()), P1, P2 );
			Q = Q * rotMatrix;

			outU = Q.x;
			outV = Q.y;
		}

		outU -= translateFrameU();
		outV -= translateFrameV();

		if( fmodf(outU, WRAPMAX) - coverageU() > eiSCALAR_EPS || 
			fmodf(outV, WRAPMAX) - coverageV() > eiSCALAR_EPS ||
			(wrapU() == eiFALSE && (outU < 0.0f || (outU * repeatU()) - repeatU() > eiSCALAR_EPS)) ||
			(wrapV() == eiFALSE && (outV < 0.0f || (outV * repeatV()) - repeatV() > eiSCALAR_EPS)))
		{
			outUV().x = UNDEFINED_UV;
			outUV().y = UNDEFINED_UV;
		}
		else
		{
			if(coverageU() < 1.0f)
			{
				outU = fmodf(outU, 1.0f);
			}

			if(coverageV() < 1.0f)
			{
				outV = fmodf(outV, 1.0f);
			}

			outU = outU * repeatU() / coverageU() + offsetU();
			outV = outV * repeatV() / coverageV() + offsetV();	

			if(fmodf(outV, 2.0f) >= 1.0f)
			{
				if(stagger() != eiFALSE)
				{
					outU += 0.5f;
				}

				if(mirrorV() != eiFALSE)
				{
					scalar axis = floor(outV) + 0.5f;
					outV = axis - (outV - axis);
				}
			}

			if(mirrorU() != eiFALSE && fmodf(outU, 2.0f) >= 1.0f)
			{
				scalar axis = floor(outU) + 0.5f;
				outU = axis - (outU - axis);
			}

			if(rotateUV() != 0.0f)
			{
				point Q = point(outU, outV, 0.0f);
				point P1 = point(0.5f, 0.5f, 0.0f);
				point P2 = point(0.5f, 0.5f, 1.0f);

				matrix rotMatrix = rotate(rotateFrame(), P2-P1 );//Q = rotate(Q, radians(rotateUV()), P1, P2 ); 
				Q = Q * rotMatrix;

				outU = fmodf(Q.x, repeatU());
				outV = fmodf(Q.y, repeatV());
			}

			outUV().x = outU;
			outUV().y = outV;
		}
	}

END(maya_place2dTexture)