/* $Id: //depot/branches/rmanprod/rman-13.5/include/ImplicitField.h#1 $ $Date: 2007/07/06 $ */
/*
** Copyright (c) 2006 PIXAR.  All rights reserved.  This program or
** documentation contains proprietary confidential information and trade
** secrets of PIXAR.  Reverse engineering of object code is prohibited.
** Use of copyright notice is precautionary and does not imply
** publication.
**
**                      RESTRICTED RIGHTS NOTICE
**
** Use, duplication, or disclosure by the Government is subject to the
** following restrictions:  For civilian agencies, subparagraphs (a) through
** (d) of the Commercial Computer Software--Restricted Rights clause at
** 52.227-19 of the FAR; and, for units of the Department of Defense, DoD
** Supplement to the FAR, clause 52.227-7013 (c)(1)(ii), Rights in
** Technical Data and Computer Software.
**
** Pixar Animation Studios
** 1200 Park Ave
** Emeryville, CA  94608
*/
#ifndef IMPLICITFIELD_H
#define	IMPLICITFIELD_H
#include <ri.h>
class ImplicitVertexValue{
private:
	/* inhibit copying */
	ImplicitVertexValue(const ImplicitVertexValue &);
	ImplicitVertexValue &operator=(const ImplicitVertexValue &);
public:
	ImplicitVertexValue(){}
	virtual ~ImplicitVertexValue(){}
	virtual void GetVertexValue(RtFloat *result, const RtPoint p)=0;
};
class ImplicitField{
public:
	/*
	 * bounding box at t=0,
	 * ImplicitField::ImplicitField fills this in
	 */
	RtBound bbox;
private:
	/* inhibit copying */
	ImplicitField(const ImplicitField &);
	ImplicitField &operator=(const ImplicitField &);
public:
	ImplicitField(){}
	virtual ~ImplicitField(){}
	virtual RtFloat Eval(const RtPoint p) = 0;
	virtual void GradientEval(RtPoint result, const RtPoint p) = 0;
	virtual void Range(RtInterval result, const RtPoint corners[8], const RtVolumeHandle h){
		result[0]=-1e30;
		result[1]=1e30;
	}
	virtual void Motion(RtPoint result, const RtPoint p){
		result[0]=0.;
		result[1]=0.;
		result[2]=0.;
	}
	virtual void BoxMotion(RtBound result, const RtBound b){
		for(int i=0;i!=6;i++) result[i]=b[i];
	}
	virtual void VolumeCompleted(const RtVolumeHandle h){}
	virtual ImplicitVertexValue *CreateVertexValue(const RtToken name, int nvalue){ return 0; }
};
#ifndef DLLEXPORT
# if defined(_MSC_VER) \
  &&  (defined(WIN32) \
    || defined(_Windows) \
    || defined(_WINDOWS) \
    || defined(_WIN32) \
    || defined(__WIN32__) \
    || defined(WINNT))
#      define DLLEXPORT __declspec(dllexport)
# else
#      define DLLEXPORT
# endif
#endif
#define	FIELDCREATE\
	extern "C" const DLLEXPORT int ImplicitFieldVersion=1;	\
	extern "C" DLLEXPORT ImplicitField *ImplicitFieldNew(	\
		int nfloat,					\
		const RtFloat *float0, const RtFloat *float1,	\
		int nstring, const RtString *string)
#endif
