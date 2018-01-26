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
#ifndef BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h
#define BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/ITexture1D.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"
#include "BlueFramework/Core/memory.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12Texture1D : public buw::ITexture1D {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12Texture1D(D3D12RenderSystem* renderSystem, const buw::texture1DDescription& td, buw::eTextureBindType bindType);
	virtual ~D3D12Texture1D();

	D3D12Texture1D::ComPtr<ID3D12Resource> getTexture() const;

	void prepareSRV();

	CD3DX12_GPU_DESCRIPTOR_HANDLE getGPUShaderResourceView() const;


private:
	bool hasShaderResourceView() const;

	void createShaderResourceView();

private:
	buw::eTextureFormat format_;
	int width_, copyRegionWidth_, copyRegionHeight_;

	D3D12RenderSystem* renderSystem_;
	ComPtr<ID3D12Resource> texture_;
	ComPtr<ID3D12Resource> cpuReadTexture_;
	bool cpuReadable_;
	bool multisampled_;
	buw::eTextureBindType bindType_;
	UINT shaderResourceView_, renderTargetView_, depthStencilView_;

	buw::ReferenceCounted<D3D12_RESOURCE_STATES> currentState_;

	UINT arraySize = 1;
	UINT mipLevels = 1;
	UINT sampleCount = 1;
	UINT sampleQuality = 0;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12RenderSystem_D3D12Texture1D_e3bb1747_8529_4160_81fa_86aaa992893e_h
