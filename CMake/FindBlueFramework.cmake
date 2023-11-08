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

find_path(BlueFramework_DIR NAMES BlueFrameworkConfig.cmake PATHS "C:/Program Files/BlueFramework" REQUIRED)

if (MSVC)
	if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")
		set(BLUEFRAMEWORK_ARCHITECTURE "x86")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")
		set(BLUEFRAMEWORK_ARCHITECTURE "x64")
    elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "ARM")
		set(BLUEFRAMEWORK_ARCHITECTURE "arm")
    else()
		message(FATAL_ERROR "Failed to determine the MSVC target architecture: ${MSVC_C_ARCHITECTURE_ID}")
    endif()
	
	if(NOT MSVC_VERSION_STRING)
		if(MSVC_VERSION EQUAL 1900)
			set(MSVC_VERSION_STRING "vs2015")
			set(MSVC_VERSION_YEAR "2015")
		elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS_EQUAL 1919)
			set(MSVC_VERSION_STRING "vs2017")
			set(MSVC_VERSION_YEAR "2017")
		else()
			message("Please switch to Visual Studio 14 2015 or Visual Studio 15 2017.")
			return()
		endif()
	endif()
endif()

if(BlueFramework_FIND_COMPONENTS)
	set(BLUEFRAMEWORK_COMPONENTS ${BlueFramework_FIND_COMPONENTS})
else(BlueFramework_FIND_COMPONENTS)
	set(BLUEFRAMEWORK_COMPONENTS Core Engine Application ImageProcessing Rasterizer D3D11RenderSystem D3D12RenderSystem GLRenderSystem)
endif(BlueFramework_FIND_COMPONENTS)

if(BlueFramework_DIR)
	include(${BlueFramework_DIR}/CMake/BlueFrameworkMacros.cmake)
	set(BLUEFRAMEWORK_INCLUDE_DIR ${BLUEFRAMEWORK_INCLUDE_DIR} ${BlueFramework_DIR}/include/)
	set(BLUEFRAMEWORK_LIBRARY_DIR ${BlueFramework_DIR}/lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/)
	
	foreach(COMP ${BLUEFRAMEWORK_COMPONENTS})
		findInclude(${COMP})		
		findLibs(${COMP})
		findBinaries(${COMP})
	endforeach()
endif()