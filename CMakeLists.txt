#Mandatory commands to use wkcmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE ( "CMake/WkCMake.cmake" )
WkCMakeDir( "CMake" )

#Project Declaration
WkProject( App42 CXX )

#NO Tests for now...
#WkTestDir ( "Tests" )

WkAddCFlags("-DCOCOS2D_DEBUG=1")
WkAddCXXFlags("-DCOCOS2D_DEBUG=1")

if(WIN32)
  WkAddCXXFlags("-D_USRDLL -DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32")

  if(MSVC)
    WkAddCXXFlags( "-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS" )
    WkAddCXXFlags( "-wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710 -wd4514 -wd4056 -wd4996 -wd4099" )
    WkAddCXXFlags( "-MP -Qpar" )
  else(MSVC)#MINGW
  
  endif(MSVC)
elseif(APPLE)


else()#Linux
  WkAddCFlags("-DLINUX")
  WkAddCXXFlags("-DLINUX")
endif()


if(NOT MSVC)# all gcc
WkAddCFlags( "-std=c99")
WkAddCXXFlags("-std=c++11")
endif()

if(MINGW)
  WkAddCXXFlags("-DGLEW_STATIC")
endif()

WkAddCXXFlags("-DCC_ENABLE_CHIPMUNK_INTEGRATION=1")

#include_directories("V_1.3/App42_Cocos2dX_SDK/libs/chipmunk/include")
#WkLibraryBuild( chipmunk STATIC "V_1.3/App42_Cocos2dX_SDK/libs/chipmunk/src")

#include_directories("V_1.3/App42_Cocos2dX_SDK/libs/cocos2dx")
#include_directories("V_1.3/App42_Cocos2dX_SDK/libs/cocos2dx/include")
#WkLibraryBuild( cocos2dx STATIC "V_1.3/App42_Cocos2dX_SDK/libs/cocos2dx")

#include_directories("V_1.3/App42_Cocos2dX_SDK/libs/CocosDenshion/include")
#WkLibraryBuild( CocosDenshion STATIC "V_1.3/App42_Cocos2dX_SDK/libs/CocosDenshion")

#include_directories("V_1.3/App42_Cocos2dX_SDK/libs/extensions")
#WkLibraryBuild( extensions STATIC "V_1.3/App42_Cocos2dX_SDK/libs/extensions")

WkIncludeDir ( "V_1.3/App42_Cocos2dX_SDK" )
#extra includes because App42 doesnt include headers with path...
include_directories(
	"V_1.3/App42_Cocos2dX_SDK/App42HTTP"
	"V_1.3/App42_Cocos2dX_SDK/cJSON"
	"V_1.3/App42_Cocos2dX_SDK/Common"
	"V_1.3/App42_Cocos2dX_SDK/Common/Exception"
	"V_1.3/App42_Cocos2dX_SDK/Crypto"
	"V_1.3/App42_Cocos2dX_SDK/CustomCodeService"
	"V_1.3/App42_Cocos2dX_SDK/EmailService"
	"V_1.3/App42_Cocos2dX_SDK/GameService"
	"V_1.3/App42_Cocos2dX_SDK/PushNotificationService"
	"V_1.3/App42_Cocos2dX_SDK/StorageService"
	"V_1.3/App42_Cocos2dX_SDK/UploadService"
	"V_1.3/App42_Cocos2dX_SDK/UserService"
	"V_1.3/App42_Cocos2dX_SDK/Util"
)
WkLibraryBuild( App42SDK STATIC "V_1.3/App42_Cocos2dX_SDK")

#Sample Project
#WkExecutableBuild( App42Sample "App42_Cocos2DX_Sample/App42CPPSDK/Classes")

#Linking with all libraries
#target_link_libraries( App42Sample
#  App42SDK
#  chipmunk
#  cocos2dx
#  #CocosDenshion
#  extensions
#  )
#
#if(WIN32)
#	#also copying dlls to binary directory for the executable to run
#	ADD_CUSTOM_COMMAND( TARGET maintest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
#				"${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll"
#				"$<TARGET_FILE_DIR:maintest>"
#				COMMENT
#			    "Copying ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll to $<TARGET_FILE_DIR:maintest>"
#			    VERBATIM)
#	ADD_CUSTOM_COMMAND( TARGET maintest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
#				"${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll"
#				"$<TARGET_FILE_DIR:maintest>"
#			    COMMENT
#			    "Copying ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll to $<TARGET_FILE_DIR:maintest>"
#			    VERBATIM)
#	ADD_CUSTOM_COMMAND( TARGET maintest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
#				"${COCOS2D_ROOT}/external/curl/prebuilt/win32/libcurl.dll"
#				"$<TARGET_FILE_DIR:maintest>"
#			    COMMENT
#			    "Copying ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll to $<TARGET_FILE_DIR:maintest>"
#			    VERBATIM)
#elseif (UNIX) #assumed linux
#endif()
