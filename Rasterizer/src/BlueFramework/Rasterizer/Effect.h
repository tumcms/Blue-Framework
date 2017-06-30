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
