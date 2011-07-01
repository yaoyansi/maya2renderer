#include "er_renderer.h"
#include "../renderermgr.h"
#include <liqlog.h>

namespace elvishray
{
	static Renderer locator;

	static const char *RendererName="elvishray";

	Renderer::Renderer()
	{
		liquid::RendererMgr::getInstancePtr()->registerRenderer(
			RendererName, this
			);
	}
	//
	Renderer::~Renderer()
	{

	}
	//
	void Renderer::test()
	{
		liquidMessage2(messageInfo, "this is %s.", RendererName );

	}
}
