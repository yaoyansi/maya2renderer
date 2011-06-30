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

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include <alloca.h>

#include <maya/MObject.h>
#include <maya/MFnDagNode.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>

#include <liquidRIBGen.h>
#include <liquidRIBStatus.h>
extern "C" {
	#include <ri.h>
}

class testRIBStatus: public liquidRIBGen {
public:
    testRIBStatus();
    virtual ~testRIBStatus();

    virtual int GenRIB( liquidRIBStatus * );
};

/*---------------------------------------------------------*/
liquidRIBGen * RIBGenCreate() {
    return new testRIBStatus();
}

void
RIBGenDestroy(liquidRIBGen * g) {
    delete dynamic_cast<testRIBStatus *>(g);
}

/*---------------------------------------------------------*/
testRIBStatus::testRIBStatus() {
}

testRIBStatus::~testRIBStatus() {
}

int testRIBStatus::GenRIB( liquidRIBStatus * ribStatus ) {
	/* initialize the rib generator! */
	initRibGen( ribStatus );

	
	MFnDagNode dagNode( ribStatus->dagPath );
	RiArchiveRecord( RI_COMMENT, "Liquid Rib Generation Test!" );
	RiAttributeBegin();
	RtColor col = { 1.0, 1.0, 1.0};
	RiColor( col );
	RiAttributeEnd();
	MString comment("Dag Path: ");
	comment += ribStatus->dagPath.fullPathName();
	comment += "   Frame : ";
	comment += ribStatus->sampleTimes[0];
	RiArchiveRecord( RI_COMMENT, (char *)comment.asChar());
	RtColor myColor;
	myColor[0] = 0.1; 
	myColor[1] = 0.2; 
	myColor[2] = 0.3; 
	RiColor( myColor );
	
  return 1;
}
