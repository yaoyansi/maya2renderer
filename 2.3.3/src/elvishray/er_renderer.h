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
	};
}



#endif//ER_Renderer_H