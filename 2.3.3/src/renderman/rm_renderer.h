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
	protected:

	};
}



#endif//RM_Renderer_H