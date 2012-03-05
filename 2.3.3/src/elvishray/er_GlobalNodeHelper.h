
#ifndef _ER_GlobalNodeHelper_H
#define _ER_GlobalNodeHelper_H

#include "../liqGlobalNodeHelper.h"

/* ______________________________________________________________________
**
** Liquid Globals Node Helper
** ______________________________________________________________________
*/
namespace elvishray
{


class GlobalNodeHelper: public liqGlobalNodeHelper
{
public:
	GlobalNodeHelper();
	explicit GlobalNodeHelper(const char* globalNodeName);
	virtual ~GlobalNodeHelper();

	virtual bool getBool(const MString& attrName) ;
	virtual int getInt(const MString& attrName) ;
	virtual MString getString(const MString& attrName);
	virtual float getFloat(const MString& attrName);
	virtual double getDouble(const MString& attrName);
	//virtual MFloatVector getVector3(const MString& attrName);
	virtual MFloatPoint getVector(const MString& attrName);
	virtual MStringArray getStringArray(const MString& attrName);

protected:
	MObject m_GlobalNode;

private:
	GlobalNodeHelper(const GlobalNodeHelper&);
	GlobalNodeHelper& operator=(const GlobalNodeHelper&);
};

}
#endif//_ER_GlobalNodeHelper_H