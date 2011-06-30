//HelloWorldRiFilter.cpp
//This Filter replaces RiCone to RiSphere using the radius parameter

#include <RifPlugin.h>
#include <ri.h>

class My_RifPlugin : public RifPlugin
{
public:
	My_RifPlugin();
	virtual 		~My_RifPlugin();

	virtual RifFilter & 	GetFilter();

private:

	RifFilter  m_rifFilter;
	static RtVoid coneV
		(RtFloat height, RtFloat radius, RtFloat tmax,RtInt, RtToken[], RtPointer[]);

};

RifPlugin *
RifPluginManufacture(int args, char **argv)
{
	return new My_RifPlugin();
}

My_RifPlugin::My_RifPlugin()
{
	m_rifFilter.ConeV = coneV;
}

My_RifPlugin::~My_RifPlugin() {
}

RifFilter & My_RifPlugin::GetFilter()
{
	return m_rifFilter;
}

RtVoid My_RifPlugin::coneV(RtFloat height, RtFloat radius, RtFloat tmax,
						   RtInt, RtToken[], RtPointer[])
{
	RiSphere(radius,-radius,radius,tmax,NULL);
}
