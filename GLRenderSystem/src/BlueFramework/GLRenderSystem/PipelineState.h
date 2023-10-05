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
	explicit PipelineState(RenderSystem* rs, buw::pipelineStateDescription const& psd) noexcept(false);
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
