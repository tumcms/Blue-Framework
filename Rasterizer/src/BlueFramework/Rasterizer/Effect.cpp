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