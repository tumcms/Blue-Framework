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
