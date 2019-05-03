/*
	This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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
