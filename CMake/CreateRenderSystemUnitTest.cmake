#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016-2020 Technical University of Munich
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

function(CreateRenderSystemUnitTest RenderSystemName UnitTestName)

set(TestExeName Test.${RenderSystemName}.${UnitTestName})

file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest					*.cpp *.h)
file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader			Shader/*.*)
file(GLOB BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader_${RenderSystemName}		Shader/${RenderSystemName}/*.*)

source_group(${UnitTestName}					                FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest})
source_group(${UnitTestName}\\Shader			                FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader})
source_group(${UnitTestName}\\Shader\\${RenderSystemName}		FILES ${BlueFramework_UnitTests_${RenderSystemName}_UnitTest_Shader_${RenderSystemName}})

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

set_target_properties(${UnitTestName} PROPERTIES FOLDER "BlueFramework/UnitTests/${RenderSystemName}")


add_test(
    NAME ${RenderSystemName}.${UnitTestName}Test
    COMMAND ${TestExeName}
)

endfunction(CreateRenderSystemUnitTest)
