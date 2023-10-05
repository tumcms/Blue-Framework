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

macro(findInclude Module)
	string(TOUPPER ${Module} Module2)	
	
	unset("BLUEFRAMEWORK_${Module2}_INCLUDE_DIR" CACHE)
	find_path("BLUEFRAMEWORK_${Module2}_INCLUDE_DIR" NAMES BlueFramework/${Module}/namespace.h HINTS ${BlueFramework_DIR}/include ${BlueFramework_DIR}/${Module}/src)	
	set(BLUEFRAMEWORK_INCLUDE_DIR ${BLUEFRAMEWORK_INCLUDE_DIR} "${BLUEFRAMEWORK_${Module2}_INCLUDE_DIR}")
endmacro()

macro(findLibs Module)
	string(TOUPPER ${Module} Module2)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG" CACHE)
	find_library("BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG" NAMES BlueFramework.${Module}d.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE" CACHE)
	find_library("BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE" NAMES BlueFramework.${Module}.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Release)
	
	unset("BLUEFRAMEWORK_${Module2}_LIBRARY_RELWITHDEBINFO" CACHE)
	find_library("BLUEFRAMEWORK_${Module2}_LIBRARY_RELWITHDEBINFO" NAMES BlueFramework.${Module}.lib PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	set(BLUEFRAMEWORK_${Module2}_LIBRARY debug "${BLUEFRAMEWORK_${Module2}_LIBRARY_DEBUG}" optimized "${BLUEFRAMEWORK_${Module2}_LIBRARY_RELEASE}")
	set(BLUEFRAMEWORK_LIBRARIES ${BLUEFRAMEWORK_LIBRARIES} "${BLUEFRAMEWORK_${Module2}_LIBRARY}")
endmacro()

macro(findBinaries Module)
	string(TOUPPER ${Module} Module2)
	
	unset("BLUEFRAMEWORK_${Module2}_DLL_DEBUG" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_DLL_RELEASE" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO" CACHE)	
	find_file("BLUEFRAMEWORK_${Module2}_DLL_DEBUG" BlueFramework.${Module}d.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	find_file("BLUEFRAMEWORK_${Module2}_DLL_RELEASE" BlueFramework.${Module}.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Release)
	find_file("BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO" BlueFramework.${Module}.dll PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	
	unset("BLUEFRAMEWORK_${Module2}_PDB_DEBUG" CACHE)
	unset("BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO" CACHE)
	find_file("BLUEFRAMEWORK_${Module2}_PDB_DEBUG" BlueFramework.${Module}d.pdb PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/Debug)
	find_file("BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO" BlueFramework.${Module}.pdb PATHS ${BLUEFRAMEWORK_LIBRARY_DIR}/RelWithDebInfo)
	
	set(BLUEFRAMEWORK_DEBUG_BINARIES ${BLUEFRAMEWORK_DEBUG_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_DEBUG}" "${BLUEFRAMEWORK_${Module2}_PDB_DEBUG}")
	set(BLUEFRAMEWORK_RELEASE_BINARIES ${BLUEFRAMEWORK_RELEASE_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_RELEASE}")
	set(BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES ${BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES} "${BLUEFRAMEWORK_${Module2}_DLL_RELWITHDEBINFO}" "${BLUEFRAMEWORK_${Module2}_PDB_RELWITHDEBINFO}")
endmacro()

function(BLUEFRAMEWORK_COPY_BINARIES TargetDirectory)
	add_custom_target(BlueFrameworkCopyBinaries
		COMMENT "Copying BlueFramwork binaries to '${TargetDirectory}'" VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_DEBUG_BINARIES} ${CMAKE_BINARY_DIR}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_RELEASE_BINARIES} ${CMAKE_BINARY_DIR}/Release
		COMMAND ${CMAKE_COMMAND} -E copy ${BLUEFRAMEWORK_RELWITHDEBINFO_BINARIES} ${CMAKE_BINARY_DIR}/RelWithDebInfo
		
		COMMAND ${CMAKE_COMMAND} -E copy ${BlueFramework_DIR}/Tools/precompileEffectFiles.py ${CMAKE_BINARY_DIR}/Tools/precompileEffectFiles.py
	)
endfunction(BLUEFRAMEWORK_COPY_BINARIES)