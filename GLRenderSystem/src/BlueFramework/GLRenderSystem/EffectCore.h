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

#ifndef __EFFECTCORE_H_3FADF2A5C7604EE38D9B970DDF447FF0__
#define __EFFECTCORE_H_3FADF2A5C7604EE38D9B970DDF447FF0__

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/Resources/IEffectCore.h>
#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IIndexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IConstantBuffer.h>
#include <BlueFramework/Rasterizer/Resources/ITexture1D.h>
#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>
#include <BlueFramework/Rasterizer/Resources/ITextureCube.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Core/Exception.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class RenderSystem;

class EffectCore : public buw::IEffectCore
{
public:
	explicit EffectCore(RenderSystem* rs);
	virtual ~EffectCore();

	buw::IRenderSystem* renderSystem() override;

    buw::ReferenceCounted<buw::IPipelineState> createPipelineState(buw::pipelineStateDescription const& psd) override;
    void setPipelineState(buw::ReferenceCounted<buw::IPipelineState> ps) override;
	void setVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vb) const override;
	void setIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> ib) const override;
	void setConstantBuffer(buw::ReferenceCounted<buw::IConstantBuffer> cb, std::string const& sstrName) const override;
	void setTexture(buw::ReferenceCounted<buw::ITexture1D> tex1d, std::string const& sstrName) const override;
	void setTexture(buw::ReferenceCounted<buw::ITexture2D> tex2d, std::string const& sstrName) const override;
    void setTexture(buw::ReferenceCounted<buw::ITextureCube> cubeTex, std::string const& sstrName) const override;
	void setSampler(buw::ReferenceCounted<buw::ISampler> sampler, std::string const& sstrName) const override;
	void setViewport(buw::ReferenceCounted<buw::IViewport>) const override;
	void setRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, buw::ReferenceCounted<buw::ITexture2D> depthStencil) const override;
    void setRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, buw::ReferenceCounted<buw::ITexture2D> depthStencil) const override;
	void draw(UINT vertices) const throw(...) override;
	void drawIndexed(UINT indices) const override;

	void preInit() override;
	void postInit() override;
	void preRender() override;
	void postRender() override;

private:
	RenderSystem* _rs;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __EFFECTCORE_H_3FADF2A5C7604EE38D9B970DDF447FF0__
