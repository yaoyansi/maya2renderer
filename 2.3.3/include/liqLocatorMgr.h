#ifndef liqLocatorMgr_H
#define liqLocatorMgr_H

#include <boost/shared_ptr.hpp>
#include <maya/MStatus.h>
#include <liqRibHT.h>


class tLocatorMgr
{
public:
	tLocatorMgr();
	virtual ~tLocatorMgr();
	void scanScene(
		const float lframe__, const int sample__,
		boost::shared_ptr< liqRibHT > &htable__,
		int &count__,
		MStatus &returnStatus__);

private:
	tLocatorMgr(const tLocatorMgr&);
	tLocatorMgr& operator=(const tLocatorMgr&);
};

#endif//liqLocatorMgr_H