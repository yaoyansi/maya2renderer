#ifndef RM_Renderer_H
#define RM_Renderer_H

#include "../rendererinterface.h"


namespace renderman
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

		void _RiOption_format_compress(bool bBinary, bool bCompress);
	
	private:

	};
}



#endif//RM_Renderer_H