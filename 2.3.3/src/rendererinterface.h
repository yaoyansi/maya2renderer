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


protected:


};

}
#endif//_RendererInterface_H_