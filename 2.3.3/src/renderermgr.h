#ifndef _RendererMgr_H_
#define _RendererMgr_H_

#include <string>
#include <map>
#include "rendererinterface.h"
#include "liqAbstractFactory.h"

namespace liquid
{


class RendererMgr
{
public:
	static RendererMgr* getInstancePtr();
	virtual ~RendererMgr();

	void createFactory(const std::string& renderername);
	void deleteFactory();

	RendererInterface* getRenderer(){ return m_renderer; }
	
	void test();
	void prologue();
	void epilogue();

	void install();
	void uninstall();

protected:
	RendererMgr();
	RendererMgr(const RendererMgr&);
	RendererMgr& operator=(const RendererMgr&);

	static RendererMgr *m_instance;
	RendererInterface *m_renderer;
	//std::map<std::string, RendererInterface*> m_registeredRenderers;

	AbstractFactory* m_factory;
};

}
#endif//_RendererMgr_H_