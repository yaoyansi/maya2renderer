#ifndef liqRibCamera_H
#define liqRibCamera_H

#include <vector>
#include <liquid.h>


struct liqGlobalVariable;



class tRibCameraMgr
{
public:
	tRibCameraMgr();
	virtual ~tRibCameraMgr();

	static void gatherDataForJob(
		struct liqGlobalVariable &liqglo___, 
		structJob &currentJob___,
		std::vector<structJob>  &jobList__,
		const bool m_outputShadowPass_,
		const bool m_outputHeroPass_
	);

	static void framePrologue_camera(long lframe, const structJob &currentJob);

protected:
	tRibCameraMgr(const tRibCameraMgr&);
	tRibCameraMgr& operator=(const tRibCameraMgr&);
};
#endif//liqRibCamera_H
