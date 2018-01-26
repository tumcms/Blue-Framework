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
