#ifndef _ER_FACTORY_H_
#define _ER_FACTORY_H_

#include "../liqAbstractFactory.h"

namespace elvishray
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

#endif//_ER_FACTORY_H_