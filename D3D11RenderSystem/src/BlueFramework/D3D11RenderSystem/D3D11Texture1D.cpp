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

#include "BlueFramework/D3D11RenderSystem/D3D11Texture1D.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

D3D11Texture1D::D3D11Texture1D(D3D11RenderSystem* renderSystem, const buw::texture1DDescription& td, buw::eTextureBindType bindType)
	: ITexture1D(), renderSystem_(renderSystem), bindType_(bindType) {
	format_ = td.format;
	width_ = td.width;

	D3D11_BIND_FLAG bindFlag = (D3D11_BIND_FLAG)0;

	if (hasShaderResourceView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_SHADER_RESOURCE);
	if (hasRenderTargetView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_RENDER_TARGET);
	if (hasDepthStencilView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_DEPTH_STENCIL);

	D3D11_TEXTURE1D_DESC desc;
	desc.Width = width_;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = mapTextureFormat(format_);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlag;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sub;
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (td.data)
	{
		sub.pSysMem = td.data;
		sub.SysMemPitch = 4 * width_;
		sub.SysMemSlicePitch = 4 * width_;
		subp = &sub;
	}

	renderSystem_->getDevice()->CreateTexture1D(&desc, subp, texture_.GetAddressOf());

	if (hasShaderResourceView())
		createShaderResourceView();
	if (hasRenderTargetView())
		createRenderTargetView();
	if (hasDepthStencilView())
		createDepthStencilView();
}

bool D3D11Texture1D::hasShaderResourceView() const {
	return bindType_ == buw::eTextureBindType::SRV || bindType_ == buw::eTextureBindType::SRV_RTV || bindType_ == buw::eTextureBindType::SRV_DSV;
}
bool D3D11Texture1D::hasRenderTargetView() const {
	return bindType_ == buw::eTextureBindType::RTV || bindType_ == buw::eTextureBindType::SRV_RTV;
}
bool D3D11Texture1D::hasDepthStencilView() const {
	return bindType_ == buw::eTextureBindType::DSV || bindType_ == buw::eTextureBindType::SRV_DSV;
}
bool D3D11Texture1D::isCPUReadable() const {
	return false;
}

void D3D11Texture1D::makeCPUReadable()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void D3D11Texture1D::resize(const buw::texture1DDescription& td)
{
	D3D11RenderSystem* rs = renderSystem_;
	buw::eTextureBindType bt = bindType_;

	this->~D3D11Texture1D();
	new (this) D3D11Texture1D(rs, td, bt);
}

D3D11Texture1D::ComPtr<ID3D11Resource> D3D11Texture1D::getTexture() const {
	return texture_;
}
D3D11Texture1D::ComPtr<ID3D11ShaderResourceView> D3D11Texture1D::getShaderResourceView() const {
	return shaderResourceView_;
}
D3D11Texture1D::ComPtr<ID3D11RenderTargetView> D3D11Texture1D::getRenderTargetView() const {
	return renderTargetView_;
}
D3D11Texture1D::ComPtr<ID3D11DepthStencilView> D3D11Texture1D::getDepthStencilView() const {
	return depthStencilView_;
}

void D3D11Texture1D::createShaderResourceView() {	
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = mapShaderResourceFormat(format_);
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	desc.Texture1D.MipLevels = 1;
	desc.Texture1D.MostDetailedMip = 0;

	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &desc, shaderResourceView_.GetAddressOf());
}
void D3D11Texture1D::createRenderTargetView() {
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = mapRenderTargetFormat(format_);
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
	desc.Texture1D.MipSlice = 0;

	renderSystem_->getDevice()->CreateRenderTargetView(texture_.Get(), &desc, renderTargetView_.GetAddressOf());
}
void D3D11Texture1D::createDepthStencilView() {	
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	desc.Format = mapDepthStencilFormat(format_);
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;
	desc.Texture1D.MipSlice = 0;

	renderSystem_->getDevice()->CreateDepthStencilView(texture_.Get(), &desc, depthStencilView_.GetAddressOf());
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END
