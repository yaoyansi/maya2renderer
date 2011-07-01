#ifndef _RendererInterface_H_
#define _RendererInterface_H_

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


protected:


};

}
#endif//_RendererInterface_H_