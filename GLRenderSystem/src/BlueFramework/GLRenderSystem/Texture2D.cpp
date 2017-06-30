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

#include <BlueFramework/GLRenderSystem/Texture2D.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/Utils.h>

#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/assert.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

Texture2D::Texture2D(buw::texture2DDescription const& td)
	: ITexture2D()
	, Texture(GL_TEXTURE_2D, td.format, td.width, td.height)
{
	resize(td);
}

Texture2D::~Texture2D()
{
}

void Texture2D::clear(float const color[4])
{
	if (_eGLFormat == GL_DEPTH_STENCIL) throw buw::NotImplementedYetException("Only for RGBA or RED texture types.");

	// Choose default color if none is given.
	float defaultColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	if (color == nullptr)
		color = defaultColor;

	// Activate/bind tex unit.
	GLenum const texUnit = getAssignedTexUnit();
	if (texUnit == INVALID_TEX_UNIT)
		setBinding(WORKING_TEX_UNIT());
	else
		glActiveTexture(GL_TEXTURE0 + texUnit);

	// If glClearTexImage() is supported we use it, otherwise we must have a
	// source buffer to copy from.
	float* pBuff = nullptr;
	if (!GLEW_ARB_clear_texture)
	{
		size_t const NUM_FLOATS = 4 * _width * _height;
		pBuff = new float[NUM_FLOATS];
		for (size_t i = 0; i < NUM_FLOATS; ++i)
			pBuff[i] = color[i % 4];
	}

	GLint nMinLevel = 0, nMaxLevel = 0;
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &nMinLevel);
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &nMaxLevel);
	for (GLint lvl = nMinLevel; lvl <= nMaxLevel; ++lvl)
	{
		// Valid level?
		GLint nWidth = 0, nHeight = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, lvl, GL_TEXTURE_WIDTH, &nWidth);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, lvl, GL_TEXTURE_HEIGHT, &nHeight);
		if (nWidth < 1 || nHeight < 1) continue;

		if (GLEW_ARB_clear_texture)
			glClearTexImage(_hTex, lvl, GL_RGBA, GL_FLOAT, color);
		else
			glTexSubImage2D(GL_TEXTURE_2D, lvl, 0, 0, nWidth, nHeight, GL_RGBA, GL_FLOAT, pBuff);
	}

	if (pBuff)
	{
		delete[] pBuff;
		pBuff = nullptr;
	}

	if (texUnit == INVALID_TEX_UNIT)
		setBinding(INVALID_TEX_UNIT);

	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

int Texture2D::width() const
{
	return _width;
}

int Texture2D::height() const
{
	return _height;
}

bool Texture2D::hasShaderResourceView() const
{
	return true;
}

bool Texture2D::hasRenderTargetView() const
{
	return false;
}

bool Texture2D::hasDepthStencilView() const
{
	return _eGLFormat == GL_DEPTH_STENCIL;
}

bool Texture2D::isCPUReadable() const
{
	return true;
}

bool Texture2D::isCPUWriteable() const
{
	return true;
}

void Texture2D::makeCPUReadable()
{
	// Is always readable by the CPU.
}

void Texture2D::makeCPUWriteable()
{
	// Is always writable by the CPU.
}

buw::eTextureBindType const Texture2D::getBindType() const
{
	return buw::eTextureBindType::SRV;
}

buw::eTextureFormat const Texture2D::getFormat() const
{
	switch (_eGLFormat)
	{
	case GL_RGBA: return buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	case GL_DEPTH_STENCIL: return buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	case GL_RED: return buw::eTextureFormat::R32_UnsignedInt;
	}

	return buw::eTextureFormat::Undefined;
}

void Texture2D::resize(buw::texture2DDescription const& td)
{
	if (td.width > getMaxTexSize() || td.height > getMaxTexSize()) BLUE_LOG(warning) <<
		"Requested texture of width " << td.width << " and height " << td.height <<
		" might be too large. Supported are only " << getMaxTexSize() <<
		" per dimension. Trying to continue anyway.";
	if (td.width <= 0 || td.height <= 0) throw buw::Exception("Bad texture dimensions requested.");
	_width = td.width;
	_height = td.height;

	// If this is only a request to resize the texture, then the data pointer might very well
	// be null. In that case we are not going to copy data but only (re)allocate the texture
	// storage.
	if (td.data != nullptr && td.format != getFormat())
		throw buw::Exception("Cannot change once fixed texture format.");

	// The following line seems (and indeed is) a little overengeneered because it always
	// evaluates to GL_UNSIGNED_BYTE, but it makes intentions explicit.
	GLenum const eGLType = td.data == nullptr ? GL_UNSIGNED_BYTE :
		(td.format == buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB) *  GL_UNSIGNED_BYTE +
		(td.format == buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt) * GL_UNSIGNED_BYTE +
		(td.format == buw::eTextureFormat::R32_UnsignedInt) * GL_UNSIGNED_BYTE;
	if (eGLType == 0) throw buw::Exception("The requested texture format is not supported or invalid.");

	// Configure texture storage, possibly uploads image data and generates (or at
	// least allocates) the mipmap levels, i.e. even generate mipmaps if the data
	// pointer is null.
	GLenum const texUnit = getAssignedTexUnit();
	if (texUnit == INVALID_TEX_UNIT)
		setBinding(WORKING_TEX_UNIT());
	else
		glActiveTexture(GL_TEXTURE0 + texUnit);
	glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _eGLFormat, eGLType, td.data /* can be null */);
	updateMipmaps();
	if (texUnit == INVALID_TEX_UNIT)
		setBinding(INVALID_TEX_UNIT);

	// Check for problems.
	GLenum const eGLErr = glGetError();
	if (eGLErr != GL_NO_ERROR)
	{
		glClearError();
		throwWithMessage("Failed to configure or upload texture.", ERROR_SUCCESS, eGLErr);
	}
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
