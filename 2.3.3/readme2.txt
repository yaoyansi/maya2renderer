-------------------
build
-------------------
- link error boost::system::get_system_category() 找不到
解决方法：在liquid项目里把\boost\1_39\libs\system\src\error_code.cpp包含进去

-------------------
install
-------------------
- for batch rendering:
run liquid_root\mel\replace_mayaBatchRenderProcedure.bat to replace maya_root\scripts\other\mayaBatchRenderProcedure.mel