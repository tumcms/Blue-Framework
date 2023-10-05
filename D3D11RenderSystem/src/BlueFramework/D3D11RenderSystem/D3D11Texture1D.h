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
#pragma once
#ifndef BlueFramework_D3D11RenderSystem_D3D11Texture1D_79439a1a_201b_47b6_be2d_51494b3637a9_h
#define BlueFramework_D3D11RenderSystem_D3D11Texture1D_79439a1a_201b_47b6_be2d_51494b3637a9_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ITexture1D.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11Texture1D : public buw::ITexture1D {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11Texture1D(D3D11RenderSystem* renderSystem, const buw::texture1DDescription& td, buw::eTextureBindType bindType);

	int width() const { return width_; }

	bool hasShaderResourceView() const;
	bool hasRenderTargetView() const;
	bool hasDepthStencilView() const;
	bool isCPUReadable() const;

	void makeCPUReadable();

	const buw::eTextureBindType getBindType() const { return bindType_; }

	const buw::eTextureFormat getFormat() const { return format_; }
	void resize(const buw::texture1DDescription&);

	ComPtr<ID3D11Resource> getTexture() const;
	ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const;
	ComPtr<ID3D11RenderTargetView> getRenderTargetView() const;
	ComPtr<ID3D11DepthStencilView> getDepthStencilView() const;

private:
	void createShaderResourceView();
	void createRenderTargetView();
	void createDepthStencilView();

private:
	buw::eTextureFormat format_;
	int width_;

	D3D11RenderSystem* renderSystem_;
	ComPtr<ID3D11Texture1D> texture_ = nullptr;

	buw::eTextureBindType bindType_;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
	ComPtr<ID3D11RenderTargetView> renderTargetView_;
	ComPtr<ID3D11DepthStencilView> depthStencilView_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11Texture1D_79439a1a_201b_47b6_be2d_51494b3637a9_h
