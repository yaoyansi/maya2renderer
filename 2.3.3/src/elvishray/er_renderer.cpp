#include "er_renderer.h"
#include "../renderermgr.h"
#include <liqlog.h>


namespace elvishray
{
	//static const char *LogName="d:/script.er";
	static const Renderer dummy; 
	// the only goal to define a Renderer variable is 
	// to run the constructor to register this renderer.

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
	//
	void Renderer::setRenderScriptFormatAndCompress(const bool bbinary, const bool bcompress)
	{
		//todo...
	}
	//
	MStatus Renderer::worldPrologue(const structJob& currentJob)
	{
		m_log.open("d:/script.er");
		_Script("ready to go!");

		if( true )
		{
			_Script("ei_make_texture(\"d:\\lunatexmap.bmp\", \"d:\\lunatexmap.tex\", EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, EI_FILTER_BOX, 1.0f, 1.0f );");
		}
		m_log.close();
		return MS::kSuccess;
	}
}
