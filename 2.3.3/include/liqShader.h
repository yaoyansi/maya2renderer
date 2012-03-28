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
#ifndef liqShader_H
#define liqShader_H

#include <string>
#include <vector>

#include <maya/MFnDependencyNode.h>
#include <maya/MString.h>
#include <maya/MObject.h>

#include "ri_interface.h"

#include "liqShaderParameterType.h"
#include "liqTokenParameterType.h"

#define MR_SURFPARAMSIZE 1024

class liqTokenPointer;
class liqRibLightData;

class liqShader
{
public :
    liqShader();
    liqShader( const liqShader & src );
    liqShader & operator=( const liqShader & src );
    explicit liqShader ( MObject shaderObj );
    virtual ~liqShader();
	MStatus liqShaderParseVectorAttr( const MFnDependencyNode& shaderNode, const std::string& argName, ParameterType pType );
    MStatus liqShaderParseVectorArrayAttr( const MFnDependencyNode& shaderNode, const std::string& argName, ParameterType pType, unsigned int arraySize );
	MStatus liqShaderParseMatrixAttr ( const MFnDependencyNode& shaderNode, const std::string& argName, ParameterType pType );

	void appendCoShader(MObject coshader, MPlug plug);
	void write();
    //void writeAsCoShader();
	//void outputIndentation(unsigned int indentLevel);

	void buildJobs();
	void scanExpressions( liqShader & currentShader );
	void processExpression( liqTokenPointer *token, const liqRibLightData *light = NULL );

    // void freeShader( void ); -- not needed anymore. vector calls the dtors itself when going out of scope
    // int numTPV; -- handled by tokenPointerArray.size() now

	std::string getName() const;
	std::string getShaderFileName() const;

	void setShaderFileName(const std::string &file_){ file = file_; }

protected:
	std::string      name;
	std::string      file;

public:
    RtColor     rmColor;
    RtColor     rmOpacity;
    bool        hasShadingRate;
    RtFloat     shadingRate;
    bool        hasDisplacementBound;
    RtFloat     displacementBound;
    bool        outputInShadow;
    bool        hasErrors;
    //SHADER_TYPE shader_type;
	MString     shader_type_ex;
    MString     shaderSpace;
    MString     shaderHandler;
    int         evaluateAtEveryFrame;
    MObject     m_mObject;
    
    std::vector< liqTokenPointer	> tokenPointerArray;
    std::vector< MObject > m_coShaderArray;
};


#endif // liqShader_H
