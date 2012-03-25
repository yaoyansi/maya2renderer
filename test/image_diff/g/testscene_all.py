import os
import testone_by_mayapy as MyTestOne


def test_all_scene():
    LIQUID_ROOT= os.environ["LIQUID_ROOT"]

    testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/deform.ma"
    MyTestOne.test_one_scene(testFile, "")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/transform.ma"
    MyTestOne.test_one_scene(testFile, "")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_rm_texture/check10_tex.ma"
    MyTestOne.test_one_scene(testFile, "renderman")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_animation/checker_anim.ma"
    MyTestOne.test_one_scene(testFile, "")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_pl/test_shader_pl.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_pl/test_shader_pl_connection.ma"
    MyTestOne.test_one_scene(testFile, "renderman")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_pl/test_type_array.ma"
    MyTestOne.test_one_scene(testFile, "renderman")

    #[Warning] test_displace_pl.ma lead mayabatch crash!
    #testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_pl/test_displace_pl.ma"
    #MyTestOne.test_one_scene(testFile, "elvishray")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_graph/er_rm_shader_graph.ma"
    MyTestOne.test_one_scene(testFile, "")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_graph/er_rm_shader_graph_phong.ma"
    MyTestOne.test_one_scene(testFile, "renderman")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_shader_graph/er_rm_shader_graph_phong_transparent.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_shader/three_boxes.ma"
    MyTestOne.test_one_scene(testFile, "")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_shader/lambert_transparent.ma"
    MyTestOne.test_one_scene(testFile, "")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_light/er_pointlight.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_light/er_spotlight.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_light/er_directlight.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_dof/er_dof2.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_dof/rm_dof2.ma"
    MyTestOne.test_one_scene(testFile, "renderman")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_env/er_env_simple_env.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_env/er_env_physicalsky.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_rm_displacement/test_displacement.ma"
    MyTestOne.test_one_scene(testFile, "renderman")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_rm_light/rm_spotlight.ma"
    MyTestOne.test_one_scene(testFile, "renderman")
    testFile=LIQUID_ROOT+"/2.3.3/test/test_rm_light/rm_directlight.ma"
    MyTestOne.test_one_scene(testFile, "renderman")

    #testFile=LIQUID_ROOT+"/2.3.3/test/hair/test_shaveHair(shave_v61).ma"
    #MyTestOne.test_one_scene(testFile, "renderman")

    #testFile=LIQUID_ROOT+"/2.3.3/test/test_pfxhair/test_pfxHair.ma"
    #MyTestOne.test_one_scene(testFile, "renderman")

    #animation
    #testFile=LIQUID_ROOT+"/2.3.3/test/test_animation/checker_anim.ma"
    #MyTestOne.test_one_scene(testFile, "renderman")
    #testFile=LIQUID_ROOT+"/2.3.3/test/test_animation/er_anim.ma"
    #MyTestOne.test_one_scene(testFile, "elvishray")

    #testFile=LIQUID_ROOT+"/2.3.3/test/test_golbalnode/test_simple.ma"
    #MyTestOne.test_one_scene(testFile, "elvishray")
    #MyTestOne.test_one_scene(testFile, "renderman")

    #MyTestOne.test_one_scene("D:/tmp/maya_test/Trex/scenes/TrexAnimation_er.ma", "elvishray")
   
    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_vertex_normal/er_vertex_normal.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_er_volume/er_volume.ma"
    MyTestOne.test_one_scene(testFile, "elvishray")
