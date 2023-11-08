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
#	This module defines the following variables:
#
#   GTEST_INCLUDE_DIRS
#	GTEST_MAIN_LIBRARIES
#   GTEST_LIBRARIES
#	GTEST_BOTH_LIBRARIES
#	GTEST_RELEASE_BINARIES
#	GTEST_DEBUG_BINARIES
#	GTEST_RELWITHDEBINFO_BINARIES
#   GTEST_FOUND
#
find_path(GTEST_ROOT NAMES googletest/include/gtest/gtest.h googlemock/include/gmock/gmock.h  REQUIRED)

if(NOT GTEST_ROOT)
	set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules)
	find_package(gtest)
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/)
	
	set(GTEST_INSTALL_DIR "C:/thirdparty/${MSVC_VERSION_STRING}/x64" CACHE FILEPATH "Please specify an installation directory.")
	option(GTEST_AUTOMATIC_INSTALL OFF)
	if(GTEST_AUTOMATIC_INSTALL AND GTEST_INSTALL_DIR)
		message(STATUS "Installing GTest...")
		if(${MSVC_VERSION_STRING} STREQUAL "vs2015")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_googletest-1.8.0_Visual Studio 14 2015 Win64.cmd"
				${GTEST_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt")
		elseif(${MSVC_VERSION_STRING} STREQUAL "vs2017")
			execute_process(COMMAND "${PROJECT_SOURCE_DIR}/external/Build_googletest-1.8.0_Visual Studio 15 2017 Win64.cmd"
				${GTEST_INSTALL_DIR}
				"${CMAKE_COMMAND}"
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external
				RESULT_VARIABLE RESULT
				ERROR_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt"
				OUTPUT_FILE "${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt")
		else()
			message(FATAL_ERROR "Couldn't determine VS version.")
		endif()
		if(RESULT EQUAL 0)
			set(GTEST_ROOT ${GTEST_INSTALL_DIR}/googletest-release-1.8.0 CACHE PATH "GTest root" FORCE)
			message(STATUS "Successfully installed GTest.")
		else()
			message(SEND_ERROR "Installation failed. Processes exited with code ${RESULT}. Output was written to ${PROJECT_SOURCE_DIR}/external/log_install_gtest.txt")
		endif()
		set(GTEST_AUTOMATIC_INSTALL OFF CACHE BOOL "Automatically install GTest" FORCE)
	endif()
endif()

if(GTEST_ROOT)
	find_path(GTEST_INCLUDE_DIR NAMES gtest/gtest.h HINTS "${GTEST_ROOT}/googletest/include")

	find_library(GTEST_LIBRARY_RELEASE NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_LIBRARY_DEBUG NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_library(GTEST_LIBRARY_RELWITHDEBINFO NAMES gtest.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	find_file(GTEST_LIBRARY_RELEASE_DLL NAMES gtest.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_file(GTEST_LIBRARY_DEBUG_DLL NAMES gtest.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_file(GTEST_LIBRARY_RELWITHDEBINFO_DLL NAMES gtest.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	find_file(GTEST_LIBRARY_DEBUG_PDB NAMES gtest.pdb HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_file(GTEST_LIBRARY_RELWITHDEBINFO_PDB NAMES gtest.pdb HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	find_library(GTEST_MAIN_LIBRARY_RELEASE NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_library(GTEST_MAIN_LIBRARY_DEBUG NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_library(GTEST_MAIN_LIBRARY_RELWITHDEBINFO NAMES gtest_main.lib HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	find_file(GTEST_MAIN_LIBRARY_RELEASE_DLL NAMES gtest_main.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/Release/")
	find_file(GTEST_MAIN_LIBRARY_DEBUG_DLL NAMES gtest_main.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_file(GTEST_MAIN_LIBRARY_RELWITHDEBINFO_DLL NAMES gtest_main.dll HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	find_file(GTEST_MAIN_LIBRARY_DEBUG_PDB NAMES gtest_main.pdb HINTS "${GTEST_ROOT}/build/googlemock/gtest/Debug/")
	find_file(GTEST_MAIN_LIBRARY_RELWITHDEBINFO_PDB NAMES gtest_main.pdb HINTS "${GTEST_ROOT}/build/googlemock/gtest/RelWithDebInfo/")
	
	if(GTEST_LIBRARY_RELEASE AND GTEST_LIBRARY_DEBUG)
		set(GTEST_LIBRARIES debug "${GTEST_LIBRARY_DEBUG}" optimized "${GTEST_LIBRARY_RELEASE}")
	endif()
	if(GTEST_MAIN_LIBRARY_RELEASE AND GTEST_MAIN_LIBRARY_DEBUG)
		set(GTEST_MAIN_LIBRARIES debug "${GTEST_MAIN_LIBRARY_DEBUG}" optimized "${GTEST_MAIN_LIBRARY_RELEASE}")
	endif()
	
	if(GTEST_LIBRARY_RELEASE_DLL AND GTEST_MAIN_LIBRARY_RELEASE_DLL)
		set(GTEST_RELEASE_BINARIES "${GTEST_LIBRARY_RELEASE_DLL}" "${GTEST_MAIN_LIBRARY_RELEASE_DLL}")
	endif()
	
	if(GTEST_LIBRARY_DEBUG_DLL AND GTEST_MAIN_LIBRARY_DEBUG_DLL AND GTEST_LIBRARY_DEBUG_PDB AND GTEST_MAIN_LIBRARY_DEBUG_PDB)
		set(GTEST_DEBUG_BINARIES 
			"${GTEST_LIBRARY_DEBUG_DLL}"
			"${GTEST_MAIN_LIBRARY_DEBUG_DLL}"
			"${GTEST_LIBRARY_DEBUG_PDB}"
			"${GTEST_MAIN_LIBRARY_DEBUG_PDB}")
	endif()
	
	if(GTEST_LIBRARY_RELWITHDEBINFO_DLL AND GTEST_MAIN_LIBRARY_RELWITHDEBINFO_DLL AND GTEST_LIBRARY_DEBUG_PDB AND GTEST_MAIN_LIBRARY_DEBUG_PDB)
		set(GTEST_RELWITHDEBINFO_BINARIES
			"${GTEST_LIBRARY_RELWITHDEBINFO_DLL}"
			"${GTEST_MAIN_LIBRARY_RELWITHDEBINFO_DLL}"
			"${GTEST_LIBRARY_RELWITHDEBINFO_PDB}"
			"${GTEST_MAIN_LIBRARY_RELWITHDEBINFO_PDB}")
	endif()
	
	if(GTEST_MAIN_LIBRARIES AND GTEST_LIBRARIES)
		set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
	endif()
	
	if(GTEST_INCLUDE_DIR)
		set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIR})
	endif()
	
	#add_library(GTest::GTest UNKNOWN IMPORTED)
	#set_target_properties(GTest::GTest PROPERTIES
	#	IMPORTED_LINK_INTERFACE_LIBRARIES "CXX"
	#	IMPORTED_LOCATION "${GTEST_LIBRARIES}"
	#	INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}"
	#)
	#
	#add_library(GTest::Main UNKNOWN IMPORTED)
	#set_target_properties(GTest::Main PROPERTIES
	#	IMPORTED_LINK_INTERFACE_LIBRARIES "CXX"
	#	IMPORTED_LOCATION "${GTEST_MAIN_LIBRARIES}"
	#	INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}"
	#)
endif()

if(GTEST_BOTH_LIBRARIES AND GTEST_INCLUDE_DIRS)
	set(GTEST_FOUND 1)
	message(STATUS "Successfully found GTest.")
else()
	unset(GTEST_FOUND)
	message(FATAL_ERROR "Could NOT find GTest.")
endif()
	
if(GTEST_RELEASE_BINARIES AND GTEST_DEBUG_BINARIES AND GTEST_RELWITHDEBINFO_BINARIES)
	function(GTEST_COPY_BINARIES TargetDirectory)
		add_custom_target(GTestCopyBinaries
			COMMENT "Copying googletest binaries to '${TargetDirectory}'" VERBATIM
			COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_RELEASE_BINARIES} ${TargetDirectory}/Release
			COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_DEBUG_BINARIES} ${TargetDirectory}/Debug
			COMMAND ${CMAKE_COMMAND} -E copy ${GTEST_RELWITHDEBINFO_BINARIES} ${TargetDirectory}/RelWithDebInfo		
		)
	endfunction(GTEST_COPY_BINARIES)
	
	GTEST_COPY_BINARIES(${CMAKE_BINARY_DIR})
endif()