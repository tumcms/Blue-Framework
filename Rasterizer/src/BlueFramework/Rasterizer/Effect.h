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
#ifndef BlueFramework_Rasterizer_Effect_2caf0cf4_b25a_4f09_84fb_7c84bae25e0a_h
#define BlueFramework_Rasterizer_Effect_2caf0cf4_b25a_4f09_84fb_7c84bae25e0a_h

#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IEffectCore.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class Effect {
public:
	Effect(IRenderSystem* renderSytem);

	virtual ~Effect();

	void init();

	void render();

    void preRender();

    void postRender();

public:
	virtual IRenderSystem* renderSystem() const;
    buw::ReferenceCounted<buw::IPipelineState> createPipelineState(const buw::pipelineStateDescription &psd);
	void setPipelineState(buw::ReferenceCounted<IPipelineState> pipelineState);
	void setVertexBuffer(buw::ReferenceCounted<IVertexBuffer> vertexBuffer) const;
	void setIndexBuffer(buw::ReferenceCounted<IIndexBuffer> indexBuffer) const;
	void setConstantBuffer(buw::ReferenceCounted<IConstantBuffer> constantBuffer, const std::string& name) const;
	void setTexture(buw::ReferenceCounted<ITexture1D> texture, const std::string& name) const;
	void setTexture(buw::ReferenceCounted<ITexture2D> texture, const std::string& name) const;
    void setTexture(buw::ReferenceCounted<ITextureCube> texture, const std::string& name) const;
	void setSampler(buw::ReferenceCounted<ISampler> sampler, const std::string& name) const;
	void setViewport(buw::ReferenceCounted<IViewport> viewport) const;
	void setRenderTarget(buw::ReferenceCounted<ITexture2D> renderTarget, buw::ReferenceCounted<ITexture2D> depthStencil) const;
    void setRenderTargets(std::vector<buw::ReferenceCounted<ITexture2D>> renderTargets, buw::ReferenceCounted<ITexture2D> depthStencil) const;

	void draw(UINT vertices) const;
	void drawIndexed(UINT indices) const;

private:
	virtual void v_init();;
	virtual void v_render();;

private:
	buw::ReferenceCounted<IEffectCore> core_;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(Effect)

#endif // end define BlueFramework_Rasterizer_Effect_2caf0cf4_b25a_4f09_84fb_7c84bae25e0a_h
