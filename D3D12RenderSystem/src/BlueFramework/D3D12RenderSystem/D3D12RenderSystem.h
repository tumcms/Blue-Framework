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

#pragma once
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12RenderSystem_f0a9e047_20b3_472a_8f34_199c32e6109d_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12RenderSystem_f0a9e047_20b3_472a_8f34_199c32e6109d_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

#include "BlueFramework/D3D12RenderSystem/D3D12EffectCore.h"
#include "BlueFramework/D3D12RenderSystem/D3D12ConstantBuffer.h"
#include "BlueFramework/D3D12RenderSystem/D3D12IndexBuffer.h"
#include "BlueFramework/D3D12RenderSystem/D3D12Sampler.h"
#include "BlueFramework/D3D12RenderSystem/D3D12Blender.h"
#include "BlueFramework/D3D12RenderSystem/D3D12Texture1D.h"
#include "BlueFramework/D3D12RenderSystem/D3D12Texture2D.h"
#include "BlueFramework/D3D12RenderSystem/D3D12TextureCube.h"
#include "BlueFramework/D3D12RenderSystem/D3D12VertexBuffer.h"
#include "BlueFramework/D3D12RenderSystem/D3D12Viewport.h"
#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/ImageProcessing/Image.h"
#include <list>

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem : public buw::IRenderSystem {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	struct DescriptorHeap {
		DescriptorHeap();
		DescriptorHeap(ComPtr<ID3D12DescriptorHeap> ptr, UINT capacity, UINT desciptorSize);
		virtual ~DescriptorHeap();

		UINT alloc(); /// Returns the slot number in which the DescriptorHeap will be placed.

		void free(UINT slot);

		CD3DX12_CPU_DESCRIPTOR_HANDLE getCPUHandleForSlot(UINT slot);
		CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUHandleForSlot(UINT slot);

		ComPtr<ID3D12DescriptorHeap> getPtr() const;

	private:
		ComPtr<ID3D12DescriptorHeap> ptr_;
		UINT capacity_;
		UINT descriptorSize_;
		std::list<UINT> freeList_;
	};

public:
	D3D12RenderSystem(const buw::renderSystemDescription& scd);
	~D3D12RenderSystem();

	buw::ReferenceCounted<buw::IEffectCore> createEffectCore() override;

	buw::ReferenceCounted<buw::IVertexBuffer> createVertexBuffer(const buw::vertexBufferDescription& vbd) override;
	buw::ReferenceCounted<buw::IIndexBuffer> createIndexBuffer(const buw::indexBufferDescription& ibd) override;
	buw::ReferenceCounted<buw::IConstantBuffer> createConstantBuffer(const buw::constantBufferDescription& cbd) override;
	buw::ReferenceCounted<buw::ITexture1D> createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) override;
	buw::ReferenceCounted<buw::ITexture2D> createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) override;
    buw::ReferenceCounted<buw::ITextureCube> createTextureCube(const buw::textureCubeDescription& td, buw::eTextureBindType bindType) override;
	buw::ReferenceCounted<buw::ISampler> createSampler(const buw::samplerStateDescription& ssd) override;
    buw::ReferenceCounted<buw::IBlender> createBlender(const buw::blendStateDescription& bsd) override;
	buw::ReferenceCounted<buw::IViewport> createViewport(const buw::viewportDescription& vpd) override;
	buw::ReferenceCounted<buw::ITexture2D> getBackBufferTarget() override;

	void clearRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, const float color[4] /*= nullptr*/) override;
    void clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, const float color[4]) override;
	void clearDepthStencilView(buw::ReferenceCounted<buw::ITexture2D> depthStencil) override;

	/// Transits resources to the present state. Waits for previous frame to finish rendering. Swaps front and back buffer. Resets the
	/// CommandAllocator used for allocation in the next frame.
	void present() override;
    


    void downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) override;
	void uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &image, const int x = 0, const int y = 0) override;

	void resize(int width, int height) override;

	ComPtr<ID3D12Device> getDevice();
	const ComPtr<ID3D12Device> getDevice() const;

	ComPtr<ID3D12GraphicsCommandList> getImmediateCommandList();
	const ComPtr<ID3D12GraphicsCommandList> getImmediateCommandList() const;

	ComPtr<ID3D12CommandAllocator> getCommandAllocator();
	const ComPtr<ID3D12CommandAllocator> getCommandAllocator() const;

	ComPtr<ID3D12CommandQueue> getCommandQueue();
	const ComPtr<ID3D12CommandQueue> getCommandQueue() const;

	DescriptorHeap* getShaderVisibleDescriptorHeap();
	const DescriptorHeap* getShaderVisibleDescriptorHeap() const;

	DescriptorHeap* getSamplerDescriptorHeap();
	const DescriptorHeap* getSamplerDescriptorHeap() const;

	DescriptorHeap* getRenderTargetDescriptorHeap();
	const DescriptorHeap* getRenderTargetDescriptorHeap() const;

	DescriptorHeap* getDepthStencilDescriptorHeap();
	const DescriptorHeap* getDepthStencilDescriptorHeap() const;

	UINT getFrameIndex() const;
	UINT64 getFenceValue() const;

	/// Copy data to a resource via new upload resource and update subresources. Used for textures etc.
	void uploadDataToUploadBuffer(ComPtr<ID3D12Resource> destResource, size_t dataRowPitch, size_t dataSlicePitch, const void ** dataPtr, UINT num_subresources);

	/// Copy data to the buffer via map/unmap. Used for Vertex-, Index- and ConstantBuffers.
	void uploadData(ComPtr<ID3D12Resource> destResource, size_t dataSize, const void* dataPtr);

	/// Calls transitResource(resource, from, to, 0);
	void transitResource(ComPtr<ID3D12Resource> resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to);
	void transitResource(ComPtr<ID3D12Resource> resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to, UINT subresources);

	/// Waiting for the CommandQueue to execute data updates and clears the allocated upload buffers.
	void flushCommandQueue();
    
	const char* getName() const override;

    const bool getMSAAEnabled() const override;

    const UINT getSampleCount() const;

    const UINT getSampleQuality() const;

private:
#if defined(_DEBUG)
	void enableDebugLayer() const;
	void disableClearWarnings() const;
#endif

	void createDevice(const buw::renderSystemDescription& scd);
	void getHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter) const;

	/// Creates the Command Queue and one CommandAllocator for each render target. Creates the
	/// immediateCommandList_.
	void createCommandQueueAndAllocatorAndList();

	void createSwapChain(const buw::renderSystemDescription& scd);

	void createDescriptorHeap(DescriptorHeap* heap, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors) const;

	void createBackBufferTarget(UINT width, UINT height);

	/// Initializes the fenceEvent_ with a new fence.
	void createFence();

	DXGI_SAMPLE_DESC findBestMSAASettings(DXGI_FORMAT format);

    void copyD3D12Texture(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b &dest, const int x = 0, const int y = 0);
    
    void copyD3D12MultisampledTexture(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b &dest, const int x = 0, const int y = 0);

    void copyD3D12MultisampledDepthStencil(buw::ReferenceCounted<D3D12Texture2D> texture, buw::Image4b &dest, const int x = 0, const int y = 0);

    void mapBufferToImage(ComPtr<ID3D12Resource> &buffer, D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout, buw::Image4b &dest, const int x, const int y);
	void mapImageToBuffer(ComPtr<ID3D12Resource> &buffer, D3D12_PLACED_SUBRESOURCE_FOOTPRINT renderTargetLayout, buw::Image4b &dest, const int x, const int y);

private:
	ComPtr<IDXGIFactory4> factory_;
	ComPtr<ID3D12Device> device_;
	static const UINT frameCount_ = 2;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	std::array<ComPtr<ID3D12CommandAllocator>, frameCount_> commandAllocator_;
	ComPtr<ID3D12GraphicsCommandList> immediateCommandList_;
	ComPtr<ID3D12CommandAllocator> immediateCommandAllocator_;
	ComPtr<IDXGISwapChain3> swapChain_;

	UINT frameIndex_ = 0;

	DescriptorHeap shaderVisibleDescriptorHeap_;
	DescriptorHeap samplerDescriptorHeap_;
	DescriptorHeap renderTargetDescriptorHeap_;
	DescriptorHeap depthStencilDescriptorHeap_;

	// Synchronization objects
	ComPtr<ID3D12Fence> fence_;
	HANDLE fenceEvent_;
	UINT64 fenceValue_;

	static const D3D_FEATURE_LEVEL featureLevel_ = D3D_FEATURE_LEVEL_11_0;

	std::array<buw::ReferenceCounted<D3D12Texture2D>, frameCount_> backBufferTargets_;

    bool enableMSAA_ = false;
    UINT sampleCount_ = 1;
    UINT sampleQuality_ = 0;
    buw::ReferenceCounted<D3D12Texture2D> backBufferMSAA_;

	std::vector<ComPtr<ID3D12Resource>> uploadBuffers_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

BLUEFRAMEWORK_D3D12RENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(D3D12RenderSystem)

extern "C" buw::IRenderSystem* createRenderSystem(const buw::renderSystemDescription& scd);

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12RenderSystem_f0a9e047_20b3_472a_8f34_199c32e6109d_h
