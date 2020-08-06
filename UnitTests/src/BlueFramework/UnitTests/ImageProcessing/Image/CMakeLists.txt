#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2020 Technical University of Munich
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

file(GLOB BlueFramework_UnitTests_ImageProcessing_Image	*.*)

source_group(BlueFramework\\UnitTests\\ImageProcessing FILES ${BlueFramework_UnitTests_ImageProcessing_Image})

add_executable(Image
	${BlueFramework_UnitTests_Source}
	${BlueFramework_UnitTests_ImageProcessing_Image}
)


target_link_libraries(Image 
	BlueFramework.Core
	BlueFramework.ImageProcessing
	gtest
	gtest_main
)

add_test(
    NAME ImageTest
    COMMAND Image
)

set_target_properties(Image PROPERTIES FOLDER "BlueFramework/UnitTests/ImageProcessing")