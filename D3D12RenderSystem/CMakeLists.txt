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

file(GLOB BlueFramework_D3D12RenderSystem_Source                          src/BlueFramework/D3D12RenderSystem/*.*)

file(GLOB_RECURSE BlueFramework_D3D12RenderSystem_Headers				   src/BlueFramework/D3D12RenderSystem/*.h)

source_group(BlueFramework\\D3D12RenderSystem                             FILES ${BlueFramework_D3D12RenderSystem_Source})

add_library(BlueFramework.D3D12RenderSystem SHARED
    ${BlueFramework_D3D12RenderSystem_Source}
)

target_include_directories(BlueFramework.D3D12RenderSystem
	PUBLIC
		src
	PRIVATE
		${TINYXML2_INCLUDE_DIR}
)

target_link_libraries(BlueFramework.D3D12RenderSystem
	PUBLIC
		BlueFramework.Core
		BlueFramework.Rasterizer
	PRIVATE
		${TINYXML2_LIBRARIES}
		#DirectX12 libs linked in source.
)

install(TARGETS BlueFramework.D3D12RenderSystem
   ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/D3D12RenderSystem/ DESTINATION include/BlueFramework/D3D12RenderSystem
		COMPONENT include
		FILES_MATCHING PATTERN "*.h")

install(DIRECTORY src/BlueFramework/D3D12RenderSystem/ DESTINATION src/BlueFramework/D3D12RenderSystem
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)
