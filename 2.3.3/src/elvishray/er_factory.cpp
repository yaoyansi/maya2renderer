#include "er_factory.h"
#include "../shadergraph/shaderOutputER.h"
#include "../shadergraph/shaderOutputERCall.h"
#include "er_renderer.h"
#include "../shadergraph/shaderOutputMgr.h"

namespace elvishray
{
	Factory::Factory()
	{
		m_renderer = 0;
	}
	//
	Factory::~Factory()
	{

	}
	//
	liquid::RendererInterface* Factory::createRenderer()
	{
		if(m_renderer==0){
			m_renderer = new Renderer();
		}
		return m_renderer;
	}
	void Factory::deleteRenderer()
	{
		if(m_renderer)
		{
			delete m_renderer;
			m_renderer = 0;
		}
	}

	//
	void Factory::createOutputReceiver()
	{
		liquidmaya::ShaderOutputMgr::getSingletonPtr()->addReceiver(new ER::Visitor());
		liquidmaya::ShaderOutputMgr::getSingletonPtr()->addReceiver(new ERCall::Visitor());
	}
	void Factory::deleteOutputReceiver()
	{
		liquidmaya::ShaderOutputMgr::getSingletonPtr()->deleteReceivers();
	}


}