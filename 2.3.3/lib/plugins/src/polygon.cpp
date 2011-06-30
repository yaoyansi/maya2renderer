#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
void doPolyGen(int nSides)
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
int main()
{

	void doPolyGen(int nSides);
	char buffer[256];
	float detail;
	int nSides;
	while(fgets(buffer,256,stdin))
	{
		sscanf(buffer,"%f %d",&detail,&nSides);
		printf("[buffer=%s]\n[detail=%f]\n[sides=%d]\n",buffer, detail, nSides);
		doPolyGen(nSides);
		fprintf(stdout,"%c", '\377');
		fflush(stdout);
	}
}/* main() */