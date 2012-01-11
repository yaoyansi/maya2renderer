#ifndef _RM_FACTORY_H_
#define _RM_FACTORY_H_

#include "../liqAbstractFactory.h"

namespace renderman
{
	class Renderer;
	//Create Factory
	class Factory: public liquid::AbstractFactory
	{
	public:
		Factory();
		virtual ~Factory();
	
		virtual liquid::RendererInterface* createRenderer();
		virtual void deleteRenderer();

		virtual void createOutputReceiver();
		virtual void deleteOutputReceiver();

	private:
		Factory(const Factory&);
		Factory& operator=(const Factory&);

		Renderer* m_renderer;
	};
}

#endif//_RM_FACTORY_H_