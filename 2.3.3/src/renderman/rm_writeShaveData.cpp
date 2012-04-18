#include "rm_renderer.h"
#include <liqRibShaveData.h>
#include <liqGlobalVariable.h>
#include "rm_helper.h"
#include "../common/prerequest_maya.h"
#include "../common/mayacheck.h"

namespace renderman
{
	//
	void Renderer::write(
		/*const*/ liqRibShaveData* pData,
		const MString &ribFileName,
		const structJob &currentJob,
		const bool bReference)
	{
		CM_TRACE_FUNC("Renderer::write("<<pData->getFullPathName()<<","<<ribFileName<<","<<currentJob.name<<",ref="<<bReference<<")");

		assert(liqglo.m_ribFileOpen&&"rm_writeShaveData.cpp");

	 	if( !bReference ){//write data at first time
			if( !currentJob.isShadow ){
				assert(pData->getRibFileFullPath().length()==0&&"rm_writeShaveData.cpp");
			}
			pData->setRibFileFullPath(ribFileName);

			//1)make a reference
			RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );

			//2)call shave command to write the rib file(not support motion blur)
			MString cmd("shaveWriteRib -hairNode \""+pData->objDagPath.partialPathName()+"\" \""+pData->getRibFileFullPath()+"\";");
			if( MFAIL(MGlobal::executeCommand(cmd, true) )){
				liquidMessage2(messageError,"write shave rib file fail:%s", cmd.asChar());
			}
	 	}else{
	 		//write the reference
	 		assert(pData->getRibFileFullPath() == ribFileName);
	 		RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
	 	}
	}
	//

}//namespace renderman
