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

#include "BlueFramework/D3D12RenderSystem/D3D12Texture1D.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12Texture1D::D3D12Texture1D(D3D12RenderSystem* renderSystem, const buw::texture1DDescription& td, buw::eTextureBindType bindType)
	: ITexture1D(), renderSystem_(renderSystem), bindType_(bindType) {
	format_ = td.format;
	width_ = td.width;
	cpuReadable_ = td.isCpuReadable;

	D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

	switch (bindType_) {
	case buw::eTextureBindType::RTV:
	case buw::eTextureBindType::SRV_RTV: flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET; break;
	case buw::eTextureBindType::DSV: flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
	case buw::eTextureBindType::SRV_DSV: flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; break;
	default: break;
	}

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC textureDesc = CD3DX12_RESOURCE_DESC::Tex1D(mapTextureFormat(format_), width_, static_cast<UINT16>(arraySize), static_cast<UINT16>(mipLevels), flags);

	throwIfFailed(
		renderSystem_->getDevice()->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&texture_)));

	if (hasShaderResourceView())
		texture_->SetName(L"SRVTexture");

	currentState_ = buw::makeReferenceCounted<D3D12_RESOURCE_STATES>(D3D12_RESOURCE_STATE_COPY_DEST);

	if (td.data)
		renderSystem_->uploadDataToUploadBuffer(texture_, 4 * width_, 4 * width_, (const void**)&(td.data), 1);

	if (hasShaderResourceView())
		createShaderResourceView();
}

D3D12Texture1D::~D3D12Texture1D() {
	if (hasShaderResourceView())
		renderSystem_->getShaderVisibleDescriptorHeap()->free(shaderResourceView_);
}

D3D12Texture1D::ComPtr<ID3D12Resource> D3D12Texture1D::getTexture() const {
	return texture_;
}

bool D3D12Texture1D::hasShaderResourceView() const {
	return bindType_ == buw::eTextureBindType::SRV || bindType_ == buw::eTextureBindType::SRV_RTV || bindType_ == buw::eTextureBindType::SRV_DSV;
}

void D3D12Texture1D::createShaderResourceView() {
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = mapShaderResourceFormat(format_);
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = mipLevels;
	srvDesc.Texture2D.PlaneSlice = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	shaderResourceView_ = renderSystem_->getShaderVisibleDescriptorHeap()->alloc();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(shaderResourceView_);
	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &srvDesc, cpuHandle);
}

void D3D12Texture1D::prepareSRV() {
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_GENERIC_READ;
	if (*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target);
		*currentState_ = target;
	}
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12Texture1D::getGPUShaderResourceView() const {
	BLUE_ASSERT(hasShaderResourceView());
	return renderSystem_->getShaderVisibleDescriptorHeap()->getGPUHandleForSlot(shaderResourceView_);
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END