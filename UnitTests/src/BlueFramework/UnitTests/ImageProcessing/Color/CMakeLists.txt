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

file(GLOB BlueFramework_UnitTests_ImageProcessing_Color	*.*)

source_group(BlueFramework\\UnitTests\\ImageProcessing FILES ${BlueFramework_UnitTests_ImageProcessing_Color})

add_executable(Color
	${BlueFramework_UnitTests_Source}
	${BlueFramework_UnitTests_ImageProcessing_Color}
)

target_link_libraries(Color 
	BlueFramework.Core
	BlueFramework.ImageProcessing
	${GTEST_BOTH_LIBRARIES}
)

add_test(
    NAME ColorTest
    COMMAND Color
)

set_target_properties(Color PROPERTIES FOLDER "BlueFramework/UnitTests/ImageProcessing")