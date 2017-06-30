/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
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

#ifndef __UTILS_H_B4EB44260AD7444EA6ED9FC53D06AD69__
#define __UTILS_H_B4EB44260AD7444EA6ED9FC53D06AD69__

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Core/Exception.h>

#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

void throwWithMessage(
	std::string const& sstrMsg,
	DWORD const nWinErrCode = ERROR_SUCCESS,
	GLenum const nGLErrCode = GL_NO_ERROR,
	GLenum const nGLEWErrCode = GLEW_OK) throw(...);

void glClearError();

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __UTILS_H_B4EB44260AD7444EA6ED9FC53D06AD69__
