#include "shaderValidConnection.h"
#include <liqlog.h>

namespace liquidmaya
{

	void ShaderValidConnection::setValidConnection_mi()
	{
		MStringArray validConnection;
		//mib_amb_occlusion
		validConnection.clear();
		validConnection.append("samples");
		validConnection.append("bright");
		validConnection.append("dark");
		validConnection.append("spread");
		validConnection.append("max_distance");
		validConnection.append("reflective");
// 		validConnection.append("output_mode");
// 		validConnection.append("occlusion_in_alpha");
// 		validConnection.append("falloff");
// 		validConnection.append("id_inclexcl");
// 		validConnection.append("id_nonself");
		validConnection.append("outValue");
		validConnectionMap.insert(std::make_pair("mib_amb_occlusion", validConnection));	

	}
}//namespace liquidmaya