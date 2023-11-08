/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2023 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/Utils.h>
#include <BlueFramework/GLRenderSystem/namespace.h>

#include <sstream>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

void throwWithMessage(
	std::string const& sstrMsg,
	DWORD const nWinErrCode,
	GLenum const nGLErrCode,
	GLenum const nGLEWErrCode)
{
	std::ostringstream osstr;
	osstr << sstrMsg;

	if (nWinErrCode != ERROR_SUCCESS)
	{
		std::size_t const MAX_ERR_MSG_SIZE = 200;
		char cstrMsg[MAX_ERR_MSG_SIZE] = { 0 };
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, nWinErrCode, 0, (LPSTR)cstrMsg, MAX_ERR_MSG_SIZE, 0);
		osstr << std::endl << "Windows error " << nWinErrCode << ": " << cstrMsg;
	}

	if (nGLEWErrCode != GLEW_OK)
		osstr << std::endl << "GLEW error " << nGLEWErrCode << ": " << glewGetErrorString(nGLEWErrCode);

	if (nGLErrCode != GL_NO_ERROR)
		osstr << std::endl << "OpenGL error " << nGLErrCode;

	throw buw::Exception(osstr.str().c_str());
}

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
