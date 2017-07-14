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

#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"
#include "BlueFramework/Core/assert.h"

// link D3D libraries with linker
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <comdef.h>
#include <lmerr.h>
#include <strsafe.h>

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

// Copied and modified code from here https://msdn.microsoft.com/de-de/library/windows/desktop/aa370285(v=vs.85).aspx
std::string getHRESULTErrorText(DWORD dwLastError) {
	HMODULE hModule = nullptr; // default to system source
	LPSTR MessageBuffer;
	DWORD dwBufferLength;

	DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM;

	//
	// If dwLastError is in the network range,
	//  load the message source.
	//

	if (dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) {
		hModule = LoadLibraryEx(TEXT("netmsg.dll"), nullptr, LOAD_LIBRARY_AS_DATAFILE);

		if (hModule != nullptr)
			dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
	}

	//
	// Call FormatMessage() to allow for message
	//  text to be acquired from the system
	//  or from the supplied module handle.
	//

	dwBufferLength = FormatMessageA(dwFormatFlags,
	                                hModule, // module to get message from (nullptr == system)
	                                dwLastError,
	                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
	                                (LPSTR)&MessageBuffer,
	                                0,
	                                nullptr);

	std::string errorMessage = MessageBuffer;

	//
	// If we loaded a message source, unload it.
	//
	if (hModule != nullptr)
		FreeLibrary(hModule);

	return errorMessage;
}

//! Determines feature level without creating a device.
D3D_FEATURE_LEVEL determineHighestSupportedFeatureLevel() {
	HRESULT hr = E_FAIL;
	D3D_FEATURE_LEVEL FeatureLevel;

	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, nullptr, &FeatureLevel, nullptr);

	if (FAILED(hr)) {
		throw buw::Exception("Determine the highest supported Direct3D11 feature level failed.");
	}

	return FeatureLevel;
}

std::string featureLevelToString(const D3D_FEATURE_LEVEL FeatureLevel) {
	std::string strFeatureLevel = "Unknown feature level";

	switch (FeatureLevel) {
	case D3D_FEATURE_LEVEL_9_1: strFeatureLevel = "D3D_FEATURE_LEVEL_9_1"; break;
	case D3D_FEATURE_LEVEL_9_2: strFeatureLevel = "D3D_FEATURE_LEVEL_9_2"; break;
	case D3D_FEATURE_LEVEL_9_3: strFeatureLevel = "D3D_FEATURE_LEVEL_9_3"; break;
	case D3D_FEATURE_LEVEL_10_0: strFeatureLevel = "D3D_FEATURE_LEVEL_10_0"; break;
	case D3D_FEATURE_LEVEL_10_1: strFeatureLevel = "D3D_FEATURE_LEVEL_10_1"; break;
	case D3D_FEATURE_LEVEL_11_0: strFeatureLevel = "D3D_FEATURE_LEVEL_11_0"; break;
	case D3D_FEATURE_LEVEL_11_1: strFeatureLevel = "D3D_FEATURE_LEVEL_11_1"; break;
	default: break;
	}

	return strFeatureLevel;
}

#include <d3d9.h>

std::string format_error(unsigned __int32 hr)
{
	std::stringstream ss;
	ss << "Error code = 0x" << std::hex << hr << std::endl;
	return ss.str();
}

void logD3DError(HRESULT hr)
{
	// todo add this states: http://msdn.microsoft.com/en-us/library/windows/desktop/bb509553(v=vs.85).aspx
	switch (hr)
	{
	case D3DERR_INVALIDCALL:
	{
		BLUE_LOG(error)
			<< "Error: D3DERR_INVALIDCALL";
	}
	break;

	case D3DERR_WASSTILLDRAWING:
	{
		BLUE_LOG(error)
			<< "Error: D3DERR_WASSTILLDRAWING";
	}
	break;

	case DXGI_ERROR_INVALID_CALL:
	{
		BLUE_LOG(error)
			<< "Error: DXGI_ERROR_INVALID_CALL";
	}
	break;

	case DXGI_ERROR_UNSUPPORTED:
	{
		BLUE_LOG(error)
			<< "Error: DXGI_ERROR_UNSUPPORTED";
	}
	break;

	case D3D11_ERROR_FILE_NOT_FOUND:
	{
		BLUE_LOG(error)
			<< "Error: D3D11_ERROR_FILE_NOT_FOUND";
	}
	break;

	case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
	{
		BLUE_LOG(error)
			<< "Error: D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS";
	}
	break;

	case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
	{
		BLUE_LOG(error)
			<< "Error: D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS";
	}
	break;

	case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
	{
		BLUE_LOG(error)
			<< "Error: D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD";
	}
	break;

	case E_FAIL:
	{
		BLUE_LOG(error)
			<< "Error: E_FAIL";
	}
	break;

	case E_INVALIDARG:
	{
		BLUE_LOG(error)
			<< "Error: E_INVALIDARG";
	}
	break;

	case E_OUTOFMEMORY:
	{
		BLUE_LOG(error)
			<< "Error: E_OUTOFMEMORY";
	}
	break;

	case S_FALSE:
	{
		BLUE_LOG(error)
			<< "Error: S_FALSE";
	}
	break;

	default:
	{
		BLUE_LOG(error)
			<< "Unknown Error Code: " << hr;

		//wchar_t errorMessage[2000];
		//DXGetErrorDescription(hr, errorMessage, 2000);
		//std::string strError = buw::String::toStdString(errorMessage);
		BLUE_LOG(error)
			<< format_error(hr);
	}
	break;
	}
}

D3D11RenderSystem::D3D11RenderSystem(const buw::renderSystemDescription& rsd) : IRenderSystem(rsd) {
	// determine the highest supported feature level
	D3D_FEATURE_LEVEL HighestSupportedFeatureLevel = determineHighestSupportedFeatureLevel();

	BLUE_LOG(trace) << "Highest Supported Feature Level: " << featureLevelToString(HighestSupportedFeatureLevel).c_str();

	featureLevel_ = HighestSupportedFeatureLevel;

	// requestedFeatureLevels[0] = getD3D11FeatureLevel(rsd.d3dFeatureLevel);

	BLUE_LOG(trace) << "Try to create device.";
	createDevice(rsd);

	BLUE_LOG(trace) << "Try to create swap chain.";
	createSwapChain(rsd);

	BLUE_LOG(trace) << "Creating back buffer";
	createBackBufferTarget(rsd.width, rsd.height);

	BLUE_LOG(trace) << "End of D3D11RenderSystem ctor";
}

D3D11RenderSystem::~D3D11RenderSystem() {
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IEffectCore> D3D11RenderSystem::createEffectCore() {
	return buw::makeReferenceCounted<D3D11EffectCore>(this);
}

const bool D3D11RenderSystem::getMSAAEnabled() const {
	return enableMSAA_;
}

const UINT D3D11RenderSystem::getSampleCount() const {
	return sampleCount_;
}

const UINT D3D11RenderSystem::getSampleQuality() const {
	return sampleQuality_;
}
const char* D3D11RenderSystem::getName() const {
	return "Direct3D 11";
}

void D3D11RenderSystem::resize(int width, int height) {
	DXGI_SWAP_CHAIN_DESC desc;
	swapChain_->GetDesc(&desc);

	backBufferTarget_ = nullptr;
	swapChain_->ResizeBuffers(2, width, height, desc.BufferDesc.Format, desc.Flags);

	createBackBufferTarget(width, height);
}

D3D11RenderSystem::ComPtr<ID3D11Device> D3D11RenderSystem::getDevice() {
	return device_;
}
const D3D11RenderSystem::ComPtr<ID3D11Device> D3D11RenderSystem::getDevice() const {
	return device_;
}

D3D11RenderSystem::ComPtr<ID3D11DeviceContext> D3D11RenderSystem::getDeviceContext() {
	return deviceContext_;
}
const D3D11RenderSystem::ComPtr<ID3D11DeviceContext> D3D11RenderSystem::getDeviceContext() const {
	return deviceContext_;
}

void D3D11RenderSystem::present() {
	if (msaaBackBufferTarget_) {
		deviceContext_->ResolveSubresource(backBufferTarget_->getTexture().Get(), 0, msaaBackBufferTarget_->getTexture().Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);
	}

	swapChain_->Present(0, 0);
}

void D3D11RenderSystem::downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b& dest, const int x /*= 0*/, const int y /*= 0*/) {
	BLUE_ASSERT(itexture->isCPUReadable());

	if (x >= 0 && y >= 0 && x < itexture->width() && y < itexture->height() && x + dest.getWidth() <= itexture->width() && y + dest.getHeight() <= itexture->height()) {
		buw::ReferenceCounted<D3D11Texture2D> texture = std::static_pointer_cast<D3D11Texture2D>(itexture);
		ComPtr<ID3D11Texture2D> tex = texture->getTexture();
		ComPtr<ID3D11Texture2D> staging = texture->getStagingTexture();

		D3D11_BOX region;
		region.left = x;
		region.right = x + dest.getWidth();
		region.top = y;
		region.bottom = y + dest.getHeight();
		region.front = 0;
		region.back = 1;

		bool copyAll = itexture->width() == dest.getWidth() && itexture->height() == dest.getHeight() && x == 0 && y == 0;
		deviceContext_->CopySubresourceRegion(staging.Get(), 0, x, y, 0, tex.Get(), 0, !copyAll ? &region: nullptr);

		D3D11_MAPPED_SUBRESOURCE sub;
		deviceContext_->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &sub);
		D3D11_TEXTURE2D_DESC desc;
		tex->GetDesc(&desc);

		for (int row = 0; row < dest.getHeight(); row++) {
			void* dst = dest.getData() + row * dest.getWidth();
			void* src = (char*)sub.pData + (y + row) * sub.RowPitch + x * getElementByteSize(desc.Format);
			memcpy(dst, src, dest.getRowPitch());
		}

		deviceContext_->Unmap(staging.Get(), 0);
	}
}

void D3D11RenderSystem::uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b& source, const int x, const int y)
{
	BLUE_ASSERT(itexture->isCPUWriteable());

	if (x >= 0 && y >= 0 && x < itexture->width() && y < itexture->height() && x + source.getWidth() <= itexture->width() && y + source.getHeight() <= itexture->height()) {
		buw::ReferenceCounted<D3D11Texture2D> texture = std::static_pointer_cast<D3D11Texture2D>(itexture);
		ComPtr<ID3D11Texture2D> tex = texture->getTexture();
		ComPtr<ID3D11Texture2D> staging = texture->getStagingTexture();

		D3D11_BOX region;
		region.left = x;
		region.right = x + source.getWidth();
		region.top = y;
		region.bottom = y + source.getHeight();
		region.front = 0;
		region.back = 1;

		D3D11_MAPPED_SUBRESOURCE sub;
		deviceContext_->Map(staging.Get(), 0, D3D11_MAP_WRITE, 0, &sub);

		for (int row = 0; row < source.getHeight(); row++) {
			// void* dst = dest.getData() + row * dest.getWidth();
			// void* src = (char*)sub.pData + (y + row) * sub.RowPitch + x * dest.getElementByteSize();

			void* src = source.getData() + row * source.getWidth();
			void* dst = (char*)sub.pData + (y + row) * sub.RowPitch + x * source.getElementByteSize();
			memcpy(dst, src, source.getRowPitch());
		}

		deviceContext_->Unmap(staging.Get(), 0);

		bool copyAll = itexture->width() == source.getWidth() && itexture->height() == source.getHeight() && x == 0 && y == 0;
		deviceContext_->CopySubresourceRegion(tex.Get(), 0, x, y, 0, staging.Get(), 0, !copyAll ? &region : nullptr);
	}
}

void D3D11RenderSystem::clearDepthStencilView(std::shared_ptr<buw::ITexture2D> depthStencil) {
	buw::ReferenceCounted<D3D11Texture2D> ds = std::static_pointer_cast<D3D11Texture2D>(depthStencil);
	deviceContext_->ClearDepthStencilView(ds->getDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 1);
}

void D3D11RenderSystem::clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, const float color[4] /*= nullptr*/) {
	for (auto& renderTarget : renderTargets) {
		float black[4] = {0, 0.2f, 0.4f, 1};
		buw::ReferenceCounted<D3D11Texture2D> rt = std::static_pointer_cast<D3D11Texture2D>(renderTarget);
		deviceContext_->ClearRenderTargetView(rt->getRenderTargetView().Get(), color ? color : black);
	}
}

void D3D11RenderSystem::clearRenderTarget(std::shared_ptr<buw::ITexture2D> renderTarget, const float color[4] /*= nullptr*/) {
	clearRenderTargets({renderTarget}, color);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> D3D11RenderSystem::getBackBufferTarget() {
	if (msaaBackBufferTarget_)
		return msaaBackBufferTarget_;

	return backBufferTarget_;
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IViewport> D3D11RenderSystem::createViewport(const buw::viewportDescription& vpd) {
	return buw::makeReferenceCounted<D3D11Viewport>(vpd);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IBlender> D3D11RenderSystem::createBlender(const buw::blendStateDescription& bsd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ISampler> D3D11RenderSystem::createSampler(const buw::samplerStateDescription& ssd) {
	return buw::makeReferenceCounted<D3D11Sampler>(this, ssd);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> D3D11RenderSystem::createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) {
	return buw::makeReferenceCounted<D3D11Texture2D>(this, td, bindType);
}

buw::ReferenceCounted<buw::ITextureCube> D3D11RenderSystem::createTextureCube(const buw::textureCubeDescription& td, buw::eTextureBindType bindType) {
	return buw::makeReferenceCounted<D3D11TextureCube>(this, td, bindType);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture1D> D3D11RenderSystem::createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) {
	return buw::makeReferenceCounted<D3D11Texture1D>(this, td, bindType);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> D3D11RenderSystem::createConstantBuffer(const buw::constantBufferDescription& cbd) {
	return buw::makeReferenceCounted<D3D11ConstantBuffer>(this, cbd);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IIndexBuffer> D3D11RenderSystem::createIndexBuffer(const buw::indexBufferDescription& ibd) {
	return buw::makeReferenceCounted<D3D11IndexBuffer>(this, ibd);
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IVertexBuffer> D3D11RenderSystem::createVertexBuffer(const buw::vertexBufferDescription& vbd) {
	return buw::makeReferenceCounted<D3D11VertexBuffer>(this, vbd);
}

void D3D11RenderSystem::createDevice(const buw::renderSystemDescription& scd) {
	factory_ = nullptr;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactoryN), (void**)&factory_);
	if (FAILED(hr)) {
		BLUE_LOG(error) << "Failed to create Direct3D11 DXGIFactoryN.";
		throw buw::Exception("Failed to create Direct3D11 DXGIFactoryN.");
	}

	ComPtr<IDXGIAdapter1> adapter = nullptr;

	UINT creationFlags = 0;
#if defined(_DEBUG)
	// If the project is in a debug build, enable the debug layer.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (!scd.forceWarpDevice) {
		getHardwareAdapter(factory_.Get(), &adapter);

		// it seems that no hardware adapter is available
		if (!adapter)
			BLUE_LOG(warning) << "It seems that no hardware adapter is available";
	}

	if (!adapter)
		throwIfFailed(factory_->EnumWarpAdapter(IID_PPV_ARGS(&adapter)));

	throwIfFailed(D3D11CreateDevice(
	  adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, creationFlags, &featureLevel_, 1, D3D11_SDK_VERSION, device_.GetAddressOf(), NULL, deviceContext_.GetAddressOf()));
}

void D3D11RenderSystem::getHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter) const {
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

		// Check to see if the adapter supports Direct3D 11, but don't create
		// the
		// actual device yet.
		if (SUCCEEDED(D3D11CreateDevice(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, NULL, &featureLevel_, 1, D3D11_SDK_VERSION, NULL, NULL, NULL))) {
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}

HRESULT D3D11RenderSystem::injectMSAASetttings(
	DXGI_SWAP_CHAIN_DESC_N &swapChainDesc,
	const bool enableMSAA,
	const D3D_FEATURE_LEVEL featureLevel)
{
	HRESULT hr = S_OK;

	// The default sampler mode, with no anti-aliasing, has a count of 1 and a quality level of 0.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// If anti-aliasing is activated the best possible sample and quality level is chosen.
	if (enableMSAA)
	{
		UINT maxQualityLevel = 0;
		UINT sampleCount = 1;

		// bool checkIfSamplingSettingsAreAvailable(const msaaSampleDescripton& desc);
		// findBestSamplingSettings

		// Find highest available sample count and quality level
		for (sampleCount = 1; sampleCount <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; sampleCount++)
		{
			hr = device_->CheckMultisampleQualityLevels(
				DXGI_FORMAT_R8G8B8A8_UNORM, sampleCount, &maxQualityLevel);

			if (maxQualityLevel > 0)
			{
				maxQualityLevel--;
			}

			if (hr != S_OK)
			{
				BLUE_LOG(error) << "CheckMultisampleQualityLevels failed.";
			}

			if (maxQualityLevel > 0)
			{
				BLUE_LOG(trace) <<
					"MSAA " << sampleCount << "X supported with " <<
					maxQualityLevel << " quality levels.";

				if (sampleCount == 4)
				{
					if (maxQualityLevel >= 8)
						BLUE_LOG(trace) << "CSAA Mode 8x is supported";
					if (maxQualityLevel >= 16)
						BLUE_LOG(trace) << "CSAA Mode 16x is supported";
					if (maxQualityLevel >= 32)
						BLUE_LOG(trace) << "CSAA Mode 32x is supported";
				}

				if (sampleCount == 8)
				{
					if (maxQualityLevel >= 8)
						BLUE_LOG(trace) << "CSAA Mode 8xQ is supported";
					if (maxQualityLevel >= 16)
						BLUE_LOG(trace) << "CSAA Mode 16xQ is supported";
					if (maxQualityLevel >= 32)
						BLUE_LOG(trace) << "CSAA Mode 32xQ is supported";
				}

				swapChainDesc.SampleDesc.Count = sampleCount;
				swapChainDesc.SampleDesc.Quality = maxQualityLevel;
			}
		}
	}

	if (enableMSAA)
	{
		// Direct3D 10.1 devices are required to support 4x MSAA
		if (swapChainDesc.SampleDesc.Count == 1 &&
			swapChainDesc.SampleDesc.Quality == 0 &&
			featureLevel == D3D_FEATURE_LEVEL_10_1)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = 0;
			BLUE_LOG(trace) << "Try to enable MSAA 4X.";
		}
	}	return hr;
}

void D3D11RenderSystem::createSwapChain(const buw::renderSystemDescription& rsd) {

// 	HRESULT hr = false;
// 
// 	DXGI_SWAP_CHAIN_DESC_N swapChainDesc;
// 	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC_N));
// 
// 	// set buffer dimensions and format
// 	swapChainDesc.BufferCount = 2;
// 	swapChainDesc.BufferDesc.Width = rsd.width;
// 	swapChainDesc.BufferDesc.Height = rsd.height;
// 	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
// 	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// 	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
// 	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
// 
// 	bool m_bVsync = true;
// 
// 	// set refresh rate
// 	if (m_bVsync)
// 	{
// 		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
// 		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
// 	}
// 	else
// 	{
// 		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
// 		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
// 	}
// 
// 	// sampling settings
// 	hr = injectMSAASetttings(swapChainDesc, rsd.enableMSAA, featureLevel_);
// 
// 
// 	BLUE_LOG(trace)
// 		<< "SwapChain.SamplerDesc: Count = " << swapChainDesc.SampleDesc.Count
// 		<< " Quality = " << swapChainDesc.SampleDesc.Quality;
// 
// 	// output window handle
// 	HWND hWnd = (HWND)rsd.windowId;
// 	swapChainDesc.OutputWindow = hWnd;
// 	swapChainDesc.Windowed = true;// rsd.windowed;
// 	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching
// 
// 	hr = E_FAIL;
// 
// 	// Attempt to create the swap chain		
// 	hr = factory_->CreateSwapChain(device_.Get(), &swapChainDesc, &swapChain_);
// 
// 	if (FAILED(hr))
// 	{
// 		// Try a second time, may fail the first time due to back buffer count,
// 		// which will be corrected by the runtime
// 		hr = factory_->CreateSwapChain(device_.Get(), &swapChainDesc, &swapChain_);
// 	}
// 
// 	if (FAILED(hr))
// 	{
// 		BLUE_LOG(error)
// 			<< "Failed to create swap chain.";
// 
// 		logD3DError(hr);
// 
// 		throw buw::Exception("Failed to create swap chain.");
// 	}


	
	HRESULT hr = S_OK;

	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = static_cast<UINT>(rsd.width);
	swapChainDesc.BufferDesc.Height = static_cast<UINT>(rsd.height);
	swapChainDesc.BufferDesc.RefreshRate = {1, 60};
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // DXGI_SWAP_EFFECT_FLIP_DISCARD supported only on Windows 10 and up
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.OutputWindow = HWND(rsd.windowId);
	swapChainDesc.Windowed = true;

	enableMSAA_ = rsd.enableMSAA;
	if (enableMSAA_) {
		// D3D11 way of MSAA, store MSAA values
		DXGI_SAMPLE_DESC desc = findBestMSAASettings(swapChainDesc.BufferDesc.Format);
		sampleCount_ = desc.Count;
		sampleQuality_ = 0;
	}

	//HWND hWnd = HWND(rsd.windowId);

	hr = factory_->CreateSwapChain(device_.Get(), &swapChainDesc, swapChain_.GetAddressOf());

	if (FAILED(hr))
	{
		// Try a second time, may fail the first time due to back buffer count,
		// which will be corrected by the runtime
		hr = factory_->CreateSwapChain(device_.Get(), &swapChainDesc, &swapChain_);
	}

	BLUE_LOG(trace) << "After CreateSwapChainForHwnd";

	if (hr != S_OK) {
		logD3DError(hr);
		throw buw::Exception("D3D11 render system error");
	}

	BLUE_LOG(trace) << "End of createSwapChain";
}

DXGI_SAMPLE_DESC D3D11RenderSystem::findBestMSAASettings(DXGI_FORMAT format) {
	HRESULT hr = S_FALSE;

	// The default sampler mode, with no anti-aliasing, has a count of 1 and a quality level of 0.
	UINT maxQualityLevel = 0;
	UINT respectiveSampleCount = 1;

	// If anti-aliasing is activated the best possible sample and quality level is chosen.
	// Find highest available sample count and quality level
	for (UINT sampleCount = 1; sampleCount <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; sampleCount++) {
		UINT numQualityLevels = 0;
		hr = device_->CheckMultisampleQualityLevels(format, sampleCount, &numQualityLevels);
		if (hr != S_OK) {
			BLUE_LOG(error) << "CheckMultisampleQualityLevels failed.";
		}
		if (numQualityLevels > 0) {
			BLUE_LOG(trace) << "MSAA with sampleCount " << sampleCount << " and qualtiy level " << numQualityLevels << " supported.";

			if (maxQualityLevel <= numQualityLevels) {
				maxQualityLevel = numQualityLevels;
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

void D3D11RenderSystem::createBackBufferTarget(UINT width, UINT height) {
	ComPtr<ID3D11Texture2D> backBuffer;
	throwIfFailed(swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer));

	backBufferTarget_ = D3D11Texture2D::fromBackBuffer(this, backBuffer, width, height);

	if (enableMSAA_) {
		buw::texture2DDescription td;
		td.width = width;
		td.height = height;
		td.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td.isCpuReadable = false;
		td.useMSAA = true;
		td.data = nullptr;
		msaaBackBufferTarget_ = buw::makeReferenceCounted<D3D11Texture2D>(this, td, buw::eTextureBindType::RTV);
	}
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

extern "C" buw::IRenderSystem* createRenderSystem(const buw::renderSystemDescription& scd) {
	BLUE_LOG(trace) << "Enter createRenderSystem...";

	return new BlueFramework::D3D11RenderSystem::D3D11RenderSystem(scd);
}