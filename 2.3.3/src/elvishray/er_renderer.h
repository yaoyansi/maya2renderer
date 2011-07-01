#ifndef ER_Renderer_H
#define ER_Renderer_H

#include "../rendererinterface.h"

namespace elvishray
{
	class Renderer : public liquid::RendererInterface
	{
	public:
		Renderer();
		virtual ~Renderer();

		virtual void test();

		virtual void setRenderScriptFormatAndCompress(const bool bbinary, const bool bcompress);
		virtual MStatus worldPrologue(const structJob& currentJob);
	
	protected:
	
	};
}



#endif//ER_Renderer_H