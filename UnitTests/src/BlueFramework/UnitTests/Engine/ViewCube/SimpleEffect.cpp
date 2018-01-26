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

#include "SimpleEffect.h"

#include <BlueFramework/Engine/Mesh/geometryGeneration.h>
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/vertex.h>

SimpleEffect::SimpleEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::ITexture2D> dsv)
    : Effect(renderSystem), viewport_(viewport), depthStencil_(dsv) {
}

void SimpleEffect::setDiffuse(buw::ReferenceCounted<buw::ITexture2D> texture) {
	texture_ = texture;
}

void SimpleEffect::setViewProjection(buw::Matrix44f& viewProjection) {
	viewProjection_ = viewProjection;
}

void SimpleEffect::v_init() {
	std::vector<buw::VertexPosition3Normal3Texture2> vertices;
	std::vector<unsigned int> indices;
	buw::createIndexedCube(vertices, indices);

	buw::VertexLayout vertexLayout;
	vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
	vertexLayout.add(buw::eVertexAttributeSemantic::Normal, buw::eVertexAttributeFormat::Float3);
	vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

	buw::vertexBufferDescription vbd;
	vbd.data = &vertices[0];
	vbd.vertexCount = static_cast<int>(vertices.size());
	vbd.vertexLayout = vertexLayout;
	vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);

	buw::indexBufferDescription ibd;
	ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
	ibd.indexCount = static_cast<int>(indices.size());
	ibd.data = &indices[0];
	indexBuffer_ = renderSystem()->createIndexBuffer(ibd);

	buw::samplerStateDescription ssd = {buw::eFilter::Linear};
	sampler_ = renderSystem()->createSampler(ssd);

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(TestBuffer);
	cbd.data = nullptr;
	constantBuffer_ = renderSystem()->createConstantBuffer(cbd);

    meshState_ = createPipelineState(buw::pipelineStateDescription(
		"Shader/Effect.be", 
		"mesh",
		vertexLayout,
		buw::ePrimitiveTopology::TriangleList,
		{ buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
		true, false));
	

	// Line
	buw::VertexLayout vertexLayoutLine;
	vertexLayoutLine.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
	vertexLayoutLine.add(buw::eVertexAttributeSemantic::Color, buw::eVertexAttributeFormat::Float4);

	std::vector<buw::VertexPosition3Color4> lineVertices = {
	  {buw::Vector3f(-1, -1, 0), buw::Vector4f(0.2f, 0.2f, 1.f, 1)}, {buw::Vector3f(0, 2, 0), buw::Vector4f(0.5f, 0.5f, 1.f, 1)},

	  {buw::Vector3f(0, 2, 0), buw::Vector4f(0.5f, 0.5f, 1.f, 1)},   {buw::Vector3f(1, -1, 0), buw::Vector4f(0.2f, 0.2f, 1, 1)},

	  {buw::Vector3f(-0.5f, 0.5f, 0), buw::Vector4f(0, 0.8f, 1, 1)}, {buw::Vector3f(0.5f, 0.5f, 0), buw::Vector4f(0, 0.8f, 1, 1)},

	};

	buw::vertexBufferDescription vbd2;
	vbd2.data = &lineVertices[0];
	vbd2.vertexCount = static_cast<int>(lineVertices.size());
	vbd2.vertexLayout = vertexLayoutLine;

	lineBuffer_ = renderSystem()->createVertexBuffer(vbd2);

	lineState_ = createPipelineState(buw::pipelineStateDescription(
		"Shader/Effect.be", 
		"line",
		vertexLayoutLine,
		buw::ePrimitiveTopology::LineList,
		{ buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
	    true, false));

	vertexCacheTriangle_ = buw::makeReferenceCounted<buw::VertexCacheTriangleT<buw::VertexPosition3>>(renderSystem());

	int width = 20;
	int height = 20;
	gridSize_ = 5;

	zValues_.resize(width);
	for (int x = 0; x < width; x++) {
		zValues_[x].resize(height);
		for (int y = 0; y < height; y++) {
			float z = rand() / (float)(RAND_MAX / 2);
			zValues_[x][y] = z - 10;
		}
	}

	for (int x = 1; x < width; x++) {
		for (int y = 1; y < height; y++) {
			buw::VertexPosition3 v[6];
			int xs[] = {x - 1, x, x, x - 1, x, x - 1};
			int ys[] = {y - 1, y - 1, y, y - 1, y, y};

			for (int i = 0; i < 6; i++) {
				v[i] = buw::VertexPosition3(buw::Vector3f((xs[i] - width / 2.f) * gridSize_, zValues_[xs[i]][ys[i]], -(ys[i] - height / 2.f) * gridSize_));
			}
			vertexCacheTriangle_->drawTriangle(v[0], v[1], v[2]);
			vertexCacheTriangle_->drawTriangle(v[3], v[4], v[5]);
		}
	}

	cacheState_ = createPipelineState(buw::pipelineStateDescription(
		"Shader/Effect.be", 
		"cache",
		vertexCacheTriangle_->vertexLayout(),
	    vertexCacheTriangle_->topology(),
        {buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB},
	    true, false));

	vertexCacheLine_ = buw::makeReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color4>>(renderSystem());

	buw::Vector3f last = buw::Vector3f(30, 0, 0);
	for (int i = 0; i <= 100; i++) {
		buw::Vector3f v = (buw::createRotationMatrixY<float>((float)M_PI * 2.f * i / 100.f) * buw::Vector4f(30, 0, 0, 0)).block<3, 1>(0, 0);
		vertexCacheLine_->drawLine({last, buw::Vector4f(1.f, 0, 0, 1)}, {v, buw::Vector4f(1.f, 0, 0, 1)});
		last = v;
	}

	cacheLineState_ = createPipelineState(buw::pipelineStateDescription(
		"Shader/Effect.be", "line",
		vertexCacheLine_->vertexLayout(),
		vertexCacheLine_->topology(),
		{ buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
	    true, false));
}

void SimpleEffect::v_render() {
	setViewport(viewport_);

	buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
	setRenderTarget(renderTarget, depthStencil_);

	setPipelineState(lineState_);
	setVertexBuffer(lineBuffer_);

	int width = (int)zValues_.size();
	int height = (int)zValues_[0].size();

	for (int x = 1; x < width; x += 3) {
		for (int y = 1; y < height; y += 3) {
			updateConstantBuffer((x - width / 2.f) * gridSize_, zValues_[x][y] + 1, -(y - height / 2.f) * gridSize_);

			setConstantBuffer(constantBuffer_, "TestBuffer");
			draw(static_cast<UINT>(lineBuffer_->getVertexCount()));
		}
	}

	setPipelineState(meshState_);
	setVertexBuffer(vertexBuffer_);
	setIndexBuffer(indexBuffer_);

	setSampler(sampler_, "samplerLinear");
	setTexture(texture_, "diffuse");

	srand(117);

	for (int x = 0; x < width; x += 3) {
		for (int y = 0; y < height; y += 3) {
			updateConstantBuffer((x - width / 2.f) * gridSize_, zValues_[x][y] + 1, -(y - height / 2.f) * gridSize_);

			setConstantBuffer(constantBuffer_, "TestBuffer");
			drawIndexed(static_cast<UINT>(indexBuffer_->getIndexCount()));
		}
	}

	setPipelineState(cacheState_);

	updateConstantBuffer(0, 0, 0);
	setConstantBuffer(constantBuffer_, "TestBuffer");

	vertexCacheTriangle_->flush();
	setVertexBuffer(vertexCacheTriangle_->vertexBuffer());
	draw(vertexCacheTriangle_->getSize());

	setPipelineState(cacheLineState_);

	updateConstantBuffer(0, 0, 0);
	setConstantBuffer(constantBuffer_, "TestBuffer");

	vertexCacheLine_->flush();
	setVertexBuffer(vertexCacheLine_->vertexBuffer());
	draw(vertexCacheLine_->getSize());
}

void SimpleEffect::updateConstantBuffer(float x, float y, float z) {
	buw::Matrix44f translation = buw::createTranslationMatrix(x, y, z);

	TestBuffer buffer;
	buffer.world = translation;
	buffer.worldViewProjection = viewProjection_ * translation;

	buw::constantBufferDescription cbd;
	cbd.sizeInBytes = sizeof(TestBuffer);
	cbd.data = &buffer;
	constantBuffer_->uploadData(cbd);
}
