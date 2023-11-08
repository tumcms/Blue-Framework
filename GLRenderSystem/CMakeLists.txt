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

find_package(OpenGL REQUIRED)

FetchContent_Declare(
	glew
	URL https://sourceforge.net/projects/glew/files/glew/2.0.0/glew-2.0.0.zip/download
)
  
if(NOT glew_POPULATED)
	FetchContent_Populate(glew)
	add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_SOURCE_DIR}/build EXCLUDE_FROM_ALL)
endif()

get_target_property(glew_INCLUDE_DIR glew_s INCLUDE_DIRECTORIES)

file(GLOB_RECURSE
	BlueFramework_GLRenderSystem_Source
	LIST_DIRECTORIES false
	src/BlueFramework/GLRenderSystem/*.*
)

file(GLOB_RECURSE
	BlueFramework_GLRenderSystem_Headers
	LIST_DIRECTORIES false
	src/BlueFramework/GLRenderSystem/*.h
)

source_group(BlueFramework\\GLRenderSystem
	FILES ${BlueFramework_GLRenderSystem_Source}
)

add_library(BlueFramework.GLRenderSystem
	SHARED
	${BlueFramework_GLRenderSystem_Source}
)

target_include_directories(BlueFramework.GLRenderSystem
	PUBLIC
		src
		${glew_INCLUDE_DIR}
)

target_link_libraries(BlueFramework.GLRenderSystem
	PUBLIC
		BlueFramework.Core
		BlueFramework.Rasterizer
		glew_s
		tinyxml2
	PRIVATE
		${OPENGL_gl_LIBRARY}
)

install(TARGETS BlueFramework.GLRenderSystem   
   ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/GLRenderSystem/ DESTINATION include/BlueFramework/GLRenderSystem
		COMPONENT include
        FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/BlueFramework/GLRenderSystem/ DESTINATION src/BlueFramework/GLRenderSystem
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)
