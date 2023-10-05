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

	set_target_properties(${UnitTestName} PROPERTIES FOLDER "BlueFramework/UnitTests/Engine")
		
	target_link_libraries(${UnitTestName}
		PRIVATE
			BlueFramework.Core
			BlueFramework.Rasterizer
			BlueFramework.Engine
			BlueFramework.D3D11RenderSystem # force this to be rebuild, because it is maybe needed by the unit test
			BlueFramework.D3D12RenderSystem # force this to be rebuild, because it is maybe needed by the unit test
			BlueFramework.GLRenderSystem # force this to be rebuild, because it is maybe needed by the unit test
			gtest
			gtest_main
			Qt5::Widgets
	)
			
	add_test(
		NAME ${UnitTestName}Test
		COMMAND ${UnitTestName}
	)
	
	if(EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data OR EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader) 
	if(EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data AND EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader) 
		# housekeeping for shaders, resources, etc. which are needed during testing
		add_custom_target(Copy${UnitTestName}UnitTestResources
			# Effect
			COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader Shader
			COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data   Data		
		)
	elseif(EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data)
		# housekeeping for shaders, resources, etc. which are needed during testing
		add_custom_target(Copy${UnitTestName}UnitTestResources
			# Effect
			COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Data Data		
		)
	elseif(EXISTS ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader)
		# housekeeping for shaders, resources, etc. which are needed during testing
		add_custom_target(Copy${UnitTestName}UnitTestResources
			# Effect
			COMMAND	${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/UnitTests/src/BlueFramework/UnitTests/Engine/${UnitTestName}/Shader Shader		
		)
	endif()

	set_target_properties(Copy${UnitTestName}UnitTestResources PROPERTIES FOLDER "BlueFramework/UnitTests/Engine/Copy")
	add_dependencies(${UnitTestName} Copy${UnitTestName}UnitTestResources)
	endif()

if(TARGET Qt5::windeployqt)
    # execute windeployqt in a tmp directory after build
    add_custom_command(TARGET ${UnitTestName}
        POST_BUILD
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
        COMMAND Qt5::windeployqt --dir "${CMAKE_BINARY_DIR}/$<CONFIG>" "$<TARGET_FILE_DIR:${UnitTestName}>/$<TARGET_FILE_NAME:${UnitTestName}>"
    )
endif()


	add_dependencies(${UnitTestName}	
		BlueFramework.Core
		BlueFramework.ImageProcessing
		BlueFramework.Rasterizer
		BlueFramework.D3D12RenderSystem
		BlueFramework.GLRenderSystem
		BlueFramework.Engine
	)	
endfunction()
