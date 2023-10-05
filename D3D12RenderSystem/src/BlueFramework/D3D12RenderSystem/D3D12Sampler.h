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
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12Sampler_b690cda5_6b52_4840_85bd_e8667b9638c5_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12Sampler_b690cda5_6b52_4840_85bd_e8667b9638c5_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ISampler.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12Sampler : public buw::ISampler {
public:
	D3D12Sampler(D3D12RenderSystem* renderSystem, buw::samplerStateDescription ssd);
	~D3D12Sampler();

	CD3DX12_CPU_DESCRIPTOR_HANDLE getCPUSamplerView() const;
	CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUSamplerView() const;
private:
	D3D12_FILTER mapFilter(buw::samplerStateDescription ssd) const;
	D3D12_TEXTURE_ADDRESS_MODE mapTextureAddressMode(buw::eTextureAddressMode textureAddressMode) const;
	D3D12_COMPARISON_FUNC mapComparisonFunction(buw::eComparisonFunction compFunction) const;

private:
	D3D12RenderSystem* renderSystem_;
	UINT samplerView_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12Sampler_b690cda5_6b52_4840_85bd_e8667b9638c5_h
