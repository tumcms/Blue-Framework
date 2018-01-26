/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
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
