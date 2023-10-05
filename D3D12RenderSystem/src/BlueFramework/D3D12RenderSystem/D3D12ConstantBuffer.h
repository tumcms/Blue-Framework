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
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12ConstantBuffer_3861c819_a00a_4dc0_9e05_e0fd484a5bec_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12ConstantBuffer_3861c819_a00a_4dc0_9e05_e0fd484a5bec_h

#include "BlueFramework/D3D12RenderSystem/d3d12.h"
#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IConstantBuffer.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12ConstantBuffer : public buw::IConstantBuffer {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12ConstantBuffer(D3D12RenderSystem* renderSystem, const buw::constantBufferDescription& cbd);
	~D3D12ConstantBuffer();

	CD3DX12_CPU_DESCRIPTOR_HANDLE getCPUConstantBufferView() const; /// Get the CPU Handle to the Descriptor Heap
	CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUConstantBufferView() const; /// Get the GPU Handle to the Descriptor Heap

	void uploadData(const buw::constantBufferDescription& cbd) override; /// Upload data to constant buffer. Fails if sizes don't match.

private:
	void addSubBuffer();

private:
	D3D12RenderSystem* renderSystem_;
	size_t constantBufferSize_;

	struct SubBuffer {
		ComPtr<ID3D12Resource> constantBuffer;
		UINT constantBufferView;
	};

	std::vector<SubBuffer> buffers_;

	UINT64 currentFence_;
	int currentBufferIndex_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12ConstantBuffer_3861c819_a00a_4dc0_9e05_e0fd484a5bec_h
