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

# Math
file(GLOB BlueFramework_UnitTests_Core_Math	*.*)

source_group(BlueFramework\\UnitTests\\Math FILES ${BlueFramework_UnitTests_Core_Math})
source_group(BlueFramework\\UnitTests       FILES ${BlueFramework_UnitTests_Source})

add_executable(Math
	${BlueFramework_UnitTests_Source}
	${BlueFramework_UnitTests_Core_Math}
)

target_include_directories(Math
	PRIVATE
		${GTEST_INCLUDE_DIRS}
)

target_link_libraries(Math 
	PRIVATE
		BlueFramework.Core
		${GTEST_BOTH_LIBRARIES}
)

add_test(
    NAME MathTest
    COMMAND Math
)

set_target_properties(Math PROPERTIES FOLDER "BlueFramework/UnitTests/Core")