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

#ifndef __TEXTURE_H_C57730F486B6439DA38788EFC2DAB3EA__
#define __TEXTURE_H_C57730F486B6439DA38788EFC2DAB3EA__

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/renderDescriptors.h>

#include <string>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class Texture
{
protected:
	explicit Texture(GLenum const eGLTextureType, buw::eTextureFormat const tf, size_t const width, size_t const height);
	virtual ~Texture();

	static GLenum const INVALID_TEX_UNIT;
	static inline GLenum WORKING_TEX_UNIT() { return _WORKING_TEX_UNIT; }
	static GLenum const ANY_VALID_TEX_UNIT;

	static GLint getMaxTexSize(); // Limit for 1D, 2D and cube maps per dimension.
	static GLint getMaxTexSize3D(); // Limit for 3D textures per dimension.

	// Set texture unit/target binding. The only allowed values for \param texUnit are INVALID_TEX_UNIT, WORKING_TEX_UNIT
	// and ANY_VALID_TEX_UNIT. INVALID_TEX_UNIT unbinds this texture. To configure but not yet permanently bind a texture
	// to a shader variable, use WORKING_TEX_UNIT. Finally, when binding to a shader variable use ANY_VALID_TEX_UNIT. The
	// value of \param sstrShaderVariable is only relevant if \param texUnit is ANY_VALID_TEX_UNIT. When this method returns,
	// the currently active texture unit is the assigned tex unit if \param texUnit was not INVALID_TEX_UNIT or unchanged if
	// \param texUnit was INVALID_TEX_UNIT. This method returns the actual assigned tex unit.
	GLenum setBinding(GLenum const texUnit, std::string const& sstrShaderVariable = std::string());
	GLenum getAssignedTexUnit() const;

	// Requires that this texture is already bound (setBinding()) and its tex unit being the active one.
	void updateMipmaps();

	GLuint _hTex;
	GLenum const _eGLTextureType; // e.g. GL_TEXTURE_1D, GL_TEXTURE_2D
	GLenum const _eGLFormat; // e.g. GL_RGBA, GL_DEPTH_STENCIL, GL_RED
	GLint const _internalFormat; // e.g. GL_RGBA32F, GL_DEPTH32F_STENCIL8, GL_R32F
	GLsizei _width;
	GLsizei _height;

public:
	virtual void setActive(std::string const& sstrName);

private:
	static GLenum _WORKING_TEX_UNIT; // A tex unit is reserved for temporary bindings for configuration of textures.
	GLenum _eGLTexUnit;
	bool _bMipMappingDirty;

	GLenum allocTexUnit();
	void recycleTexUnit();
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __TEXTURE_H_C57730F486B6439DA38788EFC2DAB3EA__
