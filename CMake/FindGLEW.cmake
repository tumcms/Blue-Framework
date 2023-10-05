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
# 	This module defines the following variables:
#
#   GLEW_INCLUDE_DIRS - include directories for GLEW
#   GLEW_LIBRARIES - libraries to link against GLEW
#   GLEW_FOUND - true if GLEW has been found and can be used
#

if(NOT GLEW_ROOT)
	set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
	find_package(glew REQUIRED)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)
	
	if(NOT GLEW_FOUND)
		find_path(GLEW_ROOT NAMES include/GL/glew.h REQUIRED)
	endif()
endif()

if(NOT GLEW_FOUND AND NOT GLEW_ROOT)
	option(GLEW_AUTOMATIC_INSTALL OFF)
	if(NOT GLEW_INSTALL_DIR)
		set(GLEW_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	endif()
	if(GLEW_AUTOMATIC_INSTALL AND GLEW_INSTALL_DIR)
		MESSAGE(STATUS "Installing glew...")
		if(${MSVC_VERSION_STRING} STREQUAL "vs2015")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_glew-2.0.0_Visual Studio 14 2015 Win64.cmd"
				${GLEW_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_glew.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_glew.txt")
		elseif(${MSVC_VERSION_STRING} STREQUAL "vs2017")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_glew-2.0.0_Visual Studio 15 2017 Win64.cmd"
				${GLEW_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_glew.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_glew.txt")
		else()
			message(FATAL_ERROR "Couldn't determine VS version.")
		endif()
		set(GLEW_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install glew" FORCE)
		if(RESULT EQUAL 0)
			message(STATUS "Successfully installed GLEW.")
			set(GLEW_ROOT ${GLEW_INSTALL_DIR}/glew-2.0.0 CACHE PATH "Glew root directory" FORCE)
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_glew.txt")
		endif()
	endif()
endif()

if(NOT GLEW_FOUND AND GLEW_ROOT)
	message(STATUS "Found GLEW_ROOT: ${GLEW_ROOT}")
	if(NOT GLEW_LIBRARY_DEBUG AND NOT GLEW_LIBRARY_RELEASE)
		find_library(GLEW_LIBRARY_DEBUG NAMES libglew32d.lib PATHS ${GLEW_ROOT}/build/lib/Debug)
		find_library(GLEW_LIBRARY_RELEASE NAMES libglew32.lib PATHS ${GLEW_ROOT}/build/lib/Release)
		find_library(GLEW_LIBRARY_RELWITHDEBINFO NAMES libglew32.lib PATHS ${GLEW_ROOT}/build/lib/RelWithDebInfo)
		find_path(GLEW_INCLUDE_DIR NAMES GL/glew.h PATHS ${GLEW_ROOT}/include)
		add_definitions(-DGLEW_STATIC)
		MESSAGE(STATUS "Using GLEW static libraries.")
	else()
		string(FIND "${GLEW_LIBRARY_DEBUG}" "libglew32" GLEW_STATIC_DEBUG)
		string(FIND "${GLEW_LIBRARY_RELEASE}" "libglew32" GLEW_STATIC_RELEASE)
		if(NOT "${GLEW_STATIC_DEBUG}" EQUAL "-1" OR NOT "${GLEW_STATIC_RELEASE}" EQUAL "-1")
			add_definitions(-DGLEW_STATIC)
			MESSAGE(STATUS "Using GLEW static libraries.")
		endif()		
	endif()
endif()

if(GLEW_LIBRARY_DEBUG AND GLEW_LIBRARY_RELEASE)
	set(GLEW_LIBRARY debug "${GLEW_LIBRARY_DEBUG}" optimized "${GLEW_LIBRARY_RELEASE}")
	set(GLEW_LIBRARIES ${GLEW_LIBRARY})
	message(STATUS "Found GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
else()
	unset(GLEW_LIBRARY)
	unset(GLEW_LIBRARIES)
endif()

if(GLEW_INCLUDE_DIR)
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
	message(STATUS "Found GLEW_INCLUDE_DIR: ${GLEW_INCLUDE_DIR}")
else()
	unset(GLEW_INCLUDE_DIRS)
endif()
	
if(GLEW_LIBRARY AND GLEW_INCLUDE_DIR)
	set(GLEW_FOUND 1)
else()
	unset(GLEW_FOUND)
endif()

if(GLEW_LIBRARIES AND GLEW_INCLUDE_DIRS AND GLEW_FOUND)
	message(STATUS "Successfully found GLEW.")
else()
	message("Missing GLEW components!")
	message("GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
	message("GLEW_INCLUDE_DIR: ${GLEW_INCLUDE_DIR}")
	message(FATAL_ERROR "Configuration process failed!")
endif()
