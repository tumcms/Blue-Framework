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