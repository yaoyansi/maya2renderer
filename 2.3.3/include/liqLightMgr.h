#ifndef liqLightMgr_H
#define liqLightMgr_H

#include <boost/shared_ptr.hpp>
#include <maya/MStatus.h>
#include <liqRibHT.h>


class tLightMgr
{
public:
	tLightMgr();
	virtual ~tLightMgr();
	void scanScene(
		const float lframe__, const int sample__,
		boost::shared_ptr< liqRibHT > &htable__,
		int &count__,
		MStatus &returnStatus__);

private:
	tLightMgr(const tLightMgr&);
	tLightMgr& operator=(const tLightMgr&);
};

#endif//liqLightMgr_H