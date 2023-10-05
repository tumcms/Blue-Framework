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
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12VertexBuffer_3abbf9c0_612d_42b9_a21d_d94ad2ff22c1_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12VertexBuffer_3abbf9c0_612d_42b9_a21d_d94ad2ff22c1_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IVertexBuffer.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12VertexBuffer : public buw::IVertexBuffer {

	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12VertexBuffer(D3D12RenderSystem* renderSystem, const buw::vertexBufferDescription& vbd);

    const buw::VertexLayout& getVertexLayout() { return vertexLayout_; }
    D3D12_VERTEX_BUFFER_VIEW getVertexBufferView() const { return buffers_[currentBufferIndex_].vertexBufferView; }
    
	size_t getVertexSize() const override { return vertexSize_; }
	size_t getVertexCount() const override { return vertexCount_; }

	void uploadData(const buw::vertexBufferDescription& vbd) override; /// Upload data to constant buffer. Fails if sizes don't match.

private:
	void addSubBuffer();

private:
	D3D12RenderSystem* renderSystem_;
	const buw::VertexLayout vertexLayout_;
	size_t vertexCount_, vertexSize_;

	struct SubBuffer
	{
		ComPtr<ID3D12Resource> vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	};

	std::vector<SubBuffer> buffers_;

	UINT64 currentFence_;
	int currentBufferIndex_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12VertexBuffer_3abbf9c0_612d_42b9_a21d_d94ad2ff22c1_h
