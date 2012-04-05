#include "rm_helper.h"

#include "../common/prerequest_maya.h"
#include "liqGlobalHelpers.h"
#include <liqRibTranslator.h>

namespace renderman
{
	Helper::Helper()
	{

	}
	//
	Helper::Helper(const std::string& ribFile)
		:m_ribFile(ribFile)
	{

	}
	Helper::~Helper()
	{

	}
	//
	void Helper::RiBeginRef(const std::string& ribFile)
	{
		CM_TRACE_FUNC("Helper::RiBeginRef("<<ribFile<<")");

		m_ribFile = ribFile;

		//if(m_ribFile=="E:/MyDocuments/maya/projects/default/rib/_Man_JAP_Man_JapSkeleton_Man_hips_Man_spine_Man_spine1_Man_xxy_Man_xxx_Man_leftShoulder_Man_leftArm_Man_leftForearm_Man_leftForeArmRoll_Man_leftHand_Man_joint13_Man_leftHandPinky1_Man_leftHandPinky2_Man_leftHandPinky3_Man_pCube11_Man_pCubeShape11.19.rib"){
		//}
		if(m_ribFile.size()>=255){
			RiArchiveRecord( RI_COMMENT, "ribfile path name is too long(>=255), don't output to file %s", m_ribFile.c_str() );
			m_ribFile.clear();
		}

		//if m_ribFileFullPath is "", write the data into the current rib file.
		if( m_ribFile != "" ){
			//log
			RiArchiveRecord( RI_COMMENT, "output: %s", m_ribFile.c_str() );
			//write the data into another rib file.
			m_contex = RiGetContext();//push context
			liquidMessage("output geometry rib: "+ std::string(m_ribFile.c_str()) , messageInfo);
			RiBegin( const_cast< RtToken >( m_ribFile.c_str() ) );
		}
	}
	//
	void Helper::RiEndRef()
	{
		CM_TRACE_FUNC("Helper::RiEndRef()");
		
		//if(m_ribFile=="E:/MyDocuments/maya/projects/default/rib/_Man_JAP_Man_JapSkeleton_Man_hips_Man_spine_Man_spine1_Man_xxy_Man_xxx_Man_leftShoulder_Man_leftArm_Man_leftForearm_Man_leftForeArmRoll_Man_leftHand_Man_joint13_Man_leftHandPinky1_Man_leftHandPinky2_Man_leftHandPinky3_Man_pCube11_Man_pCubeShape11.19.rib"){
		//	printf("getit");
		//}

		if( m_ribFile != "" ){
			RiEnd();
			RiContext(m_contex);//pop context
		}
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	RibDataExportHelper::RibDataExportHelper(){}
	RibDataExportHelper::~RibDataExportHelper(){}


}