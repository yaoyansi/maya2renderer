#include "er_renderer.h"
#include <liqRibPfxData.h>
#include "../common/prerequest_maya.h"
#include "../common/mayacheck.h"
#include "ercall.h"
#include "log_helper.h"
//#include <liqRibNode.h>
#include <liqRibTranslator.h>
#include <liqGlobalHelpers.h>
#include <eiCORE/ei_data_table.h>
#include <liqRibShaveData.h>
#include<maya/shaveAPI.h>
#include<maya/shaveItHair.h>

namespace elvishray
{
	void Renderer::write(
		/*const*/ liqRibShaveData* pData,
		const MString &fileName, 
		const structJob &currentJob,
		const bool bReference)
	{
		CM_TRACE_FUNC("Renderer::write("<<pData->getFullPathName()<<","<<fileName<<","<<currentJob.name<<",ref="<<bReference<<")");

		if( !bReference ){//write data at first time
			assert(pData->getRibFileFullPath().length()==0);
			pData->setRibFileFullPath(fileName);

// 			renderman::Helper o;
// 			o.RiBeginRef(pData->getRibFileFullPath().asChar());
 			_write_shavehair(pData, currentJob);
// 			o.RiEndRef();

		}else{
			//write the reference
			assert(pData->getRibFileFullPath() == fileName);
//			RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
		}
	}
	//
	void Renderer::_write_shavehair(liqRibShaveData* pData, const structJob &currentJob__)
	{
		CM_TRACE_FUNC("_write_shavehair("<<pData->getFullPathName()<<","<<currentJob__.name<<")");
		//

		//
 		liqRibNodePtr ribNode__ = liqRibTranslator::getInstancePtr()->htable->find(
 			pData->objDagPath.fullPathName(), 
 			pData->objDagPath,
 			MRT_Unknown
 			);
 		assert( ribNode__!=0 );
 		assert( ribNode__->path().fullPathName() == pData->objDagPath.fullPathName() );

		const bool bMotionBlur =
			ribNode__->motion.transformationBlur &&
			( ribNode__->object( 1 ) ) &&
			//( ribNode__->object(0)->type != MRT_Locator ) && // Why the fuck do we not allow motion blur for locators?
			( !currentJob__.isShadow || currentJob__.deepShadows );

		bool bGeometryMotion = 
			liqglo.liqglo_doDef 
			&& bMotionBlur
			&& ( ribNode__->object(0)->type != MRT_RibGen );

		unsigned int sample_first = 0;
		unsigned int sample_last = bGeometryMotion? (liqglo.liqglo_motionSamples - 1):sample_first;

		_s("\n// Renderer::exportOneGeometry_Mesh("<<ribNode__->name.asChar()<<","<<sample_first<<","<<sample_last<<")");

		const liqRibDataPtr data = ribNode__->object(sample_first)->getDataPtr();

//
		MStatus status;


		MFnDagNode fnDN(data->objDagPath, &status);
		IfErrorWarn(status);

		// geometry data (shape)
		_s("\n//############################### shave hair #");
		_s("//shape full path name="<<data->getFullPathName());
#ifdef TRANSFORM_SHAPE_PAIR
		const std::string objectName(ribNode__->name.asChar());//shape
#else// SHAPE SHAPE_object PAIR
		const std::string objectName(getObjectName(ribNode__->name.asChar()));//shape+"_object"
#endif
		const eiIndex degree = 3;
		_S( ei_object( objectName.c_str(), "hair" ) );
		_s("{");
			_S( ei_degree(degree) );
			this->generate_shavehair(ribNode__, pData, degree);
		_s("}//"<<objectName);
		_S( ei_end_object() );
	}
	//
	void Renderer::generate_shavehair(liqRibNodePtr &ribNode__, liqRibShaveData* pData, const int degree)
	{
		CM_TRACE_FUNC("generate_pfxhair("<<ribNode__->getTransformNodeFullPath()<<")");

		MStatus status;

		shaveAPI::HairInfo hairInfo;
		status = shaveAPI::exportAllHair(&hairInfo);
		if(MFAIL(status)){
			liquidMessage2(messageError,"shaveAPI::exportAllHair(&hairInfo)=%s", status.errorString().asChar());
			return;
		}

		_d( eiDatabase *db = ei_context_database(CONTEXT) );

		_d( eiTag vtx_list );
		_d( vtx_list = ei_tab(EI_DATA_TYPE_VECTOR4, 100000) );
		_d( ei_end_tab() );
		_d( eiTag hair_list );
		_d( hair_list = ei_tab(EI_DATA_TYPE_INDEX, 100000) );
		_d( ei_end_tab() );

	
		//for each hair
		for(int strand = 0; strand < hairInfo.numHairs; strand++ )
		{
			_s("//strand="<<strand);
			eiScalar rootRadii = hairInfo.rootRadii[strand];

			_d( eiInt index ); 
			_d( index = ei_data_table_size(db, vtx_list) );
			_d( ei_data_table_push_back(db, hair_list, &index) );//start vertex index of this hair in vtx_list

			eiIndex num_vertex = hairInfo.hairEndIndices[strand] 
			                   - hairInfo.hairStartIndices[strand];
			_s("//num_vertex="<<num_vertex);
			_d( eiIndex num_segments );
			num_segments = (num_vertex-1)/degree; _s("num_segments="<< num_segments<<";");
			_d( ei_data_table_push_back(db, hair_list, &num_segments) );//how many segments this hair contains 
			
			_d( eiVector4 vtx );
			//for each vertex on this hair
			for(eiIndex i = hairInfo.hairStartIndices[strand];
				        i < hairInfo.hairEndIndices[strand]; i++)
			{
				_s("//vertex="<<i);
				int vert = hairInfo.hairVertices[i];
					my_set_eiVector4("vtx", vtx, 
						hairInfo.vertices[vert].x,
						hairInfo.vertices[vert].y, 
						hairInfo.vertices[vert].z, 
						rootRadii*(hairInfo.hairEndIndices[strand]-1-i)/num_vertex);
					_d( ei_data_table_push_back(db, vtx_list, &vtx) );

			}//for( ; pOn < pfxVerts.length(); pOn++ ) 
		}//for lineon
		_d( ei_vertex_list(vtx_list) );
		_d( ei_hair_list(hair_list) );
	}

}//namespace elvishray
