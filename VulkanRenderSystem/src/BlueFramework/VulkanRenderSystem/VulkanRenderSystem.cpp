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

#include "VulkanRenderSystem.h"

#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"

BLUE_NAMESPACE_BLUEFRAMEWORK_VULKANRENDERSYSTEM_BEGIN

buw::ReferenceCounted<BlueFramework::Rasterizer::IEffectCore> VulkanRenderSystem::createEffectCore() {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IVertexBuffer> VulkanRenderSystem::createVertexBuffer(const buw::vertexBufferDescription& vbd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IIndexBuffer> VulkanRenderSystem::createIndexBuffer(const buw::indexBufferDescription& ibd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IConstantBuffer> VulkanRenderSystem::createConstantBuffer(const buw::constantBufferDescription& cbd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture1D> VulkanRenderSystem::createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> VulkanRenderSystem::createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITextureCube> VulkanRenderSystem::createTextureCube(const BlueFramework::Rasterizer::textureCubeDescription & td, BlueFramework::Rasterizer::eTextureBindType bindType)
{
    throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ISampler> VulkanRenderSystem::createSampler(const buw::samplerStateDescription& ssd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IBlender> VulkanRenderSystem::createBlender(const buw::blendStateDescription& bsd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::IViewport> VulkanRenderSystem::createViewport(const buw::viewportDescription& vpd) {
	throw std::logic_error("The method or operation is not implemented.");
}

buw::ReferenceCounted<BlueFramework::Rasterizer::ITexture2D> VulkanRenderSystem::getBackBufferTarget() {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::clearRenderTarget(std::shared_ptr<buw::ITexture2D> renderTarget, const float color[4] /*= nullptr*/) {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, const float color[4] /*= nullptr*/) {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::clearDepthStencilView(std::shared_ptr<buw::ITexture2D> depthStencil) {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::copyTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &dest, const int x /*= 0*/, const int y /*= 0*/) {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::present() {
	throw std::logic_error("The method or operation is not implemented.");
}

void VulkanRenderSystem::resize(int width, int height) {
	throw std::logic_error("The method or operation is not implemented.");
}

const char* VulkanRenderSystem::getName() const {
	throw std::logic_error("The method or operation is not implemented.");
}

const bool VulkanRenderSystem::getMSAAEnabled() const {
	throw std::logic_error("The method or operation is not implemented.");
}

BLUE_NAMESPACE_BLUEFRAMEWORK_VULKANRENDERSYSTEM_END

extern "C" buw::IRenderSystem* createRenderSystem(const buw::renderSystemDescription& scd) {
	BLUE_LOG(trace) << "Enter createRenderSystem...";

	return new BlueFramework::VulkanRenderSystem::VulkanRenderSystem(scd);
}