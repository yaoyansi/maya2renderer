#ifndef _CONVERT_SHADING_NETWORK_H_
#define _CONVERT_SHADING_NETWORK_H_

#include "../common/prerequest_maya.h"
#include "../common/prerequest_std.h"

namespace liquidmaya
{

class ConvertShadingNetwork
{
public:
	ConvertShadingNetwork();
	virtual ~ConvertShadingNetwork();

	void exportShaderGraph();
	bool beforeExport();
	void __export();
	void afterExport();

	//--------------------------------------------------------------------
	// Check to see if we know how to convert this node to RSL.
	//--------------------------------------------------------------------
	bool nodeIsConvertible( const MString& node ) const;

	//--------------------------------------------------------------------
	// Validate that a given plug exists.
	//--------------------------------------------------------------------
	bool ensurePlugExists(const MString& plug) const;

	//--------------------------------------------------------------------
	// Check to see if a plug (node and attribute) is connected to a node
	// that we're able to convert to RSL and, if so, what the type of
	// connection is. Preference is given to outgoing connections.
	//
	// 2 = outgoing (and possible incoming) connection
	// 1 = incoming connection
	// 0 = no connection
	//--------------------------------------------------------------------
	int convertibleConnection(const MString& plug) const;

	//--------------------------------------------------------------------
	// Generate a list of upstream nodes that we can convert to RSL, and
	// note the number of incoming connections for each.
	//--------------------------------------------------------------------
	int getUpstreamConvertibleNodes ( const MString& currentNode, 
		MStringArray& nodes, MIntArray& numConnections);

	//--------------------------------------------------------------------
	// Adds all of the valid input nodes for the given plug to the input
	// variable list.
	//--------------------------------------------------------------------
	void addNodeInputVariable(const MString& plug, MStringArray& inputVars);
	
	//--------------------------------------------------------------------
	// Adds all of the valid output nodes for the given plug to the output
	// variable list.  Also adds the variables to the shader method
	// variable list.
	//--------------------------------------------------------------------
	void addNodeOutputVariable(
		const MString& node, const MString& validConnection, 
		const MString& plug, MStringArray& outputVars);
	
	//--------------------------------------------------------------------
	// Given a convertible node and a set of valid connections for that
	// node, this function returns a string consisting of the input and
	// output variables for the this node.
	//--------------------------------------------------------------------
	MString getNodeVariables(
		const MString& node, const MStringArray& validConnection,
		MStringArray& inputVars, MStringArray& outputVars);

	//--------------------------------------------------------------------
	// Given a convertible node and its valid connections, iterates over
	// all of the convertible nodes downstream of it and decrements their
	// number of connections.
	//--------------------------------------------------------------------
	void decrementDownstreamConnections(
		const MString& node, const MStringArray& nodes, 
		MIntArray& numConnections, const MStringArray& validConnections);
	
	//--------------------------------------------------------------------
	// traverse the graph outputing functions for nodes that have received
	// all of their respective inputs.
	//--------------------------------------------------------------------
	void traverseGraphAndOutputNodeFunctions( const MStringArray& nodes, 
		MIntArray& numConnections);
		
	//--------------------------------------------------------------------
	// Outputs the shader method.
	//--------------------------------------------------------------------
	void outputShaderMethod();

	//--------------------------------------------------------------------
	// Convert a network of shading nodes to RSL.
	//--------------------------------------------------------------------
	void convertShadingNetworkToRSL(const MString& startingNode, const MString& node);

	void outputShadingGroup(const MString& shadingGroupNode);


protected:
	void exportShaderInShadingGroup(
		const MString& node, //geometry node(can be removed in future)
		const MString& sgNode, //shading group node
		const std::string& plug_);//plug in shading group, e.g. surface, displacement, volume,...

	//
	bool canShaderExported(const MString& shaderName);
	void exportShaderBegin(const MString& shaderName);
	//void exportShader(const MString& shaderName);
	void exportShaderEnd(const MString& shaderName);
	std::vector<MString> exportedShader;

	//
	bool canShadingGroupExported(const MString& shadingGroupName);
	void exportShadingGroupBegin(const MString& shadingGroupName);
	//void exportShadingGroup(const MString& shadingGroupName);
	void exportShadingGroupEnd(const MString& shadingGroupName);
	std::vector<MString> exportedShadingGroup;

private:
	ConvertShadingNetwork(const ConvertShadingNetwork&);
	ConvertShadingNetwork& operator=(const ConvertShadingNetwork&);
};

}//namespace liquidmaya
#endif//_CONVERT_SHADING_NETWORK_H_