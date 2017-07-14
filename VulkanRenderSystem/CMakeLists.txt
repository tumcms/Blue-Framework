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