/*
**
** The contents of this file are subject to the Mozilla Public License Version 1.1 (the
** "License"); you may not use this file except in compliance with the License. You may
** obtain a copy of the License at http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis, WITHOUT
** WARRANTY OF ANY KIND, either express or implied. See the License for the specific
** language governing rights and limitations under the License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions created by
** Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
**
** Contributor(s): Berj Bannayan.
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
**
*/

#ifndef liqRibSurfaceData_H
#define liqRibSurfaceData_H

/* ______________________________________________________________________
**
** Liquid Rib Surface Data Header File
** ______________________________________________________________________
*/
#include <vector>
#include <boost/shared_array.hpp>

#include <liqRibData.h>

class liqRibSurfaceData : public liqRibData {
public: // Methods

  explicit liqRibSurfaceData( MObject surface );
  virtual ~liqRibSurfaceData(){}

  virtual void write(
	  const MString &ribFileName, 
	  const structJob &currentJob, 
	  const bool bReference
	  );
  virtual unsigned      granularity() const;
  virtual bool          writeNextGrain();
  virtual bool          compare( const liqRibData & other ) const;
  virtual ObjectType    type() const;

private: // Data
  void          _write(const structJob &currentJob);
  unsigned              grain;
  bool                  hasTrims;

  RtInt                 nu, nv;
  RtInt                 uorder, vorder;
  boost::shared_array< RtFloat > uknot;
  boost::shared_array< RtFloat > vknot;
  RtFloat               umin, umax,
                        vmin, vmax;
  boost::shared_array< RtFloat > CVs;

  // Trim information

  RtInt                 nloops;
  //shared_array< RtInt > ncurves, order, n;
  //shared_array< RtFloat > knot, minKnot, maxKnot, u, v, w;

  std::vector< RtInt >       ncurves, order, numCVs;
  std::vector< RtFloat >     knot, minKnot, maxKnot, u, v, w;

private:
	liqRibSurfaceData(const liqRibSurfaceData&);
	liqRibSurfaceData& operator=(const liqRibSurfaceData&);
};

#endif
