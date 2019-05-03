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
