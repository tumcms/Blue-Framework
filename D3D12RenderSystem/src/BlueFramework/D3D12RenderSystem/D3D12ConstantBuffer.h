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
