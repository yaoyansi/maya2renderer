#include "stdio.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <cstdlib>						
#include <cstdio>						
#include <cstring>						
#include <fstream>	

#include <RifPlugin.h>
#include <ri.h>

#include <bruteNN.hpp>
#include <dpoint.hpp>
#include <nnBase.hpp>
//#include <static_chan.hpp>
#include <sfcnn_ip.hpp>

typedef reviver::dpoint<int,3> Point;

//prman.lib libprmansdk.lib Iphlpapi.lib Ws2_32.lib

using namespace std;



void setNearestDistances(int nverts,const RtPoint *P_Rib,double *nearestDistances){
  
  	double detail = 1000000;
  	double offset = 1000;
  
  	Point *P = (Point*)malloc(nverts*sizeof(Point));
  
  	for(int n = 0 ; n < nverts ; n++){
  		unsigned int P_treeX = (P_Rib[n][0]+offset)*detail;
  		unsigned int P_treeY = (P_Rib[n][1]+offset)*detail;
  		unsigned int P_treeZ = (P_Rib[n][2]+offset)*detail;
  
  		Point treeP(P_treeX,P_treeY,P_treeZ);
  
  		P[n][0] = treeP[0];
  		P[n][1] = treeP[1];
  		P[n][2] = treeP[2];
  	}
  
  	vector<const Point*> ans ;
    std::vector<long unsigned int> bf_ans;

  	int size = nverts;
  
  	ans.resize(1);
  	//nnBase<Point> *NN = new sfcnn_ip<Point>(P,size);
	bruteNN<Point> NN(P,size);

  	for(int n = 0 ; n < nverts ; n++){
  
  		Point queryP(P[n][0],P[n][1],P[n][2]);
  
  		NN.ksearch( queryP,3,bf_ans);
//   		Point tmp1 = *(ans[1]);
//   		Point tmp2 = *(ans[2]);
  
		vector<long unsigned int> PointIndex;//exclude P[n] itself from bf_ans.
		for(int i=0; i<bf_ans.size(); ++i){
			if(n!=bf_ans[i])
				PointIndex.push_back(bf_ans[i]);
		}
		
		long unsigned int index0=PointIndex[0];
  		double nX1 = double(P[index0][0]);
  		double nY1 = double(P[index0][1]);
  		double nZ1 = double(P[index0][2]);
  		
		long unsigned int index1=PointIndex[1];
  		double nX2 = double(P[index1][0]);
  		double nY2 = double(P[index1][1]);
  		double nZ2 = double(P[index1][2]);
  
  		double dist1 = sqrt(pow(double(P[n][0])-nX1,2)+pow(double(P[n][1])-nY1,2)+pow(double(P[n][2])-nZ1,2));
  		double dist2 = sqrt(pow(double(P[n][0])-nX2,2)+pow(double(P[n][1])-nY2,2)+pow(double(P[n][2])-nZ2,2));
  
  		nearestDistances[n] = ((dist1 + dist2)/2) / detail;
  
  	}
  
//  	delete NN;
  
  	free(P);
  }

class My_RifPlugin : public RifPlugin
{
public:
	My_RifPlugin();
	virtual 		~My_RifPlugin();

	virtual RifFilter &     GetFilter();

private:

	RifFilter  m_rifFilter;
	static RtVoid myPointsV(RtInt nverts, RtInt, RtToken[], RtPointer[]);


};

RifPlugin*  RifPluginManufacture(int args, char **argv)
{
	return new My_RifPlugin();
}

 My_RifPlugin::My_RifPlugin()
{
	m_rifFilter.PointsV = myPointsV;
}

 My_RifPlugin::~My_RifPlugin() {
}

 RifFilter & My_RifPlugin::GetFilter()
{
	return m_rifFilter;

}

RtVoid freestrings(RtString *twostrings) {
	free((void *)twostrings[0]);
	free((void *)twostrings[1]);
	free((void *)twostrings);
}

 RtVoid My_RifPlugin::myPointsV(RtInt nverts, RtInt numOfParam, RtToken* paramNames, RtPointer* paramValues)
{

	if(numOfParam > 3){

		RtPoint *P = (RtPoint*)paramValues[0];

		RtFloat *constantwidth = (RtFloat*)paramValues[1];
		RtColor *CS = (RtColor*)paramValues[2];

		double *nearestDistances = (double*)malloc(sizeof(double)*nverts);

		setNearestDistances(nverts,P,nearestDistances);

		int numOfDots = 30;
		constantwidth[0] = 0.02f;


		for(int n = 0; n < nverts; n++){

			float multiPointRadius = nearestDistances[n] * 1.0;

 			float px = P[n][0];
 			float py = P[n][1];
 			float pz = P[n][2]; 

			float r = CS[n][0];
			float g = CS[n][1];
			float b = CS[n][2];
			if(r > 1 || g > 1 || b >1 ){
				cout << r << " / "<< g <<" / " <<b<<" / "<<endl;
				cin >> r;
			}

			char buffer[256];
			sprintf(buffer,"%f %d %d %f %f %f %f %f %f %f", multiPointRadius,numOfDots,n, constantwidth[0], px,py,pz,  r,g,b);


			RtBound myBound = {px-multiPointRadius,px+multiPointRadius
				,py-multiPointRadius,py+multiPointRadius
				,pz-multiPointRadius,pz+multiPointRadius};

			//http://www.dotcsw.com/doc/procedurals.html
			RtString *twostrings = (RtString *)malloc(2 * sizeof(RtString));
			twostrings[0] = strdup("dots");
			twostrings[1] = strdup(buffer);

			//printf("RiProcedural(%s, %s,...)\n", twostrings[0], twostrings[1]);
			RiProcedural (twostrings,myBound,RiProcDynamicLoad,(RtProcFreeFunc)freestrings);
		}
		free(nearestDistances);

	}else{
		//printf("RiPointsV(...)\n");
		RiPointsV(nverts,numOfParam,paramNames, paramValues);

	}
}


