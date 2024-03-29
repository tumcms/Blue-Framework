#
#   This file is part of BlueFramework, a simple 3D engine.
#   Copyright (c) 2023 Technical University of Munich
#   Chair of Computational Modeling and Simulation.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

cmake_minimum_required(VERSION 3.14.3) # Kittens will die if you switch to an earlier version of CMake.
cmake_policy(VERSION 3.14.3)
 
project(BlueFramework CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)
include(ProjectVersion)
include(FetchContent)
find_package(Git REQUIRED)


#------------------------------------------------------------------------------
# Check for Microsoft VisualStudio version and processor architecture.
#------------------------------------------------------------------------------

if(MSVC_VERSION EQUAL 1900)
	set(MSVC_VERSION_STRING "vs2015")
	set(MSVC_VERSION_YEAR "2015")
elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS_EQUAL 1919)
	set(MSVC_VERSION_STRING "vs2017")
	set(MSVC_VERSION_YEAR "2017")
	set(CMAKE_CXX_STANDARD 17)
elseif(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS_EQUAL 1930)
	set(MSVC_VERSION_STRING "vs2019")
	set(MSVC_VERSION_YEAR "2019")
	set(CMAKE_CXX_STANDARD 20)
else()
	message(${MSVC_VERSION})
	message("Please switch to Visual Studio 14 2015 or Visual Studio 15 2017.")
	return()
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("Please switch to x64 build.")
	return()
endif()

#------------------------------------------------------------------------------
# Fix for MSVC 1915 / Visual Studio 2017 15.8
#------------------------------------------------------------------------------

if(MSVC_VERSION GREATER_EQUAL 1915)
	add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)
endif()

#------------------------------------------------------------------------------
# Create folders for different build configurations (if they do not exist) to 
# prevent problems with Copy*** scripts
#------------------------------------------------------------------------------

if(EXISTS ${CMAKE_BINARY_DIR}/Debug)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/Release)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/RelWithDebInfo)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/RelWithDebInfo)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/MinSizeRel)
else()
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/MinSizeRel)
endif()

option(BLUEFRAMEWORK_USE_PREDEFINED_THIRDPARTY_PATH "Set to ON to set boost, Eigen and Qt path" OFF)

if(BLUEFRAMEWORK_USE_PREDEFINED_THIRDPARTY_PATH)
    # Try to find Boost, Eigen3, Qt5 and other dependencies without user input
    find_path(BOOST_ROOT NAMES boost/version.hpp HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_65_1" "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_64_0" "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\boost_1_63_0")
    find_path(EIGEN3_INCLUDE_DIR NAMES Eigen/Core HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\Eigen_3.3.4")
    find_path(CMAKE_PREFIX_PATH NAMES include/QtCore/QObject HINTS 
				"C:\\Qt\\Qt5.9.0\\5.9\\msvc${MSVC_VERSION_YEAR}_64" 
				"C:\\Qt\\5.9\\msvc${MSVC_VERSION_YEAR}_64" 
				"C:\\Qt\\Qt5.9.1\\5.9.1\\msvc${MSVC_VERSION_YEAR}_64" 
				"C:\\Qt\\5.9.2\\msvc${MSVC_VERSION_YEAR}_64" 
				"C:\\Qt\\Qt5.9.3\\5.9.3\\msvc${MSVC_VERSION_YEAR}_64"
				"C:\\Qt\\5.10.0\\msvc${MSVC_VERSION_YEAR}_64"
				"C:\\Qt\\5.10.1\\msvc${MSVC_VERSION_YEAR}_64"
				"E:\\Qt\\5.12.3\\msvc${MSVC_VERSION_YEAR}_64")
    find_path(GLEW_ROOT NAMES include/GL/glew.h HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\glew-2.0.0")
    find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-release-1.8.0" "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\googletest-1.8.0")
    find_path(TINYXML2_ROOT NAMES tinyxml2.h HINTS "C:\\thirdparty\\${MSVC_VERSION_STRING}\\x64\\tinyxml2-master")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG     		${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG         		${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE   		${CMAKE_BINARY_DIR}/Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE       		${CMAKE_BINARY_DIR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO   ${CMAKE_BINARY_DIR}/RelWithDebInfo)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELWITHDEBINFO       ${CMAKE_BINARY_DIR}/RelWithDebInfo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL   	${CMAKE_BINARY_DIR}/MinSizeRel)
set(CMAKE_PDB_OUTPUT_DIRECTORY_MINSIZEREL       	${CMAKE_BINARY_DIR}/MinSizeRel)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER AutoMoc)

add_compile_definitions(
  EIGEN_MPL2_ONLY # Use only MP2 licenced code of Eigen
  NOMINMAX
  _UNICODE # Unicode rules https://docs.microsoft.com/en-us/cpp/text/unicode-programming-summary?view=msvc-160
)

set(CMAKE_DEBUG_POSTFIX "d")

# Compiler settings
if (WIN32)
  # Standard:          /DWIN32 /D_WINDOWS /W3 /Zm1000 /EHsc /GR
  set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /Zi /EHsc /GR /MP /openmp /bigobj")
endif (WIN32)

# remember the Kittens... do not switch to earlier versions...
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.75.0 COMPONENTS log system filesystem REQUIRED) # we suggest Boost 1.75.0

FetchContent_Declare(
	eigen
	GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror.git
	GIT_TAG 3.3.7
)
FetchContent_MakeAvailable(eigen)

FetchContent_Declare(
	tinyxml2
	GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
	GIT_TAG 7.1.0
)
  
FetchContent_GetProperties(tinyxml2)
if(NOT tinyxml2_POPULATED)
	FetchContent_Populate(tinyxml2)
	add_subdirectory(${tinyxml2_SOURCE_DIR} ${tinyxml2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# find_package(Vulkan REQUIRED)

# Qt library (do not switch to earlier versions... meow!)
cmake_policy(SET CMP0020 NEW)

find_package(Qt5 5.14.2 COMPONENTS Core Widgets Xml XmlPatterns REQUIRED)

if(Qt5_FOUND AND WIN32 AND TARGET Qt5::qmake AND NOT TARGET Qt5::windeployqt)
    get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)

    execute_process(
        COMMAND "${_qt5_qmake_location}" -query QT_INSTALL_PREFIX
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE qt5_install_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(imported_location "${qt5_install_prefix}/bin/windeployqt.exe")

    if(EXISTS ${imported_location})
        add_executable(Qt5::windeployqt IMPORTED)

        set_target_properties(Qt5::windeployqt PROPERTIES
            IMPORTED_LOCATION ${imported_location}
        )
    endif()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC OFF)

add_subdirectory(Application)
add_subdirectory(Core)
add_subdirectory(D3D11RenderSystem)
add_subdirectory(D3D12RenderSystem)
add_subdirectory(GLRenderSystem)
#add_subdirectory(VulkanRenderSystem)
add_subdirectory(Engine)
add_subdirectory(ImageProcessing)
add_subdirectory(Rasterizer)
add_subdirectory(UnitTests)

if(TARGET Qt5::windeployqt)
    # execute windeployqt in a tmp directory after build
    add_custom_target(ExecuteQtDeployTool
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
        COMMAND Qt5::windeployqt -xml ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    )
endif()

# Development
set_target_properties(BlueFramework.Application            PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.Core                   PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.D3D11RenderSystem      PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.D3D12RenderSystem      PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.GLRenderSystem        PROPERTIES FOLDER "BlueFramework")
#set_target_properties(BlueFramework.VulkanRenderSystem     PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.Engine                 PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.Rasterizer             PROPERTIES FOLDER "BlueFramework")
set_target_properties(BlueFramework.ImageProcessing        PROPERTIES FOLDER "BlueFramework")

#include(ExecuteQtDeployTool)
#set_target_properties(ExecuteQtDeployTool                 	 PROPERTIES FOLDER "Copy")

# Copy libs
macro(AddCopyCommandForModule module target dest)
	add_custom_command(TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${module}> ${dest}/$<CONFIG>/$<TARGET_FILE_NAME:${module}> VERBATIM)
	add_custom_command(TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:${module}> ${dest}/$<CONFIG>/$<TARGET_LINKER_FILE_NAME:${module}> VERBATIM)
	add_custom_command(TARGET ${target} COMMAND ${CMAKE_COMMAND} -E copy $<IF:$<OR:$<CONFIG:release>,$<CONFIG:minsizerel>>,$<TARGET_LINKER_FILE:${module}>,$<TARGET_PDB_FILE:${module}>> $<IF:$<OR:$<CONFIG:release>,$<CONFIG:minsizerel>>,${dest}/$<CONFIG>/$<TARGET_LINKER_FILE_NAME:${module}>,${dest}/$<CONFIG>/$<TARGET_PDB_FILE_NAME:${module}>> VERBATIM)	
endmacro()

macro(AddCopyCommandForAll target dest)
	AddCopyCommandForModule(BlueFramework.Application ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.Core ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.D3D11RenderSystem ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.D3D12RenderSystem ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.GLRenderSystem ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.Engine ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.ImageProcessing ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.ImageProcessing ${target} ${dest})
	AddCopyCommandForModule(BlueFramework.Rasterizer ${target} ${dest})
endmacro()

add_custom_target(UpdateLibsAndDLLsForCurrentBuildConfiguration
	DEPENDS BlueFramework.Application
	DEPENDS BlueFramework.Core
	DEPENDS BlueFramework.D3D11RenderSystem
	DEPENDS BlueFramework.D3D12RenderSystem
	DEPENDS BlueFramework.GLRenderSystem
	DEPENDS BlueFramework.Engine
	DEPENDS BlueFramework.ImageProcessing
	DEPENDS BlueFramework.ImageProcessing
	DEPENDS BlueFramework.Rasterizer
	COMMENT "Copying BlueFramework Libraries ..." VERBATIM

	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/RelWithDebInfo
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/MinSizeRel
)

AddCopyCommandForAll(UpdateLibsAndDLLsForCurrentBuildConfiguration "${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/")

add_custom_target(UpdateLibsAndDLLs
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config debug
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config release
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config relWithDebInfo
	COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config minSizeRel
	COMMENT "Copying BlueFramework Libraries ..." VERBATIM

	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/Debug
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/Release
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/RelWithDebInfo
	COMMAND ${CMAKE_COMMAND} -E make_directory ${LIB_DIR}/MinSizeRel
)

AddCopyCommandForAll(UpdateLibsAndDLLs "${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/")
	
add_custom_target(DEPLOY  
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config debug
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config release
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config relWithDebInfo
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target UpdateLibsAndDLLsForCurrentBuildConfiguration --config minSizeRel
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ExecuteQtDeployTool
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target PACKAGE
)

#-------------------------------------------------------------------------------------
# Deployment
set(CPACK_GENERATOR WIX)
set(CPACK_WIX_UPGRADE_GUID "F9D5D0DC-9801-4EC5-A72F-98A21CD8A436")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "https://www.cms.bgu.tum.de/en/")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BlueFramework")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TEWAK "${PROJECT_VERSION_TWEAK}}")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "BlueFramework")

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY "${PROJECT_NAME}")

include(CPackComponent)

set(CPACK_COMPONENTS_ALL "cmake;include;source;library_release;library_debug;library_relwithdebinfo;library_minsizerel")

cpack_add_install_type(default DISPLAY_NAME "Default")

cpack_add_component_group(library_files DISPLAY_NAME "Libraries"
  DESCRIPTION "The library files used by the application (*.lib *.dll)"
)

cpack_add_component_group(library DISPLAY_NAME "Libraries"
  DESCRIPTION "The library files used by the application (*.lib *.dll)"
)

cpack_add_component(library_release DISPLAY_NAME "Release" GROUP library INSTALL_TYPES default)
cpack_add_component(library_debug DISPLAY_NAME "Debug" GROUP library INSTALL_TYPES default)
cpack_add_component(library_relwithdebinfo DISPLAY_NAME "RelWithDebInfo" GROUP library INSTALL_TYPES default)
cpack_add_component(library_minsizerel DISPLAY_NAME "MinSizeRel" GROUP library INSTALL_TYPES default)


cpack_add_component(include DISPLAY_NAME "Header Files"
  DESCRIPTION "The header files (*.h)"
  INSTALL_TYPES default source
)

cpack_add_component(source DISPLAY_NAME "Source Files"
  DESCRIPTION "The source code files (*.h *.cpp)"
  INSTALL_TYPES default source
)

cpack_add_component(cmake DISPLAY_NAME "CMake Integration" DESCRIPTION "Allow applications to find BlueFramework using 'find_package' command." INSTALL_TYPES default)


install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/Debug/ DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/Debug
    COMPONENT library_debug
    FILES_MATCHING PATTERN "*.dll" PATTERN "*.lib" PATTERN "*.pdb")

install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/Release/ DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/Release
    COMPONENT library_release
    FILES_MATCHING PATTERN "*.dll" PATTERN "*.lib")
	
install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/RelWithDebInfo/ DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/RelWithDebInfo
    COMPONENT library_relwithdebinfo
    FILES_MATCHING PATTERN "*.dll" PATTERN "*.lib" PATTERN "*.pdb")
	
install(DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${MSVC_VERSION_STRING}/x64/MinSizeRel/ DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/MinSizeRel
    COMPONENT library_minsizerel
    FILES_MATCHING PATTERN "*.dll" PATTERN "*.lib")

	
install(DIRECTORY include/ DESTINATION include
		COMPONENT include
        FILES_MATCHING PATTERN "*.h"		
)
file(GLOB BLUEFRAMEWORK_CONFIG ${PROJECT_SOURCE_DIR}/CMake/FindBlueFramework.cmake)
file(GLOB BLUEFRAMEWORK_MACROS ${PROJECT_SOURCE_DIR}/CMake/BlueFrameworkMacros.cmake)
file(WRITE ${CMAKE_BINARY_DIR}/BlueFrameworkConfigVersion.cmake "set(PACKAGE_VERSION \"${CPACK_PACKAGE_VERSION}\") \nset(PACKAGE_VERSION_EXACT True) \nset(PACKAGE_VERSION_COMPATIBLE True) \nset(PACKAGE_VERSION_UNSUITABLE False)")
file(COPY ${BLUEFRAMEWORK_CONFIG} DESTINATION ${PROJECT_SOURCE_DIR})
file(COPY ${CMAKE_BINARY_DIR}/BlueFrameworkConfigVersion.cmake DESTINATION ${PROJECT_SOURCE_DIR})
file(RENAME "FindBlueFramework.cmake" "BlueFrameworkConfig.cmake")
install(FILES ${BLUEFRAMEWORK_CONFIG} DESTINATION / COMPONENT cmake RENAME "BlueFrameworkConfig.cmake")
install(FILES ${BLUEFRAMEWORK_MACROS} DESTINATION CMake COMPONENT cmake)
install(FILES ${CMAKE_BINARY_DIR}/BlueFrameworkConfigVersion.cmake DESTINATION / COMPONENT cmake)

include(CPack)
