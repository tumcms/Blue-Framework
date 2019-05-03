#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2019 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#   
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#   
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
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
		${EIGEN3_INCLUDE_DIR}
		src
)

target_link_libraries(BlueFramework.Core
	PUBLIC
		Boost::system
		Boost::boost  
		Boost::log
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