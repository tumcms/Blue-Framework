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

#include "BlueFramework/D3D11RenderSystem/D3D11Sampler.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

D3D11_FILTER mapFilter(buw::samplerStateDescription ssd);
D3D11_COMPARISON_FUNC mapComparisonFunction(buw::eComparisonFunction compFunction);
D3D11_TEXTURE_ADDRESS_MODE mapTextureAddressMode(buw::eTextureAddressMode textureAddressMode);

D3D11Sampler::D3D11Sampler(D3D11RenderSystem* renderSystem, buw::samplerStateDescription ssd) :
	ISampler(renderSystem, ssd),
	renderSystem_(renderSystem)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = mapFilter(ssd);
	desc.AddressU = mapTextureAddressMode(ssd.textureAddressModeU);
	desc.AddressV = mapTextureAddressMode(ssd.textureAddressModeV);
	desc.AddressW = mapTextureAddressMode(ssd.textureAddressModeW);
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 16;
	desc.ComparisonFunc = mapComparisonFunction(ssd.compFunction);
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.MinLOD = 0.0f;
	desc.MinLOD = D3D11_FLOAT32_MAX;

	renderSystem_->getDevice()->CreateSamplerState(&desc, samplerState_.GetAddressOf());
}

D3D11_FILTER mapFilter(buw::samplerStateDescription ssd)
{
	switch (ssd.minificationFilter) {
	case (buw::eFilter::Point):
		switch (ssd.magnificationFilter) {
		case Rasterizer::eFilter::Point:
			switch (ssd.mipLevelFilter) {
			case Rasterizer::eFilter::Point:
				return D3D11_FILTER_MIN_MAG_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			default:
				break;
			}
			break;
		case Rasterizer::eFilter::Linear:
			switch (ssd.mipLevelFilter) {
			case Rasterizer::eFilter::Point:
				return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
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
				return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			case Rasterizer::eFilter::Linear:
				return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			default:
				break;
			}
			break;
		case (buw::eFilter::Linear):
			switch (ssd.mipLevelFilter) {
			case (buw::eFilter::Point):
				return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			case (buw::eFilter::Linear):
				return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			default:
				break;
			}
			break;
		default:
			break;
		};
	case (buw::eFilter::Anisotropic):
		return D3D11_FILTER_ANISOTROPIC;
		break;
	default:
		break;
	}
	BLUE_LOG(warning) << "Non compatible Filter.";
	return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
}

D3D11_COMPARISON_FUNC mapComparisonFunction(buw::eComparisonFunction compFunction)
{
	switch (compFunction) {
	case (buw::eComparisonFunction::Always): return D3D11_COMPARISON_ALWAYS;
	case (buw::eComparisonFunction::Equal): return D3D11_COMPARISON_EQUAL;
	case (buw::eComparisonFunction::Greater): return D3D11_COMPARISON_GREATER;
	case (buw::eComparisonFunction::GreaterEqual): return D3D11_COMPARISON_GREATER_EQUAL;
	case (buw::eComparisonFunction::Less): return D3D11_COMPARISON_LESS;
	case (buw::eComparisonFunction::LessEqual): return D3D11_COMPARISON_LESS_EQUAL;
	case (buw::eComparisonFunction::Never): return D3D11_COMPARISON_NEVER;
	case (buw::eComparisonFunction::NotEqual): return D3D11_COMPARISON_NOT_EQUAL;
	default: return D3D11_COMPARISON_ALWAYS;
	}
}

D3D11_TEXTURE_ADDRESS_MODE mapTextureAddressMode(buw::eTextureAddressMode textureAddressMode)
{
	switch (textureAddressMode) {
	case(buw::eTextureAddressMode::Border): return D3D11_TEXTURE_ADDRESS_BORDER;
	case(buw::eTextureAddressMode::Clamp): return D3D11_TEXTURE_ADDRESS_CLAMP;
	case(buw::eTextureAddressMode::Mirror): return D3D11_TEXTURE_ADDRESS_MIRROR;
	case(buw::eTextureAddressMode::MirrorOnce): return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	case(buw::eTextureAddressMode::Wrap): return D3D11_TEXTURE_ADDRESS_WRAP;
	default: return D3D11_TEXTURE_ADDRESS_WRAP;
	}
}
BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END