#ifndef _RendererInterface_H_
#define _RendererInterface_H_

#include <string>
#include <maya/MStatus.h>
#include <liqRibNode.h>
#include "liqtypes.h"

struct structJob;
class liqRibLightData;

namespace liquid
{

class RendererInterface
{
public:
	RendererInterface(){}
	virtual ~RendererInterface() = 0 {};

//interface:
	virtual void test() = 0;
	
	// RenderScript means .rib files for renderman, and .er files for elvishray. and etc.
	virtual void setRenderScriptFormatAndCompress(const bool bbinary, const bool bcompress) = 0;

	virtual MStatus worldPrologue(const structJob& currentJob) = 0;
	virtual void openLog() = 0;
	virtual void closeLog() = 0;

	virtual MStatus exportLight(const liqRibNodePtr& light, const structJob &currentJob) = 0;
	virtual MStatus liqRibLightData_write(const liqRibLightData *lightdata, const structJob &currentJob) = 0;

	virtual liqLightHandle exportShadowPassLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqString & shadowname,
		const liqMatrix &transform) = 0;
	virtual liqLightHandle exportAmbientLight(
		const std::string &shadertype, 
		const std::string &shaderinstance, 
		const liqFloat & intensity,
		const liqColor & color,
		const liqMatrix &transform) = 0;
	virtual void transform_(const liqMatrix& transform) = 0;

protected:


};

}
#endif//_RendererInterface_H_