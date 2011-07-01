#ifndef liqFrameScriptMgr_H
#define liqFrameScriptMgr_H

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