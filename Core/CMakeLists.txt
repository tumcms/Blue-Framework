#
#   This file is part of BlueFramework, a simple 3D engine.
#   Copyright (c) 2023 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
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

# TODO: Do not use GLOBbing
file(GLOB BlueFramework_Core_Diagnostics_IC_Source           src/BlueFramework/Core/Diagnostics/ic/*.*)
file(GLOB BlueFramework_Core_Diagnostics_Source              src/BlueFramework/Core/Diagnostics/*.*)
file(GLOB BlueFramework_Core_Math_Source                     src/BlueFramework/Core/Math/*.*)
file(GLOB BlueFramework_Core_UtfConverter_Source             src/BlueFramework/Core/UtfConverter/*.*)
file(GLOB BlueFramework_Core_Source                          src/BlueFramework/Core/*.*)

file(GLOB_RECURSE BlueFramework_Core_Headers				 src/BlueFramework/Core/*.h)

source_group(BlueFramework\\Core\\Diagnostics\\ic            FILES ${BlueFramework_Core_Diagnostics_IC_Source})
source_group(BlueFramework\\Core\\Diagnostics                FILES ${BlueFramework_Core_Diagnostics_Source})
source_group(BlueFramework\\Core\\Math                       FILES ${BlueFramework_Core_Math_Source})
source_group(BlueFramework\\Core\\UtfConverter               FILES ${BlueFramework_Core_UtfConverter_Source})
source_group(BlueFramework\\Core                             FILES ${BlueFramework_Core_Source})

FetchContent_Declare(
	jk_stackwalker
	GIT_REPOSITORY https://github.com/JochenKalmbach/StackWalker
	GIT_TAG 1.20
)
FetchContent_MakeAvailable(jk_stackwalker)

target_compile_definitions(StackWalker PUBLIC _UNICODE)

FetchContent_Declare(
	c42f_tinyformat
	GIT_REPOSITORY https://github.com/c42f/tinyformat
	GIT_TAG v2.3.0
)
FetchContent_MakeAvailable(c42f_tinyformat)

add_library(BlueFramework.Core SHARED
	${BlueFramework_Core_Diagnostics_IC_Source}
    ${BlueFramework_Core_Diagnostics_Source}
    ${BlueFramework_Core_Math_Source}
	${BlueFramework_Core_UtfConverter_Source}
    ${BlueFramework_Core_Source}
)

target_include_directories(BlueFramework.Core
	PUBLIC
		${Boost_INCLUDE_DIR}
		src
		${jk_stackwalker_SOURCE_DIR}/Main/StackWalker
		${c42f_tinyformat_SOURCE_DIR}
)

target_link_libraries(BlueFramework.Core
	PUBLIC
		Boost::system
		Boost::boost  
		Boost::log
		eigen
		StackWalker
)

install(TARGETS BlueFramework.Core
	RUNTIME DESTINATION bin/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
	COMPONENT binaries
	ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
	COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/Core/ DESTINATION include/BlueFramework/Core
		COMPONENT include
        FILES_MATCHING PATTERN "*.h"		
)

install(DIRECTORY src/BlueFramework/Core/ DESTINATION src/BlueFramework/Core
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"		
)