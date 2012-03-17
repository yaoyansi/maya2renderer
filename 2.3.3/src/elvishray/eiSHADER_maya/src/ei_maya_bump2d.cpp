/* 
* Copyright 2010 elvish render Team
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

* http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <eiAPI/ei_shaderx.h>
#include "common/my_math.h"

SURFACE(maya_bump2d)
	// Inputs
	PARAM(scalar, bumpValue);
	PARAM(scalar, bumpDepth);
	PARAM(eiIndex,bumpInterp);
	PARAM(scalar, bumpFilter);
	PARAM(scalar, bumpFilterOffset);
	PARAM(normal, normalCamera);
	PARAM(normal, bumpNormal);
	// Outputs
	PARAM(normal, outNormal);

	void parameters(int pid)
	{
		// Inputs
		DECLARE_SCALAR(bumpValue,			0.0f);
		DECLARE_SCALAR(bumpDepth,			1.0f);
		DECLARE_INDEX(bumpInterp,			0);
		DECLARE_SCALAR(bumpFilter,			1.0f);
		DECLARE_SCALAR(bumpFilterOffset,	0.0f);
		DECLARE_NORMAL(normalCamera,		0.0f, 0.0f, 1.0f);
		DECLARE_NORMAL(bumpNormal,			-1.0f, -1.0f, -1.0f);
		// Outputs		
		DECLARE_NORMAL(outNormal,			0.0f, 0.0f, 1.0f);
	}

	void init()
	{
	}

	void exit()
	{
	}
	void do_bump_map(
		//const eiScalar i_bumpValue,
		//const eiScalar i_bumpDepth,
		const normal& i_normalCamera,
		normal& o_outNormal )
	{
		eiScalar LOW = -1.0f, HEIGHT=1.0f;
		eiScalar offset = clamp(bumpValue(), LOW, HEIGHT) * abs(bumpDepth());

		//Du_offset=d(offset)/du, Dv_offset=d(offset)/dv
		eiScalar Du_offset, Dv_offset;
		eiScalar DbumpValue_du, DbumpValue_dv;
		eiScalar DbumpDepth_du, DbumpDepth_dv;		
		Du(bumpValue, DbumpValue_du);
		Dv(bumpValue, DbumpValue_dv);
		Du(bumpDepth, DbumpDepth_du);
		Dv(bumpDepth, DbumpDepth_dv);
		Du_offset = D_clamp(bumpValue(), LOW,HEIGHT) * DbumpValue_du      * abs(bumpDepth()) 
			        + clamp(bumpValue(), LOW,HEIGHT) * D_abs(bumpDepth()) * DbumpDepth_du;
		Dv_offset = D_clamp(bumpValue(), LOW,HEIGHT) * DbumpValue_dv      * abs(bumpDepth()) 
			        + clamp(bumpValue(), LOW,HEIGHT) * D_abs(bumpDepth()) * DbumpDepth_dv;
		/*
		These scale factors are a bit experimental. The constant is to roughly
		match maya's bump mapping. The part about dPdu/dPdv ensures that the
		bump's scale does not depend on the underlying parametrization of the
		patch (the use of Du and Dv below introduce that) and that it happens
		in object space. Note that maya's handling of object space appears to
		be slightly broken since an enlarged sphere will have the same bump as
		a sphere with its control points moved outwards by a scale, somehow.
		*/
		matrix toLocal = to_object();
		eiScalar uscale = 1.0f / len(&(dPdu() * toLocal)) * 6.0f;
		eiScalar vscale = 1.0f / len(&(dPdv() * toLocal)) * 6.0f;

		vector gu = vector(1.0f, 0.0f, Du_offset * uscale);
		vector gv = vector(0.0f, 1.0f, Dv_offset * vscale);
		normal n = normal(gu ^ gv);

		vector basisz = normalize(i_normalCamera);
		vector basisx = normalize((basisz ^ dPdu()) ^ basisz);
		vector basisy = normalize((basisz ^ dPdv()) ^ basisz);

		o_outNormal = normal(
			n.x * basisx + n.y * basisy + n.z * basisz);

		o_outNormal = normalize(o_outNormal);
	}
	void main(void *arg)
	{
		if( bumpInterp() == 0 )
		{
			/* Bump. */
			do_bump_map(
				//bumpValue(),
				//bumpDepth(),
				normalCamera(),
				outNormal() );

		}
		else if( bumpInterp() == 1 )
		{
			///* Tangent Space Normals. */
			//vector udir, vdir;

			//if( stangent != vector(0) )
			//{
			//	vdir = stangent ^ i_normalCamera;
			//}
			//else
			//{
			//	vdir = Du(tt) * dPdu + Dv(tt) * dPdv;
			//	vdir = i_normalCamera ^ (vdir ^ i_normalCamera);
			//}

			//udir = i_normalCamera ^ vdir;
			//vector uorient = Du(ss) * dPdu + Dv(ss) * dPdv;
			//if( udir.uorient < 0 )
			//{
			//	udir = -udir;
			//}

			//vector basisx = normalize(udir);
			//vector basisy = normalize(vdir);
			//vector basisz = normalize(i_normalCamera);

			//outNormal() = normal(
			//	(bumpNormal().x - 0.5f) * basisx +
			//	(bumpNormal().y - 0.5f) * basisy +
			//	(bumpNormal().z - 0.5f) * basisz );

			//outNormal() = normalize(outNormal());
		}
		else
		{
			/* Object Space Normals. This needs some work. */
			//outNormal() = ntransform( "object", "current", bumpNormal() - 0.5f );
			//outNormal() = normalize(outNormal());
		}
	}

END(maya_bump2d)