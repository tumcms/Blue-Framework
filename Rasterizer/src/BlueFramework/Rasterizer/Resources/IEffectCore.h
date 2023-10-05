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

#pragma once
#ifndef BlueFramework_Rasterizer_IEffect_c2358884_8a62_4551_a95b_7ac3d487a051_h
#define BlueFramework_Rasterizer_IEffect_c2358884_8a62_4551_a95b_7ac3d487a051_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IRenderSystem;
class IVertexBuffer;
class IIndexBuffer;
class IConstantBuffer;
class ITexture1D;
class ITexture2D;
class ITextureCube;
class ISampler;
class IViewport;
class IBlender;

class IPipelineState : public buw::NonCopyable {
public:
	IPipelineState(IRenderSystem*, const buw::pipelineStateDescription&)
	{}
	virtual ~IPipelineState() {}

	virtual bool useAdjacency() const = 0;
};

class IEffectCore : public buw::NonCopyable {
public:
	IEffectCore(IRenderSystem*) {}
	virtual ~IEffectCore() {}

	virtual IRenderSystem* renderSystem() = 0;

    virtual buw::ReferenceCounted<IPipelineState> createPipelineState(const pipelineStateDescription &psd) = 0;
    virtual void setPipelineState(buw::ReferenceCounted<IPipelineState> pipelineState) = 0;
	virtual void setVertexBuffer(buw::ReferenceCounted<IVertexBuffer> vertexBuffer) const = 0;
	virtual void setIndexBuffer(buw::ReferenceCounted<IIndexBuffer> indexBuffer) const = 0;
	virtual void setConstantBuffer(buw::ReferenceCounted<IConstantBuffer> constantBuffer, const std::string& name) const = 0;
	virtual void setTexture(buw::ReferenceCounted<ITexture1D> texture, const std::string& name) const = 0;
	virtual void setTexture(buw::ReferenceCounted<ITexture2D> texture, const std::string& name) const = 0;
    virtual void setTexture(buw::ReferenceCounted<ITextureCube> texture, const std::string& name) const = 0;
	virtual void setSampler(buw::ReferenceCounted<ISampler> sampler, const std::string& name) const = 0;
	virtual void setViewport(buw::ReferenceCounted<IViewport> viewport) const = 0;
	virtual void setRenderTarget(buw::ReferenceCounted<ITexture2D> renderTarget, buw::ReferenceCounted<ITexture2D> depthStencil) const = 0;
    virtual void setRenderTargets(std::vector<buw::ReferenceCounted<ITexture2D>> renderTargets, buw::ReferenceCounted<ITexture2D> depthStencil) const = 0;
	virtual void draw(UINT vertices) const = 0;
	virtual void drawIndexed(UINT indices) const = 0;

	virtual void preInit() = 0;
	virtual void postInit() = 0;
	virtual void preRender() = 0;
	virtual void postRender() = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IPipelineState)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IEffectCore)

#endif // end define BlueFramework_Rasterizer_IEffect_c2358884_8a62_4551_a95b_7ac3d487a051_h
