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

file(GLOB BlueFramework_Rasterizer_Resources_Source                src/BlueFramework/Rasterizer/Resources/*.*)
file(GLOB BlueFramework_Rasterizer_Source                          src/BlueFramework/Rasterizer/*.*)
file(GLOB_RECURSE BlueFramework_Rasterizer_Headers				   src/BlueFramework/Rasterizer/*.h)

source_group(BlueFramework\\Rasterizer\\Resources                  FILES ${BlueFramework_Rasterizer_Resources_Source})
source_group(BlueFramework\\Rasterizer                             FILES ${BlueFramework_Rasterizer_Source})


add_library(BlueFramework.Rasterizer SHARED
    ${BlueFramework_Rasterizer_Descriptions_Source}
    ${BlueFramework_Rasterizer_Resources_Source}
    ${BlueFramework_Rasterizer_Source}
)

target_include_directories(BlueFramework.Rasterizer
	PUBLIC
		src
)

target_link_libraries(BlueFramework.Rasterizer
	PUBLIC
		BlueFramework.Core
		tinyxml2
)

install(TARGETS BlueFramework.Rasterizer
   RUNTIME DESTINATION bin/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT binaries
   ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
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
