#include "eiAPI/ei.h"
void ei_face_color_unittest(const eiApprox *approx, const char *suffix)
{
	char	cur_dir[ EI_MAX_FILE_NAME_LEN ];
	char	filename[ EI_MAX_FILE_NAME_LEN ];
	char	output_filename[ EI_MAX_FILE_NAME_LEN ];

	ei_get_current_directory(cur_dir);

	ei_context(ei_create_context());

	ei_verbose(EI_VERBOSE_ALL);
	ei_link("eiIMG");
	ei_link("eiSHADER");

	ei_options("opt");
		ei_samples(0, 2);
		ei_contrast(0.05f, 0.05f, 0.05f, 0.05f);
		ei_filter(EI_FILTER_GAUSSIAN, 3.0f);

		if (approx != NULL)
		{
			ei_displace(on);
			ei_max_displace(1.0f);

			ei_approx(approx);
		}

	ei_end_options();

	ei_camera("cam1");
		sprintf(filename, "frame_face_color_%s01.bmp", suffix);
		ei_append_filename(output_filename, cur_dir, filename);
		ei_output(output_filename, "bmp", EI_IMG_DATA_RGB);
			ei_output_variable("color", EI_DATA_TYPE_VECTOR);
		ei_end_output();
		ei_focal(100.0f);
		ei_aperture(144.724029f);
		ei_aspect(800.0f / 600.0f);
		ei_resolution(800, 600);
	ei_end_camera();

	ei_instance("caminst1");
		ei_element("cam1");
	ei_end_instance();

	ei_shader("point_light_shader");
		ei_shader_param_string("desc", "pointlight");
		ei_shader_param_scalar("intensity", 1.0f);
		ei_shader_param_vector("lightcolor", 1.0f, 1.0f, 1.0f);
	ei_end_shader();

	ei_light("light1");
		ei_add_light("point_light_shader");
		ei_origin(141.375732f, 83.116005f, 35.619434f);
	ei_end_light();

	ei_instance("lightinst1");
		ei_element("light1");
	ei_end_instance();

	ei_shader("phong_shader");
		ei_shader_param_string("desc", "face_plastic");
		ei_shader_param_vector("Cs", 1.0f, 0.2f, 0.3f);
		ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f);
		ei_shader_param_scalar("Ks", 1.0f);
		ei_shader_param_scalar("roughness", 0.2f);
	ei_end_shader();

	if (approx != NULL)
	{
		ei_shader("displace_shader");
			ei_shader_param_string("desc", "simple_displace");
			ei_shader_param_scalar("disp_dist", 1.0f);
		ei_end_shader();
	}

	ei_shader("opaque_shadow");
		ei_shader_param_string("desc", "opaque");
	ei_end_shader();

	ei_material("mtl");
		ei_add_surface("phong_shader");
		ei_add_shadow("opaque_shadow");
		if (approx != NULL)
		{
			ei_add_displace("displace_shader");
		}
	ei_end_material();

	ei_object("obj1", "poly");
		ei_pos_list(ei_tab(EI_DATA_TYPE_VECTOR, 1024));
			ei_tab_add_vector(-7.068787f, -4.155799f, -22.885710f);
			ei_tab_add_vector(-0.179573f, -7.973234f, -16.724060f);
			ei_tab_add_vector(-7.068787f, 4.344949f, -17.619093f);
			ei_tab_add_vector(-0.179573f, 0.527515f, -11.457443f);
			ei_tab_add_vector(0.179573f, -0.527514f, -28.742058f);
			ei_tab_add_vector(7.068787f, -4.344948f, -22.580408f);
			ei_tab_add_vector(0.179573f, 7.973235f, -23.475441f);
			ei_tab_add_vector(7.068787f, 4.155800f, -17.313791f);
		ei_end_tab();
		ei_triangle_list(ei_tab(EI_DATA_TYPE_INDEX, 1024));
			ei_tab_add_index(0); ei_tab_add_index(1); ei_tab_add_index(3);
			ei_tab_add_index(0); ei_tab_add_index(3); ei_tab_add_index(2);
			ei_tab_add_index(1); ei_tab_add_index(5); ei_tab_add_index(7);
			ei_tab_add_index(1); ei_tab_add_index(7); ei_tab_add_index(3);
			ei_tab_add_index(5); ei_tab_add_index(4); ei_tab_add_index(6);
			ei_tab_add_index(5); ei_tab_add_index(6); ei_tab_add_index(7);
			ei_tab_add_index(4); ei_tab_add_index(0); ei_tab_add_index(2);
			ei_tab_add_index(4); ei_tab_add_index(2); ei_tab_add_index(6);
			ei_tab_add_index(4); ei_tab_add_index(5); ei_tab_add_index(1);
			ei_tab_add_index(4); ei_tab_add_index(1); ei_tab_add_index(0);
			ei_tab_add_index(2); ei_tab_add_index(3); ei_tab_add_index(7);
			ei_tab_add_index(2); ei_tab_add_index(7); ei_tab_add_index(6);
		ei_end_tab();
		eiTag Cs_tab = eiNULL_TAG;
		ei_declare("Cs", eiUNIFORM, EI_DATA_TYPE_TAG, &Cs_tab);
		Cs_tab = ei_tab(EI_DATA_TYPE_VECTOR, 1024);
		ei_variable("Cs", &Cs_tab);
			eiVector col;
			setv(&col, 1.0f, 0.0f, 0.0f);
			ei_tab_add(&col);
			setv(&col, 0.0f, 1.0f, 0.0f);
			ei_tab_add(&col);
			setv(&col, 0.0f, 0.0f, 1.0f);
			ei_tab_add(&col);
			setv(&col, 1.0f, 1.0f, 0.0f);
			ei_tab_add(&col);
			setv(&col, 0.0f, 1.0f, 1.0f);
			ei_tab_add(&col);
			setv(&col, 1.0f, 1.0f, 1.0f);
			ei_tab_add(&col);
			setv(&col, 0.5f, 1.0f, 0.5f);
			ei_tab_add(&col);
			setv(&col, 1.0f, 0.0f, 1.0f);
			ei_tab_add(&col);
			setv(&col, 0.5f, 0.5f, 0.0f);
			ei_tab_add(&col);
			setv(&col, 0.0f, 0.5f, 0.5f);
			ei_tab_add(&col);
			setv(&col, 0.5f, 0.0f, 0.5f);
			ei_tab_add(&col);
			setv(&col, 1.0f, 0.5f, 0.0f);
			ei_tab_add(&col);
		ei_end_tab();
	ei_end_object();

	ei_instance("inst1");
		ei_add_material("mtl");
		ei_element("obj1");
	ei_end_instance();

	ei_instgroup("world");
		ei_add_instance("caminst1");
		ei_add_instance("lightinst1");
		ei_add_instance("inst1");
	ei_end_instgroup();

	// render frame 01
	ei_render("world", "caminst1", "opt");

	ei_camera("cam1");
		sprintf(filename, "frame_face_color_%s02.bmp", suffix);
		ei_append_filename(output_filename, cur_dir, filename);
		ei_output(output_filename, "bmp", EI_IMG_DATA_RGB);
			ei_output_variable("color", EI_DATA_TYPE_VECTOR);
		ei_end_output();
		ei_aperture(100.0f);
	ei_end_camera();

	ei_shader("point_light_shader");
		ei_shader_param_vector("lightcolor", 1.0f, 0.5f, 1.0f);
	ei_end_shader();

	// render frame 02
	ei_render("world", "caminst1", "opt");

	ei_delete_context(ei_context(NULL));
}
