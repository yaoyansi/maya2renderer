/*
	Copyright (c) 2006 soho vfx inc.
	Copyright (c) 2006 The 3Delight Team.
*/

#ifndef __place2dTexture_h
#define __place2dTexture_h

/*
begin inputs
	init={ss,tt} float2 uvCoord
	float coverageU
	float coverageV
	float mirrorU
	float mirrorV
	float noiseU
	float noiseV
	float offsetU
	float offsetV
	float repeatU
	float repeatV
	float rotateFrame
	float rotateUV
	float stagger
	float translateFrameU
	float translateFrameV
	float wrapU
	float wrapV
end inputs

begin outputs
	float2 outUV
end outputs
*/

#include "utils.h"

void
maya_place2dTexture(
	// Inputs
	//
	float i_uvCoord[2];
	uniform float i_coverageU;
	uniform float i_coverageV;
	uniform float i_mirrorU;
	uniform float i_mirrorV;
	uniform float i_noiseU;
	uniform float i_noiseV;
	float i_offsetU;
	float i_offsetV;
	uniform float i_repeatU;
	uniform float i_repeatV;
	uniform float i_rotateFrame;
	uniform float i_rotateUV;
	uniform float i_stagger;
	uniform float i_translateFrameU;
	uniform float i_translateFrameV;
	uniform float i_wrapU;
	uniform float i_wrapV;
	
	// Outputs
	//
	output float o_outUV[2];
	)
{
	float ss = i_uvCoord[0];
	float tt = i_uvCoord[1];
  
	float outU = ss;
	float outV = tt;
  
	if(i_noiseU > 0.0)
	{
		outU += 1.25 * i_noiseU * (pnoise(point(ss * 18, tt * 18, 0), 
			point(18, 18, 18)) * 2 - 1);
	}
  
	if(i_noiseV > 0.0)
	{
		outV += 1.25 * i_noiseV * (pnoise(point(ss * 18, tt * 18, 1), 
			point(18, 18, 18)) * 2 - 1);
	}
  
	if(i_rotateFrame != 0.0)
	{
		point Q = point(outU, outV, 0.0);
		point P1 = point(0.5, 0.5, 0.0);
		point P2 = point(0.5, 0.5, 1.0);
    
		Q = rotate(Q, radians(i_rotateFrame), P1, P2);
		outU = xcomp(Q);
		outV = ycomp(Q);
	}
  
	outU -= i_translateFrameU;
	outV -= i_translateFrameV;

	if(mod(outU, WRAPMAX) - i_coverageU > EPSILON|| 
	   mod(outV, WRAPMAX) - i_coverageV > EPSILON ||
	   (i_wrapU == 0 && (outU < 0 || (outU * i_repeatU) - i_repeatU > EPSILON)) ||
	   (i_wrapV == 0 && (outV < 0 || (outV * i_repeatV) - i_repeatV > EPSILON)))
	{
		o_outUV[0] = UNDEFINED_UV;
		o_outUV[1] = UNDEFINED_UV;
	}
	else
	{
		if(i_coverageU < 1.0)
		{
			outU = mod(outU, 1);
		}
		
		if(i_coverageV < 1.0)
		{
			outV = mod(outV, 1);
		}
		
		outU = outU * i_repeatU / i_coverageU + i_offsetU;
		outV = outV * i_repeatV / i_coverageV + i_offsetV;	
    
		if(mod(outV, 2) >= 1)
		{
			if(i_stagger != 0)
			{
				outU += 0.5;
			}
      
			if(i_mirrorV != 0)
			{
				float axis = floor(outV) + 0.5;
				outV = axis - (outV - axis);
			}
		}
    
		if(i_mirrorU != 0.0 && mod(outU, 2) >= 1)
		{
			float axis = floor(outU) + 0.5;
			outU = axis - (outU - axis);
		}
    
		if(i_rotateUV != 0.0)
		{
			point Q = point(outU, outV, 0.0);
			point P1 = point(0.5, 0.5, 0.0);
			point P2 = point(0.5, 0.5, 1.0);
      
			Q = rotate(Q, radians(i_rotateUV), P1, P2);
			outU = mod(xcomp(Q), i_repeatU);
			outV = mod(ycomp(Q), i_repeatV);
		}
    
		o_outUV[0] = outU;
		o_outUV[1] = outV;
	}
}

#endif /* __place2dTexture_h */

