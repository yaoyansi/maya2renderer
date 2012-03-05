
#ifndef liqGlobalNodeHelper_H
#define liqGlobalNodeHelper_H

#include "common/prerequest_maya.h"

/* ______________________________________________________________________
**
** Liquid Globals Node Helper
** ______________________________________________________________________
*/

class liqGlobalNodeHelper
{
public:
	liqGlobalNodeHelper();
	virtual ~liqGlobalNodeHelper();

	virtual bool getBool(const MString& attrName) = 0;
	virtual int getInt(const MString& attrName) = 0;
	virtual MString getString(const MString& attrName) = 0;
	virtual float getFloat(const MString& attrName) = 0;
	virtual double getDouble(const MString& attrName) = 0;
	//virtual MFloatVector getVector3(const MString& attrName) = 0;
	virtual MFloatPoint getVector(const MString& attrName) = 0;
	virtual MStringArray getStringArray(const MString& attrName) = 0;

private:
	liqGlobalNodeHelper(const liqGlobalNodeHelper&);
	liqGlobalNodeHelper& operator=(const liqGlobalNodeHelper&);
};
#endif//liqGlobalNodeHelper_H