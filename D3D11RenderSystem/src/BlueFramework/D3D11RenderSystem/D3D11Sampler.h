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
