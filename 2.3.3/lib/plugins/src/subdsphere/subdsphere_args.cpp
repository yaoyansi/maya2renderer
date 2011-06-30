#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <float.h>
#include <stdio.h>
#include <cassert>
#include <stdarg.h>
#include <string>
#include "ri.h"

using namespace std;

#pragma comment(lib, "E:/dev/tools/pixar/renderman/13.5/lib/prman.lib")

//
//
FILE *flog = NULL;
FILE* init_log(const char* filename)
{
	if( flog )
		return flog;

	if( flog = fopen(filename,"a") )
	{
	}
	else{
		puts("打开文件成败"); 
	}
	return  flog;
}
void close_log()
{
	fclose(flog);
	flog = NULL;
}

#define _rmlog(fmt, ...) fprintf(flog, fmt, ##__VA_ARGS__)

//--------------------------------------------------------------------------------
struct spheredata {
	float radius;
	float zmin, zmax;
	float thetamin, thetamax;
};

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))



//--------------------------------------------------------------------------------
static RtVoid boundRevolve(RtBound b, float rmin, float rmax,
						   float thetamin, float thetamax)
{
	/*
	* Cache commonly used sines and cosines.
	*/
	float ctm = cosf(thetamin);
	float stm = sinf(thetamin);
	float ctx = cosf(thetamax);
	float stx = sinf(thetamax);

	/*
	* Compute x bounds
	*/
	float atm = fabsf(thetamin);
	float atx = fabsf(thetamax);
	float m = min(ctx, ctm);            /* Consider theta with minimum x */
	if (atx > M_PI/2 && atm < 3*M_PI/2) {
		b[0] = -rmax;                   /* Best when patch crosses x-axis */
		if (atx < M_PI || atm > M_PI)
			b[0] *= -m;                 /* Doesn't cross, scale by cosine */
	}
	else                                /* xmin > 0: use rmin */
		b[0] = rmin * m;                /* Scale by cosine */

	m = max(ctx, ctm);                  /* Consider theta with maximum x */
	if (atm < M_PI/2 || atx > 3*M_PI/2)     /* xmax > 0: use rmax */
		b[1] = rmax * m;                /* Can't cross x-axis, just meet it */
	else                                /* xmax < 0: use rmin */
		b[1] = rmin * m;                /* Scale by cosine */

	/*
	* Compute y bound
	*/
	atm = fabsf(M_PI/2 - thetamin);
	atx = fabsf(M_PI/2 - thetamax);
	m = min(stx, stm);                  /* Consider theta with minimum y */
	if (atx > M_PI/2 && atm < 3*M_PI/2) {
		b[2] = -rmax;                   /* Best when patch crosses y-axis */
		if (atx < M_PI || atm > M_PI)
			b[2] *= -m;                 /* Doesn't cross, scale by sine */
	}
	else                                /* ymin > 0: use rmin */
		b[2] = rmin * m;                /* Scale by sine */

	atm = fabsf(M_PI/2 + thetamin);
	atx = fabsf(M_PI/2 + thetamax);
	m = max(stx, stm);                  /* Consider theta with maximum y */
	if (atx > M_PI/2 && atm < 3*M_PI/2) {
		b[3] = rmax;                    /* Best when patch crosses y-axis */
		if (atx < M_PI || atm > M_PI)
			b[3] *= m;                  /* Doesn't cross, scale by sine */
	}
	else                                /* ymax > 0: use rmin */
		b[3] = rmin * m;                /* Scale by sine */
}

static RtVoid Bound(struct spheredata *s, RtBound b)
{
	assert(s);
	/*
	* rmax is the maximum distance from the z-axis to a point on the sphere.
	* rmin is the minimum.
	* z0 is a temporary to help compute them.
	* Don't attempt to take the sqrt of a negative number.
	*/
	float rmax, rmin, z0;
	if (s->zmin < 0 && s->zmax > 0)
		rmax = s->radius;
	else {
		z0 = min(fabsf(s->zmin), fabsf(s->zmax));
		if (s->radius - z0 > FLT_EPSILON)
			rmax = sqrtf(s->radius * s->radius - z0 * z0);
		else
			rmax = 0;
	}

	z0 = max(fabsf(s->zmin), fabsf(s->zmax));
	if (s->radius - z0 > FLT_EPSILON)
		rmin = sqrtf(s->radius * s->radius - z0 * z0);
	else
		rmin = 0;

	boundRevolve(b, rmin, rmax, M_PI*s->thetamin/180, M_PI*s->thetamax/180);

	/*
	* Compute z bounds
	*/
	b[4] = s->zmin;
	b[5] = s->zmax;
}

//--------------------------------------------------------------------------------

#if (defined(_Windows) || defined(_WIN32)) && !defined(_RUN_PROGRAM_)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

RtPointer DLLEXPORT ConvertParameters(RtString paramstr)
{
	printf("ConvertParameters(%s)\n",paramstr);
	struct spheredata *sd =
		(struct spheredata *)malloc(sizeof(struct spheredata));
	assert(sd);
	assert(paramstr);
	//printf("\n\n\n\n----------------------------------%s\n", paramstr);
	sscanf(paramstr, "%f %f %f %f %f",
		&sd->radius,
		&sd->zmin,
		&sd->zmax,
		&sd->thetamin,
		&sd->thetamax);
	return (RtPointer)sd;
}

RtVoid DLLEXPORT Free(RtPointer data)
{
	printf("Free(...)\n");
	free(data);
}

#ifndef _RUN_PROGRAM_

/*
* Forward declarations
*/
extern "C" {
	RtPointer DLLEXPORT ConvertParameters(RtString paramstr);
	RtVoid DLLEXPORT Subdivide(RtPointer data, float detail);
	RtVoid DLLEXPORT Free(RtPointer data);
}




RtVoid DLLEXPORT Subdivide(RtPointer data, float detail)
{
	printf("Subdivide(...)\n");

	assert(data);


	struct spheredata *sd = (struct spheredata *)data;


	if (detail < 100 || detail > 0.9 * RI_INFINITY) {
		RiTransformBegin();
		RiRotate(sd->thetamin, 0, 0, 1);
		RiSphere(sd->radius, sd->zmin, sd->zmax, sd->thetamax - sd->thetamin,
			RI_NULL);
		RiTransformEnd();
	}
	else {
		struct spheredata *sd0 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd1 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd2 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd3 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		assert(sd0 && sd1 && sd2 && sd3);

		float zhalf = 0.5 * (sd->zmin + sd->zmax);
		float thetahalf = 0.5 * (sd->thetamin + sd->thetamax);

		RtBound b;

		sd0->radius = sd->radius;
		sd0->zmin = sd->zmin;
		sd0->zmax = zhalf;
		sd0->thetamin = sd->thetamin;
		sd0->thetamax = thetahalf;
		Bound(sd0, b);
		RiProcedural((RtPointer)sd0, b, Subdivide, Free);

		sd1->radius = sd->radius;
		sd1->zmin = zhalf;
		sd1->zmax = sd->zmax;
		sd1->thetamin = sd->thetamin;
		sd1->thetamax = thetahalf;
		Bound(sd1, b);
		RiProcedural((RtPointer)sd1, b, Subdivide, Free);

		sd2->radius = sd->radius;
		sd2->zmin = sd->zmin;
		sd2->zmax = zhalf;
		sd2->thetamin = thetahalf;
		sd2->thetamax = sd->thetamax;
		Bound(sd2, b);
		RiProcedural((RtPointer)sd2, b, Subdivide, Free);

		sd3->radius = sd->radius;
		sd3->zmin = zhalf;
		sd3->zmax = sd->zmax;
		sd3->thetamin = thetahalf;
		sd3->thetamax = sd->thetamax;
		Bound(sd3, b);
		RiProcedural((RtPointer)sd3, b, Subdivide, Free);
	}
}



// RtVoid DLLEXPORT Free(RtPointer data)
// {
// 	RtString *twostrings = (RtString *)data;
// 	free((void *)twostrings[0]);
// 	free((void *)twostrings[1]);
// 	free((void *)twostrings);
// }

#else//--------------------------------------------------------------

RtVoid  Subdivide(RtPointer data, float detail)
{
	//printf("Subdivide(...)\n");

	assert(data);


	struct spheredata *sd = (struct spheredata *)data;


	if (detail < 100 || detail > 0.9 * RI_INFINITY) {
		printf("TransformBegin\n");//RiTransformBegin();
		printf("Rotate [%f 0 0 1]\n", sd->thetamin);//RiRotate(sd->thetamin, 0, 0, 1);
		printf("Sphere [%f %f %f %f]\n",sd->radius, sd->zmin, sd->zmax, sd->thetamax - sd->thetamin);//RiSphere(sd->radius, sd->zmin, sd->zmax, sd->thetamax - sd->thetamin, RI_NULL);
		printf("TransformEnd\n");//RiTransformEnd();
	}
	else {
		struct spheredata *sd0 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd1 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd2 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		struct spheredata *sd3 =
			(struct spheredata *)malloc(sizeof(struct spheredata));
		assert(sd0 && sd1 && sd2 && sd3);

		float zhalf = 0.5 * (sd->zmin + sd->zmax);
		float thetahalf = 0.5 * (sd->thetamin + sd->thetamax);

		RtBound b;

		sd0->radius = sd->radius;
		sd0->zmin = sd->zmin;
		sd0->zmax = zhalf;
		sd0->thetamin = sd->thetamin;
		sd0->thetamax = thetahalf;
		Bound(sd0, b);
		RiProcedural((RtPointer)sd0, b, Subdivide, Free);

		sd1->radius = sd->radius;
		sd1->zmin = zhalf;
		sd1->zmax = sd->zmax;
		sd1->thetamin = sd->thetamin;
		sd1->thetamax = thetahalf;
		Bound(sd1, b);
		RiProcedural((RtPointer)sd1, b, Subdivide, Free);

		sd2->radius = sd->radius;
		sd2->zmin = sd->zmin;
		sd2->zmax = zhalf;
		sd2->thetamin = thetahalf;
		sd2->thetamax = sd->thetamax;
		Bound(sd2, b);
		RiProcedural((RtPointer)sd2, b, Subdivide, Free);

		sd3->radius = sd->radius;
		sd3->zmin = zhalf;
		sd3->zmax = sd->zmax;
		sd3->thetamin = thetahalf;
		sd3->thetamax = sd->thetamax;
		Bound(sd3, b);
		RiProcedural((RtPointer)sd3, b, Subdivide, Free);
	}
}

void doPolyGen(int nSides, float detail)
{
	int i;
	float angStep, currAng;
	printf("Polygon \"P\" [");
	if (nSides<3)nSides=3;
	angStep= 2.0*M_PI/nSides;
	for(i=0;i<nSides;i++)
	{
		float x,y,z;
		currAng = 0.5*M_PI + i*angStep;
		x = cos(currAng);
		y = sin(currAng);
		z = 0.0;
		printf("%f %f %f ",x,y,z);
	}
	printf("]\n");
}/* doPolyGen() */
int main(int argc, char ** argv)
{
	//
	flog = init_log("d:/procedural.log");

	string args;
	_rmlog("------------------%s\n", argv[0]);

	for (int i=1; i < argc; i++){
		//_rmlog(" %s,", argv[i]);
		args.append(argv[i]);
		if(i<argc-1)
			args.push_back(' ');
	}
	_rmlog( ">>main(%s)\n", args.c_str() );



// 	int a=4; float b=10;
// 	_rmlog("Hello there. %f %d\n", b, a);
	const int AGR_LEN = 1024;
	char buff[AGR_LEN];
	char *buffer=NULL;
	int nSides;

	//while(fgets(buffer,1024,stdin))
	if(args.size()>0){
		buffer = const_cast<char*>(args.c_str());
	}else{
		buffer = buff;
		fgets(buffer,AGR_LEN,stdin);
	}
	//{
		float detail;
		RtPointer sd = ConvertParameters(buffer, detail);//sscanf(buffer,"%f %d",&detail,&nSides);
		
		//printf("[buffer=%s]\n[detail=%f]\n[sides=%d]\n",buffer, detail, nSides);
		Subdivide(sd, detail);//doPolyGen(nSides, detail);
		fprintf(stdout,"%c", '\377');
		fflush(stdout);
		
		Free(sd);
	//}

	//
	close_log();
}
//
//

#endif