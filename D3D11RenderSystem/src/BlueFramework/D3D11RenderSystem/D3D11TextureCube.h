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
#ifndef BlueFramework_D3D11RenderSystem_D3D11TextureCube_aa19ce1e_d12c_4f8d_a93c_5412997c71f1_h
#define BlueFramework_D3D11RenderSystem_D3D11TextureCube_aa19ce1e_d12c_4f8d_a93c_5412997c71f1_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ITextureCube.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11TextureCube : public buw::ITextureCube {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11TextureCube(D3D11RenderSystem* renderSystem, const buw::textureCubeDescription& td, buw::eTextureBindType bindType);

	int width() const { return width_; }
	int height() const { return height_; }

	bool hasShaderResourceView() const;
	bool isCPUReadable() const;

	void makeCPUReadable();

	const buw::eTextureBindType getBindType() const { return bindType_; }

	const buw::eTextureFormat getFormat() const { return format_; }
	void resize(const buw::textureCubeDescription& td);

	ComPtr<ID3D11Resource> getTexture() const;
	ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const;

private:
	void createShaderResourceView();

private:
	buw::eTextureFormat format_;
	int width_, height_;

	D3D11RenderSystem* renderSystem_;
	ComPtr<ID3D11Texture2D> texture_ = nullptr;

	buw::eTextureBindType bindType_;
	ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11TextureCube_aa19ce1e_d12c_4f8d_a93c_5412997c71f1_h
