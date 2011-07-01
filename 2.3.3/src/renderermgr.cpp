#include "renderermgr.h"
#include "liqlog.h"

namespace liquid
{

	RendererMgr* RendererMgr::m_instance = 0;
	//
	RendererMgr::RendererMgr()
	:m_renderer(0)
	{

	}
	//
	RendererMgr::~RendererMgr()
	{

	}
	//
	RendererMgr* RendererMgr::getInstancePtr()
	{
		if(m_instance==0){
			m_instance = new RendererMgr();
		}
		return m_instance;
	}
	//
	void RendererMgr::setRenderer(const std::string &renderername)
	{
		std::map<std::string, RendererInterface*>::iterator 
			i = m_registeredRenderers.find(renderername);
		if( i != m_registeredRenderers.end())
		{ 
			m_renderer = i->second;
		}
		else {
			liquidMessage2(messageError, "Unkown renderer:%s.",renderername.c_str() );
		}
	}
	//
	void RendererMgr::registerRenderer(const std::string &renderername, RendererInterface* renderer)
	{
		m_registeredRenderers.insert(make_pair(renderername, renderer));
	}
	//
	void RendererMgr::test()
	{
		assert(m_renderer);
		m_renderer->test();
	}
	void RendererMgr::prologue()
	{
		getRenderer()->openLog();
	}
	void RendererMgr::epilogue()
	{
		getRenderer()->closeLog();
	}

}
