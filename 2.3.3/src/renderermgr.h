#ifndef _RendererMgr_H_
#define _RendererMgr_H_

#include <string>
#include <map>
#include "rendererinterface.h"

namespace liquid
{


class RendererMgr
{
public:
	static RendererMgr* getInstancePtr();
	virtual ~RendererMgr();

	void setRenderer(const std::string &renderername);
	RendererInterface* getRenderer(){ return m_renderer; }
	
	void registerRenderer(const std::string &rendername, RendererInterface* renderer);
	void test();
	void prologue();
	void epilogue();

protected:
	RendererMgr();
	RendererMgr(const RendererMgr&);
	RendererMgr& operator=(const RendererMgr&);

	static RendererMgr *m_instance;
	RendererInterface *m_renderer;
	std::map<std::string, RendererInterface*> m_registeredRenderers;

};

}
#endif//_RendererMgr_H_