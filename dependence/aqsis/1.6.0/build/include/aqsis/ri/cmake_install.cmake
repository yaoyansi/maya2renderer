# Install script for directory: E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "development")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aqsis/ri" TYPE FILE FILES
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/ndspy.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/ri.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/ritypes.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/rif.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/shadeop.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/slo.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/src/include/aqsis/ri/slx.h"
    "E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/aqsis/1.6.0/build/include/aqsis/ri/ri.inl"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "development")

