#include "rm_renderer.h"
#include "../renderermgr.h"
#include <liqlog.h>

namespace renderman
{
	static Renderer locator;

	static const char *RendererName="renderman";

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
	//

}
