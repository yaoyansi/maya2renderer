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
	static void ribPrologue_samples(RtFloat xsamples, RtFloat ysamples);
	static void ribPrologue_shadingrate(RtFloat size);
	static void ribPrologue_filter(
		liquidlong m_rFilter,
		RtFloat m_rFilterX, RtFloat m_rFilterY);
	static void ribPrologue_pass(RtString pass);

	static void framePrologue_display(const structJob &currentJob);

protected:
	tShadowRibWriterMgr(const tShadowRibWriterMgr&);
	tShadowRibWriterMgr& operator=(const tShadowRibWriterMgr&);
};
#endif//liqShadowRibWriterMgr_H
