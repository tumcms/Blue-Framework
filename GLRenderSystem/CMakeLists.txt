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

set(CMAKE_PREFIX_PATH ${GLEW_ROOT};${CMAKE_PREFIX_PATH})
set(CMAKE_LIBRARY_PATH ${GLEW_ROOT}/lib/Release/x64;${CMAKE_LIBRARY_PATH})

file(GLOB_RECURSE
	BlueFramework_GLRenderSystem_Source
	LIST_DIRECTORIES false
	src/BlueFramework/GLRenderSystem/*.*)

file(GLOB_RECURSE
	BlueFramework_GLRenderSystem_Headers
	LIST_DIRECTORIES false
	src/BlueFramework/GLRenderSystem/*.h)

source_group(BlueFramework\\GLRenderSystem
	FILES ${BlueFramework_GLRenderSystem_Source})

add_library(BlueFramework.GLRenderSystem
	SHARED
	${BlueFramework_GLRenderSystem_Source})

target_include_directories(BlueFramework.GLRenderSystem
	PUBLIC
		src
	PRIVATE
		${GLEW_INCLUDE_DIRS}
		${TINYXML2_INCLUDE_DIR}
)

target_link_libraries(BlueFramework.GLRenderSystem
	PUBLIC
		BlueFramework.Core
		BlueFramework.Rasterizer
	PRIVATE
		${GLEW_LIBRARIES}
		${OPENGL_gl_LIBRARY}
		${TINYXML2_LIB}
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
