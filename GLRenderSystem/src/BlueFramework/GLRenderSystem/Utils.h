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
    GLenum const nGLEWErrCode = GLEW_OK) noexcept(false);

void glClearError();

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __UTILS_H_B4EB44260AD7444EA6ED9FC53D06AD69__
