#include "rm_renderer.h"
#include "../renderermgr.h"
#include <liqlog.h>

namespace renderman
{
	static const Renderer dummy;
	// the only goal to define a Renderer variable is 
	// to run the constructor to register this renderer.

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
