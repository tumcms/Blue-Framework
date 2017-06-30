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