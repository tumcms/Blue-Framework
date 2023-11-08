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

#include "BlueFramework/D3D11RenderSystem/d3d11.h"
#include "BlueFramework/Core/Exception.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN


void throwIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		throw buw::Exception("D3D11 render system error");
	}
}

DXGI_FORMAT mapIndexBufferFormat(const buw::eIndexBufferFormat& format) {
	switch (format) {
	case buw::eIndexBufferFormat::UnsignedInt16: return DXGI_FORMAT_R16_UINT;
	case buw::eIndexBufferFormat::UnsignedInt32: return DXGI_FORMAT_R32_UINT;
	default: return DXGI_FORMAT_UNKNOWN;
	}
}

DXGI_FORMAT mapTextureFormat(const buw::eTextureFormat& format) {
	switch (format) {
	case buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM;
	case buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt: return DXGI_FORMAT_R24G8_TYPELESS;
	case buw::eTextureFormat::R32_UnsignedInt: return DXGI_FORMAT_R32_UINT;
	default: return DXGI_FORMAT_UNKNOWN;
	}
}

DXGI_FORMAT mapShaderResourceFormat(const buw::eTextureFormat& format) {
	switch (format) {
	case buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;

	default: return mapTextureFormat(format);
	}
}

DXGI_FORMAT mapRenderTargetFormat(const buw::eTextureFormat& format) {
	return mapTextureFormat(format);
}

DXGI_FORMAT mapDepthStencilFormat(const buw::eTextureFormat& format) {
	switch (format) {
	case buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt: return DXGI_FORMAT_D24_UNORM_S8_UINT;

	default: return mapTextureFormat(format);
	}
}

int getElementByteSize(const DXGI_FORMAT & format)
{
	switch (format) {
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return 4;
	default:
		return 0;
	}
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END