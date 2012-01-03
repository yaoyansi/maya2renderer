#ifndef _RSL_H_
#define _RSL_H_

#include "../common/prerequest_maya.h"
#include "shaderOutput.h"

namespace liquidmaya{

class RSLShaderHelper
{
public:
	RSLShaderHelper();
	~RSLShaderHelper();

	//--------------------------------------------------------------------
	// Perform the necessary setup to allow a variable to be used in the
	// current block (function) of RSL code.
	//
	// If the associated Maya plug is connected to a node we can convert,
	// then the variable is added to the block's header as an input/output
	// parameter.
	//
	// If the plug is not connected, or is connected to a node we can not
	// convert, then the variable is added to the block's body, and the
	// current Maya value is pulled in.
	//--------------------------------------------------------------------
	void addRSLVariable(MString rslType, const MString& rslName,
		const MString& mayaName, const MString& mayaNode);
	
	//--------------------------------------------------------------------
	// Add a segment of code to the current RSL block (function).
	//--------------------------------------------------------------------
	void addToRSL(const MString& code);

	//--------------------------------------------------------------------
	// Begin a new block (function) of RSL code.
	//--------------------------------------------------------------------
	void beginRSL (const MString& $name);

	//--------------------------------------------------------------------
	// End the current block (function) of RSL code.
	//--------------------------------------------------------------------
	void endRSL ();

protected:
	MString rslShaderHeader;
	MString rslShaderBody;

};
//////////////////////////////////////////////////////////////////////////
class RSL : public ShaderOutput
{
public:
	RSL();
	~RSL();

	virtual void output(const char* shaderNodeName);

protected:
	void _output(const char* shaderNodeName, const char* nodetype);


};

}//namespace liquidmaya
#endif