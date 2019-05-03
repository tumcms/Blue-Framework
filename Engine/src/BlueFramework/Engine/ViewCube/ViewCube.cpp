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

// BlueFramework Core
#include "BlueFramework/Core/Math/Matrix.h"
#include "BlueFramework/Core/Math/constants.h"
#include "BlueFramework/Core/Math/util.h"
#include <BlueFramework/Core/Diagnostics/log.h>

// BlueFramework ImageProcessing
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>

#include <boost/filesystem.hpp>

// System
#include <fstream>
#include <string>

// Qt
#pragma warning(push)
#pragma warning(disable : 4127)

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>

#pragma warning(pop)

#include "BlueFramework/Engine/ViewCube/ViewCube.h"

using eFaceId = BlueFramework::Engine::ViewCube::eFaceId;
using Description = BlueFramework::Engine::ViewCube::viewCubeDescription;
using CubeVertexType = BlueFramework::Engine::ViewCubeEffect::CubeVertexType;
using CompassVertexType = BlueFramework::Engine::ViewCubeEffect::CompassVertexType;
using IndexType = BlueFramework::Engine::ViewCubeEffect::IndexType;

const int regionIds[9][9] = {
	{0, 0, 0, 1, 1, 1, 2, 2, 2}, {0, 0, 0, 1, 1, 1, 2, 2, 2}, {0, 0, 0, 1, 1, 1, 2, 2, 2},
	{3, 3, 3, 4, 4, 4, 5, 5, 5}, {3, 3, 3, 4, 4, 4, 5, 5, 5}, {3, 3, 3, 4, 4, 4, 5, 5, 5},
	{6, 6, 6, 7, 7, 7, 8, 8, 8}, {6, 6, 6, 7, 7, 7, 8, 8, 8}, {6, 6, 6, 7, 7, 7, 8, 8, 8} };

const std::vector<std::pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>> views_ = {
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Front), 4)}, buw::ViewCube::eViewCubeOrientation::FrontView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Top), 4)}, buw::ViewCube::eViewCubeOrientation::TopView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Bottom), 4)}, buw::ViewCube::eViewCubeOrientation::BottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Back), 4)}, buw::ViewCube::eViewCubeOrientation::BackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Left), 4)}, buw::ViewCube::eViewCubeOrientation::LeftView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Right), 4)}, buw::ViewCube::eViewCubeOrientation::RightView),

  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Front), 1), buw::Vector2i(int(eFaceId::Top), 7)},
																				  buw::ViewCube::eViewCubeOrientation::TopFrontView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Front), 5), buw::Vector2i(int(eFaceId::Right), 3) },
																				  buw::ViewCube::eViewCubeOrientation::FrontRightView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Front), 3), buw::Vector2i(int(eFaceId::Left), 5) },
																				  buw::ViewCube::eViewCubeOrientation::FrontLeftView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Front), 7), buw::Vector2i(int(eFaceId::Bottom), 1)},
																				  buw::ViewCube::eViewCubeOrientation::FrontBottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Right), 1), buw::Vector2i(int(eFaceId::Top), 5)},
																				  buw::ViewCube::eViewCubeOrientation::TopRightView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Right), 7), buw::Vector2i(int(eFaceId::Bottom), 5)},
																				  buw::ViewCube::eViewCubeOrientation::RightBottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Left), 1), buw::Vector2i(int(eFaceId::Top), 3)},
																				  buw::ViewCube::eViewCubeOrientation::TopLeftView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Left), 7), buw::Vector2i(int(eFaceId::Bottom), 3)},
																				  buw::ViewCube::eViewCubeOrientation::LeftBottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Back), 3), buw::Vector2i(int(eFaceId::Right), 5) },
																				  buw::ViewCube::eViewCubeOrientation::RightBackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Back), 5), buw::Vector2i(int(eFaceId::Left), 3) },
																				  buw::ViewCube::eViewCubeOrientation::BackLeftView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Back), 1), buw::Vector2i(int(eFaceId::Top), 1)},
																				  buw::ViewCube::eViewCubeOrientation::TopBackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>({buw::Vector2i(int(eFaceId::Back), 7), buw::Vector2i(int(eFaceId::Bottom), 7)},
																				  buw::ViewCube::eViewCubeOrientation::BackBottomView),

  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Front), 2), buw::Vector2i(int(eFaceId::Top), 8), buw::Vector2i(int(eFaceId::Right), 0), buw::Vector2i(int(eFaceId::SouthEast), 9) },
	buw::ViewCube::eViewCubeOrientation::TopFrontRightView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Front), 0), buw::Vector2i(int(eFaceId::Left), 2), buw::Vector2i(int(eFaceId::Top), 6), buw::Vector2i(int(eFaceId::SouthWest), 9) },
	buw::ViewCube::eViewCubeOrientation::TopLeftFrontView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Front), 8), buw::Vector2i(int(eFaceId::Right), 6), buw::Vector2i(int(eFaceId::Bottom), 2)},
	buw::ViewCube::eViewCubeOrientation::FrontRightBottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Front), 6), buw::Vector2i(int(eFaceId::Left), 8), buw::Vector2i(int(eFaceId::Bottom), 0)},
	buw::ViewCube::eViewCubeOrientation::FrontLeftBottomView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Back), 0), buw::Vector2i(int(eFaceId::Top), 2), buw::Vector2i(int(eFaceId::Right), 2), buw::Vector2i(int(eFaceId::NorthEast), 9) },
	buw::ViewCube::eViewCubeOrientation::TopRightBackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Back), 2), buw::Vector2i(int(eFaceId::Top), 0), buw::Vector2i(int(eFaceId::Left), 0), buw::Vector2i(int(eFaceId::NorthWest), 9) },
	buw::ViewCube::eViewCubeOrientation::TopLeftBackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Back), 6), buw::Vector2i(int(eFaceId::Bottom), 8), buw::Vector2i(int(eFaceId::Right), 8)},
	buw::ViewCube::eViewCubeOrientation::RightBottomBackView),
  std::make_pair<std::vector<buw::Vector2i>, buw::ViewCube::eViewCubeOrientation>(
	{buw::Vector2i(int(eFaceId::Back), 8), buw::Vector2i(int(eFaceId::Bottom), 6), buw::Vector2i(int(eFaceId::Left), 6)},
	buw::ViewCube::eViewCubeOrientation::BackLeftBottomView) };


unsigned int BlueFramework::Engine::ViewCube::getMatchingPickId(eFaceId faceId, int regionId) {
	for(auto it : views_) {
		for(auto it_pairs : it.first) {
			if(it_pairs.x() == int(faceId) && it_pairs.y() == regionId) {
				return unsigned int(it.second);
			}
		}
	}
	return 0;
}

void BlueFramework::Engine::ViewCube::setPickIdBuffer(buw::ReferenceCounted<buw::IConstantBuffer> &pickIdBuffer)
{
	effect_.setPickIdBuffer(pickIdBuffer);
}

void BlueFramework::Engine::ViewCube::updateBorderColor(const QColor & color)
{
	desc_.bindingColor = buw::Vector3f(color.redF(), color.greenF(), color.blueF()).cast<float>();
	effect_.updateDescriptionBuffer(convert(desc_));
}

void BlueFramework::Engine::ViewCube::updateTextColor(const QColor & color)
{
	desc_.textColor = buw::Vector3f(color.redF(), color.greenF(), color.blueF()).cast<float>();
	effect_.updateDescriptionBuffer(convert(desc_));
}

void BlueFramework::Engine::ViewCube::updateHighlightColor(const QColor & color)
{
	desc_.highlightColor = buw::Vector3f(color.redF(), color.greenF(), color.blueF()).cast<float>();
	effect_.updateDescriptionBuffer(convert(desc_));
}

void BlueFramework::Engine::ViewCube::updateSize(const float & size)
{
	desc_.size = size;
	effect_.updateDescriptionBuffer(convert(desc_));
}

void BlueFramework::Engine::ViewCube::updateFaceColor(const QColor &color) {
	desc_.faceColor = buw::Vector3f(color.redF(), color.greenF(), color.blueF()).cast<float>();
	effect_.updateDescriptionBuffer(convert(desc_));
}

buw::Vector3f mapToColor(QString from) {
	QStringList colors = from.split(',');
	return buw::Vector3f(colors[0].toFloat(), colors[1].toFloat(), colors[2].toFloat());
}

QString mapToString(buw::Vector3f color) {
	char string[21];
	sprintf_s<21>(string, "%.4f,%.4f,%.4f", color.x(), color.y(), color.z());
	return QString(string);
}

buw::Vector2f mapToTexture(float x, float y) {
	return buw::Vector2f(x, 1.0f - y);
}

buw::Vector3f transform(buw::Vector3f pos, eFaceId id) {
	buw::Matrix44f rotation;
	buw::Matrix44f translation = buw::createTranslationMatrix(-0.5f, -0.5f, 0.0f);
	switch(id) {
	case eFaceId::Top: rotation = buw::createRotationMatrixX(buw::degreeToRadian<float>(90.0f)); break;
	case eFaceId::Front: rotation = buw::createRotationMatrixZ(buw::degreeToRadian<float>(0.0f)); break;
	case eFaceId::Back: rotation = buw::createRotationMatrixY(buw::degreeToRadian<float>(-180.0f)); break;
	case eFaceId::Left: rotation = buw::createRotationMatrixY(buw::degreeToRadian<float>(90.0f)); break;
	case eFaceId::Right: rotation = buw::createRotationMatrixY(buw::degreeToRadian<float>(-90.0f)); break;
	case eFaceId::Bottom: rotation = buw::createRotationMatrixX(buw::degreeToRadian<float>(-90.0f)); break;
	default: rotation = buw::createRotationMatrixX(0.0f); break;
	}
	auto transformed = buw::Vector4f(pos.x(), pos.y(), pos.z(), 1.0f);
	transformed.applyOnTheLeft(translation);
	transformed.applyOnTheLeft(rotation);
	return buw::Vector3f(transformed.x(), transformed.y(), transformed.z());
}

BlueFramework::Engine::ViewCube::ViewCube(buw::ReferenceCounted<buw::IRenderSystem> renderSystem,
	buw::ReferenceCounted<buw::ITexture2D> pickBuffer,
	buw::ReferenceCounted<buw::IConstantBuffer> pickIdBuffer /*=nullptr*/,
	buw::ReferenceCounted<buw::CameraController> cameraController /*= nullptr*/)
	: effect_(renderSystem.get(), pickBuffer) {
	effect_.init();
	effect_.updateRotationMatrix(buw::Matrix44f::Identity());
	buw::CameraFrustum frustum = buw::CameraFrustum(std::min(pickBuffer->width(), 130),
		std::min(pickBuffer->height(), 130),
		0.001f,
		100.f,
		buw::eProjectionType::Perspective,
		BlueFramework::Core::Math::constants<float>::pi_over_4());
	effect_.updateProjectionMatrix(frustum.projectionMatrix());

	std::string filenameViewCubeDescription = "Data/ViewCube.json";
	BLUE_ASSERT(boost::filesystem::exists(filenameViewCubeDescription), "Can not find view cube description file");

	if(!boost::filesystem::exists(filenameViewCubeDescription)) {
		throw buw::Exception("Can not find view cube description file (%s)", filenameViewCubeDescription.c_str());
	}

	setDescription(loadDescription(filenameViewCubeDescription));
	if(cameraController)
		connectCamera(cameraController);
	if(pickIdBuffer)
		setPickIdBuffer(pickIdBuffer);
}

BlueFramework::Engine::ViewCube::~ViewCube() {
	disconnectCamera();
}

void createCubeBufferData(Description from, std::vector<CubeVertexType>& vertices_out, std::vector<IndexType>& indices_out) {
	/*Initialize the offsets for the different viewCube regions.*/
	float offsets[9] = { from.outerBoundWidth,
						from.outerBoundHeight,
						from.innerBoundWidth,
						from.innerBoundWidth,
						1.0f - 2.0f * (from.outerBoundWidth + from.outerBoundHeight + 2.0f * from.innerBoundWidth),
						from.innerBoundWidth,
						from.innerBoundWidth,
						from.outerBoundHeight,
						from.outerBoundWidth };

	/*
	Iterate over all faces to generate the raw vertex data.
	TODO: Finish documentation!
	*/
	for(int faces = 0; faces < 6; ++faces) {
		float top = 1.0f, bottom = 1.0f;
		for(int rows = 0; rows < 9; ++rows) {
			float left = 0.0f, right = 0.0f;
			top = bottom;
			bottom -= offsets[rows];
			for(int cols = 0; cols < 9; ++cols) {
				left = right;
				right += offsets[cols];

				/*Set start index as number of vertices already created.*/
				int startIndex = int(vertices_out.size());

				/*Determine region type from horizontal and vertical position.*/
				int regionType = (cols % 3 == 1 && rows % 3 == 1) ? (cols == 4 && rows == 4) ? 2 : 1 : 0;

				int regionId = regionIds[rows][cols];
				unsigned int pickid = BlueFramework::Engine::ViewCube::getMatchingPickId(static_cast<eFaceId>(faces), regionId);

				/*Push vertices into CPU side vertex buffer.*/
				vertices_out.push_back(
					CubeVertexType(transform(buw::Vector3f(left, top, -0.5f), static_cast<eFaceId>(faces)), mapToTexture(left, top), pickid, faces, regionType));
				vertices_out.push_back(
					CubeVertexType(transform(buw::Vector3f(right, top, -0.5f), static_cast<eFaceId>(faces)), mapToTexture(right, top), pickid, faces, regionType));
				vertices_out.push_back(
					CubeVertexType(transform(buw::Vector3f(left, bottom, -0.5f), static_cast<eFaceId>(faces)), mapToTexture(left, bottom), pickid, faces, regionType));
				vertices_out.push_back(
					CubeVertexType(transform(buw::Vector3f(right, bottom, -0.5f), static_cast<eFaceId>(faces)), mapToTexture(right, bottom), pickid, faces, regionType));

				/*Push indices into CPU side index buffer.*/
				indices_out.push_back(startIndex);
				indices_out.push_back(startIndex + 1);
				indices_out.push_back(startIndex + 2);
				indices_out.push_back(startIndex + 3);
				indices_out.push_back(startIndex + 2);
				indices_out.push_back(startIndex + 1);
			}
		}
	}
}

/*Create vertices and indices for the compass from the viewCubeDescription.*/
void createCompassBufferData(Description desc, std::vector<CompassVertexType>& vertices_out, std::vector<IndexType>& indices_out)
{
	/*Create the 4 segments for diagonal segments (ne,nw,se,sw).*/
	buw::Vector3f offset = buw::Vector3f(desc.circleOffset, -0.4f, desc.circleOffset);
	float offsets[3] = { desc.outerCircleWidth, desc.innerCircleWidth, desc.outerCircleWidth };
	float radius[3] = {
		desc.outerCircleRadius,
		desc.outerCircleRadius - desc.outerCircleWidth,
		desc.outerCircleRadius - desc.outerCircleWidth - desc.innerCircleWidth 
	};

	int faceId = 6;
	/*Iterate over the 4 directions for the segments.*/
	for(int hor = -1; hor <= 1; hor += 2) {
		for(int ver = -1; ver <= 1; ver += 2) {
			buw::Vector3f direction = buw::Vector3f(hor, 1.0f, ver);
			for(int region = 0; region < 3; region++) {

				/*Iterate over a 90° arc and create the points for the circles.*/
				for(int deg = 0; deg < 90; deg++) {
					int startIndex = int(vertices_out.size());
					for(int shift = 0; shift < 2; shift++) {
						float rad = buw::degreeToRadian(1.0f*(deg + shift));

						CompassVertexType vertex;
						buw::Vector3f posXYZ = buw::Vector3f(std::cosf(rad), 0, std::sinf(rad));
						buw::Vector3f pos = posXYZ * radius[region] + offset;

						vertex.faceid = faceId;
						vertex.uv = buw::Vector2f(0.0f, 0.0f);
						unsigned int pickId = BlueFramework::Engine::ViewCube::getMatchingPickId(static_cast<eFaceId>(faceId), 9);
						vertex.pickid = pickId | 0b01000000;
						vertex.regionid = deg <= 1 || deg >= 88 ? 0 : region % 2;

						pos = (pos.array()*direction.array()).matrix();
						vertex.position = pos;
						vertices_out.push_back(vertex);

						pos = posXYZ *(radius[region] - offsets[region]) + offset;
						pos = (pos.array()*direction.array()).matrix();
						vertex.position = pos;
						vertices_out.push_back(vertex);
					}

					/*Push indices into CPU side index buffer.*/
					indices_out.push_back(startIndex);
					indices_out.push_back(startIndex + 1);
					indices_out.push_back(startIndex + 2);
					indices_out.push_back(startIndex + 3);
					indices_out.push_back(startIndex + 2);
					indices_out.push_back(startIndex + 1);
				}
			}
			faceId++;
		}
	}
}
std::string BlueFramework::Engine::ViewCube::viewCubeDescription::getFaceTexturePath(eFaceId face) {
	switch(face) {
	case eFaceId::Front: return frontTexturePath;
	case eFaceId::Back: return backTexturePath;
	case eFaceId::Left: return leftTexturePath;
	case eFaceId::Right: return rightTexturePath;
	case eFaceId::Top: return topTexturepath;
	case eFaceId::Bottom: return bottomTexturePath;
	default: return "";
	}
}

/*Save the current viewCubeDescription to a file to reimport it.*/
void BlueFramework::Engine::ViewCube::viewCubeDescription::saveToFile(QString filename)
{
	std::ofstream ofstream(filename.toStdString(), std::ofstream::out);
	QJsonObject viewCube;

	viewCube.insert("Size", QJsonValue(size));
	viewCube.insert("BindingColor", QJsonValue(mapToString(bindingColor)));
	viewCube.insert("FaceColor", QJsonValue(mapToString(faceColor)));
	viewCube.insert("HighlightColor", QJsonValue(mapToString(highlightColor)));
	viewCube.insert("TextColor", QJsonValue(mapToString(textColor)));

	viewCube.insert("OuterBoundHeight", QJsonValue(outerBoundHeight));
	viewCube.insert("InnerBoundHeight", QJsonValue(innerBoundHeight));
	viewCube.insert("OuterBoundWidth", QJsonValue(outerBoundWidth));
	viewCube.insert("InnerBoundWidth", QJsonValue(innerBoundWidth));

	viewCube.insert("OuterCircleRadius", QJsonValue(outerCircleRadius));
	viewCube.insert("OuterCircleWidth", QJsonValue(outerCircleWidth));
	viewCube.insert("InnerCircleWidth", QJsonValue(innerCircleWidth));
	viewCube.insert("CircleOffset", QJsonValue(circleOffset));

	viewCube.insert("Front", QJsonValue(QString(frontTexturePath.data())));
	viewCube.insert("Back", QJsonValue(QString(backTexturePath.data())));
	viewCube.insert("Left", QJsonValue(QString(leftTexturePath.data())));
	viewCube.insert("Right", QJsonValue(QString(rightTexturePath.data())));
	viewCube.insert("Top", QJsonValue(QString(topTexturepath.data())));
	viewCube.insert("Bottom", QJsonValue(QString(bottomTexturePath.data())));

	QJsonDocument file = QJsonDocument(viewCube);
	QByteArray data = file.toJson();
	ofstream.write(data, data.size());
	ofstream.close();
}

Description readDescription(QJsonObject from) {
	Description desc;

	// Global
	desc.size = static_cast<float>(from.value("Size").toDouble());
	desc.bindingColor = mapToColor(from.value("BindingColor").toString());
	desc.faceColor = mapToColor(from.value("FaceColor").toString());
	desc.highlightColor = mapToColor(from.value("HighlightColor").toString());
	desc.textColor = mapToColor(from.value("TextColor").toString());

	// ViewCube
	desc.outerBoundHeight = static_cast<float>(from.value("OuterBoundHeight").toDouble());
	desc.innerBoundHeight = static_cast<float>(from.value("InnerBoundHeight").toDouble());
	desc.outerBoundWidth = static_cast<float>(from.value("OuterBoundWidth").toDouble());
	desc.innerBoundWidth = static_cast<float>(from.value("InnerBoundWidth").toDouble());

	// Compass
	desc.outerCircleRadius = static_cast<float>(from.value("OuterCircleRadius").toDouble());
	desc.outerCircleWidth = static_cast<float>(from.value("OuterCircleWidth").toDouble());
	desc.innerCircleWidth = static_cast<float>(from.value("InnerCircleWidth").toDouble());
	desc.circleOffset = static_cast<float>(from.value("CircleOffset").toDouble());

	// Textures
	desc.frontTexturePath = from.value("Front").toString().toStdString();
	desc.backTexturePath = from.value("Back").toString().toStdString();
	desc.leftTexturePath = from.value("Left").toString().toStdString();
	desc.rightTexturePath = from.value("Right").toString().toStdString();
	desc.topTexturepath = from.value("Top").toString().toStdString();
	desc.bottomTexturePath = from.value("Bottom").toString().toStdString();

	return desc;
}

void BlueFramework::Engine::ViewCube::setFaceTexture(BlueFramework::Engine::ViewCube::eFaceId face, buw::ReferenceCounted<buw::ITexture2D> texture) {
	switch(face) {
	case eFaceId::Front: effect_.setFrontTexture(texture); break;
	case eFaceId::Back: effect_.setBackTexture(texture); break;
	case eFaceId::Left: effect_.setLeftTexture(texture); break;
	case eFaceId::Right: effect_.setRightTexture(texture); break;
	case eFaceId::Top: effect_.setTopTexture(texture); break;
	case eFaceId::Bottom: effect_.setBottomTexture(texture); break;
	default: break;
	}
}

Description BlueFramework::Engine::ViewCube::getDescription()
{
	return desc_;
}

void BlueFramework::Engine::ViewCube::setDescription(Description desc) {
	desc_ = desc;
	std::vector<CubeVertexType> vertices_cube;
	std::vector<CompassVertexType> vertices_compass;
	std::vector<IndexType> indices_cube, indices_compass;

	/*Create raw vertex data and create GPU buffers for the rendering effect.*/
	createCubeBufferData(desc_, vertices_cube, indices_cube);
	effect_.createCubeBuffers(vertices_cube, indices_cube);

	/*Create the CPU side buffers and let the effect create the GPU side buffers.*/
	createCompassBufferData(desc_, vertices_compass, indices_compass);
	effect_.createCompassBuffers(vertices_compass, indices_compass);

	/*Pass the description on to the effect for rendering.*/
	ViewCubeEffect::DescriptionBuffer buffer;
	buffer.size[0] = desc_.size;
	buffer.bindingColor = desc_.bindingColor;
	buffer.faceColor = desc_.faceColor;
	buffer.highlightColor = desc_.highlightColor;
	buffer.selectedId = 0;
	buffer.textColor = desc_.textColor;
	buffer.textureRange = desc_.outerBoundWidth + desc_.innerBoundHeight + 2.0f * desc_.innerBoundWidth;

	effect_.updateDescriptionBuffer(convert(desc_));

	/*Iterate over all faces and load the corresponding textures from the files specified in the description.*/
	for(int face = 0; face < 6; ++face) {
		eFaceId faceid = static_cast<eFaceId>(face);
		auto img = buw::loadImage4b(desc_.getFaceTexturePath(faceid));

		/*Create the texture description for the GPU side buffer.*/
		buw::texture2DDescription td;
		td.width = img.getWidth();
		td.height = img.getHeight();
		td.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td.data = img.getData();

		/*Create the texture on the GPU side.*/
		auto tex = effect_.renderSystem()->createTexture2D(td, buw::eTextureBindType::SRV);
		setFaceTexture(faceid, tex);
	}
}

void BlueFramework::Engine::ViewCube::render() {
	/*Update the camera matrix and render the viewCube.*/
	const buw::Matrix44f rotation = cameraController_->getCamera()->transformation().rotationMatrix();
	effect_.updateRotationMatrix(rotation);
	effect_.render();
}

void BlueFramework::Engine::ViewCube::resize(buw::viewportDescription vpd) {
	buw::CameraFrustum frustum = buw::CameraFrustum(
		std::min((int)vpd.width, 130), std::min((int)vpd.height, 130), 0.001f, 10.f, buw::eProjectionType::Perspective, BlueFramework::Core::Math::constants<float>::pi_over_4());
	effect_.updateProjectionMatrix(frustum.projectionMatrix());
	effect_.resize(vpd);
}

/*Forward mouse movement to rendering effect.*/
void BlueFramework::Engine::ViewCube::mouseMove(const int x, const int y) {
	effect_.mouseMove(x, y);
}

void BlueFramework::Engine::ViewCube::mousePress() {
	if(effect_.getLastPickId() < 128) {
		ViewCube::eViewCubeOrientation newOrientation = ViewCube::eViewCubeOrientation(effect_.getLastPickId());
		if(newOrientation != Unselected) {
			currentOrientation_ = newOrientation;
			SelectionChanged(getViewDirection(newOrientation));
		}
	}
}

/*Retrieve geometric view direction from enum.*/
const buw::Vector3f BlueFramework::Engine::ViewCube::getViewDirection(eViewCubeOrientation orientation) const {
	buw::Vector3f viewDirection;
	viewDirection[1] = ((orientation & ViewCube::eViewCubeOrientation::TopView) > 0) ? 1.0f : ((orientation & ViewCube::eViewCubeOrientation::BottomView) > 0) ? -1.0f : 0.0f;

	viewDirection[2] = ((orientation & ViewCube::eViewCubeOrientation::RightView) > 0) ? -1.0f : ((orientation & ViewCube::eViewCubeOrientation::LeftView) > 0) ? 1.0f : 0.0f;

	viewDirection[0] = ((orientation & ViewCube::eViewCubeOrientation::FrontView) > 0) ? 1.0f : ((orientation & ViewCube::eViewCubeOrientation::BackView) > 0) ? -1.0f : 0.0f;

	const buw::Vector3f const_viewDirection = buw::Vector3f(viewDirection);
	return const_viewDirection;
}

/*Convert description from format used by ViewCube class to the one used by ViewCubeEffect.*/
BlueFramework::Engine::ViewCubeEffect::DescriptionBuffer BlueFramework::Engine::ViewCube::convert(Description desc) {
	ViewCubeEffect::DescriptionBuffer buffer;
	buffer.size[0] = desc.size;
	buffer.bindingColor = desc.bindingColor;
	buffer.faceColor = desc.faceColor;
	buffer.highlightColor = desc.highlightColor;
	buffer.selectedId = effect_.getLastPickId();
	buffer.textColor = desc.textColor;
	buffer.textureRange = desc.outerBoundWidth + desc.innerBoundHeight + 2.0f * desc.innerBoundWidth;
	return buffer;
}

/*Load a description from file.*/
Description BlueFramework::Engine::ViewCube::loadDescription(std::string filename) {
	QFile file(filename.data());
	BLUE_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text))
	QByteArray data = file.readAll();
	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject obj = doc.object();
	return readDescription(obj);
}

void BlueFramework::Engine::ViewCube::connectCamera(buw::ReferenceCounted<buw::CameraController>& cameraController) {
	cameraController_ = cameraController;
	connection_ = SelectionChanged.connect(boost::bind(&buw::CameraController::setViewDirection, cameraController_.get(), _1));
}

void BlueFramework::Engine::ViewCube::disconnectCamera() {
	if(connection_.connected())
		connection_.disconnect();
	cameraController_ = nullptr;
}
