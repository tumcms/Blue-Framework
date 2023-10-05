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
