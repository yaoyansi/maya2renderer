# Install script for directory: E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files/aqsis_all")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/aqsisrc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/include/aqsis/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/math/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/util/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/riutil/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/ribparse/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/slcomp/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/tex/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/shadervm/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/slxargs/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/ri2rib/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/rib2ri/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/libs/core/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/aqsl/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/aqsltell/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/aqsis/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/miqser/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/teqser/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/displays/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/procedurals/hairgen/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/tools/neqsus/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/shaders/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/examples/cmake_install.cmake")
  INCLUDE("E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/distribution/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
