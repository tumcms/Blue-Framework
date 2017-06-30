#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016-2017 Technical University of Munich
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

project(BlueFramework.Rasterizer)

file(GLOB BlueFramework_Rasterizer_Resources_Source                src/BlueFramework/Rasterizer/Resources/*.*)
file(GLOB BlueFramework_Rasterizer_Source                          src/BlueFramework/Rasterizer/*.*)

file(GLOB_RECURSE BlueFramework_Rasterizer_Headers				   src/BlueFramework/Rasterizer/*.h)

add_library(BlueFramework.Rasterizer SHARED
    ${BlueFramework_Rasterizer_Descriptions_Source}
    ${BlueFramework_Rasterizer_Resources_Source}
    ${BlueFramework_Rasterizer_Source}
)

include_directories(
	${TINYXML2_INCLUDE_DIR}
)

source_group(BlueFramework\\Rasterizer\\Resources                  FILES ${BlueFramework_Rasterizer_Resources_Source})
source_group(BlueFramework\\Rasterizer                             FILES ${BlueFramework_Rasterizer_Source})

target_link_libraries(BlueFramework.Rasterizer
	BlueFramework.Core
	${TINYXML2_LIB}
)


install(TARGETS BlueFramework.Rasterizer
   RUNTIME DESTINATION bin/${MSVC_VERSION}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT binaries
   ARCHIVE DESTINATION lib/${MSVC_VERSION}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/Rasterizer/
		DESTINATION include/BlueFramework/Rasterizer
		COMPONENT include
		FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/BlueFramework/Rasterizer/ DESTINATION src/BlueFramework/Rasterizer
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)