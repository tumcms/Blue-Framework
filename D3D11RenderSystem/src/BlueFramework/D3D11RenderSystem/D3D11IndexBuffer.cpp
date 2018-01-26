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