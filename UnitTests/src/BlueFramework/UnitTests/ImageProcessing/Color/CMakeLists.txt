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

file(GLOB BlueFramework_UnitTests_ImageProcessing_Color	*.*)

source_group(BlueFramework\\UnitTests\\ImageProcessing FILES ${BlueFramework_UnitTests_ImageProcessing_Color})

add_executable(Color
	${BlueFramework_UnitTests_Source}
	${BlueFramework_UnitTests_ImageProcessing_Color}
)


target_link_libraries(Color 
	BlueFramework.Core
	BlueFramework.ImageProcessing
	gtest
	gtest_main
)

add_test(
    NAME ColorTest
    COMMAND Color
)

set_target_properties(Color PROPERTIES FOLDER "BlueFramework/UnitTests/ImageProcessing")
