#ifndef ER_Renderer_H
#define ER_Renderer_H

#include "../rendererinterface.h"
#include "../log/logmgr.h"

namespace liquid{
	class LogMgr;
}

namespace elvishray
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

 		liquid::LogMgr m_log;

 		void _Script(const std::string &data){ m_log.log___(data); }
	};
}



#endif//ER_Renderer_H