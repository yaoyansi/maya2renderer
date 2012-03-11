#include "eiAPI/ei.h"

void ei_img_uv(const eiBool texturing, const char *suffix)
{
	char	cur_dir[ EI_MAX_FILE_NAME_LEN ];
	char	filename[ EI_MAX_FILE_NAME_LEN ];
	char	output_filename[ EI_MAX_FILE_NAME_LEN ];
	char	picturename[ EI_MAX_FILE_NAME_LEN ];
	char	texturename1[ EI_MAX_FILE_NAME_LEN ];
	char	texturename2[ EI_MAX_FILE_NAME_LEN ];

	ei_get_current_directory(cur_dir);

	ei_context(ei_create_context());

	ei_verbose(EI_VERBOSE_ALL);
	ei_link("eiIMG");
	ei_link("eiSHADER");
	ei_link("eiSHADER_maya");

	if (texturing)
	{
		/* make the texture if we have never done so */
		ei_append_filename(picturename, cur_dir, "uv_test.bmp");
		ei_append_filename(texturename1, cur_dir, "uv_test.tex");

		if (!ei_file_exists(texturename1) && 
			ei_file_exists(picturename))
		{
			ei_make_texture(
				picturename, 
				texturename1, 
				EI_TEX_WRAP_CLAMP, EI_TEX_WRAP_CLAMP, 
				EI_FILTER_BOX, 
				1.0f, 1.0f);
		}

		if (ei_file_exists(texturename1))
		{
			ei_texture(texturename1);
			ei_file_texture(texturename1, eiFALSE);
			ei_end_texture();
		}
	}

	ei_options("opt");
	ei_samples(0, 2);
	ei_contrast(0.05f, 0.05f, 0.05f, 0.05f);
	ei_filter(EI_FILTER_GAUSSIAN, 3.0f);
	ei_end_options();

	ei_camera("cam1");
	sprintf(filename, "frame_img_uv_%s01.bmp", suffix);
	ei_append_filename(output_filename, cur_dir, filename);
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
	ei_transform(0.982935,0,-0.183951,0,   -0.151669,0.565854,-0.810435,0,   0.10409,0.824505,0.556198,0,   11.6253,81.2918,55.842,1);
	ei_end_instance();

	ei_shader("point_light_shader");
	ei_shader_param_string("desc", "pointlight");
	ei_shader_param_scalar("intensity", 1.0f);
	ei_shader_param_vector("lightcolor", 1.0f, 1.0f, 1.0f);
	ei_end_shader();

	ei_light("light1");
	ei_add_light("point_light_shader");
ei_origin(13.1371,15.4759,13.8213);
	ei_end_light();

	ei_instance("lightinst1");
	ei_element("light1");
	ei_end_instance();

	if (texturing)
	{
		ei_shader("simple_tex_shader1");
		ei_shader_param_string("desc", "simple_texture");
		ei_shader_param_texture("texture", texturename1);
		ei_end_shader();
	}

	ei_shader("phong_shader");
	ei_shader_param_string("desc", "plastic");
	ei_shader_link_param("Cs", "simple_tex_shader1", "result");
	ei_shader_param_vector("Kd", 0.7f, 1.0f, 1.0f);
	ei_shader_param_scalar("Ks", 1.0f);
	ei_shader_param_scalar("roughness", 0.2f);
	ei_end_shader();

	ei_shader("maya_lambert_shader");
	ei_shader_param_string("desc", "maya_lambert_transparent");
	ei_shader_param_texture("Cs_tex", "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/src/elvishray/test/Debug/leopard.tex");
	ei_shader_param_vector("transparency", 0, 0, 0);
	ei_shader_param_vector("ambientColor", 0, 0, 0);
	ei_shader_param_vector("incandescence", 0, 0, 0);
	ei_shader_param_scalar("diffusion", 0.8);
	ei_shader_param_vector("outColor", 0, 0, 0);
	ei_shader_param_vector("outTransparency", 0, 0, 0);
	ei_end_shader();

	ei_shader("opaque_shadow");
	ei_shader_param_string("desc", "opaque");
	ei_end_shader();

	ei_material("mtl");
	ei_add_surface("phong_shader");
	ei_add_shadow("opaque_shadow");
	ei_end_material();

	ei_material("maya_lambert");
	ei_add_surface("maya_lambert_shader");
	ei_end_material();

	ei_object("obj1", "poly");
		ei_pos_list(ei_tab(EI_DATA_TYPE_VECTOR, 1024));
		ei_tab_add_vector(-18.5024,-3.70836e-015,16.701);
		ei_tab_add_vector(18.5024,-3.70836e-015,16.701);
		ei_tab_add_vector(-18.5024,3.70836e-015,-16.701);
		ei_tab_add_vector(18.5024,3.70836e-015,-16.701);
		ei_end_tab();

		//### UV, size=4
		eiTag tag;
		//u
		tag = eiNULL_TAG;
		ei_declare("u",2,5, &tag);
		tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024);
		ei_variable("u", &tag);
		ei_tab_add_scalar(0);
		ei_tab_add_scalar(1);
		ei_tab_add_scalar(0);
		ei_tab_add_scalar(1);
		ei_end_tab();
		//v
		tag = eiNULL_TAG;
		ei_declare("v",2,5, &tag);
		tag = ei_tab(EI_DATA_TYPE_SCALAR, 1024);
		ei_variable("v", &tag);
		ei_tab_add_scalar(0);
		ei_tab_add_scalar(0);
		ei_tab_add_scalar(1);
		ei_tab_add_scalar(1);
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
	ei_add_material("mtl");
	ei_element("obj1");
	ei_transform(1,0,0,0,   0,1,0,0,   0,0,1,0,   25.642661,-10.3652,8.77257,1);
	ei_end_instance();

	ei_instance("inst2");
	ei_add_material("maya_lambert");
	ei_element("obj1");
	ei_transform(1,0,0,0,   0,1,0,0,   0,0,1,0,   -25.642661,-10.3652,8.77257,1);
	ei_end_instance();

	ei_instgroup("world");
	ei_add_instance("caminst1");
	ei_add_instance("lightinst1");
	ei_add_instance("inst1");
	ei_add_instance("inst2");
	ei_end_instgroup();

	// render frame 01
	ei_render("world", "caminst1", "opt");

	ei_delete_context(ei_context(NULL));
}
