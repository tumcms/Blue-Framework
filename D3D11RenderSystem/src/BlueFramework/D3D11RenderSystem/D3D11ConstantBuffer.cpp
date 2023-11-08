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

#include "BlueFramework/D3D11RenderSystem/D3D11ConstantBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

D3D11ConstantBuffer::D3D11ConstantBuffer(D3D11RenderSystem* renderSystem, const buw::constantBufferDescription& cbd) :
	IConstantBuffer(renderSystem, cbd),
	renderSystem_(renderSystem)
{
	constantBufferSize_ = cbd.sizeInBytes;
	UINT alignedSize = (constantBufferSize_ + 255) & ~255;

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = alignedSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = constantBufferSize_;

	D3D11_SUBRESOURCE_DATA sub;
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (cbd.data)
	{
		sub.pSysMem = cbd.data;
		sub.SysMemPitch = constantBufferSize_;
		sub.SysMemSlicePitch = constantBufferSize_;
		subp = &sub;
	}

	renderSystem_->getDevice()->CreateBuffer(&desc, subp, constantBuffer_.GetAddressOf());
}

void D3D11ConstantBuffer::uploadData(const buw::constantBufferDescription& cbd)
{
	D3D11_MAPPED_SUBRESOURCE sub;
	renderSystem_->getDeviceContext()->Map(constantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	memcpy(sub.pData, cbd.data, cbd.sizeInBytes);
	renderSystem_->getDeviceContext()->Unmap(constantBuffer_.Get(), 0);
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END