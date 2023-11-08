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
