#Mandatory commands to use wkcmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE ( "../../../../CMake/WkCMake.cmake" )
WkCMakeDir( "../../../../CMake" )

#Project Declaration
WkProject( chipmunk CXX )

# NOT USING WKCMAKE TO BUILD
# because chipmunk uses C++ syntax in C source files
# and this will not be supported by WkCMake.

SET ( chipmunk_SOURCE_DIR "..")
SET ( BUILD_STATIC TRUE )
add_subdirectory("src")

# Addons for upper WkCMake project to use this properly


