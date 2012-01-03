#include "convertShadingNetwork.h"
#include <boost/algorithm/string.hpp>
#include "../common/mayacheck.h"
#include <liqlog.h>
#include "shadermgr.h"
#include "shaderOutputMgr.h"

namespace liquidmaya{


ConvertShadingNetwork::ConvertShadingNetwork()
{
	{// init convertibleNodeTypes
		//Materials.
		convertibleNodeTypes.push_back("blinn");
		convertibleNodeTypes.push_back("layeredShader");
		convertibleNodeTypes.push_back("lambert");
		convertibleNodeTypes.push_back("phong");
		//Textures.
		convertibleNodeTypes.push_back("checker");
		convertibleNodeTypes.push_back("cloth");
		convertibleNodeTypes.push_back("file");
		convertibleNodeTypes.push_back("fractal");
		convertibleNodeTypes.push_back("snow");
		convertibleNodeTypes.push_back("solidFractal");
		convertibleNodeTypes.push_back("grid");
		//Utilities.
		convertibleNodeTypes.push_back("condition");
		convertibleNodeTypes.push_back("multiplyDivide");
		convertibleNodeTypes.push_back("place2dTexture");
		convertibleNodeTypes.push_back("reverse");
		convertibleNodeTypes.push_back("samplerInfo");
		convertibleNodeTypes.push_back("blendColors");
		convertibleNodeTypes.push_back("gammaCorrect");
		convertibleNodeTypes.push_back("hsvToRgb");
		convertibleNodeTypes.push_back("luminance");
		convertibleNodeTypes.push_back("rgbToHsv");
		convertibleNodeTypes.push_back("clamp");
	}
}
//
ConvertShadingNetwork::~ConvertShadingNetwork()
{

}
//

//
void ConvertShadingNetwork::exportShaderGraph()
{
	if( beforeExport() )
	{
		__export();
		afterExport();
	}

}
//
bool ConvertShadingNetwork::beforeExport()
{
	return true;
}
//
void ConvertShadingNetwork::afterExport()
{

}
//
bool ConvertShadingNetwork::nodeIsConvertible ( const MString& node ) const
{
	MString cmd;

	MString nodetype;
	cmd = "nodeType \""+node+"\"";
	IfMErrorWarn(MGlobal::executeCommand( cmd, nodetype));
	return (convertibleNodeTypes.end()!=std::find(convertibleNodeTypes.begin(), convertibleNodeTypes.end(), nodetype.asChar() ) );
}
//
bool ConvertShadingNetwork::ensurePlugExists(const MString& plug) const
{
	MStringArray components;
	plug.split('.', components);
	MString node(components[0]);
	MString attribute(components[1]);

	//$attribute = `substitute "\\[.*" $attribute ""`;
	MString cmd("substitute \"\\[.*\" "+attribute+" \"\"");
	IfMErrorWarn(MGlobal::executeCommand( cmd, attribute));

	int exist;
	cmd = "attributeExists \""+attribute+"\" \""+node+"\"";
	IfMErrorWarn(MGlobal::executeCommand( cmd, exist));
	if( !exist ){
		liquidMessage2(messageError, ("Attribute '" + attribute + "' is not part of the '" + node + "'." ).asChar());
		return false;
	}
	return true;
}
//
int ConvertShadingNetwork::convertibleConnection(const MString& plug) const
{
	// Check to see if the plug even exists!
	if( !ensurePlugExists(plug) )
		return 0;
	
	MStringArray connections;

	// Check to see if the plug is connected as an output
	// to any node(s) we can convert.
	MString cmd;
	cmd = "listConnections -source off -destination on \""+plug+"\"";
	IfMErrorWarn(MGlobal::executeCommand( cmd, connections));
	
	for(size_t i=0; i<connections.length(); ++i)
	{
		if( nodeIsConvertible(connections[i]) )
			return 2;
	}
	
	// Check to see if the plug is connected as an input from any
	// node(s) we can convert.
	cmd = "listConnections -source on -destination off \""+plug+"\"";
	IfMErrorWarn(MGlobal::executeCommand( cmd, connections));
	
	for(size_t i=0; i<connections.length(); ++i)
	{
		if( nodeIsConvertible(connections[i]) )
			return 1;
	}

	// Otherwise, return "no convertible connection".
	return 0;
}
//addRSLVariable()
//addToRSL
//endRSL ()
//beginRSL ( string $name )
int ConvertShadingNetwork::getUpstreamConvertibleNodes ( const MString& currentNode, 
								 MStringArray& nodes, MIntArray& numConnections)
{
	// If the current node has already been visited
	for(std::size_t i=0; i<nodes.length(); ++i)
	{
		if( nodes[i]==currentNode)
			return 1;
	}

	// If the node is not supported
	if( !nodeIsConvertible( currentNode ) )
	{
		return 0;
	}

	const int index = nodes.length();

	// Append the current node to the list of nodes
	if( nodes.length()<(index+1) ){
		nodes.setLength(index+1);
	}
	nodes[index] = currentNode;
	
	// Initialize the number of input connections to 0 for the newly found node
	if( numConnections.length()<(index+1) ){
		numConnections.setLength(index+1);
	}
	numConnections[index] = 0;//numConnections.set(0, index);//

	MString nodetype;
	IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+currentNode+"\""), nodetype));
	const liquidmaya::Shader* shader = ShaderMgr::getSingletonPtr()->getShader(nodetype.asChar());
	assert( shader );

	// Get the list of supported connections from the current node
	const MStringArray& validConnections = shader->getValidConnectionRef();
	// Get the list of up stream nodes along supported connections
	std::set<const std::string> upstreamNodes;
	for(size_t i=0; i < validConnections.length(); ++i)
	{
		const MString validConnection( validConnections[i] );
		const MString plug(currentNode+"."+validConnection);
		
		if( convertibleConnection(plug) != 0 )
		{
			MStringArray connection;
			IfMErrorWarn(MGlobal::executeCommand( ("listConnections -source on -destination off \""+plug+"\""), connection));
		
			//append connection to upstreamNodes
			for(std::size_t i=0; i<connection.length(); ++i){
				upstreamNodes.insert(connection[i].asChar());
			}
		}
	}

	// Remove duplicate nodes from the upstreamNodes
	// upstreamNodes is std::set, so no need to remove the duplicate

	//
	std::set<const std::string>::const_iterator i2 = upstreamNodes.begin();
	std::set<const std::string>::const_iterator e2 = upstreamNodes.end();
	for(; i2 != e2; ++i2)
	{
		MString node( i2->c_str() );

		if( numConnections.length()<(index+1) ){
			numConnections.setLength(index+1);
		}
		numConnections[index] += 
			getUpstreamConvertibleNodes(node, nodes, numConnections);
	}

	return 1;
}
//
void ConvertShadingNetwork::addNodeInputVariable(const MString& plug, MStringArray& inputVars)
{
	MString cmd;

	MStringArray inputPlugs;
	IfMErrorWarn(MGlobal::executeCommand( ("listConnections -plugs true \""+plug+"\""), inputPlugs));
	MString varName;
	MString inputNode;
	int inputIndex = inputVars.length();

	for(size_t i=0; i<inputPlugs.length(); ++i)
	{
		const MString inputPlug( inputPlugs[i] );

		MStringArray buffer;
		inputPlug.split('.', buffer);

		inputNode = buffer[0];

		if( nodeIsConvertible( inputNode ) )
		{
			// Ensure that the connected plug is being exported
			// (ie supported by the converter).
			MString inputAttribute = buffer[ 1 ];
			bool notConnected = true;
			
			MString nodetype;
			IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+inputNode+"\""), nodetype));
			const liquidmaya::Shader* shader = ShaderMgr::getSingletonPtr()->getShader(nodetype.asChar());
			assert( shader );
			const MStringArray& validConnections =
				shader->getValidConnectionRef();
			
			for(size_t i=0; i < validConnections.length(); ++i)
			{
				const MString connection(validConnections[i]);

				if(connection == inputAttribute){
					notConnected = false;
					break;
				}
			}
			if(notConnected == true){
				continue;
			}

			const std::string varName(boost::replace_all_copy(std::string(inputPlug.asChar()),".","_"));
			
			if( inputVars.length()<(inputIndex+1) ){
				inputVars.setLength(inputIndex+1);
			}
			inputVars[inputIndex] = varName.c_str();
			inputIndex++;
		}
	}

}
//
void ConvertShadingNetwork::addNodeOutputVariable(
	const MString& node, const MString& validConnection, 
	const MString& plug, MStringArray& outputVars,
	MStringArray& shaderData)
{
	MString cmd;

	MString type_;
	IfMErrorWarn(MGlobal::executeCommand( ("getAttr -type \""+plug+"\""), type_ ));

	const MString varName(node+"_"+validConnection);
	const int outputIndex = outputVars.length();

	MString matchedStr;
	IfMErrorWarn(MGlobal::executeCommand( ("match(\"float[0-9]*$\", \""+type_+"\")"), matchedStr));
	if( matchedStr != "" )
	{
		MString typeSize;
		IfMErrorWarn(MGlobal::executeCommand( ("match(\"[0-9]*$\", \""+type_+"\")"), typeSize));
		if(typeSize=="")
		{
			shaderData[0] += " float "+varName+";\n";
		}else if(typeSize=="3"){
			shaderData[0] += " vector "+varName+";\n";
		}else{
			shaderData[0] += " float "+varName+"["+typeSize+"];\n";
		}

		if( outputVars.length()<(outputIndex+1) ){
			outputVars.setLength(outputIndex+1);
		}
		outputVars[outputIndex] = varName;
	}

}
//
MString ConvertShadingNetwork::getNodeVariables(
	const MString& node, const MStringArray& validConnections, MStringArray& shaderData)
{
	MStringArray vars;
	MString varString;
	MStringArray inputVars;
	MStringArray outputVars;
	int connectionType = 0;

	for( std::size_t i = 0; i<validConnections.length(); ++i )
	{
		const MString validConnection(validConnections[i]);
		const MString plug(node+"."+validConnection);
		connectionType = convertibleConnection(plug);
		
		// If the connection is neither an input or output connection
		if( connectionType != 1 && connectionType != 2 )
		{
			continue;
		}

		// Get input variable
		if( connectionType == 1 )
		{
			addNodeInputVariable( plug, inputVars );
		}
		// Get output variable
		else if( connectionType == 2 ){
			addNodeOutputVariable( node, validConnection, plug,
				outputVars, shaderData );
		}
	}

	// Creates the variable string from the variable list
	//$vars = stringArrayCatenate( $inputVars, $outputVars );
	vars.clear();
	for(std::size_t i=0; i<inputVars.length(); ++i){
		vars.append(inputVars[i]);
	}
	for(std::size_t i=0; i<outputVars.length(); ++i){
		vars.append(outputVars[i]);
	}

	for(std::size_t index=0; index<vars.length(); ++index){
		varString += (index == vars.length() - 1)?(vars[index]):(vars[index]+", ");
	}

	return varString;
}
//
void ConvertShadingNetwork::decrementDownstreamConnections(
	const MString& node, const MStringArray& nodes, 
	MIntArray& numConnections, const MStringArray& validConnections
	)
{
	std::set<const std::string> downstreamNodes;

	// Get the list of down stream nodes along supported connections
	for(std::size_t i=0; i<validConnections.length(); ++i)
	{
		const MString validConnection(validConnections[i]);
		const MString plug(node+"."+validConnection);

		MStringArray con;
		IfMErrorWarn(MGlobal::executeCommand( "listConnections -source off -destination on \""+plug+"\"", con));
		for(std::size_t i=0; i<con.length(); ++i)
		{
			downstreamNodes.insert(con[i].asChar());
		}
	}
	// Remove duplicate nodes from the list
	// Because downstreamNodes is std::set, no need to remove duplicate

	// For each down stream node, decrement the number of connections
	int numNodes = nodes.length();
	std::set<const std::string>::const_iterator i = downstreamNodes.begin();
	std::set<const std::string>::const_iterator e = downstreamNodes.end();
	for( ; i != e; ++i )
	{
		MString downstreamNode( i->c_str() );
		for(int index = 0; index<numNodes; ++index)
		{
			if(downstreamNode==nodes[index])
			{
				(numConnections[index])--;
				break;
			}
		}
	}

	downstreamNodes.clear();
}
void ConvertShadingNetwork::traverseGraphAndOutputNodeFunctions( 
	const MStringArray& nodes, MIntArray& numConnections,
	MStringArray& shaderData)
{
	MString cmd;

	//test
	int n0 = nodes.length();
	int n1 = numConnections.length();

	for(size_t index = 0; index< nodes.length(); ++index)
	{
		// if the current node has all of its required inputs, then
		// write out the information for the current node and decrement
		// the number of inputs for all nodes awaiting the completion of
		// the current node
		if( numConnections[index] == 0 )
		{
			MString currentNode(nodes[index]);
			
			MString nodetype;
			IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+currentNode+"\""), nodetype));

			// write out the current node's function
			ShaderOutputMgr::getSingletonPtr()->outputUpstreamShader(currentNode.asChar());//shader->writeRSL(currentNode.asChar());

			// Get the list of supported connections from the current node			
			const liquidmaya::Shader* shader 
				= ShaderMgr::getSingletonPtr()->getShader(nodetype.asChar());
			assert( shader );
			const MStringArray& validConnections = shader->getValidConnectionRef();

			decrementDownstreamConnections( currentNode,
				nodes,
				numConnections,
				validConnections );
			
			MString vars = getNodeVariables( currentNode,
				validConnections,
				shaderData );

			// Add the current node method to the shader body
			shaderData[ 1 ] += " " + currentNode +"("+vars+");\n";
		
			// We are done with the current node
			numConnections[ index ] = -1;

			// Start back at the beginning
			index = -1;
		}
	}
}
//
void ConvertShadingNetwork::outputShaderMethod( const MStringArray& shaderData )
{
	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputShaderMethod(
		shaderData[SHADER_NAME_I].asChar(),
		shaderData[SHADER_METHOD_VARIAVLES_I].asChar(),
		shaderData[SHADER_METHOD_BODY_I].asChar()
	);

}
//
void ConvertShadingNetwork::convertShadingNetworkToRSL(const MString& startingNode, const MString& node)
{
	MString cmd;

	MStringArray nodes;
	MIntArray numConnections;

	MStringArray shaderData;
	shaderData.setLength(3);
	shaderData[SHADER_METHOD_VARIAVLES_I] = "";// shader method variables
	shaderData[SHADER_METHOD_BODY_I]      = "";// shader method body
	shaderData[SHADER_NAME_I]             = startingNode;// shader name

	getUpstreamConvertibleNodes(startingNode, nodes, numConnections);

	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputBegin(startingNode.asChar());

	// Traverse the graph outputing functions for nodes that have received all
	// of their respective inputs
	traverseGraphAndOutputNodeFunctions(nodes, numConnections, shaderData);
	
	// Output the shader method
	outputShaderMethod(shaderData);

	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputEnd();


	//...
}
//
void ConvertShadingNetwork::__export()
{
	MString cmd;

	MStringArray sel;
	IfMErrorWarn(MGlobal::executeCommand( "ls -selection -dag -shapes", sel));

	for(std::size_t i=0; i<sel.length(); ++i)
	{
		const MString node(sel[i]);

		//string $sgNodes[] = `listConnections -type "shadingEngine" -destination on ( $node + ".instObjGroups" )`;//add -type "shadingEngine" for multy renderlayers
		MStringArray sgNodes;		
		cmd = "listConnections -type \"shadingEngine\" -destination on (\""+node+"\" + \".instObjGroups\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, sgNodes));

		//string $shaders[] = `listConnections ( $sgNodes[0] + ".surfaceShader" )`;
		MStringArray shaders;
		cmd = "listConnections (\""+sgNodes[0]+"\" + \".surfaceShader\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, shaders));

		const MString startingNode(shaders[0]);

		MString nodetype;
		cmd = "nodeType \""+startingNode+"\"";
		IfMErrorWarn(MGlobal::executeCommand( cmd, nodetype));

		if(nodetype=="liquidSurface"||nodetype=="liquidVolume"||nodetype=="liquidDisplacement"){
			liquidMessage2(messageInfo, (startingNode+"'s type is "+nodetype+", no need to convert").asChar());
		}else{
			convertShadingNetworkToRSL(startingNode, node);
		}
	}

}
//

//





}//namespace liquidmaya