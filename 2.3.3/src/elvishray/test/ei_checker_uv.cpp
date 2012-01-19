#include "eiAPI/ei.h"

void ei_checker_uv()
{
	char	cur_dir[ EI_MAX_FILE_NAME_LEN ];
	char	output_filename[ EI_MAX_FILE_NAME_LEN ];

	ei_get_current_directory(cur_dir);

	ei_context(ei_create_context());

	ei_verbose(EI_VERBOSE_ALL);
	ei_link("eiIMG");
	ei_link("eiSHADER");
	ei_link("eiSHADER_maya");

	ei_options("opt");
	ei_samples(0, 2);
	ei_contrast(0.05f, 0.05f, 0.05f, 0.05f);
	ei_filter(EI_FILTER_GAUSSIAN, 3.0f);
	ei_end_options();

	ei_camera("cam1");
	ei_append_filename(output_filename, cur_dir, "frame_checker_uv01.bmp");
	ei_output(output_filename, "bmp", EI_IMG_DATA_RGB);
	ei_output_variable("color", EI_DATA_TYPE_VECTOR);
	ei_end_output();
	ei_focal(35);
	ei_aperture(36);
	ei_aspect(1.33333);
	ei_resolution(768,576);
	ei_clip(0.1,1000);
	ei_end_camera();

	ei_instance("caminst1");
	ei_element("cam1");
	ei_transform(0.99824,0,0.0593064,0,   0.0566963,0.2934,-0.954307,0,   -0.0174005,0.95599,0.292884,0,   -0.49545,21.243,1.94647,1);
	ei_end_instance();

	ei_shader("point_light_shader");
	ei_shader_param_string("desc", "pointlight");
	ei_shader_param_scalar("intensity", 1.0f);
	ei_shader_param_vector("lightcolor", 1.0f, 1.0f, 1.0f);
	ei_end_shader();

	ei_light("light1");
	ei_add_light("point_light_shader");
	ei_origin(0,5.23026,0);
	ei_end_light();

	ei_instance("lightinst1");
	ei_element("light1");
	ei_end_instance();
	//############################### initialShadingGroup
	ei_shader("place2dTexture2");
	ei_shader_param_string("desc", "maya_place2dTexture");
	ei_shader_param_vector("repeatUV", 5, 5, 4.5499e+174);
	ei_shader_param_vector("outUV", 0, 0, 4.5499e+174);
	ei_end_shader();

	ei_shader("checker1");
	ei_shader_param_string("desc", "maya_checker_uv2");
	ei_shader_param_vector("color1", 1, 1, 1);
	ei_shader_param_vector("color2", 0, 0, 0);
	ei_shader_param_scalar("uscale", 5.0f);
	ei_shader_param_scalar("vscale", 5.0f);
	ei_end_shader();
	ei_shader("checker2");
	ei_shader_param_string("desc", "checker_uv");
	ei_shader_param_vector("color1", 1, 1, 1);
	ei_shader_param_vector("color2", 0, 0, 0);
	ei_shader_param_scalar("uscale", 5.0f);
	ei_shader_param_scalar("vscale", 5.0f);
	ei_end_shader();

	ei_shader("lambert2");
	ei_shader_param_string("desc", "plastic");
	//ei_shader_link_param("Cs", "checker1", "result");
	ei_shader_link_param("Cs", "checker2", "result");
	ei_shader_param_vector("transparency", 0, 0, 0);
	ei_shader_param_vector("ambientColor", 0, 0, 0);
	ei_shader_param_vector("incandescence", 0, 0, 0);
	ei_shader_param_scalar("diffusion", 0.8);
	ei_shader_param_vector("outColor", 0, 0, 0);
	ei_shader_param_vector("outTransparency", 0, 0, 0);
	ei_end_shader();

	ei_material("initialShadingGroup");
	ei_add_surface("lambert2");
	ei_end_material();
	//############################### mtl
	ei_shader("checker_shader");
	ei_shader_param_string("desc", "checker_uv");
	ei_shader_param_vector("color1", 1.0f, 0.2f, 0.2f);
	ei_shader_param_scalar("uscale", 2.0f);
	ei_shader_param_scalar("vscale", 2.0f);
	ei_end_shader();

	ei_shader("phong_shader");
	ei_shader_param_string("desc", "plastic");
	//ei_shader_param_vector("Cs", 1.0f, 0.2f, 0.3f);
	ei_shader_link_param("Cs", "checker_shader", "result");
	ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f);
	ei_shader_param_scalar("Ks", 1.0f);
	ei_shader_param_scalar("roughness", 0.02f);
	ei_end_shader();

	ei_shader("opaque_shadow");
	ei_shader_param_string("desc", "opaque");
	ei_end_shader();

	ei_material("mtl");
	ei_add_surface("phong_shader");
	ei_add_shadow("opaque_shadow");
	ei_end_material();
	//###################################################
	ei_object("obj1", "poly");
	ei_pos_list(ei_tab(EI_DATA_TYPE_VECTOR, 1024));
	ei_tab_add_vector(-4.74457,0.549288,-2.45983);
	ei_tab_add_vector(2.82455,0.549288,-2.45983);
	ei_tab_add_vector(-4.74457,0.549288,-8.67472);
	ei_tab_add_vector(2.82455,0.549288,-8.67472);
	ei_end_tab();
	eiTag tagVal = eiNULL_TAG;
	ei_declare("N", eiVARYING, EI_DATA_TYPE_TAG, &tagVal);
	tagVal = ei_tab(EI_DATA_TYPE_VECTOR, 1024);
	ei_variable("N", &tagVal);
	ei_tab_add_vector(0,1,2.22045e-016);
	ei_tab_add_vector(0,1,2.22045e-016);
	ei_tab_add_vector(0,1,2.22045e-016);
	ei_tab_add_vector(0,1,2.22045e-016);
	ei_end_tab();
	tagVal = eiNULL_TAG;
	ei_declare("u", eiVARYING, EI_DATA_TYPE_TAG, &tagVal);
	tagVal = ei_tab(EI_DATA_TYPE_SCALAR, 1024);
	ei_variable("u", &tagVal);
	ei_tab_add_scalar(0);
	ei_tab_add_scalar(1);
	ei_tab_add_scalar(0);
	ei_tab_add_scalar(1);
	ei_end_tab();
	tagVal = eiNULL_TAG;
	ei_declare("v", eiVARYING, EI_DATA_TYPE_TAG, &tagVal);
	tagVal = ei_tab(EI_DATA_TYPE_SCALAR, 1024);
	ei_variable("v", &tagVal);
	ei_tab_add_scalar(0);
	ei_tab_add_scalar(0);
	ei_tab_add_scalar(0.821085);
	ei_tab_add_scalar(0.821085);
	ei_end_tab();
	ei_triangle_list(ei_tab(EI_DATA_TYPE_INDEX, 1024));
	ei_tab_add_index(0);
	ei_tab_add_index(1);
	ei_tab_add_index(2);
	ei_tab_add_index(2);
	ei_tab_add_index(1);
	ei_tab_add_index(3);
	ei_end_tab();
	ei_end_object();

	ei_instance("inst1");
	//ei_add_material("mtl");
	ei_add_material("initialShadingGroup");
	ei_element("obj1");
	ei_transform(1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 2.742935, 1.037594, 0.000000, 1.000000);
	ei_end_instance();

	ei_instgroup("world");
	ei_add_instance("caminst1");
	ei_add_instance("lightinst1");
	ei_add_instance("inst1");
	ei_end_instgroup();

	// render frame 01
	ei_render("world", "caminst1", "opt");

	ei_delete_context(ei_context(NULL));
}
