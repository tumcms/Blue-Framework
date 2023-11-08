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

#include "BlueFramework/D3D12RenderSystem/D3D12TextureCube.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"


BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12TextureCube::D3D12TextureCube(D3D12RenderSystem* renderSystem, const buw::textureCubeDescription& td, buw::eTextureBindType bindType)
	: ITextureCube(), renderSystem_(renderSystem){
	format_ = td.format;
	width_ = td.width;
	height_ = td.height;
    bindType_ = bindType;

	D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;	

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC textureDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		mapTextureFormat(format_),
		width_,
		height_,
		static_cast<UINT16>(arraySize),
		static_cast<UINT16>(mipLevels), sampleCount, sampleQuality, flags);
    

    throwIfFailed(
        renderSystem_->getDevice()->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&texture_)));

    texture_->SetName(L"SRVTextureCube");

    currentState_ = buw::makeReferenceCounted<D3D12_RESOURCE_STATES>(D3D12_RESOURCE_STATE_COPY_DEST);


    if(td.data)
        renderSystem_->uploadDataToUploadBuffer(texture_, 4 * width_, 4 * width_ * height_, td.data, 6);

    if(bindType == buw::eTextureBindType::SRV)
        createShaderResourceView();
}

D3D12TextureCube::D3D12TextureCube()
    : ITextureCube(), format_(buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB), width_(0), height_(0), renderSystem_(nullptr), bindType_(buw::eTextureBindType::None) {}


D3D12TextureCube::~D3D12TextureCube()
{
    if(hasShaderResourceView())
        renderSystem_->getShaderVisibleDescriptorHeap()->free(shaderResourceView_);
}

bool D3D12TextureCube::hasShaderResourceView() const
{
    return bindType_ == buw::eTextureBindType::SRV;
}

void D3D12TextureCube::prepareSRV()
{
    D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_GENERIC_READ;
    if(*currentState_ != target) {
        renderSystem_->transitResource(texture_.Get(), *currentState_, target);
        *currentState_ = target;
    }
}

int D3D12TextureCube::width() const
{
    return width_;
}

int D3D12TextureCube::height() const
{
    return height_;
}

const buw::eTextureFormat D3D12TextureCube::getFormat() const
{
    return format_;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12TextureCube::getCPUShaderResourceView() const
{
    BLUE_ASSERT(hasShaderResourceView());
    return renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(shaderResourceView_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12TextureCube::getGPUShaderResourceView() const
{
    BLUE_ASSERT(hasShaderResourceView());
    return renderSystem_->getShaderVisibleDescriptorHeap()->getGPUHandleForSlot(shaderResourceView_);
}

void D3D12TextureCube::createShaderResourceView()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = mapShaderResourceFormat(format_);
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = mipLevels;
	srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;

	shaderResourceView_ = renderSystem_->getShaderVisibleDescriptorHeap()->alloc();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(shaderResourceView_);
	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &srvDesc, cpuHandle);
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END
