if(WIN32)
	# Unit tests need access to Qt DLLs and resources - this project copies this stuff to the right place
	add_custom_target(ExecuteQtDeployTool
		#------------------------------------------------------------------------------------------------------
		# Variant A: This does not need a prebuild DrawTriangle.exe
		# This parts builds just the DrawTriangle unit test which is needed by windeployqt
		# Actually this takes a long time...
		#COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target DrawTriangle --config debug
		#COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target DrawTriangle --config release
		#COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target DrawTriangle --config relWithDebInfo
		#------------------------------------------------------------------------------------------------------
			
		#------------------------------------------------------------------------------------------------------
		# Variant B: This requires a prebuild DrawTriangle.exe
		# From my experience it is fine to use for every build type the debug.exe...
		COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Deploy/Debug/DrawTriangle.exe        ${CMAKE_BINARY_DIR}/Debug
		COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Deploy/Debug/DrawTriangle.exe        ${CMAKE_BINARY_DIR}/RelWithDebInfo
		COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Deploy/Debug/DrawTriangle.exe        ${CMAKE_BINARY_DIR}/Release
		#------------------------------------------------------------------------------------------------------
				
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --debug ${CMAKE_BINARY_DIR}/Debug/DrawTriangle.exe
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --pdb ${CMAKE_BINARY_DIR}/Debug/DrawTriangle.exe
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --release ${CMAKE_BINARY_DIR}/RelWithDebInfo/DrawTriangle.exe
		COMMAND  ${Qt5Core_DIR}/../../../bin/windeployqt.exe --no-system-d3d-compiler --force --release ${CMAKE_BINARY_DIR}/Release/DrawTriangle.exe
	)
endif()