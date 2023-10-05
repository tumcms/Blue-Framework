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
#ifndef BlueFramework_D3D11RenderSystem_D3D11Sampler_557560ca_35f5_40c0_9e78_da73334978b6_h
#define BlueFramework_D3D11RenderSystem_D3D11Sampler_557560ca_35f5_40c0_9e78_da73334978b6_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ISampler.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11Sampler : public buw::ISampler {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11Sampler(D3D11RenderSystem* renderSystem, buw::samplerStateDescription ssd);

	ComPtr<ID3D11SamplerState> getSamplerState() { return samplerState_; }

private:
	D3D11RenderSystem* renderSystem_;
	ComPtr<ID3D11SamplerState> samplerState_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11Sampler_557560ca_35f5_40c0_9e78_da73334978b6_h
