#ifndef liqHeroRibWriterMgr_H
#define liqHeroRibWriterMgr_H

#include <vector>
#include <liquid.h>


struct liqGlobalVariable;

class tHeroRibWriterMgr
{
public:
	tHeroRibWriterMgr();
	virtual ~tHeroRibWriterMgr();

	TempControlBreak write(struct liqGlobalVariable &liqglo___, 
		const structJob &currentJob___,
		const long scanTime__,
		const bool m_outputLightsInDeepShadows__
		//,std::vector<structJob>  jobList__
		);
	static void ribPrologue_samples(RtFloat xsamples, RtFloat ysamples);
	static void ribPrologue_shadingrate(RtFloat size);
	static void ribPrologue_filter(
		liquidlong m_rFilter,
		RtFloat m_rFilterX, RtFloat m_rFilterY
		);
	static void ribPrologue_hider(HiderType hidertype);
	static void ribPrologue_pass(RtString pass);

protected:
	tHeroRibWriterMgr(const tHeroRibWriterMgr&);
	tHeroRibWriterMgr& operator=(const tHeroRibWriterMgr&);
};
#endif//liqHeroRibWriterMgr_H
