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

#include "BlueFramework/Rasterizer/Effect.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

Effect::Effect(IRenderSystem* renderSytem) {
	core_ = renderSytem->createEffectCore();
}

Effect::~Effect() {

}

void Effect::v_init() {
	
}

void Effect::drawIndexed(UINT indices) const {
	core_->drawIndexed(indices);
}

void Effect::draw(UINT vertices) const {
	core_->draw(vertices);
}

void Effect::setRenderTargets(std::vector<buw::ReferenceCounted<ITexture2D>> renderTargets, buw::ReferenceCounted<ITexture2D> depthStencil) const {
	core_->setRenderTargets(renderTargets, depthStencil);
}

void Effect::setRenderTarget(buw::ReferenceCounted<ITexture2D> renderTarget, buw::ReferenceCounted<ITexture2D> depthStencil) const {
	core_->setRenderTarget(renderTarget, depthStencil);
}

void Effect::setViewport(buw::ReferenceCounted<IViewport> viewport) const {
	core_->setViewport(viewport);
}

void Effect::setSampler(buw::ReferenceCounted<ISampler> sampler, const std::string& name) const {
	core_->setSampler(sampler, name);
}

void Effect::setTexture(buw::ReferenceCounted<ITextureCube> texture, const std::string& name) const {
	core_->setTexture(texture, name);
}

void Effect::setTexture(buw::ReferenceCounted<ITexture2D> texture, const std::string& name) const {
	core_->setTexture(texture, name);
}

void Effect::setTexture(buw::ReferenceCounted<ITexture1D> texture, const std::string& name) const {
	core_->setTexture(texture, name);
}

void Effect::setConstantBuffer(buw::ReferenceCounted<IConstantBuffer> constantBuffer, const std::string& name) const {
	core_->setConstantBuffer(constantBuffer, name);
}

void Effect::setIndexBuffer(buw::ReferenceCounted<IIndexBuffer> indexBuffer) const {
	core_->setIndexBuffer(indexBuffer);
}

void Effect::setVertexBuffer(buw::ReferenceCounted<IVertexBuffer> vertexBuffer) const {
	core_->setVertexBuffer(vertexBuffer);
}

void Effect::setPipelineState(buw::ReferenceCounted<IPipelineState> pipelineState) {
	core_->setPipelineState(pipelineState);
}

buw::ReferenceCounted<buw::IPipelineState> Effect::createPipelineState(const buw::pipelineStateDescription &psd) {
	return core_->createPipelineState(psd);
}

BlueFramework::Rasterizer::IRenderSystem* Effect::renderSystem() const {
	return core_->renderSystem();
}

void Effect::postRender() {
	core_->postRender();
}

void Effect::preRender() {
	core_->preRender();
}

void Effect::render() {
	core_->preRender();
	v_render();
	core_->postRender();
}

void Effect::init() {
	core_->preInit();
	v_init();
	core_->postInit();
}

void Effect::v_render() {

}

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END