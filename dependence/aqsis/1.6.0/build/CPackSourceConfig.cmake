# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. Example variables are:
#   CPACK_GENERATOR                     - Generator used to create package
#   CPACK_INSTALL_CMAKE_PROJECTS        - For each project (path, name, component)
#   CPACK_CMAKE_GENERATOR               - CMake Generator used for the projects
#   CPACK_INSTALL_COMMANDS              - Extra commands to install components
#   CPACK_INSTALL_DIRECTORIES           - Extra directories to install
#   CPACK_PACKAGE_DESCRIPTION_FILE      - Description file for the package
#   CPACK_PACKAGE_DESCRIPTION_SUMMARY   - Summary of the package
#   CPACK_PACKAGE_EXECUTABLES           - List of pairs of executables and labels
#   CPACK_PACKAGE_FILE_NAME             - Name of the package generated
#   CPACK_PACKAGE_ICON                  - Icon used for the package
#   CPACK_PACKAGE_INSTALL_DIRECTORY     - Name of directory for the installer
#   CPACK_PACKAGE_NAME                  - Package project name
#   CPACK_PACKAGE_VENDOR                - Package project vendor
#   CPACK_PACKAGE_VERSION               - Package project version
#   CPACK_PACKAGE_VERSION_MAJOR         - Package project version (major)
#   CPACK_PACKAGE_VERSION_MINOR         - Package project version (minor)
#   CPACK_PACKAGE_VERSION_PATCH         - Package project version (patch)

# There are certain generator specific ones

# NSIS Generator:
#   CPACK_PACKAGE_INSTALL_REGISTRY_KEY  - Name of the registry key for the installer
#   CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS - Extra commands used during uninstall
#   CPACK_NSIS_EXTRA_INSTALL_COMMANDS   - Extra commands used during install


SET(CPACK_ALL_INSTALL_TYPES "Full;Minimal")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 8 2005")
SET(CPACK_COMPONENTS_ALL "main;examples;shaders;plugins;development;Unspecified")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Include and library files for software development")
SET(CPACK_COMPONENT_DEVELOPMENT_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "Example files (.rib)")
SET(CPACK_COMPONENT_EXAMPLES_GROUP "content")
SET(CPACK_COMPONENT_EXAMPLES_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_GROUP_CONTENT_DESCRIPTION "Examples and shader source files")
SET(CPACK_COMPONENT_MAIN_DESCRIPTION "Rendering application and essential files only")
SET(CPACK_COMPONENT_MAIN_INSTALL_TYPES "Full;Minimal")
SET(CPACK_COMPONENT_MAIN_REQUIRED "TRUE")
SET(CPACK_COMPONENT_PLUGINS_DESCRIPTION "Plugins for external applications")
SET(CPACK_COMPONENT_PLUGINS_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_SHADERS_DESCRIPTION "Generic shader source files (.sl)")
SET(CPACK_COMPONENT_SHADERS_GROUP "content")
SET(CPACK_COMPONENT_SHADERS_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "ZIP")
SET(CPACK_IGNORE_FILES ".*/\\.git/")
SET(CPACK_INSTALLED_DIRECTORIES "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "C:/Program Files/aqsis_all")
SET(CPACK_MODULE_PATH "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/cmake/modules;E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/cmake")
SET(CPACK_NSIS_CONTACT "packages@aqsis.org")
SET(CPACK_NSIS_DISPLAY_NAME "Aqsis Renderer 1.6.0")
SET(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
		!addincludedir \"E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/distribution/win/nsis\"
		!include custom_install.nsi")
SET(CPACK_NSIS_HELP_LINK "http:\\\\community.aqsis.org")
SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\eqsl.exe")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_MODIFY_PATH "ON")
SET(CPACK_NSIS_PACKAGE_NAME "Aqsis Renderer 1.6.0")
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\www.aqsis.org")
SET(CPACK_OUTPUT_CONFIG_FILE "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/README")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Aqsis Renderer")
SET(CPACK_PACKAGE_EXECUTABLES "eqsl;Aqsis Renderer")
SET(CPACK_PACKAGE_FILE_NAME "Aqsis-1.6.0-Source")
SET(CPACK_PACKAGE_ICON "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/distribution/win\\header.bmp")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Aqsis")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Aqsis 1.6.0")
SET(CPACK_PACKAGE_NAME "Aqsis")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Aqsis Team")
SET(CPACK_PACKAGE_VERSION "1.6.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "6")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RESOURCE_FILE_LICENSE "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/COPYING")
SET(CPACK_RESOURCE_FILE_README "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/README")
SET(CPACK_RESOURCE_FILE_WELCOME "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/README")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "ZIP")
SET(CPACK_SOURCE_IGNORE_FILES ".*/\\.git/")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "Aqsis-1.6.0-Source")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TOPLEVEL_TAG "win32-Source")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "win32")
SET(CPACK_TOPLEVEL_TAG "win32-Source")
