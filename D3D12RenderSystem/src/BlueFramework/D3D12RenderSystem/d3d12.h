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

#pragma once
#ifndef BlueFramework_D3D12EffectRenderSystem_d3d12_04a50695_ac1a_4a2d_8023_bc60d0ef6a2d_h
#define BlueFramework_D3D12EffectRenderSystem_d3d12_04a50695_ac1a_4a2d_8023_bc60d0ef6a2d_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"

#include <wrl.h> // ComPtr
#include <d3d12.h>
#include <d3dcompiler.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

void throwIfFailed(HRESULT hr);
DXGI_FORMAT mapTextureFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapShaderResourceFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapRenderTargetFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapDepthStencilFormat(const buw::eTextureFormat& format);
int getElementByteSize(const DXGI_FORMAT &format);

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_d3d12_04a50695_ac1a_4a2d_8023_bc60d0ef6a2d_h