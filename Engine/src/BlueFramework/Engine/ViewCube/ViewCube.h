/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_Engine_ViewCube_20fd69b4_212a_4a6c_b6e8_a0feb904cb1d_h
#define BlueFramework_Engine_ViewCube_20fd69b4_212a_4a6c_b6e8_a0feb904cb1d_h

#include "BlueFramework/Core/Math/Vector.h"
#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Engine/namespace.h"
#include "BlueFramework/Engine/Camera/Camera.h"
#include "BlueFramework/Engine/ViewCube/ViewCubeEffect.h"

#include <boost/bind.hpp>
#include <boost/signals2.hpp>

#include <QColor>
#include <QObject>
#include <map>
#include <string>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

class ViewCube : public QObject {
	Q_OBJECT;

public:
	enum class eFaceId : int {
		Front = 0,
		Back = 1,
		Left = 2,
		Right = 3,
		Top = 4,
		Bottom = 5,
		SouthWest = 6,
		NorthWest = 7,
		SouthEast = 8,
		NorthEast = 9};

	enum eViewCubeOrientation : const short {
		Unselected = 0b00000000,
		FrontView = 0b00000001,
		BackView = 0b00000010,
		TopView = 0b00000100,
		BottomView = 0b00001000,
		LeftView = 0b00010000,
		RightView = 0b00100000,
		TopLeftFrontView = TopView | FrontView | LeftView,
		TopFrontView = TopView | FrontView,
		TopFrontRightView = TopView | FrontView | RightView,
		FrontLeftView = FrontView | LeftView,
		FrontRightView = FrontView | RightView,
		FrontLeftBottomView = FrontView | LeftView | BottomView,
		FrontBottomView = FrontView | BottomView,
		FrontRightBottomView = FrontView | RightView | BottomView,
		TopRightView = TopView | RightView,
		TopRightBackView = TopView | RightView | BackView,
		RightBackView = RightView | BackView,
		RightBottomView = RightView | BottomView,
		RightBottomBackView = RightView | BackView | BottomView,
		TopBackView = TopView | BackView,
		TopLeftBackView = TopView | BackView | LeftView,
		BackLeftView = BackView | LeftView,
		BackBottomView = BackView | BottomView,
		BackLeftBottomView = BackView | BottomView | LeftView,
		TopLeftView = TopView | LeftView,
		LeftBottomView = BottomView | LeftView
	};

	struct viewCubeDescription {
		float outerBoundWidth, innerBoundWidth, boundHeight, innerBoundHeight, outerBoundHeight, size;
		buw::Vector3f bindingColor, highlightColor, faceColor, textColor;
		float outerCircleWidth, innerCircleWidth, outerCircleRadius, circleOffset;
		std::string frontTexturePath, backTexturePath, leftTexturePath, rightTexturePath, topTexturepath, bottomTexturePath;

		std::string getFaceTexturePath(eFaceId face);

		viewCubeDescription(){};

        void saveToFile(QString filename);	};

	enum class eRegionType : int { Border = 0, Tile = 1, Center = 2 };

	ViewCube(buw::ReferenceCounted<buw::IRenderSystem> renderSystem,
	         buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
             buw::ReferenceCounted<buw::IConstantBuffer> pickIdBuffer = nullptr,
	         buw::ReferenceCounted<buw::CameraController> cameraController = nullptr,
			 std::string ssResourceRootDir = "");
	// ViewCube() {};
	virtual ~ViewCube();

    viewCubeDescription loadDescription(std::string filename);

	void setFaceTexture(eFaceId face, buw::ReferenceCounted<buw::ITexture2D> texture);

	void setDescription(viewCubeDescription desc);

    viewCubeDescription getDescription();

	void setPickBuffer(buw::ReferenceCounted<buw::ITexture2D> pickBuffer) {
		effect_.setPickBuffer(pickBuffer);
	}

	buw::ReferenceCounted<buw::ITexture2D>& getPickBuffer() {
		return effect_.getPickBuffer();
	}

	void render();

	void resize(buw::viewportDescription vpd);

	void showCube(bool value) {
		effect_.setRenderCube(value);
	}
	void showCompass(bool value) {
		effect_.setRenderCompass(value);
	}
	void showArrows(bool value) {
		effect_.setRenderArrows(value);
	}

	void mouseMove(const int x, const int y);
	void mousePress();

	void connectCamera(buw::ReferenceCounted<buw::CameraController>& cameraController);

	void disconnectCamera();

	boost::signals2::signal<void(const buw::Vector3f&)> SelectionChanged;

	static unsigned int getMatchingPickId(eFaceId faceId, int regionId);

    void setPickIdBuffer(buw::ReferenceCounted<buw::IConstantBuffer> &pickIdBuffer);

    UINT getLastPickID() { return effect_.getLastPickId(); }

	void setPickId(UINT id) { effect_.updatePickId(id); }

public Q_SLOTS:
	void updateFaceColor(const QColor &color);
	void updateBorderColor(const QColor &color);
	void updateTextColor(const QColor &color);
    void updateHighlightColor(const QColor &color);
    void updateSize(const float &size);

private:
	void updatePickId();

	const buw::Vector3f getViewDirection(eViewCubeOrientation orientation) const;

	void updateEffectDescription(const viewCubeDescription& desc);

private:
	viewCubeDescription desc_;
	ViewCubeEffect effect_;
	ViewCubeEffect::DescriptionBuffer buffer_;
	// static std::multimap<unsigned int, std::pair<buw::Vector2i, eViewCubeOrientation>>	mapping;
	buw::ReferenceCounted<buw::CameraController> cameraController_;
	boost::signals2::connection connection_;
	eViewCubeOrientation currentOrientation_;
};

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(ViewCube)

#endif // end define BlueFramework_Engine_ViewCube_20fd69b4_212a_4a6c_b6e8_a0feb904cb1d_h
