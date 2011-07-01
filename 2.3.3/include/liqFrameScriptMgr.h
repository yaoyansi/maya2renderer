#ifndef liqFrameScriptMgr_H
#define liqFrameScriptMgr_H

#include <liquid.h>
#include <liqRenderScript.h>

class tFrameScriptJobMgr
{
public:
	tFrameScriptJobMgr(liqRenderScript::Job& script);
	virtual ~tFrameScriptJobMgr();

	void setCommonParameters(const std::string &title  );

	void addInstanceJob( const bool isInstance,
		const std::string &title
		);
	void makeTexture(std::vector<structJob>  &txtList__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__
	);
	void makeTexturePass(
		std::vector<structJob> &shadowList__, 
		liqRenderScript::Job &shadowJob__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__
		);
	void makeShadow(
		std::vector<structJob> &shadowList__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__,
		const int currentBlock__
		);
	void makeShadowPass(
		std::vector<structJob> &shadowList__, 
		liqRenderScript::Job &shadowJob__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__,
		const MString &framePreCommand__,
		const MString &frameRenderCommand__,
		const int currentBlock__
		);
	void makeReflection(
		std::vector<structJob> &refList__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__
		);
	void makeReflectionPass(
		std::vector<structJob> &refList__, 
		liqRenderScript::Job &reflectJob__,
		bool &alf_textures__,
		bool &alf_shadows__,
		bool &alf_refmaps__
		);
	void try_addPreFrameCommand(const MString &framePreFrameCommand__);
	void try_addPostFrameCommand(const MString &framePostFrameCommand__);
	void addHeroPass(
		const MString &ribFileName__,
		const MString &framePreCommand__, 
		const MString &frameRenderCommand__
		);
	void addShadowPass(
		const MString &ribFileName__,
		const MString &framePreCommand__, 
		const MString &frameRenderCommand__
		);
protected:
	liqRenderScript::Job &m_frameScriptJob;

	//
protected:
	tFrameScriptJobMgr();
private:
	tFrameScriptJobMgr(const tFrameScriptJobMgr&);
	tFrameScriptJobMgr& operator=(const tFrameScriptJobMgr&);
};

#endif//liqFrameScriptMgr_H