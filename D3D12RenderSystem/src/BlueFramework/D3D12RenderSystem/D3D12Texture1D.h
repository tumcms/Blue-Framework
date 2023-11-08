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
#ifndef BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h
#define BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ITexture1D.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"
#include "BlueFramework/Core/memory.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12Texture1D : public buw::ITexture1D {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12Texture1D(D3D12RenderSystem* renderSystem, const buw::texture1DDescription& td, buw::eTextureBindType bindType);
	virtual ~D3D12Texture1D();

	D3D12Texture1D::ComPtr<ID3D12Resource> getTexture() const;

	void prepareSRV();

	CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUShaderResourceView() const;


private:
	bool hasShaderResourceView() const;

	void createShaderResourceView();

private:
	buw::eTextureFormat format_;
	int width_, copyRegionWidth_, copyRegionHeight_;

	D3D12RenderSystem* renderSystem_;
	ComPtr<ID3D12Resource> texture_;
	ComPtr<ID3D12Resource> cpuReadTexture_;
	bool cpuReadable_;
	bool multisampled_;
	buw::eTextureBindType bindType_;
	UINT shaderResourceView_, renderTargetView_, depthStencilView_;

	buw::ReferenceCounted<D3D12_RESOURCE_STATES> currentState_;

	UINT arraySize = 1;
	UINT mipLevels = 1;
	UINT sampleCount = 1;
	UINT sampleQuality = 0;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h
