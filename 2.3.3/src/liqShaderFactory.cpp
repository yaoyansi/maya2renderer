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
** Contributor(s): Baptiste Sansierra.
**
**
** The RenderMan (R) Interface Procedures and Protocol are:
** Copyright 1988, 1989, Pixar
** All Rights Reserved
**
**
** RenderMan (R) is a registered trademark of Pixar
*/


#include <liqShaderFactory.h>

#include <string>

#include <maya/MFnDependencyNode.h>
#include <maya/MPlug.h>

#include <liquid.h>
#include <liqShader.h>

using namespace std;

liqShaderFactory * liqShaderFactory::_instance=NULL;


liqShaderFactory::liqShaderFactory()
{
	shaderHandlerId = 0;
}


liqShaderFactory::~liqShaderFactory()
{
	clearShaders();
}


void liqShaderFactory::clearShaders()
{
	CM_TRACE_FUNC("liqShaderFactory::clearShaders()");

	vector<liqShader*>::iterator iter;
	vector<liqShader*>::iterator end = m_shaders.end();
	for( iter=m_shaders.begin(); iter!=end; iter++ )
	{
		if( *iter )
		{
			delete (*iter);
		}
	}
	m_shaders.clear();
	shaderHandlerId = 0;
}


liqShader &liqShaderFactory::getShader( MObject shaderObj )
{
	CM_TRACE_FUNC("liqShaderFactory::getShader("<<MFnDependencyNode(shaderObj).name()<<")");

	MString rmShaderStr;
	MFnDependencyNode shaderNode( shaderObj );
	MPlug rmanShaderNamePlug = shaderNode.findPlug( MString( "rmanShaderLong" ) );
	rmanShaderNamePlug.getValue( rmShaderStr );
	LIQDEBUGPRINTF( "[liqShaderFactory::getShader] Using Renderman Shader %s\n", rmShaderStr.asChar() );
	vector<liqShader*>::iterator iter = m_shaders.begin();
	while ( iter != m_shaders.end() )
	{
		//string shaderNodeName = shaderNode.name().asChar();
		if( (*iter)->m_mObject == shaderObj )
		{
			// Already got it : nothing to do
			return **iter;
		}
		++iter;
	}
	liqShader *currentShader = new liqShader( shaderObj );
	LIQDEBUGPRINTF("CREATE AND PUSH SHADER FOR NODE %s \n", shaderNode.name().asChar() );
	LIQDEBUGPRINTF("    name = %s\n", currentShader->getName().c_str());
	LIQDEBUGPRINTF("    file = %s\n", currentShader->getShaderFileName().c_str());
	LIQDEBUGPRINTF("    hdl  = %s\n", currentShader->shaderHandler.asChar());
	m_shaders.push_back( currentShader );
	return *(m_shaders.back());
}


MString liqShaderFactory::getShaderId( MObject shaderObj )
{
	CM_TRACE_FUNC("liqShaderFactory::getShader("<<MFnDependencyNode(shaderObj).name()<<")");

	liqShader &shader = liqShaderFactory::getShader( shaderObj );
	return shader.shaderHandler;
}


MString liqShaderFactory::getUniqueShaderHandler()
{
	CM_TRACE_FUNC("liqShaderFactory::getUniqueShaderHandler()");

	shaderHandlerId++;
	//char shaderHandler[512];
	// sprintf(shaderHandler, "CO_SHADER_%d", shaderHandlerId);
	MString shaderHandler;
	shaderHandler.set( (double)shaderHandlerId );
	shaderHandler = "CO_SHADER_" + shaderHandler;
	return shaderHandler;
}


