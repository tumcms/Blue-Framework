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

#pragma once
#ifndef BlueFramework_D3D11RenderSystem_d3d11_c6b162d3_c193_4949_a81a_06ee1f41f242_h
#define BlueFramework_D3D11RenderSystem_d3d11_c6b162d3_c193_4949_a81a_06ee1f41f242_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"

#include <wrl.h> // ComPtr
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_4.h>
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

void throwIfFailed(HRESULT hr);
DXGI_FORMAT mapIndexBufferFormat(const buw::eIndexBufferFormat& format);
DXGI_FORMAT mapTextureFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapShaderResourceFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapRenderTargetFormat(const buw::eTextureFormat& format);
DXGI_FORMAT mapDepthStencilFormat(const buw::eTextureFormat& format);
int getElementByteSize(const DXGI_FORMAT &format);

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_d3d11_c6b162d3_c193_4949_a81a_06ee1f41f242_h
