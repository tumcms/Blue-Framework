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

#include "BlueFramework/D3D11RenderSystem/D3D11IndexBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

D3D11IndexBuffer::D3D11IndexBuffer(D3D11RenderSystem* renderSystem, const buw::indexBufferDescription& ibd) :
	buw::IIndexBuffer(renderSystem, ibd),
	renderSystem_(renderSystem),
	indexCount_(ibd.indexCount),
	format_(ibd.format)
{
	UINT indexBufferSize = (UINT)(getIndexSize() * indexCount_);

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = indexBufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = getIndexSize();
	
	D3D11_SUBRESOURCE_DATA sub;
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (ibd.data)
	{
		sub.pSysMem = ibd.data;
		sub.SysMemPitch = indexBufferSize;
		sub.SysMemSlicePitch = indexBufferSize;
		subp = &sub;
	}

	renderSystem_->getDevice()->CreateBuffer(&desc, subp, indexBuffer_.GetAddressOf());
}

void D3D11IndexBuffer::uploadData(const buw::indexBufferDescription& ibd)
{
	assert(indexCount_ == ibd.indexCount);
	UINT indexBufferSize = (UINT)(getIndexSize() * indexCount_);

	D3D11_MAPPED_SUBRESOURCE sub;
	renderSystem_->getDeviceContext()->Map(indexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	memcpy(sub.pData, ibd.data, indexBufferSize);
	renderSystem_->getDeviceContext()->Unmap(indexBuffer_.Get(), 0);
}

size_t D3D11IndexBuffer::getIndexSize() const {
	switch (format_) {
	case buw::eIndexBufferFormat::UnsignedInt16:
		return sizeof(std::uint16_t);
	case buw::eIndexBufferFormat::UnsignedInt32:
		return sizeof(std::uint32_t);
	default:
		throw buw::Exception("Unknown index buffer format.");
	}
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END