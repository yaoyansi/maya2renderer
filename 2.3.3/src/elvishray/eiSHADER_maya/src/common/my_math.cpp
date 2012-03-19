#include "my_math.h"
#include <stdio.h>

//d(clamp(x,LOW,HEIGHT))/dx
float D_clamp(const float x, const float LOW, const float HEIGHT)
{
	if(x<LOW || HEIGHT<x)
		return 0.0f;
	if(LOW<x && x<HEIGHT)
		return 1.0f;
	
	//if(LOW==x || x==HEIGHT){
	//printf("D_clamp(%f,%f,%f) is undefined, return 0.0f;\n", x, LOW,HEIGHT);
	return 0.0f;
	//}
}

//d(abs(x))/dx
float D_abs(const float x)
{
	if(x>0)
		return 1.0f;
	if(x<0)
		return -1.0f;

	//if(x==0.0f){
	//printf("D_abs(0.0) is undefined, return 0.0f;\n");
	return 0.0f;
	//}
}
