#include "convertShadingNetwork.h"
#include "../common/mayacheck.h"
#include <liqShader.h>
#include <liqShaderFactory.h>
#include <liqlog.h>
#include "shadermgr.h"
#include "shaderOutputMgr.h"
#include "../renderermgr.h"

namespace liquidmaya{

void connectMStringArray(MString& des, const MStringArray& src)
{
	des.clear();
	for(std::size_t i=0; i<src.length(); ++i){
		des += src[ i ] + ",";
	}
}

ConvertShadingNetwork::ConvertShadingNetwork()
{
}
//
ConvertShadingNetwork::~ConvertShadingNetwork()
{

}
//

//
void ConvertShadingNetwork::exportShaderGraph()
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShaderGraph()");

	if( beforeExport() )
	{
		__export();
		afterExport();
	}

}
//
bool ConvertShadingNetwork::beforeExport()
{
	CM_TRACE_FUNC("ConvertShadingNetwork::beforeExport()");

	exportedShader.clear();
	exportedShadingGroup.clear();
	return true;
}
//
void ConvertShadingNetwork::afterExport()
{
	CM_TRACE_FUNC(" ConvertShadingNetwork::afterExport()");

}
//
bool ConvertShadingNetwork::nodeIsConvertible ( const MString& node ) const
{
	CM_TRACE_FUNC("ConvertShadingNetwork::nodeIsConvertible("<<node<<")");

	MString cmd;

	MString nodetype;
	cmd = "nodeType \""+node+"\"";
	IfMErrorWarn(MGlobal::executeCommand( cmd, nodetype));
	
	return ShaderMgr::getSingletonPtr()->hasShaderType(nodetype.asChar());
}
//
bool ConvertShadingNetwork::ensurePlugExists(const MString& plug) const
{	
	CM_TRACE_FUNC("ConvertShadingNetwork::ensurePlugExists("<<plug<<")");

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
	CM_TRACE_FUNC("ConvertShadingNetwork::convertibleConnection("<<plug<<")");

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
	CM_TRACE_FUNC("ConvertShadingNetwork::getUpstreamConvertibleNodes("<<currentNode<<", nodes, numConnections)");

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
	//std::cout<<"numConnections[]="<<numConnections<<std::endl;
	MString nodetype;
	IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+currentNode+"\""), nodetype));

	// Get the list of supported connections from the current node
	const MStringArray& validConnections =
		ShaderMgr::getSingletonPtr()->getValidConnectionRef(nodetype.asChar());
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
	//std::cout<<"numConnections[]="<<numConnections<<std::endl;
	return 1;
}
//
void ConvertShadingNetwork::addNodeInputVariable(const MString& plug, MStringArray& inputVars)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::addNodeInputVariable("<<plug<<", inputVars)");

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

			const MStringArray& validConnections =
				ShaderMgr::getSingletonPtr()->getValidConnectionRef(nodetype.asChar());
			
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
	CM_TRACE_FUNC("ConvertShadingNetwork::addNodeOutputVariable("<<node<<","<<validConnection<<","<<plug<<", outputVars, shaderData)");
	
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
			shaderData[SHADER_METHOD_VARIAVLES_I] += " float "+varName+";\n";
		}else if(typeSize=="3"){
			shaderData[SHADER_METHOD_VARIAVLES_I] += " vector "+varName+";\n";
		}else{
			shaderData[SHADER_METHOD_VARIAVLES_I] += " float "+varName+"["+typeSize+"];\n";
		}

		if( outputVars.length()<(outputIndex+1) ){
			outputVars.setLength(outputIndex+1);
		}
		outputVars[outputIndex] = varName;
	}

}
//
MString ConvertShadingNetwork::getNodeVariables(
	const MString& node, const MStringArray& validConnections, MStringArray& shaderData,
	MStringArray& inputVars, MStringArray& outputVars)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::getNodeVariables("<<node<<", validConnections, shaderData, inputVars, outputVars)");

	MStringArray vars;
	MString varString;
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
	CM_TRACE_FUNC("ConvertShadingNetwork::decrementDownstreamConnections("<<node<<", nodes, numConnections, validConnections)");

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
	//std::cout<<"numConnections[]="<<numConnections<<std::endl;
	downstreamNodes.clear();
}
void ConvertShadingNetwork::traverseGraphAndOutputNodeFunctions( 
	const MStringArray& nodes, MIntArray& numConnections,
	MStringArray& shaderData)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::traverseGraphAndOutputNodeFunctions( nodes, numConnections, shaderData)");

	MString cmd;

	//test
	int n0 = nodes.length();
	int n1 = numConnections.length();

	for(size_t index = 0; index< nodes.length(); ++index)
	{
		MString currentNode(nodes[index]);
		// if the current node has all of its required inputs, then
		// write out the information for the current node and decrement
		// the number of inputs for all nodes awaiting the completion of
		// the current node
		if( numConnections[index] == 0 )
		{
			MString nodetype;
			IfMErrorWarn(MGlobal::executeCommand( ("nodeType \""+currentNode+"\""), nodetype));

			// write out the current node's function
			ShaderOutputMgr::getSingletonPtr()->outputUpstreamShader(currentNode.asChar());//shader->writeRSL(currentNode.asChar());

			// Get the list of supported connections from the current node			
			const MStringArray& validConnections = 
				ShaderMgr::getSingletonPtr()->getValidConnectionRef(nodetype.asChar());

			decrementDownstreamConnections( currentNode,
				nodes,
				numConnections,
				validConnections );

			MStringArray inputVars; 
			MStringArray outputVars;
			MString vars = getNodeVariables( currentNode,
				validConnections,
				shaderData,
				inputVars,
				outputVars);

			// Add the current node method to the shader body
			shaderData[ SHADER_METHOD_BODY_I ] += " " + currentNode +"("+vars+");\n";
			
			// test the input and output of currentNode
			{	
				MString inputVarsStr; 
				MString outputVarsStr;
				connectMStringArray(inputVarsStr, inputVars);
				connectMStringArray(outputVarsStr, outputVars);
				shaderData[ SHADER_METHOD_BODY_I ] += "//input: " + inputVarsStr +"\n";
				shaderData[ SHADER_METHOD_BODY_I ] += "//output:" + outputVarsStr +"\n\n";
			}

			// We are done with the current node
			numConnections[ index ] = -1;

			// Start back at the beginning
			index = -1;
		}
		//std::cout<<"numConnections[]="<<numConnections<<std::endl;
	}
}
//
void ConvertShadingNetwork::outputShaderMethod( const MStringArray& shaderData )
{
	CM_TRACE_FUNC("ConvertShadingNetwork::outputShaderMethod(shaderData)");

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
	CM_TRACE_FUNC("ConvertShadingNetwork::convertShadingNetworkToRSL("<<startingNode<<","<<node<<")");

	MString cmd;

	MStringArray nodes;
	MIntArray numConnections;

	MStringArray shaderData;
	shaderData.setLength(3);
	shaderData[SHADER_METHOD_VARIAVLES_I] = "";// shader method variables
	shaderData[SHADER_METHOD_BODY_I]      = "";// shader method body
	shaderData[SHADER_NAME_I]             = startingNode;// shader name

	getUpstreamConvertibleNodes(startingNode, nodes, numConnections);
	//std::cout<<"numConnections[]="<<numConnections<<std::endl;
	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		preOutput(startingNode.asChar());
	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputBegin(startingNode.asChar());

	// Traverse the graph outputing functions for nodes that have received all
	// of their respective inputs
	traverseGraphAndOutputNodeFunctions(nodes, numConnections, shaderData);
	
	// Output the shader method
	outputShaderMethod(shaderData);

	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputEnd();
	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		postOutput();

	//...
}
//
void ConvertShadingNetwork::__export()
{
	CM_TRACE_FUNC("ConvertShadingNetwork::__export()");

	MString cmd;

	MStringArray geometryArray;
	//IfMErrorWarn(MGlobal::executeCommand( "ls -selection -dag -shapes", geometryArray));
	IfMErrorWarn(MGlobal::executeCommand( "ls -geometry", geometryArray));

	if(geometryArray.length()==0){
		liquidMessage2(messageWarning ,"no shape is selected, no shader will be exported.\n");
	}

	for(std::size_t i=0; i<geometryArray.length(); ++i)
	{
		const MString node(geometryArray[i]);

		//string $sgNodes[] = `listConnections -type "shadingEngine" -destination on ( $node + ".instObjGroups" )`;//add -type "shadingEngine" for multy renderlayers
		MStringArray sgNodes;		
		cmd = "listConnections -type \"shadingEngine\" -destination on (\""+node+"\" + \".instObjGroups\")";
		IfMErrorWarn(MGlobal::executeCommand( cmd, sgNodes));

		if( sgNodes.length() !=0 )
		{
			if( canShadingGroupExported(sgNodes[0]) )
			{
				//1.shaders must be exported before shading group
				{
					//get the shader plugs in ShadingGroup
					std::vector<std::string> plugs;
					liquid::RendererMgr::getInstancePtr()->
						getRenderer()->getValidShaderPlugsInShadingGroup(plugs);
					//export the plugs
					for_each(plugs.begin(), plugs.end(),
						boost::bind( &ConvertShadingNetwork::exportShaderInShadingGroup, this, node, sgNodes[0], _1 )
					);
				}
				//2.begin
				exportShadingGroupBegin(sgNodes[0]);
				//3.export shading group
				outputShadingGroup(sgNodes[0]);
				//4.end
				exportShadingGroupEnd(sgNodes[0]);
			}
		}else{
			liquidMessage2(messageInfo, ("\""+node +"\" has not shading group, skip.").asChar() );
		}
	}

}
//
void ConvertShadingNetwork::outputShadingGroup(const MString& shadingGroupNode)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::outputShadingGroup("<<shadingGroupNode<<")");

	liquidmaya::ShaderOutputMgr::getSingletonPtr()->
		outputShadingGroup(shadingGroupNode.asChar());
}
//
void ConvertShadingNetwork::exportShaderInShadingGroup(
	const MString& node, 
	const MString& sgNode, 
	const std::string& plug_)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShaderInShadingGroup("<<node<<","<<sgNode<<","<<plug_<<")");

	const MString plug(plug_.c_str());
	MString cmd;

	int isShaderPlugExist;
	cmd = "attributeQuery -node \""+sgNode+"\" -ex \""+plug+"\"";
	IfMErrorMsgWarn(MGlobal::executeCommand( cmd, isShaderPlugExist), cmd);
	if(isShaderPlugExist)
	{
		MStringArray shaders;
		cmd = "listConnections (\""+sgNode+"\" + \"."+plug+"\")";
		IfMErrorMsgWarn(MGlobal::executeCommand( cmd, shaders), cmd);

		if( shaders.length() != 0 )
		{
			const MString startingNode(shaders[0]);

			if( canShaderExported(startingNode) )
			{
				//1.begin
				exportShaderBegin(startingNode);

				//2.export shader
				MString nodetype;
				cmd = "nodeType \""+startingNode+"\"";
				IfMErrorWarn(MGlobal::executeCommand( cmd, nodetype));

				if(nodetype=="liquidSurface"||nodetype=="liquidVolume"||nodetype=="liquidDisplacement"){
					//liquidMessage2(messageInfo, (startingNode+"'s type is "+nodetype+", no need to convert").asChar());
					MObject shaderObj;
					getDependNodeByName( shaderObj,startingNode.asChar());
					liqShader &currentShader = liqShaderFactory::instance().getShader( shaderObj );
					currentShader.write();
				}else{
					convertShadingNetworkToRSL(startingNode, node);
				}

				//3.end
				exportShaderEnd(startingNode);
			}
		}
	}
}
//
bool ConvertShadingNetwork::canShaderExported(const MString& shaderName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::canShaderExported("<<shaderName<<")");

	if(shaderName.length()==0)
	{
		liquidMessage2(messageInfo, ("shader name is empty,") );
		return false;
	}
	if(exportedShader.end() != std::find(exportedShader.begin(), exportedShader.end(), shaderName) )
	{
		liquidMessage2(messageInfo, ("\""+shaderName+"\" is already exported, skip.").asChar() );
		return false;
	}

	return true;
}
void ConvertShadingNetwork::exportShaderBegin(const MString& shaderName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShaderBegin("<<shaderName<<")");
}
//void ConvertShadingNetwork::exportShader(const MString& shaderName){}
void ConvertShadingNetwork::exportShaderEnd(const MString& shaderName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShaderEnd("<<shaderName<<")");
	// if shaderName already exists in exportedShader, 
	//canShaderExported() will return false, and exportShaderEnd() will not called.
	exportedShader.push_back(shaderName);
}
//
bool ConvertShadingNetwork::canShadingGroupExported(const MString& shadingGroupName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::canShadingGroupExported("<<shadingGroupName<<")");

	if(shadingGroupName.length()==0)
	{
		liquidMessage2(messageInfo, ("shading group name is empty,") );
		return false;
	}
	if(exportedShadingGroup.end() != std::find(exportedShadingGroup.begin(), exportedShadingGroup.end(), shadingGroupName) )
	{
		liquidMessage2(messageInfo, ("\""+shadingGroupName+"\" is already exported, skip.").asChar() );
		return false;
	}

	return true;
}
void ConvertShadingNetwork::exportShadingGroupBegin(const MString& shadingGroupName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShadingGroupBegin("<<shadingGroupName<<")");
}
//void ConvertShadingNetwork::exportShadingGroup(const MString& shadingGroupName){}
void ConvertShadingNetwork::exportShadingGroupEnd(const MString& shadingGroupName)
{
	CM_TRACE_FUNC("ConvertShadingNetwork::exportShadingGroupEnd("<<shadingGroupName<<")");
	// if shadingGroupName already exists in exportedShadingGroup, 
	//canShadingGroupExported() will return false, and exportShadingGroupEnd() will not called.
	exportedShadingGroup.push_back(shadingGroupName);
}

}//namespace liquidmaya