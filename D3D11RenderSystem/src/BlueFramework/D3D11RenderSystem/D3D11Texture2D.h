/*
	This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_D3D11RenderSystem_D3D11Texture_16dbdaf5_26e1_4b3d_ad0c_7e9c0bd189cd_h
#define BlueFramework_D3D11RenderSystem_D3D11Texture_16dbdaf5_26e1_4b3d_ad0c_7e9c0bd189cd_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11Texture2D : public buw::ITexture2D {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static buw::ReferenceCounted<D3D11Texture2D> fromBackBuffer(D3D11RenderSystem* renderSystem, ComPtr<ID3D11Texture2D> backBuffer, UINT width, UINT height);

public:
	D3D11Texture2D();
	D3D11Texture2D(D3D11RenderSystem* renderSystem, const buw::texture2DDescription& td, buw::eTextureBindType bindType);

	int width() const { return width_; }
	int height() const { return height_; }
	bool isMultisampled() const override { return msaa_; }

	bool hasShaderResourceView() const;
	bool hasRenderTargetView() const;
	bool hasDepthStencilView() const;
	bool isCPUReadable() const override;
	bool isCPUWriteable() const override;

	void makeCPUReadable() override;
	void makeCPUWriteable() override;

	const buw::eTextureBindType getBindType() const { return bindType_; }

	const buw::eTextureFormat getFormat() const { return format_; }
	void resize(const buw::texture2DDescription&) override;

	ComPtr<ID3D11Texture2D> getTexture() const;
	ComPtr<ID3D11Texture2D> getStagingTexture() const;
	ComPtr<ID3D11Texture2D> getMSAAStagingTexture() const;
	ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const;
	ComPtr<ID3D11RenderTargetView> getRenderTargetView() const;
	ComPtr<ID3D11DepthStencilView> getDepthStencilView() const;

private:
	void createTexture(const void* data);
	void createStagingTexture(bool cpuReadable, bool cpuWriteable);
	void createShaderResourceView();
	void createRenderTargetView();
	void createDepthStencilView();

private:
	buw::eTextureFormat format_;
	int width_, height_;
	bool msaa_, isCPUReadable_, isCPUWriteable_;

	D3D11RenderSystem* renderSystem_;
	ComPtr<ID3D11Texture2D> texture_ = nullptr;
	ComPtr<ID3D11Texture2D> stagingTexture_ = nullptr;
	ComPtr<ID3D11Texture2D> msaaStagingTexture_ = nullptr;

	buw::eTextureBindType bindType_;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
	ComPtr<ID3D11RenderTargetView> renderTargetView_;
	ComPtr<ID3D11DepthStencilView> depthStencilView_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11Texture_16dbdaf5_26e1_4b3d_ad0c_7e9c0bd189cd_h
