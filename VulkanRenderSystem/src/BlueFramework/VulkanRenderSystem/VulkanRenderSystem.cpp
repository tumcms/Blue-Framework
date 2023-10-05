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