#ifndef liqShadowRibWriterMgr_H
#define liqShadowRibWriterMgr_H

#include <vector>
#include <liquid.h>


struct liqGlobalVariable;

class tShadowRibWriterMgr
{
public:
	tShadowRibWriterMgr();
	virtual ~tShadowRibWriterMgr();

	TempControlBreak write(struct liqGlobalVariable &liqglo___, 
		const structJob &currentJob___,
		const long scanTime__,
		const bool m_outputLightsInDeepShadows__,
		std::vector<structJob>  jobList__);

protected:
	tShadowRibWriterMgr(const tShadowRibWriterMgr&);
	tShadowRibWriterMgr& operator=(const tShadowRibWriterMgr&);
};
#endif//liqShadowRibWriterMgr_H
