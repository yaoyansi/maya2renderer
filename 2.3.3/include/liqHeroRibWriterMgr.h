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

protected:
	tHeroRibWriterMgr(const tHeroRibWriterMgr&);
	tHeroRibWriterMgr& operator=(const tHeroRibWriterMgr&);
};
#endif//liqHeroRibWriterMgr_H
