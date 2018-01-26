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

#pragma once
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12Effect_df34034b_ec3d_4ba7_b7c6_7f5b5833153a_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12Effect_df34034b_ec3d_4ba7_b7c6_7f5b5833153a_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"
#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Rasterizer/Resources/IBlender.h"
#include "BlueFramework/Rasterizer/Resources/IConstantBuffer.h"
#include "BlueFramework/Rasterizer/Resources/IEffectCore.h"
#include "BlueFramework/Rasterizer/Resources/IIndexBuffer.h"
#include "BlueFramework/Rasterizer/Resources/ISampler.h"
#include "BlueFramework/Rasterizer/Resources/ITexture1D.h"
#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"
#include "BlueFramework/Rasterizer/Resources/ITextureCube.h"
#include "BlueFramework/Rasterizer/Resources/IVertexBuffer.h"
#include "BlueFramework/Rasterizer/Resources/IViewport.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

struct Binding {
	const char* name;
	UINT reg, slot;
	D3D12_SHADER_VISIBILITY visibility;

	Binding(const char* n, UINT r, D3D12_SHADER_VISIBILITY v) : name(n), reg(r), slot(0), visibility(v) {
	}
};

class D3D12PipelineState : public buw::IPipelineState {
	friend class D3D12EffectCore;

	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12PipelineState(D3D12RenderSystem* renderSystem, const buw::pipelineStateDescription& psd);
	~D3D12PipelineState();

	bool useAdjacency() const override;
	
private:
	/// Parses the ShaderReflection and fills the Bindings with name, register, the slot in the root signature table (currently 0) and the sahder
	/// visibility.
	void fillBindings(ID3D12ShaderReflection* reflection, const D3D12_SHADER_VISIBILITY visibility);

private:
	D3D12RenderSystem* renderSystem_;
	ComPtr<ID3D12RootSignature> rootSignature_;
	ComPtr<ID3D12PipelineState> pipelineState_;

	std::vector<Binding> cbBindings_, samplerBindings_, srvBindings_;
	buw::ePrimitiveTopology primitiveTopology_;
	UINT numRenderTargets_;
	bool adjacency_ = false;
};

class D3D12EffectCore : public buw::IEffectCore {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	friend class Effect;

public:
	D3D12EffectCore(D3D12RenderSystem* renderSystem);

	buw::IRenderSystem* renderSystem() override;


	buw::ReferenceCounted<buw::IPipelineState>
	createPipelineState(const buw::pipelineStateDescription& psd) override; // TODO: Maybe move method to render system?
	void setPipelineState(buw::ReferenceCounted<buw::IPipelineState> pipelineState) override;
	void setVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer) const override;
	void setIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer) const override;
	void setConstantBuffer(buw::ReferenceCounted<buw::IConstantBuffer> constantBuffer, const std::string& name) const override;
	void setTexture(buw::ReferenceCounted<buw::ITexture1D> texture, const std::string& name) const override;
	void setTexture(buw::ReferenceCounted<buw::ITexture2D> texture, const std::string& name) const override;
    void setTexture(buw::ReferenceCounted<buw::ITextureCube> texture, const std::string& name) const override;
	void setSampler(buw::ReferenceCounted<buw::ISampler> sampler, const std::string& name) const override;
	void setViewport(buw::ReferenceCounted<buw::IViewport> viewport) const override;
	void setRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, buw::ReferenceCounted<buw::ITexture2D> depthStencil) const override;
	void setRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets,
	                      buw::ReferenceCounted<buw::ITexture2D> depthStencil) const override;
	void draw(UINT vertices) const;
	void drawIndexed(UINT indices) const;

	void preInit();
	void postInit();
	void preRender();
	void postRender();

private:
	D3D12RenderSystem* renderSystem_;

	buw::ReferenceCounted<D3D12PipelineState> current_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12Effect_df34034b_ec3d_4ba7_b7c6_7f5b5833153a_h
