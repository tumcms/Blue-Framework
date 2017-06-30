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

#include "BlueFramework/D3D11RenderSystem/D3D11Texture2D.h"
#include "BlueFramework/D3D11RenderSystem/D3D11RenderSystem.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

buw::ReferenceCounted<D3D11Texture2D> D3D11Texture2D::fromBackBuffer(D3D11RenderSystem* renderSystem, ComPtr<ID3D11Texture2D> backBuffer, UINT width, UINT height)
{
	buw::ReferenceCounted<D3D11Texture2D> tex = buw::makeReferenceCounted<D3D11Texture2D>();
	tex->format_ = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
	tex->width_ = width;
	tex->height_ = height;
	tex->renderSystem_ = renderSystem;
	tex->texture_ = backBuffer;
	tex->bindType_ = buw::eTextureBindType::RTV;
	tex->createRenderTargetView();
	return tex;
}


D3D11Texture2D::D3D11Texture2D(D3D11RenderSystem* renderSystem, const buw::texture2DDescription& td, buw::eTextureBindType bindType)
	: ITexture2D(), renderSystem_(renderSystem), bindType_(bindType) {
	format_ = td.format;
	width_ = td.width;
	height_ = td.height;
	msaa_ = td.useMSAA;

	createTexture(td.data);

	if(td.isCpuReadable || td.isCpuWriteable)
		createStagingTexture(td.isCpuReadable, td.isCpuWriteable);

	if (hasShaderResourceView())
		createShaderResourceView();
	if (hasRenderTargetView())
		createRenderTargetView();
	if (hasDepthStencilView())
		createDepthStencilView();
}


D3D11Texture2D::D3D11Texture2D()
	: ITexture2D(), format_(buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB), width_(0), height_(0), renderSystem_(nullptr), bindType_(buw::eTextureBindType::None) {
}

bool D3D11Texture2D::hasShaderResourceView() const {
	return bindType_ == buw::eTextureBindType::SRV || bindType_ == buw::eTextureBindType::SRV_RTV || bindType_ == buw::eTextureBindType::SRV_DSV;
}
bool D3D11Texture2D::hasRenderTargetView() const {
	return bindType_ == buw::eTextureBindType::RTV || bindType_ == buw::eTextureBindType::SRV_RTV;
}
bool D3D11Texture2D::hasDepthStencilView() const {
	return bindType_ == buw::eTextureBindType::DSV || bindType_ == buw::eTextureBindType::SRV_DSV;
}
bool D3D11Texture2D::isCPUReadable() const {
	return isCPUReadable_ && stagingTexture_ != nullptr;
}
bool D3D11Texture2D::isCPUWriteable() const {
	return isCPUWriteable_ && stagingTexture_ != nullptr;
}

void D3D11Texture2D::makeCPUReadable()
{
	createStagingTexture(true, isCPUWriteable_);
}

void D3D11Texture2D::makeCPUWriteable()
{
	createStagingTexture(isCPUReadable_, true);
}

void D3D11Texture2D::resize(const buw::texture2DDescription& td)
{
	D3D11RenderSystem* rs = renderSystem_;
	buw::eTextureBindType bt = bindType_;

	this->~D3D11Texture2D();
	new (this) D3D11Texture2D(rs, td, bt);
}

D3D11Texture2D::ComPtr<ID3D11Texture2D> D3D11Texture2D::getTexture() const {
	return texture_;
}
D3D11Texture2D::ComPtr<ID3D11Texture2D> D3D11Texture2D::getStagingTexture() const {
	return stagingTexture_;
}
D3D11Texture2D::ComPtr<ID3D11ShaderResourceView> D3D11Texture2D::getShaderResourceView() const {
	return shaderResourceView_;
}
D3D11Texture2D::ComPtr<ID3D11RenderTargetView> D3D11Texture2D::getRenderTargetView() const {
	return renderTargetView_;
}
D3D11Texture2D::ComPtr<ID3D11DepthStencilView> D3D11Texture2D::getDepthStencilView() const {
	return depthStencilView_;
}

void D3D11Texture2D::createTexture(const void* data)
{
	D3D11_BIND_FLAG bindFlag = (D3D11_BIND_FLAG)0;

	if (hasShaderResourceView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_SHADER_RESOURCE);
	if (hasRenderTargetView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_RENDER_TARGET);
	if (hasDepthStencilView())
		bindFlag = (D3D11_BIND_FLAG)(bindFlag | D3D11_BIND_DEPTH_STENCIL);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width_;
	desc.Height = height_;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = mapTextureFormat(format_);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bindFlag;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	if (renderSystem_->getMSAAEnabled() && msaa_)
	{
		desc.SampleDesc.Count = renderSystem_->getSampleCount();
		desc.SampleDesc.Quality = renderSystem_->getSampleQuality();
	}

	D3D11_SUBRESOURCE_DATA sub;
	D3D11_SUBRESOURCE_DATA* subp = nullptr;
	if (data)
	{
		sub.pSysMem = data;
		sub.SysMemPitch = 4 * width_;
		sub.SysMemSlicePitch = 4 * width_ * height_;
		subp = &sub;
	}

	renderSystem_->getDevice()->CreateTexture2D(&desc, subp, texture_.GetAddressOf());
}

void D3D11Texture2D::createStagingTexture(bool cpuReadable, bool cpuWriteable)
{
	isCPUReadable_ = cpuReadable;
	isCPUWriteable_ = cpuWriteable;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width_;
	desc.Height = height_;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = mapTextureFormat(format_);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = (isCPUReadable_ ? D3D11_CPU_ACCESS_READ : 0) | (isCPUWriteable_ ? D3D11_CPU_ACCESS_WRITE : 0);
	desc.MiscFlags = 0;

	renderSystem_->getDevice()->CreateTexture2D(&desc, nullptr, stagingTexture_.GetAddressOf());
}

void D3D11Texture2D::createShaderResourceView() {	
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = mapShaderResourceFormat(format_);
	if (!msaa_)
	{
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = 1;
		desc.Texture2D.MostDetailedMip = 0;
	}
	else
		desc.ViewDimension =  D3D11_SRV_DIMENSION_TEXTURE2DMS;

	renderSystem_->getDevice()->CreateShaderResourceView(texture_.Get(), &desc, shaderResourceView_.GetAddressOf());
}
void D3D11Texture2D::createRenderTargetView() {
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	desc.Format = mapRenderTargetFormat(format_);
	if (!msaa_)
	{
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;
	}
	else
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

	renderSystem_->getDevice()->CreateRenderTargetView(texture_.Get(), &desc, renderTargetView_.GetAddressOf());
}
void D3D11Texture2D::createDepthStencilView() {	
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	desc.Format = mapDepthStencilFormat(format_);
	if (!msaa_)
	{
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;
		
	}
	else
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	desc.Flags = 0;
	renderSystem_->getDevice()->CreateDepthStencilView(texture_.Get(), &desc, depthStencilView_.GetAddressOf());
}

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END
