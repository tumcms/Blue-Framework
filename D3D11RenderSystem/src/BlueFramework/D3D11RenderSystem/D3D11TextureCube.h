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
