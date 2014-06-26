#Mandatory commands to use wkcmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE ( "../../../../CMake/WkCMake.cmake" )
WkCMakeDir( "../../../../CMake" )

#Project Declaration
WkProject( cocos2dx CXX )

WkIncludeDir (".")

#additional include directories
include_directories("include" "kazmath/include")

WkLibraryBuild (cocos2dx ".")


