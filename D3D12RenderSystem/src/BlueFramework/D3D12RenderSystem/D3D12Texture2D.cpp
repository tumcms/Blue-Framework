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

#include "BlueFramework/D3D12RenderSystem/D3D12Texture2D.h"
#include "BlueFramework/Core/assert.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

bool BlueFramework::D3D12RenderSystem::D3D12Texture2D::hasRenderTargetView() const {
	return bindType_ == buw::eTextureBindType::RTV || bindType_ == buw::eTextureBindType::SRV_RTV;
}

D3D12Texture2D::D3D12Texture2D(D3D12RenderSystem* renderSystem, const buw::texture2DDescription& td, buw::eTextureBindType bindType)
    : ITexture2D(), renderSystem_(renderSystem), bindType_(bindType) {
	format_ = td.format;
	width_ = td.width;
	height_ = td.height;
	cpuReadable_ = td.isCpuReadable;
	cpuWriteable_ = td.isCpuWriteable;

	D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;

	switch (bindType_) {
	case buw::eTextureBindType::RTV:
	case buw::eTextureBindType::SRV_RTV: flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET; break;
	case buw::eTextureBindType::DSV: flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
	case buw::eTextureBindType::SRV_DSV: flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; break;
	default: break;
	}

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_RESOURCE_DESC textureDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		mapTextureFormat(format_), 
		width_, 
		height_, 
		static_cast<UINT16>(arraySize), 
		static_cast<UINT16>(mipLevels), sampleCount, sampleQuality, flags);
    //textureDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
	if (renderSystem_->getMSAAEnabled() == true) {
		if (td.useMSAA == true) {
			multisampled_ = true;
			textureDesc.SampleDesc.Count = renderSystem_->getSampleCount();
			textureDesc.SampleDesc.Quality = renderSystem_->getSampleQuality();
		} else {
			multisampled_ = false;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
		}
	} else if (renderSystem_->getMSAAEnabled() == false) {
		if (td.useMSAA == true)
			BLUE_LOG(warning) << "MSAA is disabled.";
		multisampled_ = false;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
	}

	throwIfFailed(
	  renderSystem_->getDevice()->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&texture_)));

    if (isCPUReadable()) {
        makeCPUReadable();
	}

	if (isCPUWriteable())
	{
		makeCPUWriteable();
	}

	if (hasShaderResourceView())
		texture_->SetName(L"SRVTexture");
	if (hasRenderTargetView())
		texture_->SetName(L"RTVTexture");
	if (hasDepthStencilView())
		texture_->SetName(L"DSVTexture");
    if (isCPUReadable())
        cpuReadBuffer_->SetName(L"CRATexture");

	currentState_ = buw::makeReferenceCounted<D3D12_RESOURCE_STATES>(D3D12_RESOURCE_STATE_COPY_DEST);

    if(td.data) {
        const void** dataPtr = (const void**)&(td.data);
        renderSystem_->uploadDataToUploadBuffer(texture_, 4 * width_, 4 * width_ * height_, dataPtr, 1);
    }

	if (hasShaderResourceView())
		createShaderResourceView();
	if (hasRenderTargetView())
		createRenderTargetView();
	if (hasDepthStencilView())
		createDepthStencilView();
}

D3D12Texture2D::~D3D12Texture2D() {
	if (hasShaderResourceView())
		renderSystem_->getShaderVisibleDescriptorHeap()->free(shaderResourceView_);
	if (hasRenderTargetView())
		renderSystem_->getRenderTargetDescriptorHeap()->free(renderTargetView_);
	if (hasDepthStencilView())
		renderSystem_->getDepthStencilDescriptorHeap()->free(depthStencilView_);
}

bool D3D12Texture2D::hasDepthStencilView() const
{
    return bindType_ == buw::eTextureBindType::DSV || bindType_ == buw::eTextureBindType::SRV_DSV;;
}


D3D12Texture2D::D3D12Texture2D()
    : ITexture2D(), format_(buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB), width_(0), height_(0), renderSystem_(nullptr), bindType_(buw::eTextureBindType::None) {
}

buw::ReferenceCounted<D3D12Texture2D> D3D12Texture2D::fromBackBuffer(D3D12RenderSystem* renderSystem, ComPtr<ID3D12Resource> backBuffer, UINT width, UINT height) {
	buw::ReferenceCounted<D3D12Texture2D> tex = buw::makeReferenceCounted<D3D12Texture2D>();
	tex->format_ = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	tex->width_ = width;
	tex->height_ = height;
	tex->renderSystem_ = renderSystem;
	tex->texture_ = backBuffer;
	tex->bindType_ = buw::eTextureBindType::RTV;
	tex->createRenderTargetView();
	tex->currentState_ = buw::makeReferenceCounted<D3D12_RESOURCE_STATES>(D3D12_RESOURCE_STATE_RENDER_TARGET);
	tex->texture_->SetName(L"BackBuffer");
	return tex;
}

void D3D12Texture2D::resize(const buw::texture2DDescription& td) {
	D3D12RenderSystem* rs = renderSystem_;
	buw::eTextureBindType bt = bindType_;

	this->~D3D12Texture2D();
	new (this) D3D12Texture2D(rs, td, bt);
}

D3D12Texture2D::ComPtr<ID3D12Resource> D3D12Texture2D::getTexture() const {
	return texture_;
}

D3D12Texture2D::ComPtr<ID3D12Resource>& D3D12Texture2D::getCPUReadableBuffer() {
	return cpuReadBuffer_;
}

D3D12Texture2D::ComPtr<ID3D12Resource>& D3D12Texture2D::getCPUWriteableBuffer()
{
	return cpuWriteBuffer_;
}

D3D12Texture2D::ComPtr<ID3D12Resource> D3D12Texture2D::getNoMSAATexture()
{
    return noMSAATexture_;
}

D3D12Texture2D::ComPtr<ID3D12Resource> D3D12Texture2D::getIntermediateTexture()
{
    return intermediateTexture_;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12Texture2D::getCPUShaderResourceView() const {
	BLUE_ASSERT(hasShaderResourceView());
	return renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(shaderResourceView_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12Texture2D::getGPUShaderResourceView() const {
	BLUE_ASSERT(hasShaderResourceView());
	return renderSystem_->getShaderVisibleDescriptorHeap()->getGPUHandleForSlot(shaderResourceView_);
}

CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12Texture2D::getCPURenderTargetView() const {
	BLUE_ASSERT(hasRenderTargetView());
	return renderSystem_->getRenderTargetDescriptorHeap()->getCPUHandleForSlot(renderTargetView_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12Texture2D::getGPURenderTargetView() const {
	BLUE_ASSERT(hasRenderTargetView());
	return renderSystem_->getRenderTargetDescriptorHeap()->getGPUHandleForSlot(renderTargetView_);
}

CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12Texture2D::getCPUDepthStencilView() const {
	BLUE_ASSERT(hasDepthStencilView());
	return renderSystem_->getDepthStencilDescriptorHeap()->getCPUHandleForSlot(depthStencilView_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12Texture2D::getGPUDepthStencilView() const {
	BLUE_ASSERT(hasDepthStencilView());
	return renderSystem_->getDepthStencilDescriptorHeap()->getGPUHandleForSlot(depthStencilView_);
}

void D3D12Texture2D::makeCPUReadable() {
    if (multisampled_) {
        CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_CUSTOM);
        heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE;
        heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
        heapProperties.CreationNodeMask = 0;
        heapProperties.VisibleNodeMask = 0;

        CD3DX12_RESOURCE_DESC textureDesc = CD3DX12_RESOURCE_DESC::Tex2D(mapTextureFormat(format_), width_, height_, 1, 1, 1, 0, D3D12_RESOURCE_FLAG_NONE);
        if (bindType_ == buw::eTextureBindType::DSV || bindType_ == buw::eTextureBindType::SRV_DSV) textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        /*textureDesc.Format = mapTextureFormat(format_);
        textureDesc.Width = width_;
        textureDesc.Height = height_;
        textureDesc.DepthOrArraySize = 1;
        textureDesc.MipLevels = 1;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
        textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;*/

        throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
            &heapProperties,
            D3D12_HEAP_FLAG_NONE,
            &textureDesc,
            D3D12_RESOURCE_STATE_COPY_SOURCE,
            nullptr,
            IID_PPV_ARGS(&noMSAATexture_)));

        if (bindType_ == buw::eTextureBindType::DSV || bindType_ == buw::eTextureBindType::SRV_DSV) {
            CD3DX12_HEAP_PROPERTIES depthHeap(D3D12_HEAP_TYPE_DEFAULT);

            CD3DX12_RESOURCE_DESC depthDesc = textureDesc;
            depthDesc.Format = DXGI_FORMAT_R32_TYPELESS;
            depthDesc.SampleDesc.Count = renderSystem_->getSampleCount();
            depthDesc.SampleDesc.Quality = renderSystem_->getSampleQuality();
            depthDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

            throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
                &depthHeap,
                D3D12_HEAP_FLAG_NONE,
                &depthDesc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&intermediateTexture_)));
        }
    }

    // This is what we always need, the CPUBuffer
    CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_READBACK);

    CD3DX12_RESOURCE_DESC desc;
    desc.Alignment = 0;
    desc.DepthOrArraySize = 1;
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Height = 1;
    int elementByteSize = getElementByteSize(mapTextureFormat(format_));
    if((width_ * elementByteSize) % 512 == 0) {
        desc.Width = width_ * height_ * elementByteSize;
    }
    else {
        int rowPitch = width_ * elementByteSize + 512 - (width_ * elementByteSize) % 512;
        desc.Width = rowPitch * (height_ - 1) + width_ * elementByteSize;
    }
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;
    desc.MipLevels = 1;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;

    throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&cpuReadBuffer_)));
    cpuReadable_ = true;
}

void D3D12Texture2D::makeCPUWriteable()
{
	// This is what we always need, the CPUBuffer
	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);

	CD3DX12_RESOURCE_DESC desc;
	desc.Alignment = 0;
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	int elementByteSize = getElementByteSize(mapTextureFormat(format_));
	if ((width_ * elementByteSize) % 512 == 0) {
		desc.Width = width_ * height_ * elementByteSize;
	}
	else {
		int rowPitch = width_ * elementByteSize + 512 - (width_ * elementByteSize) % 512;
		desc.Width = rowPitch * (height_ - 1) + width_ * elementByteSize;
	}
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags = D3D12_RESOURCE_FLAG_NONE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	throwIfFailed(renderSystem_->getDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cpuWriteBuffer_)));
	//renderSystem_->transitResource(cpuWriteBuffer_, D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_SOURCE);
	cpuWriteable_ = true;
}

bool BlueFramework::D3D12RenderSystem::D3D12Texture2D::hasShaderResourceView() const {
	return bindType_ == buw::eTextureBindType::SRV || bindType_ == buw::eTextureBindType::SRV_RTV || bindType_ == buw::eTextureBindType::SRV_DSV;
}

void D3D12Texture2D::createShaderResourceView() {
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = mapShaderResourceFormat(format_);
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = mipLevels;
	srvDesc.Texture2D.PlaneSlice = 0;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	shaderResourceView_ = renderSystem_->getShaderVisibleDescriptorHeap()->alloc();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = renderSystem_->getShaderVisibleDescriptorHeap()->getCPUHandleForSlot(shaderResourceView_);
	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &srvDesc, cpuHandle);
}

void D3D12Texture2D::createRenderTargetView() {
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = mapRenderTargetFormat(format_);
	if (renderSystem_->getMSAAEnabled() && multisampled_)
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
	else
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;
	rtvDesc.Texture2D.PlaneSlice = 0;

	renderTargetView_ = renderSystem_->getRenderTargetDescriptorHeap()->alloc();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = renderSystem_->getRenderTargetDescriptorHeap()->getCPUHandleForSlot(renderTargetView_);
	renderSystem_->getDevice()->CreateRenderTargetView(texture_.Get(), &rtvDesc, cpuHandle);
}

void D3D12Texture2D::createDepthStencilView() {
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = mapDepthStencilFormat(format_);
	if (renderSystem_->getMSAAEnabled() && multisampled_)
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
	else
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.Texture2D.MipSlice = 0;

	depthStencilView_ = renderSystem_->getDepthStencilDescriptorHeap()->alloc();
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle = renderSystem_->getDepthStencilDescriptorHeap()->getCPUHandleForSlot(depthStencilView_);
	renderSystem_->getDevice()->CreateDepthStencilView(texture_.Get(), &dsvDesc, cpuHandle);
}

void D3D12Texture2D::prepareSRV() {
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_GENERIC_READ;
	if (*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target);
		*currentState_ = target;
	}
}
void D3D12Texture2D::prepareRTV() {
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_RENDER_TARGET;
	if (*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target);
		*currentState_ = target;
	}
}
void D3D12Texture2D::prepareDSV() {
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	if (*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
		*currentState_ = target;
	}
}

void D3D12Texture2D::prepareCRA() {
    BLUE_ASSERT(isCPUReadable());
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_COPY_SOURCE;
	if (*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
		*currentState_ = target;
	}
}

void D3D12Texture2D::prepareCWA()
{
	BLUE_ASSERT(isCPUWriteable());
	D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_COPY_DEST;
	if(*currentState_ != target) {
		renderSystem_->transitResource(texture_.Get(), *currentState_, target, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
		*currentState_ = target;
	}
}

void D3D12Texture2D::prepareResolve()
{
    BLUE_ASSERT(isMultisampled());
    D3D12_RESOURCE_STATES target = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
    if(*currentState_ != target) {
        renderSystem_->transitResource(texture_.Get(), *currentState_, target, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
        *currentState_ = target;
    }
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END
