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

#include "D3D12VertexBuffer.h"
#include "D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12VertexBuffer::D3D12VertexBuffer(D3D12RenderSystem* renderSystem, const buw::vertexBufferDescription& vbd) :
	IVertexBuffer(renderSystem, vbd),
	renderSystem_(renderSystem),
	vertexLayout_(vbd.vertexLayout),
	vertexCount_(vbd.vertexCount)
{
	vertexSize_ = vertexLayout_.getVertexByteSize();

	currentFence_ = (UINT64)-1;
	currentBufferIndex_ = 0;
	addSubBuffer();

	if (vbd.data)
		uploadData(vbd);
}

void D3D12VertexBuffer::uploadData(const buw::vertexBufferDescription &vbd)
{
	assert(vbd.vertexCount <= vertexCount_);

	UINT64 fence = renderSystem_->getFenceValue();
	if (fence == currentFence_)
		currentBufferIndex_++;
	else
		currentBufferIndex_ = 0;

	if (currentBufferIndex_ >= buffers_.size())
		addSubBuffer();

	renderSystem_->uploadData(buffers_[currentBufferIndex_].vertexBuffer, vbd.vertexCount * vertexSize_, vbd.data);

	currentFence_ = fence;
}

void D3D12VertexBuffer::addSubBuffer()
{
	ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	assert(std::numeric_limits<UINT>::max() > vertexSize_ * vertexCount_);
	UINT vertexBufferSize = (UINT)(vertexSize_ * vertexCount_);

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);

	throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&bufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBuffer)));


	assert(std::numeric_limits<UINT>::max() >= vertexSize_);
	// Initialize the vertex buffer view.
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = (UINT)vertexSize_;
	vertexBufferView.SizeInBytes = vertexBufferSize;

	// Name D3D12 object for debug purpose.
	std::wstring name = L"VertexBuffer@" + std::to_wstring(vertexBufferView.BufferLocation);
	vertexBuffer->SetName(name.c_str());

	buffers_.push_back({ vertexBuffer, vertexBufferView });
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END
