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

#ifndef __PIPELINESTATE_H_C94AE92E4E1343B5AE9FFE5747115B1A__
#define __PIPELINESTATE_H_C94AE92E4E1343B5AE9FFE5747115B1A__

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/Resources/IEffectCore.h>
#include <BlueFramework/Rasterizer/renderDescriptors.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/memory.h>

#include <memory>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class RenderSystem;

class PipelineState : public buw::IPipelineState, public std::enable_shared_from_this<PipelineState>
{
public:
	explicit PipelineState(RenderSystem* rs, buw::pipelineStateDescription const& psd) throw(...);
	virtual ~PipelineState();

	void setActive();
	static buw::ReferenceCounted<PipelineState> getActive();

	bool useAdjacency() const override;
	GLenum getPrimitiveType() const;
	GLuint getShaderProgram() const;

private:
	static std::weak_ptr<PipelineState> _active;
	bool const _bAdjacency;
	GLuint _hProg;
	GLenum const _ePrimitiveType;
	bool const _bMSAA;
	bool const _bDepthTest;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __PIPELINESTATE_H_C94AE92E4E1343B5AE9FFE5747115B1A__
