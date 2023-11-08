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

#include "BlueFramework/D3D12RenderSystem/D3D12IndexBuffer.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12IndexBuffer::D3D12IndexBuffer(D3D12RenderSystem* renderSystem, const buw::indexBufferDescription& ibd) : IIndexBuffer(renderSystem, ibd), indexCount_(ibd.indexCount) {
	format_ = ibd.format;
	indexCount_ = ibd.indexCount;
	UINT indexBufferSize = static_cast<UINT>(ibd.getElementByteSize() * ibd.indexCount);

	BLUE_ASSERT(indexBufferSize, "Index buffer should not be 0.");

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);

	throwIfFailed(renderSystem->getDevice()->CreateCommittedResource(
	  &heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuffer_)));

	renderSystem->uploadData(indexBuffer_, indexBufferSize, ibd.data);

	// Initialize the index buffer view.
	indexBufferView_.BufferLocation = indexBuffer_->GetGPUVirtualAddress();

	if (ibd.format == buw::eIndexBufferFormat::UnsignedInt16) {
		indexBufferView_.Format = DXGI_FORMAT_R16_UINT;
	} else if (ibd.format == buw::eIndexBufferFormat::UnsignedInt32) {
		indexBufferView_.Format = DXGI_FORMAT_R32_UINT;
	} else {
		throw buw::Exception("Invalid index buffer format.");
	}

	indexBufferView_.SizeInBytes = indexBufferSize;

	// Name the D3D12 object for debugging purpose.
	std::wstring name = L"IndexBuffer@" + std::to_wstring(indexBufferView_.BufferLocation);
	indexBuffer_->SetName(name.c_str());
}

void D3D12IndexBuffer::setIndexCount(size_t val) {
	indexCount_ = val;
}

size_t D3D12IndexBuffer::getIndexSize() const {
	switch (format_) {
	case buw::eIndexBufferFormat::UnsignedInt16:
		return sizeof(std::uint16_t);
	case buw::eIndexBufferFormat::UnsignedInt32:
		return sizeof(std::uint32_t);
	default:
		throw buw::Exception("Unknown index buffer format.");
	}
}


D3D12_INDEX_BUFFER_VIEW D3D12IndexBuffer::getIndexBufferView() const {
	return indexBufferView_;
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END
