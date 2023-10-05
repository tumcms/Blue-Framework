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

function(CreateRenderSystemUnitTest RenderSystemName UnitTestName)

set(TestExeName ${RenderSystemName}.${UnitTestName})

file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest					*.cpp *.h)
file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader			Shader/*.*)
file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader_${RenderSystemName}		Shader/${RenderSystemName}/*.*)

source_group(${RenderSystemName}\\${UnitTestName}					                FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest})
source_group(${RenderSystemName}\\${UnitTestName}\\Shader			                FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader})
source_group(${RenderSystemName}\\${UnitTestName}\\Shader\\${RenderSystemName}		FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader_${RenderSystemName}})

add_executable(${TestExeName}
    ${BlueFramework_BLUE_TEST}
    ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest}
    ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader}
    ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader_${RenderSystemName}}
)

target_link_libraries(${TestExeName}
    PRIVATE
        BlueFramework.Core
        BlueFramework.Rasterizer
        BlueFramework.${RenderSystemName}
        gtest
        gtest_main
)

set_target_properties(${TestExeName} PROPERTIES FOLDER "BlueFramework/UnitTests/${RenderSystemName}")


add_test(
    NAME ${TestExeName}Test
    COMMAND ${TestExeName}
)

endfunction(CreateRenderSystemUnitTest)
