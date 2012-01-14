#ifndef _SHADER_OUTPUT_H_
#define _SHADER_OUTPUT_H_

namespace liquidmaya{

// Visitor Pattern
class ShaderOutputVisitor
{
public:
	ShaderOutputVisitor();
	virtual ~ShaderOutputVisitor();

	virtual void preOutput(const char* shaderNodeName) = 0;
	virtual void outputBegin(const char* shaderNodeName) = 0;
	virtual void outputUpstreamShader(const char* shaderNodeName) = 0;
	virtual void outputShaderMethod(
		const char* shaderName,
		const char* shaderMethodVariavles,
		const char* shaderMethodBody
		) = 0;
	virtual void outputEnd() = 0;
	virtual void postOutput() = 0;
	virtual void outputShadingGroup(const char* shadingGroupNode) = 0;
	//
	// @node	maya shader node name
	virtual void visitLambert(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitBlinn(const char* node) = 0;
	// @node	maya shader node name
	//virtual void visitPhong(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitFile(const char* node) = 0;
	// @node	maya shader node name
	virtual void visitPlace2dTexture(const char* node) = 0;
private:
	ShaderOutputVisitor(const ShaderOutputVisitor&);
	ShaderOutputVisitor& operator=(const ShaderOutputVisitor&);
};
//

}//namespace liquidmaya
#endif//_SHADER_OUTPUT_H_