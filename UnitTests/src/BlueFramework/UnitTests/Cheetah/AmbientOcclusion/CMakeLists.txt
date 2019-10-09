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

file(GLOB BlueFramework_UnitTests_Cheetah_AmbientOcclusion	*.*)

source_group(BlueFramework\\UnitTests\\AmbientOcclusion FILES ${BlueFramework_UnitTests_Cheetah_AmbientOcclusion})
source_group(BlueFramework\\UnitTests                   FILES ${BlueFramework_UnitTests_Source})

add_executable(AmbientOcclusion
	${BlueFramework_UnitTests_Cheetah_AmbientOcclusion}
	${BlueFramework_UnitTests_Source}
)

target_link_libraries(AmbientOcclusion
	BlueFramework.Core
	BlueFramework.Cheetah
	gtest
	gtest_main
)

add_test(
    NAME AmbientOcclusionTest
    COMMAND AmbientOcclusion
)

set_target_properties(AmbientOcclusion PROPERTIES FOLDER "BlueFramework/UnitTests/Cheetah")