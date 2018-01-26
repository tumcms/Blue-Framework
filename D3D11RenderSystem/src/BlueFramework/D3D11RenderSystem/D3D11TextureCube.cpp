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

#include "BlueFramework/D3D11RenderSystem/D3D11TextureCube.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN


D3D11TextureCube::D3D11TextureCube(D3D11RenderSystem* renderSystem, const buw::textureCubeDescription& td, buw::eTextureBindType bindType)
	: ITextureCube(), renderSystem_(renderSystem), bindType_(bindType) {
	format_ = td.format;
	width_ = td.width;
	height_ = td.height;

	D3D11_BIND_FLAG bindFlag = (D3D11_BIND_FLAG)0;

	if (hasShaderResourceView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_SHADER_RESOURCE);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width_;
	desc.Height = height_;
	desc.MipLevels = 1;
	desc.ArraySize = 6;
	desc.Format = mapTextureFormat(format_);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlag;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	D3D11_SUBRESOURCE_DATA sub[6];
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (td.data)
	{
		for (int i = 0; i < 6; i++)
		{
			sub[i].pSysMem = td.data[i];
			sub[i].SysMemPitch = 4 * width_;
			sub[i].SysMemSlicePitch = 4 * width_ * height_;
		}
		subp = sub;
	}

	renderSystem_->getDevice()->CreateTexture2D(&desc, subp, texture_.GetAddressOf());

	if (hasShaderResourceView())
		createShaderResourceView();
}

bool D3D11TextureCube::hasShaderResourceView() const {
	return bindType_ == buw::eTextureBindType::SRV || bindType_ == buw::eTextureBindType::SRV_RTV || bindType_ == buw::eTextureBindType::SRV_DSV;
}
bool D3D11TextureCube::isCPUReadable() const {
	return false;
}

void D3D11TextureCube::makeCPUReadable()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void D3D11TextureCube::resize(const buw::textureCubeDescription& td)
{
	D3D11RenderSystem* rs = renderSystem_;
	buw::eTextureBindType bt = bindType_;

	this->~D3D11TextureCube();
	new (this) D3D11TextureCube(rs, td, bt);
}

D3D11TextureCube::ComPtr<ID3D11Resource> D3D11TextureCube::getTexture() const {
	return texture_;
}
D3D11TextureCube::ComPtr<ID3D11ShaderResourceView> D3D11TextureCube::getShaderResourceView() const {
	return shaderResourceView_;
}

void D3D11TextureCube::createShaderResourceView() {	
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = mapShaderResourceFormat(format_);
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	desc.TextureCube.MipLevels = 1;
	desc.TextureCube.MostDetailedMip = 0;

	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &desc, shaderResourceView_.GetAddressOf());
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END
