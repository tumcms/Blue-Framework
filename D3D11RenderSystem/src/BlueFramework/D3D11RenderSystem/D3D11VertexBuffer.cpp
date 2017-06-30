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

#include "BlueFramework/D3D11RenderSystem/D3D11VertexBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

D3D11VertexBuffer::D3D11VertexBuffer(D3D11RenderSystem* renderSystem, const buw::vertexBufferDescription& vbd) : 
	IVertexBuffer(renderSystem, vbd),
	renderSystem_(renderSystem),
	vertexLayout_(vbd.vertexLayout),
	vertexCount_(vbd.vertexCount)
{
	vertexSize_ = vertexLayout_.getVertexByteSize();

	assert(std::numeric_limits<UINT>::max() > vertexSize_ * vertexCount_);
	UINT vertexBufferSize = (UINT)(vertexSize_ * vertexCount_);


	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = vertexBufferSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = vertexSize_;

	D3D11_SUBRESOURCE_DATA sub;
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (vbd.data)
	{
		sub.pSysMem = vbd.data;
		sub.SysMemPitch = vertexBufferSize;
		sub.SysMemSlicePitch = vertexBufferSize;
		subp = &sub;
	}

	renderSystem_->getDevice()->CreateBuffer(&desc, subp, vertexBuffer_.GetAddressOf());
}

void D3D11VertexBuffer::uploadData(const buw::vertexBufferDescription& vbd)
{
	assert(vertexCount_ > vbd.vertexCount);
	assert(vertexSize_ == vbd.vertexLayout.getVertexByteSize());
	UINT vertexBufferSize = (UINT)(vertexSize_ * vbd.vertexCount);

	D3D11_MAPPED_SUBRESOURCE sub;
	renderSystem_->getDeviceContext()->Map(vertexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	memcpy(sub.pData, vbd.data, vertexBufferSize);
	renderSystem_->getDeviceContext()->Unmap(vertexBuffer_.Get(), 0);
}


BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END