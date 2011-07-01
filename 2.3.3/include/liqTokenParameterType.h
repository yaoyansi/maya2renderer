#ifndef _TOKEN_PARAMETER_TYPE_
#define _TOKEN_PARAMETER_TYPE_

// token/pointer pairs structure

enum ParameterType 
{
	rFloat  = 0,
	rPoint  = 1,
	rVector = 2,
	rNormal = 3,
	rColor  = 4,
	rString = 5,
	rHpoint = 6,
	rMatrix = 7,
	rShader = 8
};

enum DetailType 
{
	rUndefined    = -1,
	rUniform      =  0,
	rVarying      =  1,
	rVertex       =  2,
	rConstant	    =  3,
	rFaceVarying  =  4,
	rFaceVertex   =  5
};

#endif/_TOKEN_PARAMETER_TYPE_