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

#include "BlueFramework/D3D12RenderSystem/D3D12Sampler.h"
#include "BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

D3D12Sampler::D3D12Sampler(D3D12RenderSystem* renderSystem, buw::samplerStateDescription ssd) :
	ISampler(renderSystem, ssd),
	renderSystem_(renderSystem)
{
	D3D12_SAMPLER_DESC samplerDesc = {};
	ZeroMemory(&samplerDesc, sizeof(D3D12_SAMPLER_DESC));
	samplerDesc.Filter = mapFilter(ssd);
	samplerDesc.AddressU = mapTextureAddressMode(ssd.textureAddressModeU);
	samplerDesc.AddressV = mapTextureAddressMode(ssd.textureAddressModeV);
	samplerDesc.AddressW = mapTextureAddressMode(ssd.textureAddressModeW);
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = mapComparisonFunction(ssd.compFunction);
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.BorderColor[0] = 1.0f;
	samplerDesc.BorderColor[1] = 1.0f;
	samplerDesc.BorderColor[2] = 1.0f;
	samplerDesc.BorderColor[3] = 1.0f;

	samplerView_ = renderSystem_->getSamplerDescriptorHeap()->alloc();
	renderSystem_->getDevice()->CreateSampler(
		&samplerDesc,
		renderSystem_->getSamplerDescriptorHeap()->getCPUHandleForSlot(samplerView_)
	);
}

D3D12Sampler::~D3D12Sampler()
{
	renderSystem_->getSamplerDescriptorHeap()->free(samplerView_);
}


CD3DX12_CPU_DESCRIPTOR_HANDLE D3D12Sampler::getCPUSamplerView() const
{
	return renderSystem_->getSamplerDescriptorHeap()->getCPUHandleForSlot(samplerView_);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12Sampler::getGPUSamplerView() const
{
	return renderSystem_->getSamplerDescriptorHeap()->getGPUHandleForSlot(samplerView_);
}

D3D12_FILTER D3D12Sampler::mapFilter(buw::samplerStateDescription ssd) const
{
	switch (ssd.minificationFilter) {
	case (buw::eFilter::Point):
		switch (ssd.magnificationFilter) {
		case Rasterizer::eFilter::Point:
			switch (ssd.mipLevelFilter) {
			case Rasterizer::eFilter::Point:
				return D3D12_FILTER_MIN_MAG_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			default:
				break;
			}
			break;
		case Rasterizer::eFilter::Linear:
			switch (ssd.mipLevelFilter) {
			case Rasterizer::eFilter::Point:
				return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			default:
				break;
			}
			break;
		default:
			break;
		}
	case (buw::eFilter::Linear):
		switch (ssd.magnificationFilter) {
		case (buw::eFilter::Point):
			switch (ssd.mipLevelFilter) {
			case Rasterizer::eFilter::Point:
				return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			default:
				break;
			}
			break;
		case (buw::eFilter::Linear):
			switch (ssd.mipLevelFilter) {
			case (buw::eFilter::Point):
				return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			case (buw::eFilter::Linear):
				return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			default:
				break;
			}
			break;
		default:
			break;
		};
	case (buw::eFilter::Anisotropic):
		return D3D12_FILTER_ANISOTROPIC;
		break;
	default:
		break;
	}
	BLUE_LOG(warning) << "Non compatible Filter.";
	return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
}

D3D12_COMPARISON_FUNC D3D12Sampler::mapComparisonFunction(buw::eComparisonFunction compFunction) const
{
	switch (compFunction) {
	case (buw::eComparisonFunction::Always): return D3D12_COMPARISON_FUNC_ALWAYS;
	case (buw::eComparisonFunction::Equal): return D3D12_COMPARISON_FUNC_EQUAL;
	case (buw::eComparisonFunction::Greater): return D3D12_COMPARISON_FUNC_GREATER;
	case (buw::eComparisonFunction::GreaterEqual): return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	case (buw::eComparisonFunction::Less): return D3D12_COMPARISON_FUNC_LESS;
	case (buw::eComparisonFunction::LessEqual): return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case (buw::eComparisonFunction::Never): return D3D12_COMPARISON_FUNC_NEVER;
	case (buw::eComparisonFunction::NotEqual): return D3D12_COMPARISON_FUNC_NOT_EQUAL;
	default: return D3D12_COMPARISON_FUNC_ALWAYS;
	}
}

D3D12_TEXTURE_ADDRESS_MODE D3D12Sampler::mapTextureAddressMode(buw::eTextureAddressMode textureAddressMode) const
{
	switch (textureAddressMode) {
	case(buw::eTextureAddressMode::Border): return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	case(buw::eTextureAddressMode::Clamp): return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	case(buw::eTextureAddressMode::Mirror): return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
	case(buw::eTextureAddressMode::MirrorOnce): return D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
	case(buw::eTextureAddressMode::Wrap): return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	default: return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	}
}

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END