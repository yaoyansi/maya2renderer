#include "er_renderer.h"
#include <liqRibPfxHairData.h>
#include "../common/prerequest_maya.h"
#include "../common/mayacheck.h"
#include "ercall.h"
#include "log_helper.h"
//#include <liqRibNode.h>
#include <liqRibTranslator.h>
#include <liqGlobalHelpers.h>
#include <eiCORE/ei_data_table.h>

namespace elvishray
{
	void Renderer::write(
		/*const*/ liqRibPfxHairData* pData,
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
 			_write_pfxhair(pData, currentJob);
// 			o.RiEndRef();

		}else{
			//write the reference
			assert(pData->getRibFileFullPath() == fileName);
//			RiReadArchive( const_cast< RtToken >( pData->getRibFileFullPath().asChar() ), NULL, RI_NULL );
		}
	}
	//
	void Renderer::_write_pfxhair(liqRibPfxHairData* pData, const structJob &currentJob__)
	{
		CM_TRACE_FUNC("_write("<<pData->getFullPathName()<<","<<currentJob__.name<<")");
		//
		if( pData->isEmpty() ) 
		{
			liquidMessage2(messageWarning, "pfxHair is empty: %s",  pData->getFullPathName());
			return;
		}

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


//		//
		MStatus status;

		int degree;
		MFnDagNode fnDN(data->objDagPath);
		IfMErrorWarn( liquidGetPlugValue(fnDN, "degree", degree, status) );
//
//		MIntArray triangleCounts,triangleVertices;
//		IfMErrorWarn(fnMesh.getTriangles(triangleCounts, triangleVertices));
//
//		MString currentUVsetName;
//		IfMErrorWarn(fnMesh.getCurrentUVSetName(currentUVsetName));
//
		// geometry data (shape)
		_s("\n//############################### mesh #");
		_s("//shape full path name="<<data->getFullPathName());
#ifdef TRANSFORM_SHAPE_PAIR
		const std::string objectName(ribNode__->name.asChar());//shape
#else// SHAPE SHAPE_object PAIR
		const std::string objectName(getObjectName(ribNode__->name.asChar()));//shape+"_object"
#endif
		_S( ei_object( objectName.c_str(), "hair" ) );
		_s("{");
			_d( ei_degree(degree) );
			this->generate_pfxhair(ribNode__, pData, degree);
//		_d( eiTag tag );
//
//		//vertex position
//		_s("//### vertex positions, fnMesh.numVertices()="<<fnMesh.numVertices() );
//		_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
//		_S( ei_pos_list( tag ) );
//
//		//_exportVertexFromDagNode(fnMesh);
//		_exportVertexFromNodePlug(ribNode__, sample_first);
//
//		_S( ei_end_tab() );
//
//		{//deform motion
//			if( sample_first != sample_last )
//			{
//				_s("//### vertex deform positions, " );
//				_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
//				_S( ei_motion_pos_list( tag ) );
//
//				_exportVertexFromNodePlug(ribNode__, sample_last);
//
//				_S( ei_end_tab() );
//			}
//		}
//
//// 		_s("//### vertex color");
//// 		for(int i=0; i<position.length(); i++)
//// 		{
//// 			_S( ei_vertex(i) );
//// 			//_S( ei_variable_color( "Cs", color( 1.0f, 0.0f, 1.0f ) ) );
//// 		}
//
//		// get normal for each vertex
//		// but the render result seems very weird, see test/test_er_light/output_img_std/er_pointlight.perspShape.1.elvishray_vertex_normal.bmp
//		// so I ommit this section temporarily.
//		_s("//vertex normals are not output temporarily.");
//		if(fnMesh.numVertices() == fnMesh.numNormals())//smooth normal, like a sphere
//		{
//			_s("//### N");
//			_d( tag = eiNULL_TAG );
//			_S( ei_declare("N", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
//			_d( tag = ei_tab(EI_DATA_TYPE_VECTOR, 1024) )
//			_S( ei_variable("N", &tag) );
//			MVector nml;
//			for(size_t i = 0; i<fnMesh.numVertices(); ++i)
//			{
//				IfMErrorWarn(fnMesh.getVertexNormal(i, false, nml, MSpace::kObject));
//				_S( ei_tab_add_vector(nml.x, nml.y, nml.z) );
//			}
//			_S( ei_end_tab() );
//		}else{//sharp edge, like a cube
//			// in this case, like a cube, a vertex has a specified normal corresponding to each adjacent polygon.
//			// but elvishray's only allow a vertex to be assigned only one normal.
//			// so I can't generate the normal list for this case.
//		}
//
//		if( currentUVsetName.length() != 0 )//there is a current uv set
//		{
//			MFloatArray u_coords;
//			MFloatArray v_coords;
//
//			IfMErrorWarn( fnMesh.getUVs(u_coords,v_coords,&currentUVsetName) );
//			_s("//### UV("<<currentUVsetName<<"), size="<< fnMesh.numUVs(currentUVsetName) );
//			// u
//			_d( tag = eiNULL_TAG );
//			_S( ei_declare("u", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
//			_d( tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024) )
//			_S( ei_variable("u", &tag) );
//			for(size_t i = 0; i<fnMesh.numUVs(currentUVsetName); ++i)
//			{
//				_S( ei_tab_add_scalar(u_coords[i]) );
//			}
//			_S( ei_end_tab() );
//			// v
//			_d( tag = eiNULL_TAG );
//			_S( ei_declare("v", eiVARYING, EI_DATA_TYPE_TAG, &tag) );
//			_d( tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024) )
//			_S( ei_variable("v", &tag) );
//			for(size_t i = 0; i<fnMesh.numUVs(currentUVsetName); ++i)
//			{
//				_S( ei_tab_add_scalar(v_coords[i]) );
//			}
//			_S( ei_end_tab() );
//		}
//
//		_s("//### triangles, size="<< triangleCounts);
//		_d( tag = ei_tab(EI_DATA_TYPE_INDEX, 1024) )
//		_S( ei_triangle_list( tag ) );
//		for(size_t i=0; i<triangleVertices.length(); i=i+3)
//		{
//			_S( ei_tab_add_index(triangleVertices[i])); 
//			_S( ei_tab_add_index(triangleVertices[i+1])); 
//			_S( ei_tab_add_index(triangleVertices[i+2])); 
//		}
//		_S( ei_end_tab() );
		_s("}//"<<objectName);
		_S( ei_end_object() );
	}
	//
	static eiIndex getSegment(const eiIndex degree) 
	{
		eiIndex ret = 0;
		switch(degree)
		{
		case 1: case 2: case 3: 
			ret = degree; break;
		default:
			liquidMessage2(messageError, "invalid pfxhair degree:%d", degree);
		}
		return ret;
	}
	void Renderer::generate_pfxhair(liqRibNodePtr &ribNode__, liqRibPfxHairData* phair, const int degree)
	{
		CM_TRACE_FUNC("generate_pfxhair("<<ribNode__->getTransformNodeFullPath()<<")");

		MStatus status;
		MFnPfxGeometry pfxhair(phair->objDagPath, &status);
		IfMErrorWarn(status);



		MRenderLineArray profileArray;
		MRenderLineArray creaseArray;
		MRenderLineArray intersectionArray;
		MRenderLineArray copy;

		bool doLines          = true;
		bool doTwist          = true;
		bool doWidth          = true;
		bool doFlatness       = false;
		bool doParameter      = false;
		bool doColor          = true;
		bool doIncandescence  = false;
		bool doTransparency   = true;
		bool doWorldSpace     = false;

		IfMErrorWarn( pfxhair.getLineData( profileArray, creaseArray, intersectionArray, doLines, doTwist, doWidth, doFlatness, doParameter, doColor, doIncandescence, doTransparency, doWorldSpace) );



		_d( eiDatabase *db = ei_context_database(CONTEXT) );
		eiIndex num_segments = getSegment(degree);

		_d( eiTag vtx_list );
		_d( vtx_list = ei_tab(EI_DATA_TYPE_VECTOR4, 100000) );
		_d( ei_end_tab() );
		_d( eiTag hair_list );
		_d( hair_list = ei_tab(EI_DATA_TYPE_INDEX, 100000) );
		_d( ei_end_tab() );

		for (eiInt j = 0; j < phair->ncurves; ++j)
		{
			_d( eiInt index ); 
			_d( index = ei_data_table_size(db, vtx_list) );
			_d( ei_data_table_push_back(db, hair_list, &index) );//start vertex index of this hair in vtx_list

			MRenderLine theLine( profileArray.renderLine( j, &status ) );
			IfMErrorWarn(status);

			const MVectorArray& vertex( theLine.getLine() );

			_d( eiIndex nverts = vertex.length() + 2 );
            _d( ei_data_table_push_back(db, hair_list, &nverts) );//how many segments this hair contains 
			
			//first vertex
			unsigned int vertIndex = 0;
			{
				eiVector4	vtx;
				vtx.x = vertex[ vertIndex ].x;
				vtx.y = vertex[ vertIndex ].y;
				vtx.z = vertex[ vertIndex ].z;
				vtx.w = 0.01f;
				_d( ei_data_table_push_back(db, vtx_list, &vtx) );
			}
			for ( ; vertIndex < vertex.length(); vertIndex++ )
			{
				{
					eiVector4	vtx;
					vtx.x = vertex[ vertIndex ].x;
					vtx.y = vertex[ vertIndex ].y;
					vtx.z = vertex[ vertIndex ].z;
					vtx.w = 0.01f;
					_d( ei_data_table_push_back(db, vtx_list, &vtx) );
				}
			}
			//tail vertex
			{
				eiVector4	vtx;
				vtx.x = vertex[ vertIndex-1 ].x;
				vtx.y = vertex[ vertIndex-1 ].y;
				vtx.z = vertex[ vertIndex-1 ].z;
				vtx.w = 0.01f;
				_d( ei_data_table_push_back(db, vtx_list, &vtx) );
			}
		}

		_d( ei_vertex_list(vtx_list) );
		_d( ei_hair_list(hair_list) );

	}
}//namespace elvishray
