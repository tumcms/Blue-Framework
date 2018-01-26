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

#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"
#include "BlueFramework/Core/assert.h"
#include "BlueFramework/Rasterizer/vertex.h"
#include <thread>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12RenderSystem::DescriptorHeap::DescriptorHeap() : ptr_(nullptr), capacity_(0), descriptorSize_(0) {
}

D3D12RenderSystem::DescriptorHeap::DescriptorHeap(ComPtr<ID3D12DescriptorHeap> ptr, UINT capacity, UINT desciptorSize)
    : ptr_(ptr), capacity_(capacity), descriptorSize_(desciptorSize) {
	for (UINT i = capacity; i > 0; i--)
		freeList_.push_back(i - 1);
}

D3D12RenderSystem::DescriptorHeap::~DescriptorHeap() {
	ptr_ = nullptr;
	BLUE_ASSERT(freeList_.size() == capacity_);
}

UINT D3D12RenderSystem::DescriptorHeap::alloc() {
	BLUE_ASSERT(!freeList_.empty());

	UINT slot = freeList_.back();
	freeList_.pop_back();
	return slot;
}

void D3D12RenderSystem::DescriptorHeap::free(UINT slot) {
	BLUE_ASSERT(slot < capacity_);

	freeList_.push_back(slot);
}

CD3DX12_CPU_DESCRIPTOR_HANDLE
D3D12RenderSystem::DescriptorHeap::getCPUHandleForSlot(UINT slot) {
	BLUE_ASSERT(slot < capacity_);
	BLUE_ASSERT(std::find(freeList_.begin(), freeList_.end(), slot) == freeList_.end());

	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle(ptr_->GetCPUDescriptorHandleForHeapStart());
	return cpuHandle.Offset(slot, descriptorSize_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE
D3D12RenderSystem::DescriptorHeap::getGPUHandleForSlot(UINT slot) {
	BLUE_ASSERT(slot < capacity_);
	BLUE_ASSERT(std::find(freeList_.begin(), freeList_.end(), slot) == freeList_.end());

	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle(ptr_->GetGPUDescriptorHandleForHeapStart());
	return gpuHandle.Offset(slot, descriptorSize_);
}

D3D12RenderSystem::ComPtr<ID3D12DescriptorHeap> D3D12RenderSystem::DescriptorHeap::getPtr() const {
	return ptr_;
}

D3D12RenderSystem::D3D12RenderSystem(const buw::renderSystemDescription& scd) :
	buw::IRenderSystem(scd)
{
	throwIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory_)));

#if defined(_DEBUG)
	enableDebugLayer();
#endif

	createDevice(scd);

#if defined(_DEBUG)
	disableClearWarnings();
#endif

	createCommandQueueAndAllocatorAndList();
	createSwapChain(scd);

    createFence();
    
	BLUE_LOG(trace) << "Creating descriptor heaps";

	createDescriptorHeap(&shaderVisibleDescriptorHeap_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 510);
	createDescriptorHeap(&samplerDescriptorHeap_, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, 100);
	createDescriptorHeap(&renderTargetDescriptorHeap_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 20);
	createDescriptorHeap(&depthStencilDescriptorHeap_, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 20);

	BLUE_LOG(trace) << "Creating back buffer";
	createBackBufferTarget(scd.width, scd.height);	

	BLUE_LOG(trace) << "End of D3D12RenderSystem ctor";
}

D3D12RenderSystem::~D3D12RenderSystem()
{
	// do manual deletion to be able to detect memory leaks and synchronization problems faster
	flushCommandQueue();
	CloseHandle(fenceEvent_);

	return;

	// Order in which render system resources should be deleted - uncomment this to find memory leaks
/*
	fence_ = nullptr;
	swapChain_ = nullptr;
	immediateCommandList_ = nullptr;
	immediateCommandAllocator_ = nullptr;

	for (int i = 0; i < frameCount_; ++i) {
		commandAllocator_[i] = nullptr;
	}

	commandQueue_ = nullptr;

	device_ = nullptr;
	factory_ = nullptr;
*/

	// Uncomment this section only if you are searching for memory leaks - Begin
/*
#if defined(_DEBUG)
	ComPtr<ID3D12DebugDevice> debug;
	device_.As(&debug);

	if (debug) {
		debug->ReportLiveDeviceObjects(D3D12_RLDO_FLAGS::D3D12_RLDO_DETAIL);
	}
#endif
*/
	// Uncomment this section only if you are searching for memory leaks - End
}


buw::ReferenceCounted<buw::IEffectCore> D3D12RenderSystem::createEffectCore() {
	return buw::makeReferenceCounted<D3D12EffectCore>(this);
}

buw::ReferenceCounted<buw::IVertexBuffer> D3D12RenderSystem::createVertexBuffer(const buw::vertexBufferDescription& vbd) {
	return buw::makeReferenceCounted<D3D12VertexBuffer>(this, vbd);
}

buw::ReferenceCounted<buw::IIndexBuffer> D3D12RenderSystem::createIndexBuffer(const buw::indexBufferDescription& ibd) {
	return buw::makeReferenceCounted<D3D12IndexBuffer>(this, ibd);
}

buw::ReferenceCounted<buw::IConstantBuffer> D3D12RenderSystem::createConstantBuffer(const buw::constantBufferDescription& cbd) {
	return buw::makeReferenceCounted<D3D12ConstantBuffer>(this, cbd);
}

buw::ReferenceCounted<buw::ITexture1D> D3D12RenderSystem::createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) {
	return buw::makeReferenceCounted<D3D12Texture1D>(this, td, bindType);
}

buw::ReferenceCounted<buw::ITexture2D> D3D12RenderSystem::createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) {
	return buw::makeReferenceCounted<D3D12Texture2D>(this, td, bindType);
}

buw::ReferenceCounted<buw::ITextureCube> D3D12RenderSystem::createTextureCube(const buw::textureCubeDescription & td, buw::eTextureBindType bindType)
{
    return buw::makeReferenceCounted<D3D12TextureCube>(this, td, bindType);
}

buw::ReferenceCounted<buw::ISampler> D3D12RenderSystem::createSampler(const buw::samplerStateDescription& ssd) {
	return buw::makeReferenceCounted<D3D12Sampler>(this, ssd);
}

buw::ReferenceCounted<buw::IBlender> D3D12RenderSystem::createBlender(const buw::blendStateDescription& bsd) {
    return buw::makeReferenceCounted<D3D12Blender>(bsd);
}

buw::ReferenceCounted<buw::IViewport> D3D12RenderSystem::createViewport(const buw::viewportDescription& vpd) {
	buw::ReferenceCounted<D3D12Viewport> viewport = buw::makeReferenceCounted<D3D12Viewport>(vpd);
	return viewport;
}

buw::ReferenceCounted<buw::ITexture2D> D3D12RenderSystem::getBackBufferTarget() {
    if (enableMSAA_) return std::static_pointer_cast<buw::ITexture2D>(backBufferMSAA_);
    else return backBufferTargets_[frameIndex_];
}

void D3D12RenderSystem::clearRenderTarget(buw::ReferenceCounted<buw::ITexture2D> irenderTarget, const float color[4] /*= nullptr*/) {
    clearRenderTargets({ irenderTarget }, color);
}

void D3D12RenderSystem::clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> irenderTargets, const float color[4]) {
	for (auto it : irenderTargets)
		std::static_pointer_cast<D3D12Texture2D>(it)->prepareRTV();

	immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);

	for (auto it : irenderTargets) {
		// clear current render target
		buw::ReferenceCounted<D3D12Texture2D> renderTarget = std::static_pointer_cast<D3D12Texture2D>(it);

		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->getCPURenderTargetView();

		float black[4] = { 0, 0.2f, 0.4f, 1 };
		immediateCommandList_->ClearRenderTargetView(rtvHandle, color ? color : black, 0, nullptr);
	}
	immediateCommandList_->Close();
	ID3D12CommandList* com = immediateCommandList_.Get();
	commandQueue_->ExecuteCommandLists(1, &com);
}

void D3D12RenderSystem::clearDepthStencilView(buw::ReferenceCounted<buw::ITexture2D> idepthStencil) {
	buw::ReferenceCounted<D3D12Texture2D> depthStencil = std::static_pointer_cast<D3D12Texture2D>(idepthStencil);
	
	depthStencil->prepareDSV();

	immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil->getCPUDepthStencilView();

	immediateCommandList_->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1,
		1, 0, nullptr);

	immediateCommandList_->Close();
	ID3D12CommandList* com = immediateCommandList_.Get();
	commandQueue_->ExecuteCommandLists(1, &com);
}

void D3D12RenderSystem::present() {
    if (enableMSAA_) {
        transitResource(backBufferMSAA_->getTexture().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_RESOLVE_SOURCE, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
        transitResource(backBufferTargets_[frameIndex_]->getTexture().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_RESOLVE_DEST, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

        immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
        immediateCommandList_->ResolveSubresource(backBufferTargets_[frameIndex_]->getTexture().Get(), 0, backBufferMSAA_->getTexture().Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
        immediateCommandList_->Close();
        ID3D12CommandList* com = immediateCommandList_.Get();
        commandQueue_->ExecuteCommandLists(1, &com);

        transitResource(backBufferMSAA_->getTexture().Get(), D3D12_RESOURCE_STATE_RESOLVE_SOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
        transitResource(backBufferTargets_[frameIndex_]->getTexture().Get(), D3D12_RESOURCE_STATE_RESOLVE_DEST, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
    }

    buw::ReferenceCounted<D3D12Texture2D> backBuffer = std::static_pointer_cast<D3D12Texture2D>(backBufferTargets_[frameIndex_]);
    transitResource(backBuffer->getTexture().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    throwIfFailed(swapChain_->Present(1, 0));

    frameIndex_ = swapChain_->GetCurrentBackBufferIndex();

    const UINT64 fence = fenceValue_;
    throwIfFailed(commandQueue_->Signal(fence_.Get(), fence));
    fenceValue_++;

    // Wait until the previous frame is finished.
    if (fence_->GetCompletedValue() < fence) {
        throwIfFailed(fence_->SetEventOnCompletion(fence, fenceEvent_));
        WaitForSingleObject(fenceEvent_, INFINITE);
    }

    backBuffer = std::static_pointer_cast<D3D12Texture2D>(backBufferTargets_[frameIndex_]);
    transitResource(backBuffer->getTexture().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
    flushCommandQueue();
    getCommandAllocator()->Reset();
    immediateCommandAllocator_->Reset();    
}

void D3D12RenderSystem::copyD3D12Texture(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b &dest, const int x, const int y)
{
    texture->prepareCRA();

    D3D12_RESOURCE_DESC renderTargetDesc = texture->getTexture()->GetDesc();
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout;
   
    device_->GetCopyableFootprints(&renderTargetDesc, 0, 1, 0, &renderTargetLayout, nullptr, nullptr, nullptr);

    CD3DX12_TEXTURE_COPY_LOCATION dstResource(texture->getCPUReadableBuffer().Get(), renderTargetLayout);
    CD3DX12_TEXTURE_COPY_LOCATION srcResource(texture->getTexture().Get(), 0);
        
    immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
    immediateCommandList_->CopyTextureRegion(&dstResource, 0, 0, 0, &srcResource, nullptr);
    immediateCommandList_->Close();
    ID3D12CommandList* com = immediateCommandList_.Get();
    commandQueue_->ExecuteCommandLists(1, &com);
    
    flushCommandQueue();

    mapBufferToImage(texture->getCPUReadableBuffer(), renderTargetLayout, dest, x, y);
}

void D3D12RenderSystem::copyD3D12MultisampledTexture(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b & dest, const int x, const int y)
{
    texture->prepareResolve();

    CD3DX12_RESOURCE_BARRIER transition = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getNoMSAATexture().Get(),
        D3D12_RESOURCE_STATE_COPY_SOURCE,
        D3D12_RESOURCE_STATE_RESOLVE_DEST,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
    immediateCommandList_->ResourceBarrier(1, &transition);
    immediateCommandList_->ResolveSubresource(texture->getNoMSAATexture().Get(), 0, texture->getTexture().Get(), 0, mapTextureFormat(texture->getFormat()));

    transition = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getNoMSAATexture().Get(),
        D3D12_RESOURCE_STATE_RESOLVE_DEST,
        D3D12_RESOURCE_STATE_COPY_SOURCE,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    immediateCommandList_->ResourceBarrier(1, &transition);

    D3D12_RESOURCE_DESC renderTargetDesc = texture->getNoMSAATexture()->GetDesc();
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout;

    device_->GetCopyableFootprints(&renderTargetDesc, 0, 1, 0, &renderTargetLayout, nullptr, nullptr, nullptr);

    CD3DX12_TEXTURE_COPY_LOCATION dstResource(texture->getCPUReadableBuffer().Get(), renderTargetLayout);
    CD3DX12_TEXTURE_COPY_LOCATION srcResource(texture->getNoMSAATexture().Get(), 0);

    immediateCommandList_->CopyTextureRegion(&dstResource, 0, 0, 0, &srcResource, nullptr);
    immediateCommandList_->Close();
    ID3D12CommandList* com = immediateCommandList_.Get();
    commandQueue_->ExecuteCommandLists(1, &com);

    flushCommandQueue();

    mapBufferToImage(texture->getCPUReadableBuffer(), renderTargetLayout, dest, x, y);
}

void D3D12RenderSystem::copyD3D12MultisampledDepthStencil(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b & dest, const int x, const int y)
{
    texture->prepareCRA();

    //ID3D12Resource* srcResource = texture->getTexture().Get(); // warning: initialized but not referenced

    CD3DX12_TEXTURE_COPY_LOCATION dst(texture->getIntermediateTexture().Get(), 0);
    CD3DX12_TEXTURE_COPY_LOCATION src(texture->getTexture().Get(), 0);

    immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
    immediateCommandList_->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
   
    CD3DX12_RESOURCE_BARRIER transitionBarrierSource = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getIntermediateTexture().Get(),
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    CD3DX12_RESOURCE_BARRIER transitionBarrierDest = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getNoMSAATexture().Get(),
        D3D12_RESOURCE_STATE_COPY_SOURCE,
        D3D12_RESOURCE_STATE_RESOLVE_DEST,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    immediateCommandList_->ResourceBarrier(1, &transitionBarrierSource);
    immediateCommandList_->ResourceBarrier(1, &transitionBarrierDest);
    immediateCommandList_->ResolveSubresource(texture->getNoMSAATexture().Get(), 0, texture->getIntermediateTexture().Get(), 0, DXGI_FORMAT_R32_FLOAT);
    
    transitionBarrierSource = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getIntermediateTexture().Get(),
        D3D12_RESOURCE_STATE_RESOLVE_SOURCE,
        D3D12_RESOURCE_STATE_COPY_DEST,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    transitionBarrierDest = CD3DX12_RESOURCE_BARRIER::Transition(
        texture->getNoMSAATexture().Get(),
        D3D12_RESOURCE_STATE_RESOLVE_DEST,
        D3D12_RESOURCE_STATE_COPY_SOURCE,
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

    immediateCommandList_->ResourceBarrier(1, &transitionBarrierSource);
    immediateCommandList_->ResourceBarrier(1, &transitionBarrierDest);
    
    D3D12_RESOURCE_DESC renderTargetDesc = texture->getNoMSAATexture().Get()->GetDesc();
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout;

    device_->GetCopyableFootprints(&renderTargetDesc, 0, 1, 0, &renderTargetLayout, nullptr, nullptr, nullptr);

    dst = CD3DX12_TEXTURE_COPY_LOCATION(texture->getCPUReadableBuffer().Get(), renderTargetLayout);
    src = CD3DX12_TEXTURE_COPY_LOCATION(texture->getNoMSAATexture().Get(), 0);

    immediateCommandList_->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
    immediateCommandList_->Close();
    ID3D12CommandList* com = immediateCommandList_.Get();
    commandQueue_->ExecuteCommandLists(1, &com);
    flushCommandQueue();

    mapBufferToImage(texture->getCPUReadableBuffer(), renderTargetLayout, dest, x, y);
}

void D3D12RenderSystem::mapBufferToImage(ComPtr<ID3D12Resource> &buffer, D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout, buw::Image4b &dest, const int x, const int y)
{
    void* data;
    
    SIZE_T start = 0;
    SIZE_T end = renderTargetLayout.Footprint.RowPitch * (renderTargetLayout.Footprint.Height - 1) + renderTargetLayout.Footprint.Width * getElementByteSize(renderTargetLayout.Footprint.Format);
    auto range = CD3DX12_RANGE(start, end);
    throwIfFailed(buffer->Map(0, &range, &data));

    for(int row = 0; row < dest.getHeight(); row++) {
        void* dst = dest.getData() + row * dest.getWidth();
        void* src = (char*)data + (row + y) * renderTargetLayout.Footprint.RowPitch + (x * getElementByteSize(renderTargetLayout.Footprint.Format));
        memcpy(dst, src, dest.getRowPitch());
    }

	CD3DX12_RANGE writtenRange(0, 0);
    buffer->Unmap(0, &writtenRange);
}

void D3D12RenderSystem::mapImageToBuffer(ComPtr<ID3D12Resource>& buffer, D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout, buw::Image4b & dest, const int x, const int y)
{
	void* data;

	SIZE_T start = 0;
	SIZE_T end = renderTargetLayout.Footprint.RowPitch * (renderTargetLayout.Footprint.Height - 1) + renderTargetLayout.Footprint.Width * getElementByteSize(renderTargetLayout.Footprint.Format);
	auto range = CD3DX12_RANGE(start, end);
	throwIfFailed(buffer->Map(0, &range, &data));

	for(int row = 0; row < dest.getHeight(); row++) {
		void* src = dest.getData() + row * dest.getWidth();
		void* dst = (char*)data + (row + y) * renderTargetLayout.Footprint.RowPitch + (x * getElementByteSize(renderTargetLayout.Footprint.Format));
		memcpy(dst, src, dest.getRowPitch());
	}

	CD3DX12_RANGE writtenRange(0, 0);
	buffer->Unmap(0, &writtenRange);
}

void D3D12RenderSystem::downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b & dest, const int x, const int y)
{
    BLUE_ASSERT(itexture->isCPUReadable());
    buw::ReferenceCounted<D3D12Texture2D> texture = std::static_pointer_cast<D3D12Texture2D>(itexture);
        if(x >= 0 
            && y >= 0
            && x < texture->width()
            && y < texture->height()
            && x + dest.getWidth() <= texture->width()
            && y + dest.getHeight() <= texture->height()) {
        if(texture->isMultisampled()) {
            if(texture->hasDepthStencilView())
                copyD3D12MultisampledDepthStencil(texture, dest, x, y);
            else
                copyD3D12MultisampledTexture(texture, dest, x, y);
        }
        else {
            copyD3D12Texture(texture, dest, x, y);
        }
    }
}

void D3D12RenderSystem::uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b & image, const int x, const int y)
{

	BLUE_ASSERT(itexture->isCPUWriteable());
	buw::ReferenceCounted<D3D12Texture2D> texture = std::static_pointer_cast<D3D12Texture2D>(itexture);
	if(x >= 0
		&& y >= 0
		&& x < texture->width()
		&& y < texture->height()
		&& x + image.getWidth() <= texture->width()
		&& y + image.getHeight() <= texture->height()) {
		texture->prepareCWA();
		
		D3D12_RESOURCE_DESC renderTargetDesc = texture->getTexture()->GetDesc();
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout;
		device_->GetCopyableFootprints(&renderTargetDesc, 0, 1, 0, &renderTargetLayout, nullptr, nullptr, nullptr);

		mapImageToBuffer(texture->getCPUWriteableBuffer(), renderTargetLayout, image, x, y);


		CD3DX12_TEXTURE_COPY_LOCATION srcResource(texture->getCPUWriteableBuffer().Get(), renderTargetLayout);
		CD3DX12_TEXTURE_COPY_LOCATION dstResource(texture->getTexture().Get(), 0);

		immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
		immediateCommandList_->CopyTextureRegion(&dstResource, 0, 0, 0, &srcResource, nullptr);
		immediateCommandList_->Close();
		ID3D12CommandList* com = immediateCommandList_.Get();
		commandQueue_->ExecuteCommandLists(1, &com);

		flushCommandQueue();

	}
}

void D3D12RenderSystem::resize(int width, int height)
{
	for (int i = 0; i < frameCount_; i++) {
		backBufferTargets_[i] = nullptr;
	}

	throwIfFailed(swapChain_->ResizeBuffers(frameCount_, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

	for (int i = 0; i < frameCount_; i++) {
		ComPtr<ID3D12Resource> backBuffer;
		throwIfFailed(swapChain_->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));
		backBufferTargets_[i] = D3D12Texture2D::fromBackBuffer(this, backBuffer, width, height);
	}

    if (enableMSAA_) {
        buw::texture2DDescription msaaRTDesc;
        msaaRTDesc.width = width;
        msaaRTDesc.height = height;
        msaaRTDesc.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
        msaaRTDesc.data = nullptr;
        msaaRTDesc.useMSAA = true;
        backBufferMSAA_->resize(msaaRTDesc);
    }

	frameIndex_ = 0;

	transitResource(backBufferTargets_[frameIndex_]->getTexture().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);

	flushCommandQueue();
}

D3D12RenderSystem::ComPtr<ID3D12Device> D3D12RenderSystem::getDevice() {
	return device_;
}

const D3D12RenderSystem::ComPtr<ID3D12Device> D3D12RenderSystem::getDevice() const {
	return device_;
}

D3D12RenderSystem::ComPtr<ID3D12GraphicsCommandList> D3D12RenderSystem::getImmediateCommandList() {
	return immediateCommandList_;
}
const D3D12RenderSystem::ComPtr<ID3D12GraphicsCommandList> D3D12RenderSystem::getImmediateCommandList() const {
	return immediateCommandList_;
}

D3D12RenderSystem::ComPtr<ID3D12CommandAllocator> D3D12RenderSystem::getCommandAllocator() {
	return commandAllocator_[frameIndex_];
}
const D3D12RenderSystem::ComPtr<ID3D12CommandAllocator> D3D12RenderSystem::getCommandAllocator() const {
	return commandAllocator_[frameIndex_];
}

D3D12RenderSystem::ComPtr<ID3D12CommandQueue> D3D12RenderSystem::getCommandQueue() {
	return commandQueue_;
}
const D3D12RenderSystem::ComPtr<ID3D12CommandQueue> D3D12RenderSystem::getCommandQueue() const {
	return commandQueue_;
}

D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getShaderVisibleDescriptorHeap() {
	return &shaderVisibleDescriptorHeap_;
}
const D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getShaderVisibleDescriptorHeap() const {
	return &shaderVisibleDescriptorHeap_;
}

D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getSamplerDescriptorHeap() {
	return &samplerDescriptorHeap_;
}
const D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getSamplerDescriptorHeap() const {
	return &samplerDescriptorHeap_;
}

D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getRenderTargetDescriptorHeap() {
	return &renderTargetDescriptorHeap_;
}
const D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getRenderTargetDescriptorHeap() const {
	return &renderTargetDescriptorHeap_;
}

D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getDepthStencilDescriptorHeap() {
	return &depthStencilDescriptorHeap_;
}
const D3D12RenderSystem::DescriptorHeap* D3D12RenderSystem::getDepthStencilDescriptorHeap() const {
	return &depthStencilDescriptorHeap_;
}

UINT D3D12RenderSystem::getFrameIndex() const {
	return frameIndex_;
}

UINT64 D3D12RenderSystem::getFenceValue() const {
	return fenceValue_;
}

void D3D12RenderSystem::uploadDataToUploadBuffer(ComPtr<ID3D12Resource> destResource, size_t dataRowPitch, size_t dataSlicePitch, const void ** dataPtr, UINT num_subresources) {
	size_t requiredDataSize = GetRequiredIntermediateSize(destResource.Get(), 0, num_subresources);

	ComPtr<ID3D12Resource> uploadBuffer;

	CD3DX12_HEAP_PROPERTIES heapProperties(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(requiredDataSize);

	throwIfFailed(device_->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadBuffer)));
	uploadBuffer->SetName(L"UploadBuffer");

    D3D12_SUBRESOURCE_DATA* subResourceData = new D3D12_SUBRESOURCE_DATA[num_subresources];

    for(int subresource = 0; subresource < num_subresources; subresource++) {
        subResourceData[subresource].pData = dataPtr[subresource];
        subResourceData[subresource].RowPitch = dataRowPitch;
        subResourceData[subresource].SlicePitch = dataSlicePitch;
    }
	
	immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
	UpdateSubresources(immediateCommandList_.Get(), destResource.Get(), uploadBuffer.Get(), 0, 0, num_subresources, subResourceData);
	immediateCommandList_->Close();

	ID3D12CommandList* com = immediateCommandList_.Get();
	commandQueue_->ExecuteCommandLists(1, &com);

	uploadBuffers_.push_back(uploadBuffer);
    delete(subResourceData);
}

void D3D12RenderSystem::uploadData(ComPtr<ID3D12Resource> destResource, size_t dataSize, const void* dataPtr) {
	UINT8* pDst;
	CD3DX12_RANGE readRange(0, 0);
	throwIfFailed(destResource->Map(0, &readRange, reinterpret_cast<void**>(&pDst)));
	memcpy(pDst, dataPtr, dataSize);
	destResource->Unmap(0, nullptr);
}

void D3D12RenderSystem::transitResource(ComPtr<ID3D12Resource> resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) {
	transitResource(resource, from, to, 0);
}

void D3D12RenderSystem::transitResource(ComPtr<ID3D12Resource> resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to, UINT subresources) {
	CD3DX12_RESOURCE_BARRIER transitionBarrier = CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), from, to, subresources);

	immediateCommandList_->Reset(immediateCommandAllocator_.Get(), nullptr);
	immediateCommandList_->ResourceBarrier(1, &transitionBarrier);
	immediateCommandList_->Close();

	ID3D12CommandList* com = immediateCommandList_.Get();
	commandQueue_->ExecuteCommandLists(1, &com);
}

void D3D12RenderSystem::flushCommandQueue() {
	// Wait for the command list to execute; we are reusing the same command
	// list in our main loop but for now, we just want to wait for setup to
	// complete before continuing.

	// Signal and increment the fence value.
	const UINT64 fenceToWaitFor = fenceValue_;
	throwIfFailed(commandQueue_->Signal(fence_.Get(), fenceToWaitFor));
	fenceValue_++;

	// Wait until the fence is completed.
	throwIfFailed(fence_->SetEventOnCompletion(fenceToWaitFor, fenceEvent_));

	WaitForSingleObject(fenceEvent_, INFINITE);

	uploadBuffers_.clear();
}


#if defined(_DEBUG)
void D3D12RenderSystem::enableDebugLayer() const {

	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
}

void D3D12RenderSystem::disableClearWarnings() const {
	ComPtr<ID3D12DebugDevice> debug;
	if (SUCCEEDED(device_.As(&debug))) {

		ComPtr<ID3D12InfoQueue> info;
		if (SUCCEEDED(debug.As(&info))) {
			D3D12_MESSAGE_ID hide[] =
			{
				D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,
				D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE
			};

			D3D12_INFO_QUEUE_FILTER filter;
			memset(&filter, 0, sizeof(filter));
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			info->AddStorageFilterEntries(&filter);
		}
	}
}
#endif

void D3D12RenderSystem::createDevice(const buw::renderSystemDescription& scd) {
	ComPtr<IDXGIAdapter1> adapter = nullptr;

	if (!scd.forceWarpDevice) {
		getHardwareAdapter(factory_.Get(), &adapter);

		if (!adapter)
			BLUE_LOG(warning) << "It seems that no hardware adapter is available";
	}

	if (!adapter)
		throwIfFailed(factory_->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));

	throwIfFailed(D3D12CreateDevice(adapter.Get(), featureLevel_, IID_PPV_ARGS(&device_)));
}

void D3D12RenderSystem::getHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter) const {
	ComPtr<IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex) {
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			// Don't select the Basic Render Driver adapter.
			// If you want a software adapter, pass in "/warp" on the command
			// line.
			continue;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create
		// the
		// actual device yet.
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevel_, _uuidof(ID3D12Device), nullptr))) {
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}

void D3D12RenderSystem::createCommandQueueAndAllocatorAndList() {
	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	throwIfFailed(device_->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue_)));

	for (int i = 0; i < frameCount_; ++i) {
		throwIfFailed(device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator_[i])));
	}

	throwIfFailed(device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&immediateCommandAllocator_)));
	throwIfFailed(device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, immediateCommandAllocator_.Get(), nullptr, IID_PPV_ARGS(&immediateCommandList_)));

	immediateCommandList_->Close();
}

DXGI_SAMPLE_DESC D3D12RenderSystem::findBestMSAASettings(DXGI_FORMAT format)
{
	HRESULT hr = S_FALSE;

	// The default sampler mode, with no anti-aliasing, has a count of 1 and a quality level of 0.
	UINT maxQualityLevel = 0;
	UINT respectiveSampleCount = 1;

	// If anti-aliasing is activated the best possible sample and quality level is chosen.
	// Find highest available sample count and quality level
	for (UINT sampleCount = 1; sampleCount <= D3D12_MAX_MULTISAMPLE_SAMPLE_COUNT; sampleCount++) {
		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityDesc{};
		msaaQualityDesc.SampleCount = sampleCount;
		msaaQualityDesc.Format = format; // DXGI_FORMAT_R8G8B8A8_UNORM;
		msaaQualityDesc.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
		msaaQualityDesc.NumQualityLevels = 0;

		hr = device_->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityDesc, sizeof(msaaQualityDesc));
		if (hr != S_OK) {
			BLUE_LOG(error) << "CheckMultisampleQualityLevels failed.";
		}
		if (msaaQualityDesc.NumQualityLevels > 0) {
			BLUE_LOG(trace) << "MSAA with sampleCount " << msaaQualityDesc.SampleCount << " and qualtiy level " << msaaQualityDesc.NumQualityLevels << " supported.";

			if (maxQualityLevel <= msaaQualityDesc.NumQualityLevels) {
				maxQualityLevel = msaaQualityDesc.NumQualityLevels;
				respectiveSampleCount = sampleCount;
			}
		}
	}

	BLUE_ASSERT(hr == S_OK, "find best MSAA setting failed.")

	DXGI_SAMPLE_DESC sd;
	sd.Count = respectiveSampleCount;
	sd.Quality = maxQualityLevel;
	
	return sd;
}

void D3D12RenderSystem::createSwapChain(const buw::renderSystemDescription& rsd) {
	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = frameCount_;
	swapChainDesc.Width = static_cast<UINT>(rsd.width);
	swapChainDesc.Height = static_cast<UINT>(rsd.height);
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

    enableMSAA_ = rsd.enableMSAA;
	if (enableMSAA_) {
		// D3D12 way of MSAA, store MSAA values
		DXGI_SAMPLE_DESC desc = findBestMSAASettings(swapChainDesc.Format);
        sampleCount_ = desc.Count;
        sampleQuality_ = 0;
	}

	HWND hWnd = HWND(rsd.windowId);

	ComPtr<IDXGISwapChain1> swapChain;

	HRESULT hr = factory_->CreateSwapChainForHwnd(commandQueue_.Get(), // Swap chain needs the queue so that it can force a flush on it.
	                                              hWnd, &swapChainDesc, nullptr, nullptr, &swapChain);
    BLUE_LOG(trace) << "After CreateSwapChainForHwnd";

	if (hr != S_OK) {
		throw buw::Exception("D3D12 render system error");
	}

	throwIfFailed(factory_->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));

	throwIfFailed(swapChain.As(&swapChain_));
	frameIndex_ = swapChain_->GetCurrentBackBufferIndex();

	BLUE_LOG(trace) << "End of createSwapChain";
}

void D3D12RenderSystem::createDescriptorHeap(D3D12RenderSystem::DescriptorHeap* heap, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors) const {
	D3D12_DESCRIPTOR_HEAP_DESC descHeapCbvSrv = {};
	descHeapCbvSrv.NumDescriptors = numDescriptors;
	descHeapCbvSrv.Type = type;
	descHeapCbvSrv.Flags = (type == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV || type == D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER) ?
	                         D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE :
	                         D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ID3D12DescriptorHeap* ptr;
	throwIfFailed(device_->CreateDescriptorHeap(&descHeapCbvSrv, __uuidof(ID3D12DescriptorHeap), reinterpret_cast<void**>(&ptr)));

	new (heap) DescriptorHeap(ptr, numDescriptors, device_->GetDescriptorHandleIncrementSize(type));

	ptr->Release();
}

void D3D12RenderSystem::createBackBufferTarget(UINT width, UINT height) {
	for (int i = 0; i < frameCount_; i++) {
		ComPtr<ID3D12Resource> backBuffer;
		throwIfFailed(swapChain_->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));
		backBufferTargets_[i] = D3D12Texture2D::fromBackBuffer(this, backBuffer, width, height);
	}

    if (enableMSAA_) {
        buw::texture2DDescription msaaRTDesc;
        msaaRTDesc.width = width;
        msaaRTDesc.height = height;
        msaaRTDesc.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
        msaaRTDesc.data = nullptr;
        msaaRTDesc.useMSAA = true;
        backBufferMSAA_ = buw::makeReferenceCounted<D3D12Texture2D>(this, msaaRTDesc, buw::eTextureBindType::RTV);
    }

	transitResource(backBufferTargets_[frameIndex_]->getTexture().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET,
	                D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
}

void D3D12RenderSystem::createFence() {
	throwIfFailed(device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_)));
	fenceValue_ = 1;

	// Create an event handle to use for frame synchronization.
	fenceEvent_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (fenceEvent_ == nullptr) {
		throwIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}
}

const char* D3D12RenderSystem::getName() const {
	return "Direct3D 12";
}

const bool D3D12RenderSystem::getMSAAEnabled() const
{
    return enableMSAA_;
}

const UINT D3D12RenderSystem::getSampleCount() const
{
    return sampleCount_;
}

const UINT D3D12RenderSystem::getSampleQuality() const
{
    return sampleQuality_;
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

extern "C" buw::IRenderSystem* createRenderSystem(const buw::renderSystemDescription& scd)
{
	BLUE_LOG(trace) << "Enter createRenderSystem...";

	return new BlueFramework::D3D12RenderSystem::D3D12RenderSystem(scd);
}