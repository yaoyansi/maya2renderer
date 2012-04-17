#include "shaderOutputRSL.h"
#include "../common/mayacheck.h"
#include "ri_interface.h"
#include <trace/trace.hpp>

namespace RSL
{
//

//
// @node	mr shader node name
void Visitor::visit_mib_amb_occlusion(const char* node)
{
	CM_TRACE_FUNC("Visitor::visit_mib_amb_occlusion("<<node<<")");

	OutputHelper o(RSLfile);
	o.beginRSL(node);

	o.addRSLVariable("float",	"i_samples",	"samples",		node);
	o.addRSLVariable("color",	"i_bright",		"bright",		node);
	o.addRSLVariable("color",	"i_dark",		"dark",			node);
	o.addRSLVariable("float",	"i_spread",		"spread",		node);
	o.addRSLVariable("float",	"i_max_distance","max_distance",node);
	o.addRSLVariable("float",	"i_reflective",	"reflective",	node);
	o.addRSLVariable("vector",	"o_outValue",	"outValue",		node);

	o.addToRSL( 
		"extern point P;\n"
		"extern normal N;\n"
		"extern vector I;\n"
		"if(i_max_distance < 0.0001){//If it is zero, the entire scene is sampled\n"
		"      i_max_distance = 1.0e38;\n"
		"}\n"
		"\n"
		"normal Nn = faceforward(normalize(N), I);\n"
		"\n"
		"if(i_reflective != 0)				\n"
		"	Nn = normal reflect( I, Nn );	\n"
		"\n"
		"float occ= 1 - occlusion(P, Nn, i_samples,				\n"
		"                        \"adaptive\", 1,					\n"
		"                        \"maxdist\", i_max_distance,		\n"
		"                        \"coneangle\", i_spread * PI / 2);	\n"
		"\n"
		"o_outValue = vector mix( i_dark, i_bright, occ );				\n"
	);

	o.endRSL();
}

}//namespace RSL