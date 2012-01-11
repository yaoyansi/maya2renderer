#ifndef _LIQ_CREATE_ABSTRACT_FACTORY_H_
#define _LIQ_CREATE_ABSTRACT_FACTORY_H_

#include "rendererinterface.h"

namespace liquid
{
	//
	class AbstractFactory
	{
	public:
		AbstractFactory(){}
		virtual ~AbstractFactory(){}

		virtual RendererInterface* createRenderer() = 0;
		virtual void deleteRenderer() = 0;

		virtual void createOutputReceiver() = 0;
		virtual void deleteOutputReceiver() = 0;

	private:
		AbstractFactory(const AbstractFactory&);
		AbstractFactory& operator=(const AbstractFactory&);
	};
}

#endif//_LIQ_CREATE_ABSTRACT_FACTORY_H_