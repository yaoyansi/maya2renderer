
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <ri.h>
#include <RslPlugin.h>


#define PI 3.14159265

#ifdef _WIN32
#define MYDLLEXPORT __declspec(dllexport)
#else
#define MYDLLEXPORT
#endif
extern "C" {
	MYDLLEXPORT RtPointer ConvertParameters(RtString paramstr);
	MYDLLEXPORT RtVoid Subdivide(RtPointer data, RtFloat detail);
	MYDLLEXPORT RtVoid Free(RtPointer data);
}

#ifdef __cplusplus
extern "C" {
#endif

	float degToRad(float deg){
		return deg * (PI / 180.0);
	}
	float radToDeg(float rad){
		return rad * 180.0 / PI;
	}

	void convertToSphericalCoordination(
		float x, float y, float z,
		float *r, float *t, float *p)
	{	

		*r = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
		if(x > 0){
			*t = atan((y / x))+PI;
		}else if(x == 0){
			if(y > 0){
				*t = PI /2;
			}else{
				*t = -PI /2;
			}
		}
		else{
			*t = atan((y / x));
		}
		*p = acos((z / *r));
	}

	void convertToXYZ(
		float r, float t, float p,
		float *x, float *y, float *z)
	{
		*x = r * cos(t) * sin(p);
		*y = r * sin(t) * sin(p);
		*z = r * cos(p);
	}


	float floatRand(){
		return (float)rand() / (float)RAND_MAX;
	}

	void sphereRandom(float *x,float *y,float *z){

		// 0 <=- theta <= 2PI
		float theta = floatRand() * (2*PI);

		// -1 <= u <= 1
		float u = (floatRand() * 2) -1.0;

		*x = cos(theta) * sqrt(1.0-(u*u));
		*y = sin(theta) * sqrt(1.0-(u*u));
		*z = u;
	}

	void inSphereRandom(float *x,float *y,float *z, float radius){

		float r[1] = {0},t[1] = {0},p[1] = {0};
		sphereRandom(x,y,z);

		convertToSphericalCoordination(*x,*y,*z,r,t,p);
		*r *= sqrt(floatRand());
		*r *= radius;
		convertToXYZ(*r,*t,*p,x,y,z);
	}


	RtPointer
		ConvertParameters(RtString paramstr)
	{

		const int numOfParams = 10;

		RtFloat *data = (RtFloat*)malloc(sizeof(RtFloat)*numOfParams);

		data[0] = atof(strtok(paramstr," "));
		data[1] = atof(strtok(NULL," "));
		data[2] = atof(strtok(NULL," "));
		data[3] = atof(strtok(NULL," "));
		data[4] = atof(strtok(NULL," "));
		data[5] = atof(strtok(NULL," "));
		data[6] = atof(strtok(NULL," "));
		//CS
		data[7] = atof(strtok(NULL," "));
		data[8] = atof(strtok(NULL," "));
		data[9] = atof(strtok(NULL," "));

		return (RtPointer)data;

	}

	RtVoid
		Subdivide(RtPointer data, RtFloat detail)
	{
		float *params = (float*)data;

		RtFloat multiPointsRadius = params[0];
		RtInt numOfDots = (RtInt)params[1];
		RtInt id = (RtInt)params[2];
		RtFloat dotSize = (RtFloat)params[3];
		float xCenter = (float)params[4];
		float yCenter = (float)params[5];
		float zCenter = (float)params[6];
		//CS
		float r = (float)params[7];
		float g = (float)params[8];
		float b = (float)params[9];

		RtToken P = "P";
		RtToken constantwidth = "constantwidth";
		RtToken CS = "Cs";
		RtToken keys[] = {P , constantwidth, CS};

		RtPoint *p = (RtPoint*) malloc(sizeof(RtPoint)*numOfDots);
		RtColor *cs = (RtColor*) malloc(sizeof(RtColor)*numOfDots);
		srand(id);
		for(int n = 0 ; n < numOfDots ; n += 1){

			inSphereRandom (&(p[n][0]),&(p[n][1]),&(p[n][2]),multiPointsRadius);

			p[n][0] += xCenter;
			p[n][1] += yCenter;
			p[n][2] += zCenter;

			cs[n][0] = r;
			cs[n][1] = g;
			cs[n][2] = b;
		}

		RtFloat constantwidthV[1] = {dotSize};
		RtPointer vals[3] = {(RtPointer)p , (RtPointer)constantwidthV, (RtPointer)cs};

		RiPointsV(numOfDots,3,keys,vals);

		free(p);
		free(cs);

	}
	RtVoid Free(RtPointer data)
	{
		free(data);
	}


#ifdef __cplusplus
	}
#endif

