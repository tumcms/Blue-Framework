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

#include "BoxEffect.h"

BoxEffect::BoxEffect(buw::IRenderSystem * renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer, buw::ReferenceCounted<buw::IConstantBuffer> viewportBuffer)
	: buw::Effect(renderSystem), viewport_(viewport), worldBuffer_(worldBuffer), depthStencilMSAA_(depthStencilMSAA), viewportBuffer_(viewportBuffer)
{
}

BoxEffect::~BoxEffect()
{
	worldBuffer_ = nullptr;
	viewportBuffer_ = nullptr;
	vertexBuffer_ = nullptr;
	indexBuffer_ = nullptr;
	depthStencilMSAA_ = nullptr;
	pipelineState_ = nullptr;
	viewport_ = nullptr;
}

void BoxEffect::loadShader()
{
	try {		
		/*Create the pipeline state.*/
		buw::pipelineStateDescription psd;
		psd.effectFilename = "Shader/BoxEffect.be";
		psd.pipelineStateName = "main";
		psd.vertexLayout = buw::VertexPosition3Color3Size1::getVertexLayout();
		psd.primitiveTopology = buw::ePrimitiveTopology::LineList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = true;
		psd.useMSAA = true;
		psd.fillMode = buw::eFillMode::Solid;
		psd.cullMode = buw::eCullMode::None;
		pipelineState_ = createPipelineState(psd);
	}
	catch(...) {
		pipelineState_ = nullptr;
	}
}


void BoxEffect::show(const bool checked)
{
	bShow_ = checked;
}

void BoxEffect::assignVertexBuffer(buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer)
{
	vertexBuffer_ = vertexBuffer;
}

void BoxEffect::assignIndexBuffer(buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer)
{
	indexBuffer_ = indexBuffer;
}


void BoxEffect::v_init()
{
	loadShader();	
}

void BoxEffect::v_render()
{
	if(bShow_) {
		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();

		setPipelineState(pipelineState_);
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setViewport(viewport_);
		setConstantBuffer(worldBuffer_, "WorldBuffer");
		setConstantBuffer(viewportBuffer_, "ViewportBuffer");
		setVertexBuffer(vertexBuffer_);
		setIndexBuffer(indexBuffer_);
		drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
	}
}