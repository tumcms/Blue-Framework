#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016 Technical University of Munich
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

include(CreateEngineUnitTest)

file(GLOB BlueFramework_UnitTests_Source src/BlueFramework/UnitTests/*.*)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Logging)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/Core/Version)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/ImageProcessing/Color)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/BlueFramework/UnitTests/ImageProcessing/RandomHeightmapGeneration)

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
