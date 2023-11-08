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
