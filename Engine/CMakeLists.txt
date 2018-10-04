#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2018 Technical University of Munich
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

set(CMAKE_AUTOMOC ON)

file(GLOB BlueFramework_Engine_Camera_Source                   src/BlueFramework/Engine/Camera/*.*)
file(GLOB BlueFramework_Engine_Mesh_Source                     src/BlueFramework/Engine/Mesh/*.*)
file(GLOB BlueFramework_Engine_ResourceManagment_Source        src/BlueFramework/Engine/ResourceManagment/*.*)
file(GLOB BlueFramework_Engine_SDF_Source                      src/BlueFramework/Engine/SDF/*.*)
file(GLOB BlueFramework_Engine_Source                          src/BlueFramework/Engine/*.*)
file(GLOB BlueFramework_Engine_VertexCache_Source              src/BlueFramework/Engine/VertexCache/*.*)
file(GLOB BlueFramework_Engine_ViewCube_Source				   src/BlueFramework/Engine/ViewCube/*.*)

file(GLOB_RECURSE BlueFramework_Engine_Headers				   src/BlueFramework/Engine/*.h)

source_group(BlueFramework\\Engine							FILES ${BlueFramework_Engine_Source})
source_group(BlueFramework\\Engine\\Camera					FILES ${BlueFramework_Engine_Camera_Source})
source_group(BlueFramework\\Engine\\Mesh					FILES ${BlueFramework_Engine_Mesh_Source})
source_group(BlueFramework\\Engine\\ResourceManagment       FILES ${BlueFramework_Engine_ResourceManagment_Source})
source_group(BlueFramework\\Engine\\SDF						FILES ${BlueFramework_Engine_SDF_Source})
source_group(BlueFramework\\Engine\\VertexCache             FILES ${BlueFramework_Engine_VertexCache_Source})
source_group(BlueFramework\\Engine\\ViewCube				FILES ${BlueFramework_Engine_ViewCube_Source})

add_library(BlueFramework.Engine SHARED
	${BlueFramework_Engine_Camera_Source}
	${BlueFramework_Engine_Mesh_Source}
	${BlueFramework_Engine_ResourceManagment_Source}
	#${BlueFramework_Engine_SDF_Source}
	${BlueFramework_Engine_Source}
	${BlueFramework_Engine_VertexCache_Source}
	${BlueFramework_Engine_ViewCube_Source}
)

target_include_directories(BlueFramework.Engine
	PUBLIC
		src
	PRIVATE
		${TINYXML2_INCLUDE_DIR}
)

target_link_libraries(BlueFramework.Engine
	PUBLIC
		BlueFramework.Core
		BlueFramework.Rasterizer
		BlueFramework.ImageProcessing
	PRIVATE
		${TINYXML2_LIB}
		Qt5::Core
		Qt5::Widgets
)

install(TARGETS BlueFramework.Engine
    RUNTIME DESTINATION bin/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
	COMPONENT binaries
    ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
    COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/Engine/ DESTINATION include/BlueFramework/Engine
		COMPONENT include
		FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/BlueFramework/Engine/ DESTINATION src/BlueFramework/Engine
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)
