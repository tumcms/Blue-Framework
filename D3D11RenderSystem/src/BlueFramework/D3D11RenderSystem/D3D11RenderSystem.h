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
#ifndef BlueFramework_D3D11RenderSystem_D3D11RenderSystem_a3d55f24_51a9_4b39_8098_11cab8c59842_h
#define BlueFramework_D3D11RenderSystem_D3D11RenderSystem_a3d55f24_51a9_4b39_8098_11cab8c59842_h


#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Rasterizer/Resources/IBlender.h"
#include "BlueFramework/D3D11RenderSystem/D3D11ConstantBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11TextureCube.h"
#include "BlueFramework/D3D11RenderSystem/D3D11EffectCore.h"
#include "BlueFramework/D3D11RenderSystem/D3D11IndexBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11Sampler.h"
#include "BlueFramework/D3D11RenderSystem/D3D11Texture1D.h"
#include "BlueFramework/D3D11RenderSystem/D3D11Texture2D.h"
#include "BlueFramework/D3D11RenderSystem/D3D11VertexBuffer.h"
#include "BlueFramework/D3D11RenderSystem/D3D11Viewport.h"

#include "BlueFramework/Rasterizer/Effect.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

typedef ID3D11Device			ID3D11DeviceN;
typedef ID3D11DeviceContext		ID3D11DeviceContextN;
typedef ID3D11RasterizerState	ID3D11RasterizerStateN;
typedef IDXGIFactory1			IDXGIFactoryN;
typedef IDXGIAdapter1			IDXGIAdapterN;
typedef IDXGIDevice1			IDXGIDeviceN;
typedef IDXGISwapChain			IDXGISwapChainN;
typedef DXGI_SWAP_CHAIN_DESC	DXGI_SWAP_CHAIN_DESC_N;

class D3D11RenderSystem : public buw::IRenderSystem {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11RenderSystem(const buw::renderSystemDescription& rsd);
	virtual ~D3D11RenderSystem();

	virtual buw::ReferenceCounted<buw::IEffectCore> createEffectCore() override;
	virtual buw::ReferenceCounted<buw::IVertexBuffer> createVertexBuffer(const buw::vertexBufferDescription& vbd) override;
	virtual buw::ReferenceCounted<buw::IIndexBuffer> createIndexBuffer(const buw::indexBufferDescription& ibd) override;	
	virtual buw::ReferenceCounted<buw::IConstantBuffer> createConstantBuffer(const buw::constantBufferDescription& cbd) override;	
	virtual buw::ReferenceCounted<buw::ITexture1D> createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) override;	
	virtual buw::ReferenceCounted<buw::ITexture2D> createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) override;

    virtual buw::ReferenceCounted<buw::ITextureCube> createTextureCube(const buw::textureCubeDescription& td, buw::eTextureBindType bindType) override;
	virtual buw::ReferenceCounted<buw::ISampler> createSampler(const buw::samplerStateDescription& ssd) override;	
	virtual buw::ReferenceCounted<buw::IBlender> createBlender(const buw::blendStateDescription& bsd) override;	
	virtual buw::ReferenceCounted<buw::IViewport> createViewport(const buw::viewportDescription& vpd) override;	
	virtual buw::ReferenceCounted<buw::ITexture2D> getBackBufferTarget() override;
	
	virtual void clearRenderTarget(std::shared_ptr<buw::ITexture2D> renderTarget, const float color[4] = nullptr) override;	
	virtual void clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, const float color[4] = nullptr) override;	
	virtual void clearDepthStencilView(std::shared_ptr<buw::ITexture2D> depthStencil) override;
	
	virtual void downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) override;
	virtual void uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &source, const int x = 0, const int y = 0) override;

	virtual void present() override;
	
	virtual void resize(int width, int height) override;
	
	ComPtr<ID3D11Device> getDevice();
	const ComPtr<ID3D11Device> getDevice() const;

	ComPtr<ID3D11DeviceContext> getDeviceContext();
	const ComPtr<ID3D11DeviceContext> getDeviceContext() const;

	virtual const char* getName() const override;	
	virtual const bool getMSAAEnabled() const override;
	const UINT getSampleCount() const;
	const UINT getSampleQuality() const;

private:
	void createDevice(const buw::renderSystemDescription& scd);
	void getHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter) const;
	
	void createSwapChain(const buw::renderSystemDescription& scd);
	DXGI_SAMPLE_DESC findBestMSAASettings(DXGI_FORMAT format);

	void createBackBufferTarget(UINT width, UINT height);
	
	HRESULT injectMSAASetttings(
		DXGI_SWAP_CHAIN_DESC_N &swapChainDesc,
		const bool enableMSAA,
		const D3D_FEATURE_LEVEL featureLevel);

private:
	ComPtr<IDXGIFactory4> factory_;
	ComPtr<ID3D11Device> device_;
	ComPtr<ID3D11DeviceContext> deviceContext_;
	ComPtr<IDXGISwapChain> swapChain_;

	D3D_FEATURE_LEVEL featureLevel_ = D3D_FEATURE_LEVEL_11_0;

	buw::ReferenceCounted<D3D11Texture2D> backBufferTarget_, msaaBackBufferTarget_;

	bool enableMSAA_ = false;
	UINT sampleCount_ = 1;
	UINT sampleQuality_ = 0;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11RenderSystem_a3d55f24_51a9_4b39_8098_11cab8c59842_h
