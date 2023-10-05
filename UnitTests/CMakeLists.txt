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

FetchContent_Declare(
	dep_gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.11.0
)
 
FetchContent_GetProperties(dep_gtest)
if(NOT dep_gtest_POPULATED)
	FetchContent_Populate(dep_gtest)
	add_subdirectory(${dep_gtest_SOURCE_DIR} ${dep_gtest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


include(CreateEngineUnitTest)

file(GLOB BlueFramework_UnitTests_Source src/BlueFramework/UnitTests/*.*)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Logging)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Version)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/ImageProcessing/Color)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/ImageProcessing/RandomHeightmapGeneration)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/ImageProcessing/Image)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/ClearScreen)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/CopyTextureRegion)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/DrawTriangle)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/MSAA)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/PixelToaster)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/Skybox)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/Snow)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/Testbed)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/Texture1D)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/Texture2D)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/ViewCube)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/TextRendering)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Engine/DrawBoundingBox)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/D3D11RenderSystem)
