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

#include "ViewCubeEffect.h"

#include "BlueFramework/Rasterizer/util.h"
#include "BlueFramework/Core/memory.h"
#include <boost/filesystem.hpp>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

ViewCubeEffect::ViewCubeEffect(buw::IRenderSystem* renderSystem,

                                                      buw::ReferenceCounted<buw::ITexture2D> pickBuffer)
    : buw::Effect(renderSystem), pickBufferImage_(1, 1), pickBuffer_(pickBuffer) {
}

ViewCubeEffect::~ViewCubeEffect() {
	cubeState_ = nullptr;
	pickState_ = nullptr;
	compassState_ = nullptr;
	arrowsState_ = nullptr;

	vertexBufferCube_ = nullptr;
	vertexBufferCompass_ = nullptr;
	vertexBufferArrows_ = nullptr;

	indexBufferCube_ = nullptr;
	indexBufferCompass_ = nullptr;
	indexBufferArrows_ = nullptr;

	cameraBuffer_ = nullptr;
	descriptionBuffer_ = nullptr;
	pickIdBuffer_ = nullptr;

	sampler_ = nullptr;
	blender_ = nullptr;

	depthStencilMSAA_ = nullptr;
	depthStencil_ = nullptr;
	pickBuffer_ = nullptr;

	viewport_ = nullptr;

	topTexture_ = nullptr;
	bottomTexture_ = nullptr;
	leftTexture_ = nullptr;
	rightTexture_ = nullptr;
	frontTexture_ = nullptr;
	backTexture_ = nullptr;
}

void ViewCubeEffect::createCubeBuffers(std::vector<CubeVertexType>& vertices, std::vector<IndexType>& indices) {
	buw::vertexBufferDescription vbd;
	vbd.data = &vertices[0];
	vbd.vertexCount = static_cast<int>(vertices.size());
	vbd.vertexLayout = CubeVertexType::getVertexLayout();

    if(vertexBufferCube_) vertexBufferCube_.reset();
	vertexBufferCube_ = renderSystem()->createVertexBuffer(vbd);

	buw::indexBufferDescription ibd;
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.indexCount = static_cast<int>(indices.size());
	ibd.data = &indices[0];

    if(indexBufferCube_) indexBufferCube_.reset();
	indexBufferCube_ = renderSystem()->createIndexBuffer(ibd);
}

void ViewCubeEffect::updateDescriptionBuffer(DescriptionBuffer& buffer) {
	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(DescriptionBuffer);
	cbd.data = &buffer;
	descriptionBuffer_->uploadData(cbd);
}

void ViewCubeEffect::updatePickId(unsigned int pickId) {
	lastPickId_ = pickId;
	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(unsigned int);
	cbd.data = &pickId;
	pickIdBuffer_->uploadData(cbd);
}

void ViewCubeEffect::setDepthStencil(buw::ReferenceCounted<buw::ITexture2D> dsv) {
	depthStencilMSAA_ = dsv;
}

void ViewCubeEffect::mouseMove(const int x, const int y) {
	renderSystem()->downloadTexture(pickBuffer_, pickBufferImage_, x, y);
	unsigned int* id = (unsigned int*)&pickBufferImage_.getPixelColor(0, 0)[0];
	if (*id != lastPickId_) {
		updatePickId(*id);
	}
}

void ViewCubeEffect::v_init() {
	buw::samplerStateDescription ssd = {buw::eFilter::Anisotropic};
	sampler_ = renderSystem()->createSampler(ssd);

	int width = renderSystem()->getBackBufferTarget()->width();
	int height = renderSystem()->getBackBufferTarget()->height();

	buw::viewportDescription vpd(std::min(width, 130), std::min(height, 130), std::max(width - 130, 0));
	viewport_ = renderSystem()->createViewport(vpd);

	std::string filename = "Shader/ViewCubeEffect.be";

	BLUE_ASSERT(boost::filesystem::exists(filename), "ViewCube shader does not exist.");

	if (!boost::filesystem::exists(filename)) {
		throw buw::Exception("ViewCube shader (%s) does not exist.", filename);
	}

	buw::renderTargetBlendDescription rtbd;
	rtbd.blendEnable = true;
	rtbd.blendOp = buw::eBlendOperation::Add;
	rtbd.srcBlend = buw::eBlendValue::SrcAlpha;
	rtbd.destBlend = buw::eBlendValue::InvSrcAlpha;
	rtbd.destBlendAlpha = buw::eBlendValue::Zero;
	rtbd.srcBlendAlpha = buw::eBlendValue::Zero;
	rtbd.blendOpAlpha = buw::eBlendOperation::Add;

	buw::blendStateDescription bsd;
	bsd.alphaToCoverageEnable = true;
	bsd.independentBlendEnable = false;
	bsd.renderTarget[0] = rtbd;

	buw::pipelineStateDescription cubePSD;
	cubePSD.effectFilename = filename;
	cubePSD.pipelineStateName = "cube";
	cubePSD.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
	cubePSD.vertexLayout = CubeVertexType::getVertexLayout();
	cubePSD.renderTargetFormats = {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB};
	cubePSD.useDepth = true;
	cubePSD.useMSAA = renderSystem()->getMSAAEnabled();
	//cubePSD.blendStateDesc = bsd;
	cubeState_ = createPipelineState(cubePSD);

	buw::pipelineStateDescription pickPSD;
	pickPSD.effectFilename = filename;
	pickPSD.pipelineStateName = "pick";
	pickPSD.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
	pickPSD.vertexLayout = CubeVertexType::getVertexLayout();
	pickPSD.renderTargetFormats = {buw::eTextureFormat::R32_UnsignedInt};
	pickPSD.useDepth = true;
	pickPSD.useMSAA = false;
	pickState_ = createPipelineState(pickPSD);

	buw::texture2DDescription dsvTD;
	dsvTD.width = width;
	dsvTD.height = height;
	dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	dsvTD.data = nullptr;
	dsvTD.isCpuReadable = false;
	dsvTD.useMSAA = renderSystem()->getMSAAEnabled();
	depthStencilMSAA_ = renderSystem()->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

	dsvTD.useMSAA = false;
	depthStencil_ = renderSystem()->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

	buw::constantBufferDescription cbd1;
	cbd1.sizeInBytes = sizeof(DescriptionBuffer);
	cbd1.data = nullptr;
	descriptionBuffer_ = renderSystem()->createConstantBuffer(cbd1);

	buw::constantBufferDescription cbd2;
	cbd2.sizeInBytes = sizeof(CameraBuffer);
	cbd2.data = nullptr;
	cameraBuffer_ = renderSystem()->createConstantBuffer(cbd2);

	lastPickId_ = 0;

	buw::constantBufferDescription cbd3;
	cbd3.sizeInBytes = sizeof(unsigned int);
	cbd3.data = &lastPickId_;
	pickIdBuffer_ = renderSystem()->createConstantBuffer(cbd3);
}

void ViewCubeEffect::resize(buw::viewportDescription vpd) {
	viewport_->resize(buw::viewportDescription(std::min((int)vpd.width, 130), std::min((int)vpd.height, 130), std::max((int)vpd.width - 130, 0)));

	buw::texture2DDescription dsvTD;
	dsvTD.width = vpd.width;
	dsvTD.height = vpd.height;
	dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
	dsvTD.data = nullptr;
	dsvTD.isCpuReadable = false;
	dsvTD.useMSAA = renderSystem()->getMSAAEnabled();
	depthStencilMSAA_->resize(dsvTD);

	dsvTD.useMSAA = false;
	depthStencil_->resize(dsvTD);
}

void ViewCubeEffect::updateRotationMatrix(const buw::Matrix44f& rotation) {
	cameraMatrices_.rotation = rotation;
}

void ViewCubeEffect::updateProjectionMatrix(const buw::Matrix44f& projection) {
	cameraMatrices_.projection = projection;
}

void ViewCubeEffect::v_render() {
	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
	renderSystem()->clearDepthStencilView(depthStencilMSAA_);
	renderSystem()->clearDepthStencilView(depthStencil_);

	updateCameraBuffer();

	if (renderCube_) {
		// render cube
		setPipelineState(cubeState_);
		setViewport(viewport_);
		setRenderTarget(renderTarget, depthStencilMSAA_);
		setSampler(sampler_, "samplerLinear");
		setVertexBuffer(vertexBufferCube_);
		setIndexBuffer(indexBufferCube_);
		setConstantBuffer(cameraBuffer_, "CameraTransformations");
		setConstantBuffer(descriptionBuffer_, "RenderingDescription");
		setConstantBuffer(pickIdBuffer_, "PickId");

		setTexture(frontTexture_, "front");
		setTexture(backTexture_, "back");
		setTexture(leftTexture_, "left");
		setTexture(rightTexture_, "right");
		setTexture(topTexture_, "top");
		setTexture(bottomTexture_, "bottom");

		drawIndexed(static_cast<UINT>(indexBufferCube_->getIndexCount()));

		// render cube pick buffer
		setPipelineState(pickState_);
		setViewport(viewport_);
		setRenderTarget(pickBuffer_, depthStencil_);
		setVertexBuffer(vertexBufferCube_);
		setIndexBuffer(indexBufferCube_);
		setConstantBuffer(cameraBuffer_, "CameraTransformations");

		drawIndexed(static_cast<UINT>(indexBufferCube_->getIndexCount()));
	}

	if (renderCompass_) {
		// TODO: draw compass
	}

	if (renderArrows_) {
		// TODO: draw arrows
	}
}

void ViewCubeEffect::updateCameraBuffer() {
	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(CameraBuffer);
	cbd.data = &cameraMatrices_;
	cameraBuffer_->uploadData(cbd);
}

bool ViewCubeEffect::getRenderCube() const {
	return renderCube_;
}

void ViewCubeEffect::setRenderCube(const bool render_cube) {
	renderCube_ = render_cube;
}

bool ViewCubeEffect::getRenderCompass() const {
	return renderCompass_;
}

void ViewCubeEffect::setRenderCompass(const bool render_compass) {
	renderCompass_ = render_compass;
}

bool ViewCubeEffect::getRenderArrows() const {
	return renderArrows_;
}

void ViewCubeEffect::setRenderArrows(const bool render_arrows) {
	renderArrows_ = render_arrows;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getFrontTexture() {
	return frontTexture_;
}

void ViewCubeEffect::setFrontTexture(buw::ReferenceCounted<buw::ITexture2D> front_texture) {
    if(frontTexture_) frontTexture_.reset();
    frontTexture_ = front_texture;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getTopTexture() {
	return topTexture_;
}

void ViewCubeEffect::setTopTexture(buw::ReferenceCounted<buw::ITexture2D> top_texture) {
    if(topTexture_) topTexture_.reset();
    topTexture_ = top_texture;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getBackTexture() {
	return backTexture_;
}

void ViewCubeEffect::setBackTexture(buw::ReferenceCounted<buw::ITexture2D> back_texture) {
    if(backTexture_) backTexture_.reset();
	backTexture_ = back_texture;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getBottomTexture() {
	return bottomTexture_;
}

void ViewCubeEffect::setBottomTexture(buw::ReferenceCounted<buw::ITexture2D> bottom_texture) {
    if(bottomTexture_) bottomTexture_.reset();
	bottomTexture_ = bottom_texture;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getRightTexture() {
	return rightTexture_;
}

void ViewCubeEffect::setRightTexture(buw::ReferenceCounted<buw::ITexture2D> right_texture) {
    if(rightTexture_) rightTexture_.reset();
    rightTexture_ = right_texture;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getLeftTexture() {
	return leftTexture_;
}

void ViewCubeEffect::setLeftTexture(buw::ReferenceCounted<buw::ITexture2D> left_texture) {
    if(leftTexture_) leftTexture_.reset();
    leftTexture_ = left_texture;
}

unsigned int ViewCubeEffect::getLastPickId() {
	return lastPickId_;
}

buw::ReferenceCounted<buw::ITexture2D>& ViewCubeEffect::getPickBuffer() {
	return pickBuffer_;
}

void ViewCubeEffect::setPickBuffer(buw::ReferenceCounted<buw::ITexture2D> pickBuffer) {
	pickBuffer_ = pickBuffer;
}

void ViewCubeEffect::setPickIdBuffer(buw::ReferenceCounted<buw::IConstantBuffer> &pickIdBuffer)
{
    pickIdBuffer_ = pickIdBuffer;
}

BLUEFRAMEWORK_ENGINE_NAMESPACE_END