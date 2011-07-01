#ifndef RM_Renderer_H
#define RM_Renderer_H

#include "../rendererinterface.h"


namespace renderman
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
		Renderer(const Renderer&);
		Renderer& operator=(const Renderer&);

		void _RiOption_format_compress(bool bBinary, bool bCompress);
	
	private:

	};
}



#endif//RM_Renderer_H