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

#include <BlueFramework/GLRenderSystem/Texture.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/PipelineState.h>
#include <BlueFramework/GLRenderSystem/Sampler.h>
#include <BlueFramework/GLRenderSystem/Utils.h>

#include <BlueFramework/Core/assert.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Rasterizer/renderDescriptors.h>

#include <boost/iterator/counting_iterator.hpp>

#include <map>
#include <set>

namespace
{
	std::map<std::string, BlueFramework::GLRenderSystem::Texture*> texName2texObj;
	std::set<GLenum> freeTexUnits;
	BlueFramework::GLRenderSystem::Texture* pOnWorkingTexUnit = nullptr;
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

GLenum const Texture::INVALID_TEX_UNIT = (GLenum)-1;
GLenum const Texture::ANY_VALID_TEX_UNIT = (GLenum)-2;
GLenum Texture::_WORKING_TEX_UNIT = Texture::INVALID_TEX_UNIT;

Texture::Texture(GLenum const eGLTextureType, buw::eTextureFormat const tf, size_t const width, size_t const height)
	: _hTex(0)
	, _eGLTextureType(eGLTextureType)
	, _eGLFormat(
		(tf == buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB) * GL_RGBA +
		(tf == buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt) * GL_DEPTH_STENCIL +
		(tf == buw::eTextureFormat::R32_UnsignedInt) * GL_RED)
	, _internalFormat(
		(_eGLFormat == GL_RGBA) * GL_RGBA32F +
		(_eGLFormat == GL_DEPTH_STENCIL) * GL_DEPTH32F_STENCIL8 + //GL_DEPTH_STENCIL
		(_eGLFormat == GL_RED) * GL_R32F)
	, _width((GLsizei)width)
	, _height(eGLTextureType == GL_TEXTURE_1D ? 1 : (GLsizei)height)
	, _eGLTexUnit(INVALID_TEX_UNIT)
	, _bMipMappingDirty(true)
{
	// Initialize statics when the first texture is constructed. An empty set indicates
	// this because we never let it become empty. We reserve one tex unit to temporarily
	// bind a texture for configuration (the "working texture unit").
	if (freeTexUnits.empty())
	{
		freeTexUnits.insert(boost::counting_iterator<GLenum>(0), boost::counting_iterator<GLenum>([]()->GLenum {
			GLint maxTexUnits = 0;
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTexUnits);
			return maxTexUnits;
		}()));

		_WORKING_TEX_UNIT = *--freeTexUnits.cend(); // Returns highest tex unit.
	}

	// Make some assertions.
	if (_eGLFormat == 0) throw buw::Exception("The given texture format is not supported or invalid.");

	// Create the texture object.
	glGenTextures(1, &_hTex);

	// Configure default texture parameters.
	setBinding(WORKING_TEX_UNIT());
	glTexParameteri(_eGLTextureType, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(_eGLTextureType, GL_TEXTURE_MAX_LEVEL, 0);

	// Configure default sampling parameters.
	glTexParameteri(_eGLTextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(_eGLTextureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(_eGLTextureType, GL_TEXTURE_COMPARE_MODE,
		_eGLFormat == GL_DEPTH_STENCIL ? GL_COMPARE_REF_TO_TEXTURE : GL_NONE);
	GLfloat const pBorderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(_eGLTextureType, GL_TEXTURE_BORDER_COLOR, pBorderColor);
	setBinding(INVALID_TEX_UNIT);

	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

Texture::~Texture()
{
	setBinding(INVALID_TEX_UNIT);
	glDeleteTextures(1,  &_hTex);
	BLUE_ASSERT(glGetError() == GL_NO_ERROR);
}

GLint Texture::getMaxTexSize()
{
	static GLint nMaxTexDim = []()->GLint {
		GLint _nMaxTexDim = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_nMaxTexDim);
		return _nMaxTexDim;
	}();

	return nMaxTexDim;
}

GLint Texture::getMaxTexSize3D()
{
	static GLint nMaxTexDim = []()->GLint {
		GLint _nMaxTexDim = 0;
		glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &_nMaxTexDim);
		return _nMaxTexDim;
	}();

	return nMaxTexDim;
}

GLenum Texture::setBinding(GLenum const texUnit, std::string const& sstrShaderVariable)
{
	/*
	Texture unit		Bind target		Texture
	============		===========     =======
	tex unit 0
						GL_TEXTURE_1D	0
						GL_TEXTURE_2D	CheckerBoard
						...
	tex unit 1
						GL_TEXTURE_1D	ColorRamp
						GL_TEXTURE_2D	0
						...
	...
	tex unit N-1
	(working tex unit)	GL_TEXTURE_1D	0
						GL_TEXTURE_2D	AnotherTexture
						...

	When establishing a binding we have to:

	1. Unbind from the current tex unit, if it's not invalid.
	2. Recycle the current tex unit, if it's not invalid or the working tex unit N-1.
	3. Unbind a possibly existing other texture bound to the same shader variable or the
	   working tex unit, if the new tex unit is not invalid.
	4. Invalidate the tex unit member of the possibly existing other texture, if the new tex
	   unit is not invalid.
	5. Bind to the new tex unit, if the new tex unit is not invalid.
	6. Lastly, when leaving this method, the currently active texture unit shall be the new
	   one if that's not invalid or be unchanged if it's invalid.

	Because all these steps drastically simplify if the current and the new texture units are
	the same (but only the shader variable name changed), we specially treat this case.

	Note: Even though it is technically possible to have multiple textures bound at the same
	texture unit through different targets, it is discouraged to make use of this by the
	documentation, read here: https://www.khronos.org/opengl/wiki/Texture#Texture_image_units
	Therefore we want to avoid this situation:

	...
	tex unit n
				GL_TEXTURE_1D	SomeTex1
				GL_TEXTURE_2D	SomeTex2
				...
	...
	*/

	BLUE_ASSERT(texUnit == INVALID_TEX_UNIT || texUnit == _WORKING_TEX_UNIT || texUnit == ANY_VALID_TEX_UNIT,
		"A concrete tex unit is assigned by this method only. Use ANY_VALID_TEX_UNIT.");

	// Get the currently active texture unit in order to possibly restore it later.
	GLint activeTexUnitRestore = 0;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &activeTexUnitRestore);

	// Determine a texture unit to assign to this texture.
	GLenum texUnitToAssign = texUnit;
	if (texUnitToAssign == ANY_VALID_TEX_UNIT)
	{
		// Reuse a tex unit that is already associated to the same shader variable if applicable.
		auto findIt = texName2texObj.find(sstrShaderVariable);
		if (findIt == texName2texObj.end())
			texUnitToAssign = allocTexUnit();
		else
			texUnitToAssign = findIt->second->_eGLTexUnit;
	}

	// Special treatment if tex unit doesn't change.
	if (_eGLTexUnit == texUnitToAssign && _eGLTexUnit != INVALID_TEX_UNIT)
	{
		if (_eGLTexUnit != _WORKING_TEX_UNIT)
		{
			// The shader variable name possibly changed. Reinsert.
			for (auto it = texName2texObj.begin(); it != texName2texObj.end(); ++it)
				if (it->second == this)
				{
					texName2texObj.erase(it);
					break;
				}
			texName2texObj[sstrShaderVariable] = this;
		}
		glActiveTexture(GL_TEXTURE0 + _eGLTexUnit);
		BLUE_ASSERT(!((_eGLTexUnit == _WORKING_TEX_UNIT) ^ (pOnWorkingTexUnit == this)));
	}
	else if(_eGLTexUnit != texUnitToAssign)
	{
		// Unbind from the current tex unit, if it's not invalid and
		// recycle if applicable.
		if (_eGLTexUnit != INVALID_TEX_UNIT)
		{
			glActiveTexture(GL_TEXTURE0 + _eGLTexUnit);
			glBindTexture(_eGLTextureType, 0);
			if (_eGLTexUnit != _WORKING_TEX_UNIT)
				recycleTexUnit();
		}

		// Unbind and invalidate a possibly existing other texture bound to the same shader variable
		// or the working tex unit, if the new tex unit is not invalid.
		if (texUnitToAssign != INVALID_TEX_UNIT)
		{
			Texture* pEvict = nullptr;
			if (texUnitToAssign == _WORKING_TEX_UNIT)
				pEvict = pOnWorkingTexUnit;
			else
			{
				auto findIt = texName2texObj.find(sstrShaderVariable);
				if (findIt != texName2texObj.end())
					pEvict = findIt->second;
			}

			if (pEvict != nullptr)
			{
				glActiveTexture(GL_TEXTURE0 + pEvict->_eGLTexUnit);
				glBindTexture(pEvict->_eGLTextureType, 0);
				pEvict->_eGLTexUnit = INVALID_TEX_UNIT;
			}
		}

		// Bind to the new tex unit, if the new tex unit is not invalid.
		if (texUnitToAssign != INVALID_TEX_UNIT)
		{
			glActiveTexture(GL_TEXTURE0 + texUnitToAssign);
			glBindTexture(_eGLTextureType, _hTex);
			if (texUnitToAssign != _WORKING_TEX_UNIT)
				texName2texObj[sstrShaderVariable] = this;
		}
	}

	// Remember who's on the working texture unit.
	if (texUnitToAssign == _WORKING_TEX_UNIT)
		pOnWorkingTexUnit = this;
	else if(_eGLTexUnit == _WORKING_TEX_UNIT)
		pOnWorkingTexUnit = nullptr;

	// Make sure the currently active texture unit is unchanged on exit, if the new tex unit
	// is invalid.
	if (texUnitToAssign == INVALID_TEX_UNIT)
		glActiveTexture(activeTexUnitRestore);

	_eGLTexUnit = texUnitToAssign;

	return _eGLTexUnit;
}

GLenum Texture::getAssignedTexUnit() const
{
	return _eGLTexUnit;
}

void Texture::updateMipmaps()
{
#ifdef _DEBUG
	GLint hTex = 0;
	glGetIntegerv(_eGLTextureType == GL_TEXTURE_1D ? GL_TEXTURE_BINDING_1D : GL_TEXTURE_BINDING_2D, &hTex);
	if((GLuint)hTex != _hTex) throw buw::Exception("Bind and activate this texture first. Use setBinding().");
#endif

	GLint nMinLevel = 0, nMaxLevel = 0;
	glGetTexParameteriv(_eGLTextureType, GL_TEXTURE_BASE_LEVEL, &nMinLevel);
	glGetTexParameteriv(_eGLTextureType, GL_TEXTURE_MAX_LEVEL, &nMaxLevel);
	if (nMaxLevel - nMinLevel > 0) glGenerateMipmap(_eGLTextureType);
}

void Texture::setActive(std::string const& sstrName)
{
	// OpenGL context binding.
	GLenum const eTexUnit = setBinding(ANY_VALID_TEX_UNIT, sstrName);

	// Shader binding.
	auto ps = PipelineState::getActive();
	if (!ps) throw buw::Exception("There is no active pipeline state. Use PipelineState::setActive() first.");
	GLint const hSampler = glGetUniformLocation(ps->getShaderProgram(), sstrName.c_str());
	if (hSampler == -1) throw buw::Exception(("Invalid sampler/texture name: " + sstrName).c_str());
	glUniform1i(hSampler, eTexUnit);

	// Configure sampling parameters according to last set sampler.
	auto sampler = Sampler::getActive();
	if (sampler)
	{
		// Filtering.
		buw::samplerStateDescription const& ssd = sampler->getSamplerDescription();
		GLint const minFilter =
			(ssd.mipLevelFilter == buw::eFilter::None) * (
				(ssd.minificationFilter == buw::eFilter::None) * GL_NEAREST +
				(ssd.minificationFilter == buw::eFilter::Point) * GL_NEAREST +
				(ssd.minificationFilter == buw::eFilter::Linear) * GL_LINEAR +
				(ssd.minificationFilter == buw::eFilter::Anisotropic) * GL_LINEAR) +
			(ssd.mipLevelFilter == buw::eFilter::Point) * (
				(ssd.minificationFilter == buw::eFilter::None) * GL_NEAREST_MIPMAP_NEAREST +
				(ssd.minificationFilter == buw::eFilter::Point) * GL_NEAREST_MIPMAP_NEAREST +
				(ssd.minificationFilter == buw::eFilter::Linear) * GL_LINEAR_MIPMAP_NEAREST +
				(ssd.minificationFilter == buw::eFilter::Anisotropic) * GL_LINEAR_MIPMAP_NEAREST) +
			(ssd.mipLevelFilter == buw::eFilter::Linear) * (
				(ssd.minificationFilter == buw::eFilter::None) * GL_NEAREST_MIPMAP_LINEAR +
				(ssd.minificationFilter == buw::eFilter::Point) * GL_NEAREST_MIPMAP_LINEAR +
				(ssd.minificationFilter == buw::eFilter::Linear) * GL_LINEAR_MIPMAP_LINEAR +
				(ssd.minificationFilter == buw::eFilter::Anisotropic) * GL_LINEAR_MIPMAP_LINEAR);
		if (minFilter == 0) throw buw::Exception("Unsupported texture filtering.");
		GLint const magFilter =
			(ssd.magnificationFilter == buw::eFilter::None) * GL_NEAREST +
			(ssd.magnificationFilter == buw::eFilter::Point) * GL_NEAREST +
			(ssd.magnificationFilter == buw::eFilter::Linear) * GL_LINEAR +
			(ssd.magnificationFilter == buw::eFilter::Anisotropic) * GL_LINEAR;
		if (magFilter == 0) throw buw::Exception("Unsupported texture filtering.");

		glTexParameteri(_eGLTextureType, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(_eGLTextureType, GL_TEXTURE_MAG_FILTER, magFilter);

		// Mipmapping.
		if (minFilter == GL_NEAREST_MIPMAP_NEAREST || minFilter == GL_LINEAR_MIPMAP_NEAREST
			|| minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_LINEAR)
		{
			glTexParameteri(_eGLTextureType, GL_TEXTURE_MAX_LEVEL, 20); // Suggestion: Up to 20 mipmap levels.
			if(_bMipMappingDirty) glGenerateMipmap(_eGLTextureType);
			glTexParameterf(_eGLTextureType, GL_TEXTURE_MIN_LOD, -1000.0f);
			glTexParameterf(_eGLTextureType, GL_TEXTURE_MAX_LOD, 1000.0f);
			glTexParameterf(_eGLTextureType, GL_TEXTURE_LOD_BIAS, 0.0f);
			_bMipMappingDirty = false;
		}
		else
		{
			// Try to release driver memory by unused mipmaps as good as possible.
			GLint nMinLevel = 0, nMaxLevel = 0;
			glGetTexParameteriv(_eGLTextureType, GL_TEXTURE_BASE_LEVEL, &nMinLevel);
			glGetTexParameteriv(_eGLTextureType, GL_TEXTURE_MAX_LEVEL, &nMaxLevel);
			for (GLint lvl = nMinLevel + 1; lvl <= nMaxLevel; ++lvl)
			{
				switch (_eGLTextureType)
				{
				case GL_TEXTURE_1D:
					glTexImage1D(_eGLTextureType, lvl, _internalFormat, 0, 0, _eGLFormat, GL_UNSIGNED_BYTE, nullptr);
					break;
				case GL_TEXTURE_2D:
					glTexImage2D(_eGLTextureType, lvl, _internalFormat, 0, 0, 0, _eGLFormat, GL_UNSIGNED_BYTE, nullptr);
					break;
				default:
					// Not dramatic.
					BLUE_LOG(warning) << "Unknown texture type.";
					break;
				}
			}

			glTexParameteri(_eGLTextureType, GL_TEXTURE_MAX_LEVEL, 0);
			_bMipMappingDirty = true;
		}

		// Anisotropic filtering.
		if (GLEW_EXT_texture_filter_anisotropic)
		{
			GLfloat fAnisotropy = 1.0f; // 1.0f = no anisotropy
			if (ssd.minificationFilter == buw::eFilter::Anisotropic)
			{
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fAnisotropy);
				fAnisotropy = fAnisotropy < 8.0f ? fAnisotropy : 8.0f;
			}
			glTexParameterf(_eGLTextureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, fAnisotropy);
		}

		// Depth comparison mode.
		if (_eGLFormat == GL_DEPTH_STENCIL)
		{
			GLint const compFunc =
				(ssd.compFunction == buw::eComparisonFunction::Never) * GL_NEVER +
				(ssd.compFunction == buw::eComparisonFunction::Less) * GL_LESS +
				(ssd.compFunction == buw::eComparisonFunction::Equal) * GL_EQUAL +
				(ssd.compFunction == buw::eComparisonFunction::LessEqual) * GL_LEQUAL +
				(ssd.compFunction == buw::eComparisonFunction::Greater) * GL_GREATER +
				(ssd.compFunction == buw::eComparisonFunction::NotEqual) * GL_NOTEQUAL +
				(ssd.compFunction == buw::eComparisonFunction::GreaterEqual) * GL_GEQUAL +
				(ssd.compFunction == buw::eComparisonFunction::Always) * GL_ALWAYS;
			if(compFunc == 0) throw buw::Exception("Unsupported depth texture comparison function.");
			glTexParameteri(_eGLTextureType, GL_TEXTURE_COMPARE_FUNC, compFunc);
		}

		// Wrapping.
		int const params[][2] = {
			{(int)ssd.textureAddressModeU, GL_TEXTURE_WRAP_S},
			{(int)ssd.textureAddressModeV, GL_TEXTURE_WRAP_T} };
		for (size_t i = 0; i < (_eGLTextureType == GL_TEXTURE_2D ? 2 : 1); ++i)
		{
			buw::eTextureAddressMode const wrapMode = (buw::eTextureAddressMode)params[i][0];
			GLint glWrapMode =
				(wrapMode == buw::eTextureAddressMode::Wrap) * GL_REPEAT +
				(wrapMode == buw::eTextureAddressMode::Clamp) * GL_CLAMP_TO_EDGE +
				(wrapMode == buw::eTextureAddressMode::Mirror) * GL_MIRRORED_REPEAT +
				(wrapMode == buw::eTextureAddressMode::Border) * GL_CLAMP_TO_BORDER;
			if (wrapMode == buw::eTextureAddressMode::MirrorOnce && GLEW_ARB_texture_mirror_clamp_to_edge)
			{
				BLUE_ASSERT(glWrapMode == 0);
				glWrapMode = GL_MIRROR_CLAMP_TO_EDGE;
			}
			if(glWrapMode == 0) throw buw::Exception("Unsupported texture wrap mode.");
			glTexParameteri(_eGLTextureType, params[i][1], glWrapMode);
		}
	}

	// Check for problems.
	GLenum const eGLErr = glGetError();
	if (eGLErr != GL_NO_ERROR)
	{
		glClearError();
		throwWithMessage("Failed to set the sampler/texture named \"" + sstrName
			+ "\". Was it declared as \"uniform sampler...\" type?", ERROR_SUCCESS, eGLErr);
	}
}

GLenum Texture::allocTexUnit()
{
	// A tex unit is reserved for temporary bindings for configuration of textures.
	if (freeTexUnits.size() <= 1) throw buw::Exception("Out of texture units.");
	auto const texUnitIt = freeTexUnits.cbegin();
	GLenum const eRetVal = *texUnitIt;
	freeTexUnits.erase(texUnitIt);
	return eRetVal;
}

void Texture::recycleTexUnit()
{
	// Removing/inserting from/into both containers must be an atomic operation.

	BLUE_ASSERT(freeTexUnits.find(_eGLTexUnit) == freeTexUnits.end());
	freeTexUnits.insert(_eGLTexUnit);

	for (auto it = texName2texObj.begin(); it != texName2texObj.end(); ++it)
		if (it->second == this)
		{
			texName2texObj.erase(it);
			break;
		}
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
