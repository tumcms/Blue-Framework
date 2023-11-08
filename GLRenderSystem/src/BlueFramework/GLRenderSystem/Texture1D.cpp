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

#include <BlueFramework/GLRenderSystem/Texture1D.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/Utils.h>

#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Exception.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

Texture1D::Texture1D(buw::texture1DDescription const& td)
	: buw::ITexture1D()
	, Texture(GL_TEXTURE_1D, td.format, td.width, 1)
{
	GLenum const eGLType =
		(td.format == buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB) *  GL_UNSIGNED_BYTE +
		(td.format == buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt) * GL_UNSIGNED_BYTE +
		(td.format == buw::eTextureFormat::R32_UnsignedInt) * GL_UNSIGNED_BYTE;

	// Make some assertions.
	if (eGLType == 0) throw buw::Exception("The given texture format is not supported or invalid.");
	if (_width > getMaxTexSize()) BLUE_LOG(warning) << "Given texture of width " << _width <<
		" might be too large. Supported are only " << getMaxTexSize() << ". Trying to continue anyway.";

	// Configure texture storage.
	setBinding(WORKING_TEX_UNIT());
	glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, _width, 0, _eGLFormat, eGLType, td.data);
	updateMipmaps();
	setBinding(INVALID_TEX_UNIT);

	// Check for problems.
	GLenum const eGLErr = glGetError();
	if (eGLErr != GL_NO_ERROR)
	{
		glClearError();
		throwWithMessage("Failed to upload texture data.", ERROR_SUCCESS, eGLErr);
	}
}

Texture1D::~Texture1D()
{
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
