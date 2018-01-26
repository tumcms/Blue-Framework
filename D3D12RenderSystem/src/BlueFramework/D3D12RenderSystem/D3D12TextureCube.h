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
#ifndef BlueFramework_Rasterizer_D3D12TextureCube_4f108734_b2e2_4dec_9e81_8bc9f520a4f0_h
#define BlueFramework_Rasterizer_D3D12TextureCube_4f108734_b2e2_4dec_9e81_8bc9f520a4f0_h

#include "BlueFramework/Rasterizer/Resources/ITextureCube.h"
#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12TextureCube : public buw::ITextureCube {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    D3D12TextureCube();
	D3D12TextureCube(D3D12RenderSystem* renderSystem, const buw::textureCubeDescription &td, buw::eTextureBindType bindType);
    ~D3D12TextureCube();

    bool hasShaderResourceView() const override;

    void prepareSRV();

    int width() const override;
    int height() const override;

    const buw::eTextureFormat getFormat() const override;

    CD3DX12_CPU_DESCRIPTOR_HANDLE getCPUShaderResourceView() const;
    CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUShaderResourceView() const;

private:
	void createShaderResourceView();

private:
	buw::eTextureFormat format_;
	int width_, height_;

	D3D12RenderSystem* renderSystem_;
	ComPtr<ID3D12Resource> texture_ = nullptr;
	
	UINT shaderResourceView_;
    buw::eTextureBindType bindType_;

	buw::ReferenceCounted<D3D12_RESOURCE_STATES> currentState_ = nullptr;

	UINT arraySize = 6;
	UINT mipLevels = 1;
	UINT sampleCount = 1;
	UINT sampleQuality = 0;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_Rasterizer_D3D12CubeTexture_4f108734_b2e2_4dec_9e81_8bc9f520a4f0_h
