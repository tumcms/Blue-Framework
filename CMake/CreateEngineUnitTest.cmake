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

function(CreateEngineUnitTest UnitTestName)
	set(CMAKE_AUTOMOC ON)

	file(GLOB BlueFramework_UnitTests_Engine_UnitTest					*.cpp *.h)
	file(GLOB BlueFramework_UnitTests_Engine_UnitTest_Shader			Shader/*.*)
	file(GLOB BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D		Shader/D3D/*.*)
	file(GLOB BlueFramework_UnitTests_Engine_UnitTest_Shader_OGL		Shader/OGL/*.*)
	file(GLOB BlueFramework_UnitTests_Engine_UnitTest_ReferenceImages	*.png *.exr)
	
	source_group(${UnitTestName}					FILES ${BlueFramework_UnitTests_Engine_UnitTest})
	source_group(${UnitTestName}\\Shader			FILES ${BlueFramework_UnitTests_Engine_UnitTest_Shader})
	source_group(${UnitTestName}\\Shader\\D3D		FILES ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D})
	source_group(${UnitTestName}\\Shader\\OGL		FILES ${BlueFramework_UnitTests_Engine_UnitTest_Shader_OGL})
	source_group(${UnitTestName}\\ReferenceImages	FILES ${BlueFramework_UnitTests_Engine_UnitTest_ReferenceImages})
	
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY VS_SHADER_TYPE Vertex)
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY VS_SHADER_ENTRYPOINT VS_main)
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY VS_SHADER_MODEL 5.0)
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY PS_SHADER_TYPE PIXEL)
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY PS_SHADER_ENTRYPOINT PS_main)
	set_property(SOURCE ${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D} PROPERTY PS_SHADER_MODEL 5.0)

	#message(${BlueFramework_UnitTests_Engine_UnitTest})
	
	add_executable(${UnitTestName}
		${BlueFramework_BLUE_TEST}

		# source files
		${BlueFramework_UnitTests_Engine_UnitTest}
		${BlueFramework_UnitTests_Engine_UnitTest_Shader}
		${BlueFramework_UnitTests_Engine_UnitTest_Shader_D3D}
		${BlueFramework_UnitTests_Engine_UnitTest_Shader_OGL}
		${BlueFramework_UnitTests_Engine_UnitTest_ReferenceImages}
	)
	
	link_against_gtest(${UnitTestName})
	
	target_link_libraries(${UnitTestName}
		BlueFramework.Core
		BlueFramework.Rasterizer
		BlueFramework.Engine
		BlueFramework.D3D11RenderSystem # force this to be rebuild, because it is needed by the unit test
		BlueFramework.D3D12RenderSystem # force this to be rebuild, because it is needed by the unit test
	)
	
	add_test(
		NAME ${UnitTestName}Test
		COMMAND ${UnitTestName}
	)
	
	# housekeeping for shaders, resources, etc. which are needed during testing
	add_custom_target(Copy${UnitTestName}UnitTestResources
		# Effect
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader Shader
		COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data   Data		
	)
	
	set_target_properties(${UnitTestName} PROPERTIES FOLDER "BlueFramework/UnitTests/Engine")
	set_target_properties(Copy${UnitTestName}UnitTestResources PROPERTIES FOLDER "BlueFramework/UnitTests/Engine/Copy")

	add_dependencies(${UnitTestName}	
		BlueFramework.Core
		BlueFramework.ImageProcessing
		BlueFramework.Rasterizer
		BlueFramework.D3D12RenderSystem
		BlueFramework.GLRenderSystem
		BlueFramework.Engine
		Copy${UnitTestName}UnitTestResources # Copy resources
	)	
	
	qt5_use_modules(${UnitTestName} Widgets)
endfunction()
