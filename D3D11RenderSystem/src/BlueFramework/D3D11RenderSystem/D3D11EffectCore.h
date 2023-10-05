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
#ifndef BlueFramework_D3D11RenderSystem_D3D11EffectCore_e657fb06_6377_443b_a3b3_51afdb9f2d9f_h
#define BlueFramework_D3D11RenderSystem_D3D11EffectCore_e657fb06_6377_443b_a3b3_51afdb9f2d9f_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"
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

#include <map>

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

struct Binding {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	int vsBindPoint = -1, gsBindPoint = -1, psBindPoint = -1;
	int vsBindCount = 0, gsBindCount = 0, psBindCount = 0;
};

class D3D11PipelineState : public buw::IPipelineState {
	friend class D3D11EffectCore;

	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11PipelineState(D3D11RenderSystem* renderSystem, const buw::pipelineStateDescription& psd);
	~D3D11PipelineState();

	bool useAdjacency() const override;

private:
	void fillBindings(ID3D11ShaderReflection* reflection, int type);

private:
	D3D11RenderSystem* renderSystem_;

	ComPtr<ID3D11VertexShader> vertexShader_;
	ComPtr<ID3D11GeometryShader> geometryShader_;
	ComPtr<ID3D11PixelShader> pixelShader_;

	ComPtr<ID3D11InputLayout> inputLayout_;
	ComPtr<ID3D11RasterizerState> rasterizerState_;
	ComPtr<ID3D11BlendState> blendState_;

	std::map<std::string, Binding> bindings_;
	buw::ePrimitiveTopology primitiveTopology_;
	UINT numRenderTargets_;
	bool adjacency_ = false;
};

class D3D11EffectCore : public buw::IEffectCore {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	friend class Effect;

public:
	D3D11EffectCore(D3D11RenderSystem* renderSystem);

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
	D3D11RenderSystem* renderSystem_;

	buw::ReferenceCounted<D3D11PipelineState> current_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11EffectCore_e657fb06_6377_443b_a3b3_51afdb9f2d9f_h
