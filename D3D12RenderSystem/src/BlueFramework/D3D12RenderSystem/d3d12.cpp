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

#include "BlueFramework/D3D12RenderSystem/d3d12.h"
#include "BlueFramework/Core/Exception.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

void throwIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		throw buw::Exception("D3D12 render system error");
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
    switch(format) {
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

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END