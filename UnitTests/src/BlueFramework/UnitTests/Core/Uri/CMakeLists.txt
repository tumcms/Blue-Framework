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
file(GLOB BlueFramework_UnitTests_Core_Uri	*.*)

source_group(BlueFramework\\UnitTests\\Uri	   FILES ${BlueFramework_UnitTests_Core_Uri})
source_group(BlueFramework\\UnitTests          FILES ${BlueFramework_UnitTests_Source})

add_executable(Uri
	${BlueFramework_UnitTests_Source}
	${BlueFramework_UnitTests_Core_Uri}
)

target_include_directories(Uri
	PRIVATE
		${GTEST_INCLUDE_DIRS}
)

target_link_libraries(Uri
	PRIVATE
		BlueFramework.Core
		${GTEST_BOTH_LIBRARIES}
)

add_test(
    NAME UriTest
    COMMAND Uri
)

set_target_properties(Uri PROPERTIES FOLDER "BlueFramework/UnitTests/Core")