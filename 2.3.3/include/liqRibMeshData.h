/*
**
** The contents of this file are subject to the Mozilla Public License Version
** 1.1 (the "License"); you may not use this file except in compliance with
** the License. You may obtain a copy of the License at
** http://www.mozilla.org/MPL/
**
** Software distributed under the License is distributed on an "AS IS" basis,
** WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
** for the specific language governing rights and limitations under the
** License.
**
** The Original Code is the Liquid Rendering Toolkit.
**
** The Initial Developer of the Original Code is Colin Doncaster. Portions
** created by Colin Doncaster are Copyright (C) 2002. All Rights Reserved.
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

*/

#ifndef liqRibMeshData_H
#define liqRibMeshData_H

/* ______________________________________________________________________
**
** Liquid Rib Mesh Data Header File
** ______________________________________________________________________
*/

#include <liqRibData.h>

#include <boost/shared_array.hpp>

class liqRibMeshData : public liqRibData {
public: // Methods

  explicit liqRibMeshData( MObject mesh );
  virtual ~liqRibMeshData(){}

  virtual void       _write(const structJob &currentJob);
  virtual void       printMesh();
  virtual bool       compare( const liqRibData & other ) const;
  virtual ObjectType type() const;
  const RtInt getNumFaces()const{ return numFaces; }
  const boost::shared_array< RtInt >& getNverts()const
  {
	  return nverts;
  }
  const boost::shared_array< RtInt >& getVerts()const
  {
	  return verts;
  }
  const char* getName()const{ return name.asChar(); }

private: // Data
  RtInt     numFaces;
  RtInt     numPoints;
  RtInt     numNormals;
  boost::shared_array< RtInt > nverts;
  boost::shared_array< RtInt > verts;
  const RtFloat* vertexParam;
  const RtFloat* normalParam;

  bool    	areaLight;
  MString 	name;
  RtMatrix	transformationMatrix;
  float   	areaIntensity;

private:
	liqRibMeshData(const liqRibMeshData&);
	liqRibMeshData& operator=(const liqRibMeshData&);
};

#endif
