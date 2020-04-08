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

file(GLOB BlueFramework_ImageProcessing_Source                          src/BlueFramework/ImageProcessing/*.*)

file(GLOB_RECURSE BlueFramework_ImageProcessing_Headers				   src/BlueFramework/ImageProcessing/*.h)

source_group(BlueFramework\\ImageProcessing                             FILES ${BlueFramework_ImageProcessing_Source})

add_library(BlueFramework.ImageProcessing SHARED
    ${BlueFramework_ImageProcessing_Source}
)

target_include_directories(BlueFramework.Core
	PUBLIC
		src
)

target_link_libraries(BlueFramework.ImageProcessing
	PUBLIC
		BlueFramework.Core
		Qt5::Widgets
		Qt5::Gui
)

if(TARGET Qt5::windeployqt)
    # execute windeployqt in a tmp directory after build
    add_custom_command(TARGET BlueFramework.ImageProcessing
        POST_BUILD
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
        COMMAND Qt5::windeployqt --dir "${CMAKE_BINARY_DIR}/$<CONFIG>" "$<TARGET_FILE_DIR:BlueFramework.ImageProcessing>/$<TARGET_FILE_NAME:BlueFramework.ImageProcessing>"
    )
endif()

install(
	TARGETS BlueFramework.ImageProcessing
	RUNTIME DESTINATION bin/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
	COMPONENT binaries
	ARCHIVE DESTINATION lib/${MSVC_VERSION_STRING}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
	COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/ImageProcessing/
	DESTINATION include/BlueFramework/ImageProcessing
	COMPONENT include
	FILES_MATCHING PATTERN "*.h" PATTERN "*.inc"
)

install(
	DIRECTORY src/BlueFramework/ImageProcessing/ DESTINATION src/BlueFramework/ImageProcessing
	COMPONENT source
    FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h" PATTERN "*.inc"
)