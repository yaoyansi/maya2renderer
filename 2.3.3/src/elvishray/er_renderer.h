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
		virtual MStatus exportLight(const liqRibNodePtr& light, const structJob &currentJob);
		virtual MStatus liqRibLightData_write(const liqRibLightData *lightdata, const structJob &currentJob);

		virtual void openLog();
		virtual void closeLog();

		virtual liqLightHandle exportShadowPassLight(
			const std::string &shadertype, 
			const std::string &shaderinstance, 
			const liqString & shadowname,
			const liqMatrix &transform);
		virtual liqLightHandle exportAmbientLight(
			const std::string &shadertype, 
			const std::string &shaderinstance, 
			const liqFloat & intensity,
			const liqColor & color,
			const liqMatrix &transform);
		virtual void transform_(const liqMatrix& transform);

	protected:
		Renderer(const Renderer&);
		Renderer& operator=(const Renderer&);

 		liquid::LogMgr m_log;

 		void _Script(const std::string &data){ m_log.log___(data); }
	};
}



#endif//ER_Renderer_H