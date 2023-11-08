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

#pragma once

#include "BlueFramework/Rasterizer/Resources/IConstantBuffer.h"
#include "BlueFramework/Rasterizer/Resources/IViewport.h"
#include "BlueFramework/Rasterizer/Resources/IIndexBuffer.h"
#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"
#include "BlueFramework/Rasterizer/Resources/ISampler.h"
#include "BlueFramework/Rasterizer/Effect.h"
#include "BlueFramework/Core/Math/Matrix.h"
#include "BlueFramework/Engine/VertexCache/VertexCache.h"
#include "BlueFramework/Rasterizer/vertex.h"

class SimpleEffect : public buw::Effect {
	struct TestBuffer {
		buw::Matrix44f worldViewProjection;
		buw::Matrix44f world;
	};

public:
	SimpleEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::ITexture2D> dsv);

	void setDiffuse(buw::ReferenceCounted<buw::ITexture2D> texture);

	void setViewProjection(buw::Matrix44f& viewProjection);

private:
	void v_init() override;
	void v_render() override;

	void updateConstantBuffer(float x, float y, float z);

private:
	buw::ReferenceCounted<buw::IPipelineState> meshState_, lineState_, cacheState_, cacheLineState_;

	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_, lineBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;
	buw::ReferenceCounted<buw::ITexture2D> texture_, depthStencil_;
	buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::IConstantBuffer> constantBuffer_;

	buw::ReferenceCounted<buw::VertexCacheTriangleT<buw::VertexPosition3>> vertexCacheTriangle_;
	buw::ReferenceCounted<buw::VertexCacheLineT<buw::VertexPosition3Color4>> vertexCacheLine_;

	buw::Matrix44f viewProjection_;

	float gridSize_;
	std::vector<std::vector<float>> zValues_;
};
