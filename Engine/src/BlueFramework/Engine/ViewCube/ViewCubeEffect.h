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

#pragma once
#ifndef BlueFramework_Engine_ViewCubeEffect_8fbf70e0_a8c3_4a4c_b26f_bf186fad77b3_h
#define BlueFramework_Engine_ViewCubeEffect_8fbf70e0_a8c3_4a4c_b26f_bf186fad77b3_h

#include "BlueFramework/Engine/namespace.h"
#include "BlueFramework/Rasterizer/Effect.h"
#include "BlueFramework/Rasterizer/IRenderSystem.h"
#include "BlueFramework/Rasterizer/Resources/IBlender.h"
#include "BlueFramework/Rasterizer/Resources/IConstantBuffer.h"
#include "BlueFramework/Rasterizer/Resources/IIndexBuffer.h"
#include "BlueFramework/Rasterizer/Resources/ISampler.h"
#include "BlueFramework/Rasterizer/Resources/ITexture2D.h"
#include "BlueFramework/Rasterizer/Resources/IVertexBuffer.h"
#include "BlueFramework/Rasterizer/Resources/IViewport.h"
#include "BlueFramework/Rasterizer/vertex.h"

#include "BlueFramework/Core/Math/Matrix.h"

#include "BlueFramework/ImageProcessing/Image.h"

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

class ViewCubeEffect : public buw::Effect {
public:
	struct DescriptionBuffer {
		// Alignment is required for Shader registers in D3D12
		Rasterizer::AlignedTo16Byte::Float3 bindingColor;
		Rasterizer::AlignedTo16Byte::Float3 highlightColor;
		Rasterizer::AlignedTo16Byte::Float3 faceColor;
		Rasterizer::AlignedTo16Byte::Float3 textColor;
		Rasterizer::AlignedTo16Byte::Float textureRange;
		Rasterizer::AlignedTo16Byte::Float size;
		Rasterizer::AlignedTo16Byte::Int selectedId;

		DescriptionBuffer(){};
	};

	struct CameraBuffer {
		buw::Matrix44f rotation;
		buw::Matrix44f projection;
	};

public:
	typedef uint32_t IndexType;
	typedef buw::VertexPosition3Texture2PickId1FaceId1RegionId1 CubeVertexType;
	typedef buw::VertexPosition3Texture2PickId1FaceId1RegionId1 CompassVertexType;

	ViewCubeEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::ITexture2D> pickBuffer);
	// ViewCubeEffect() {};
	virtual ~ViewCubeEffect();

	void createCubeBuffers(std::vector<CubeVertexType>& vertices, std::vector<IndexType>& indices);

	void createCompassBuffers(std::vector<CompassVertexType>& vertices, std::vector<IndexType>& indices);

	void updateDescriptionBuffer(DescriptionBuffer& buffer);
	void updatePickId(unsigned int pickId);

	void setDepthStencil(buw::ReferenceCounted<buw::ITexture2D> dsv);

	void mouseMove(const int x, const int y);
	void mousePress(); // TODO

	unsigned int getLastPickId();

	void resize(buw::viewportDescription vpd);

	void updateRotationMatrix(const buw::Matrix44f& rotation);
	void updateProjectionMatrix(const buw::Matrix44f& projection);
	void updateFaceColor(const buw::Vector3f& faceColor);

public:
	buw::ReferenceCounted<buw::ITexture2D>& getFrontTexture();
	void setFrontTexture(buw::ReferenceCounted<buw::ITexture2D> front_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getTopTexture();
	void setTopTexture(buw::ReferenceCounted<buw::ITexture2D> top_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getBackTexture();
	void setBackTexture(buw::ReferenceCounted<buw::ITexture2D> back_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getBottomTexture();
	void setBottomTexture(buw::ReferenceCounted<buw::ITexture2D> bottom_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getRightTexture();
	void setRightTexture(buw::ReferenceCounted<buw::ITexture2D> right_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getLeftTexture();
	void setLeftTexture(buw::ReferenceCounted<buw::ITexture2D> left_texture);

	buw::ReferenceCounted<buw::ITexture2D>& getTestTexture();
	void setTestTexture(buw::ReferenceCounted<buw::ITexture2D> test_texture);

public:
	bool getRenderCube() const;
	void setRenderCube(const bool render_cube);

	bool getRenderCompass() const;
	void setRenderCompass(const bool render_compass);

	bool getRenderArrows() const;
	void setRenderArrows(const bool render_arrows);

	void setPickBuffer(buw::ReferenceCounted<buw::ITexture2D> pickBuffer);
    void setPickIdBuffer(buw::ReferenceCounted<buw::IConstantBuffer> &pickIdBuffer);
	buw::ReferenceCounted<buw::ITexture2D>& getPickBuffer();

private:
	void v_init() override;
	void v_render() override;

	void drawCube();
	void drawCompass();
	void drawArrows();

	void updateCameraBuffer();

private:
	bool renderCube_ = true, renderCompass_ = true, renderArrows_ = false;

	buw::ReferenceCounted<buw::IPipelineState> cubeState_, compassState_, arrowsState_, pickState_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferCube_, vertexBufferCompass_, vertexBufferArrows_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferCube_, indexBufferCompass_, indexBufferArrows_;

	buw::ReferenceCounted<buw::ITexture2D> frontTexture_, topTexture_, backTexture_, bottomTexture_, rightTexture_, leftTexture_;

	buw::ReferenceCounted<buw::IConstantBuffer> cameraBuffer_, descriptionBuffer_, pickIdBuffer_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencilMSAA_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<buw::ITexture2D> pickBuffer_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::IBlender> blender_;

	CameraBuffer cameraMatrices_;
	buw::Image4b pickBufferImage_;
	unsigned int lastPickId_;
};

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

#endif // end define BlueFramework_Engine_ViewCubeEffect_8fbf70e0_a8c3_4a4c_b26f_bf186fad77b3_h
