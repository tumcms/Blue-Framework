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
