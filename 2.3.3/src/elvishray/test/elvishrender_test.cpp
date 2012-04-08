/*---------------------------------------------------------------------------------------------
This file is part of elvish ray Renderer.
Copyright (C) 2007-2009  Enning Liang(Len3d)

elvish ray Renderer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

elvish ray Renderer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------*/
#include <iostream>
#include "eiAPI/ei.h"

using namespace std;

/*---------------------------------------------------------------------------------------------

Function	:	test_example_scene
Inputs		:	
Outputs		:	
Description	:	test the basic rendering functionalities of the renderer with a very 
simple example scene.
Comments	:	
History		:	

---------------------------------------------------------------------------------------------*/

extern void ei_face_color_unittest(const eiApprox *approx, const char *suffix);
extern void ei_shader_graph_unittest(const eiBool texturing, const char *suffix);
extern void ei_shader_link_test(const eiBool texturing, const char *suffix);
extern void ei_checker_uv();
extern void er_shader_transparent_test();
void ei_displace_unittest();
extern void ei_volume_unittest();
extern void ei_dof_unittest();
extern void spotlight_test();
extern void spotlight_test2();
extern void ei_img_uv(const eiBool texturing, const char *suffix);
extern void ei_env_test(const char *env_shader_name);

void test_liquid2er()
{
//#include"cornellbox.esa"
//#include "./liq_er_displace_good.er"
//#include "E:/MyDocuments/maya/projects/default/rib/box.rib.er"
#include "E:/MyDocuments/maya/projects/default/rib/MoxMotionMeetsFBIK_NoAux_perspShape.0001.rib.er"
//#include"ei_scene_unittest.esa"//<----- use your own elvishender api script file here.
	
	//ei_face_color_unittest(NULL, "suffix");
	//ei_shader_graph_unittest(true, "suffix");
	//ei_shader_link_test(false, "suffix");
	//ei_checker_uv();
	//er_shader_transparent_test();
	//ei_displace_unittest();
	//ei_volume_unittest();
	//ei_dof_unittest();
	//spotlight_test();
	//spotlight_test2();
	//ei_img_uv(true, "suffix");
	//ei_env_test("physicalsky");//"simple_env" //""
}
//
int main()
{
	cout << "Launching elvish ray Renderer..." << endl;

 
	test_liquid2er();


	cout << "all tests done." << endl;
 

	return 0;
}

