/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
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

#include "BlueFramework/D3D12RenderSystem/D3D12ConstantBuffer.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12ConstantBuffer::D3D12ConstantBuffer(D3D12RenderSystem* renderSystem, const buw::constantBufferDescription& cbd)
    : IConstantBuffer(renderSystem, cbd), renderSystem_(renderSystem), constantBufferSize_(cbd.sizeInBytes) {
	currentFence_ = (UINT64)-1;
	currentBufferIndex_ = 0;
	addSubBuffer();

	if (cbd.data)
		uploadData(cbd);
}

D3D12ConstantBuffer::~D3D12ConstantBuffer() {
	for (SubBuffer& buffer : buffers_) {
		renderSystem_->getShaderVisibleDescriptorHeap()->free(buffer.constantBufferView);
	}
}

CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12ConstantBuffer::getCPUConstantBufferView() const {
	return renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(buffers_[currentBufferIndex_].constantBufferView);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12ConstantBuffer::getGPUConstantBufferView() const {
	return renderSystem_->getShaderVisibleDescriptorHeap()->getGPUHandleForSlot(buffers_[currentBufferIndex_].constantBufferView);
}

void D3D12ConstantBuffer::uploadData(const buw::constantBufferDescription& cbd) {
	BLUE_ASSERT(cbd.sizeInBytes == constantBufferSize_, "Invalid size");

	UINT64 fence = renderSystem_->getFenceValue();
	if (fence == currentFence_)
		currentBufferIndex_++;
	else
		currentBufferIndex_ = 0;

	if (currentBufferIndex_ >= buffers_.size())
		addSubBuffer();

	renderSystem_->uploadData(buffers_[currentBufferIndex_].constantBuffer, constantBufferSize_, cbd.data);

	currentFence_ = fence;
}

void D3D12ConstantBuffer::addSubBuffer() {
	ComPtr<ID3D12Resource> constantBuffer;
	UINT constantBufferView;

	UINT alignedSize = (constantBufferSize_ + 255) & ~255; // CB size is required to be 256-byte aligned.

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(alignedSize);

	throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
	  &heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constantBuffer)));

	// Describe and create a constant buffer view.
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
	cbvDesc.BufferLocation = constantBuffer->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = alignedSize;
	constantBufferView = renderSystem_->getShaderVisibleDescriptorHeap()->alloc();
	renderSystem_->getDevice()->CreateConstantBufferView(&cbvDesc, renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(constantBufferView));

	// Name D3D12 object for debugging purposes.
	std::wstring name = L"ConstantBuffer@" + std::to_wstring(constantBufferView);
	constantBuffer->SetName(name.c_str());

	buffers_.push_back({constantBuffer, constantBufferView});
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END