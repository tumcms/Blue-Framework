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

file(GLOB BlueFramework_VulkanRenderSystem_Source                          src/BlueFramework/VulkanRenderSystem/*.*)

file(GLOB_RECURSE BlueFramework_VulkanRenderSystem_Headers				   src/BlueFramework/VulkanRenderSystem/*.h)

source_group(BlueFramework\\VulkanRenderSystem                             FILES ${BlueFramework_VulkanRenderSystem_Source})

add_library(BlueFramework.VulkanRenderSystem SHARED
    ${BlueFramework_VulkanRenderSystem_Source}
)


target_link_libraries(BlueFramework.VulkanRenderSystem
	BlueFramework.Core
	BlueFramework.Rasterizer	
)

install(TARGETS BlueFramework.VulkanRenderSystem   
   ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/VulkanRenderSystem/ DESTINATION include/BlueFramework/VulkanRenderSystem
		COMPONENT include
		FILES_MATCHING PATTERN "*.h")

install(DIRECTORY src/BlueFramework/VulkanRenderSystem/ DESTINATION src/BlueFramework/VulkanRenderSystem
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)
