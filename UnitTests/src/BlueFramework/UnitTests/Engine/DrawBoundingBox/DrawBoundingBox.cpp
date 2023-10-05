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

#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Rasterizer/vertex.h>

#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

struct WorldBuffer {
	buw::Matrix44f viewProjection;
	buw::Matrix44f projection;
	buw::Matrix44f view;
	buw::Vector3f cam;
	buw::Matrix44f rotation;
};

struct ViewportBuffer {
	int width, height;
	int p1, p2;
};

class Viewport : public QWidget {
	Q_OBJECT;

public:
	Viewport(const buw::eRenderAPI renderAPI)
	{
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);

		camera_ = buw::makeReferenceCounted<buw::Camera>();
		camera_->frustum() = buw::CameraFrustum(width(), height(), 0.1f, 1000.f, buw::eProjectionType::Perspective);
		camera_->transformation().offset() = 15;
		camera_->transformation().yaw() = buw::constantsf::pi_over_4();

		cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);


		buw::renderSystemDescription rsd;
		rsd.width = width();
		rsd.height = height();
		rsd.windowId = (void*)winId();
		rsd.forceWarpDevice = false;
		rsd.enableMSAA = true;
		rsd.renderAPI = renderAPI;

		renderSystem_ = buw::createRenderSystem(rsd);

		std::stringstream ss;
		ss << "DrawBoundingBox Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		buw::constantBufferDescription cbd0;
		cbd0.sizeInBytes = sizeof(WorldBuffer);
		cbd0.data = nullptr;
		worldBuffer_ = renderSystem_->createConstantBuffer(cbd0);

		ViewportBuffer buffer = { width(), height() };

		buw::constantBufferDescription cbd1;
		cbd1.sizeInBytes = sizeof(ViewportBuffer);
		cbd1.data = &buffer;
		viewportBuffer_ = renderSystem_->createConstantBuffer(cbd1);

		buw::texture2DDescription dsvTD;
		dsvTD.width = width();
		dsvTD.height = height();
		dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
		dsvTD.useMSAA = true;
		dsvTD.data = nullptr;
		depthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

		effect_ = buw::makeReferenceCounted<BoxEffect>(renderSystem_.get(), viewport_, depthStencil_, worldBuffer_, viewportBuffer_);

		effect_->init();

		auto createBuffers = [&](buw::Vector3f position, buw::Vector3f boxSize, buw::Vector3f color, float size, buw::ReferenceCounted<buw::IVertexBuffer> &vb, buw::ReferenceCounted<buw::IIndexBuffer> &ib, Eigen::Quaternion<double> rotation = Eigen::Quaternion<double>::Identity()) {
			std::vector<buw::VertexPosition3> localVertices = std::vector<buw::VertexPosition3>();
			std::vector<uint32_t> localIndices = std::vector<uint32_t>();

			buw::createBoundingBox(localVertices, localIndices, position.x(), position.y(), position.z(), boxSize.x(), boxSize.y(), boxSize.z());

			std::vector<buw::VertexPosition3Color3Size1> vertices = std::vector<buw::VertexPosition3Color3Size1>();
			for(auto vertex : localVertices) {
				auto pos = buw::Vector3f(vertex.position[0], vertex.position[1], vertex.position[2]);
				pos = (rotation.cast<float>() * (pos - position)) + position;
				vertices.push_back(buw::VertexPosition3Color3Size1(pos, color, size));
			}

			buw::indexBufferDescription ibd;
			ibd.indexCount = localIndices.size();
			ibd.data = localIndices.data();
			ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
			ib = renderSystem_->createIndexBuffer(ibd);

			// Fill vertex buffer description and create vertex buffer.
			buw::vertexBufferDescription vbd;
			vbd.vertexCount = vertices.size();
			vbd.vertexLayout = buw::VertexPosition3Color3Size1::getVertexLayout();
			vbd.data = vertices.data();
			vb = renderSystem_->createVertexBuffer(vbd);
		};
		Eigen::Quaternion<double> rotation = Eigen::Quaternion<double>(Eigen::AngleAxisd(M_PI / 1.4, buw::Vector3d::UnitX()));
		rotation = rotation * Eigen::AngleAxisd(M_PI / 2.4, buw::Vector3d::UnitY());
		rotation = rotation * Eigen::AngleAxisd(M_PI / 6.2, buw::Vector3d::UnitZ());

		{
			//Create cube buffers.
			createBuffers(buw::Vector3f(5, 5, 5), buw::Vector3f(3, 3, 3), buw::Vector3f(1, 1, 1), 3, vertexBufferCube_, indexBufferCube_, rotation);

			// CreateAxisBuffers
			createBuffers(buw::Vector3f(0, 0, 0), buw::Vector3f(10, 0.01, 0.01), buw::Vector3f(1, 0, 0), 2, vertexBufferXAxis_, indexBufferXAxis_);
			createBuffers(buw::Vector3f(0, 0, 0), buw::Vector3f(0.01, 10, 0.01), buw::Vector3f(0, 1, 0), 2, vertexBufferYAxis_, indexBufferYAxis_);
			createBuffers(buw::Vector3f(0, 0, 0), buw::Vector3f(0.01, 0.01, 10), buw::Vector3f(0, 0, 1), 2, vertexBufferZAxis_, indexBufferZAxis_);
		}

		
		auto rotationMatrix = rotation.matrix();
		Eigen::Matrix3d inverseRotationMatrix = rotationMatrix.inverse();

		// Get the inverse as matrix
		Eigen::Quaternion<double> inverseQuaternion = rotation.conjugate();
		auto inverseQuaternionRotationMatrix = inverseQuaternion.matrix();

		std::vector<buw::VertexPosition3> localVertices = std::vector<buw::VertexPosition3>();
		std::vector<uint32_t> localIndices = std::vector<uint32_t>();

		buw::createBoundingBox(localVertices, localIndices, 5, 5, 5, 3, 3, 3);

		std::vector<buw::VertexPosition3Color3Size1> vertices = std::vector<buw::VertexPosition3Color3Size1>();
		for(auto &vertex : localVertices) {
			vertex.position = buw::Vector3f((rotation.cast<float>() * (buw::Vector3f(vertex.position[0], vertex.position[1], vertex.position[2]) - buw::Vector3f(5, 5, 5))) + buw::Vector3f(5,5,5));
		}

		// Now try to reconstruct the rotation using PCA.
		auto getPCA = [&](std::vector<buw::VertexPosition3> points)->Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> {
			//Matrix which is capable of holding all points for PCA.
			Eigen::MatrixX3d mat;
			mat.resize(points.size(), 3);
			for(size_t i = 0; i < points.size(); i++) {
				mat.row(i) = Eigen::Vector3d(points[i].position[0], points[i].position[1], points[i].position[2]);
			}

			//Do PCA to find the largest eigenvector -> main axis.
			Eigen::MatrixXd centered = mat.rowwise() - mat.colwise().mean();
			Eigen::MatrixXd cov = centered.adjoint() * centered;
			return Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd>(cov);			
		};

		auto eig = getPCA(localVertices);
		Eigen::Matrix3d eigenvectors = eig.eigenvectors().rightCols(3);

		Eigen::Matrix3d orientation;
		orientation.col(0) = eigenvectors.col(2);
		orientation.col(1) = eigenvectors.col(1);
		orientation.col(2) = eigenvectors.col(0);

		Eigen::Matrix3d inverseOrientation = orientation.inverse();
		Eigen::Matrix3d inverseTransposedOrientation = orientation.transpose().inverse();
		Eigen::Matrix3d transposedInverseOrientation = inverseOrientation.transpose();
		buw::Vector3d eigenvalues = eig.eigenvalues().transpose();
		
		for(auto vertex : localVertices) {
			auto position = buw::Vector3f(vertex.position[0], vertex.position[1], vertex.position[2]);
			position -= buw::Vector3f(5, 5, 5);
			position = inverseOrientation.cast<float>() * position;
			position += buw::Vector3f(5, 5, 5);
			
			position -= buw::Vector3f(5, 5, 5);
			position = orientation.cast<float>() * position;
			position += buw::Vector3f(5, 5, 5);

			vertices.push_back(buw::VertexPosition3Color3Size1(position, buw::Vector3f(0, 0, 0), 3));
		}

		buw::indexBufferDescription ibd;
		ibd.indexCount = localIndices.size();
		ibd.data = localIndices.data();
		ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
		indexBufferOOBB_ = renderSystem_->createIndexBuffer(ibd);

		// Fill vertex buffer description and create vertex buffer.
		buw::vertexBufferDescription vbd;
		vbd.vertexCount = vertices.size();
		vbd.vertexLayout = buw::VertexPosition3Color3Size1::getVertexLayout();
		vbd.data = vertices.data();
		vertexBufferOOBB_ = renderSystem_->createVertexBuffer(vbd);
	}

	~Viewport()
	{
		depthStencil_ = nullptr;
		viewport_ = nullptr;
		effect_ = nullptr;
		worldBuffer_ = nullptr;
		viewportBuffer_ = nullptr;

		vertexBufferCube_ = nullptr;
		indexBufferCube_ = nullptr;

		vertexBufferOOBB_ = nullptr;
		indexBufferOOBB_ = nullptr;

		vertexBufferXAxis_ = nullptr;
		indexBufferXAxis_ = nullptr;

		vertexBufferYAxis_ = nullptr;
		indexBufferYAxis_ = nullptr;

		vertexBufferZAxis_ = nullptr;
		indexBufferZAxis_ = nullptr;
	
		renderSystem_ = nullptr;
	}

	void paintEvent(QPaintEvent *)
	{
		float color[] = { 0.3f, 0.5f, 0.9f, 0.0f };

		renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);
		renderSystem_->clearDepthStencilView(depthStencil_);

		auto vp = camera_->viewProjectionMatrix();

		updateWorldBuffer();

		// Draw cube.
		effect_->assignVertexBuffer(vertexBufferCube_);
		effect_->assignIndexBuffer(indexBufferCube_);
		effect_->render();

		// Draw reconstructed cube.
		effect_->assignVertexBuffer(vertexBufferOOBB_);
		effect_->assignIndexBuffer(indexBufferOOBB_);
		effect_->render();

		//Draw axis.
		effect_->assignVertexBuffer(vertexBufferXAxis_);
		effect_->assignIndexBuffer(indexBufferXAxis_);
		effect_->render();

		effect_->assignVertexBuffer(vertexBufferYAxis_);
		effect_->assignIndexBuffer(indexBufferYAxis_);
		effect_->render();

		effect_->assignVertexBuffer(vertexBufferZAxis_);
		effect_->assignIndexBuffer(indexBufferZAxis_);
		effect_->render();

		renderSystem_->present();
	}

	void updateWorldBuffer()
	{
		WorldBuffer world;
		world.viewProjection = camera_->viewProjectionMatrix();
		world.projection = camera_->frustum().projectionMatrix();
		world.view = camera_->transformation().viewMatrix();
		world.cam = (camera_->transformation().transformationMatrix() * buw::Vector4f(0, 0, 0, 1)).block<3, 1>(0, 0);
		world.rotation = camera_->transformation().rotationMatrix();

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(WorldBuffer);
		cbd.data = &world;
		worldBuffer_->uploadData(cbd);
	}

	QPaintEngine *paintEngine() const
	{
		return nullptr;
	}

	public Q_SLOTS:
	void drawNextFrame()
	{
		this->repaint();

		QTimer::singleShot(0, this, SLOT(drawNextFrame()));
	}

	

	void mousePressEvent(QMouseEvent *event)
	{
		if(event->buttons()) {
			buw::Vector2f mouse(event->x(), event->y());
			lastMousePos_ = mouse;			
		}
		
		// To avoid continuous rendering.
		repaint();
	}

	void mouseMoveEvent(QMouseEvent *event)
	{
		if(event->buttons()) {
			// Normalize mouse movement
			buw::Vector2f mouse(event->x(), event->y());
			buw::Vector2f delta = lastMousePos_ - mouse;
			delta[0] /= width() / 2.f;
			delta[1] /= height() / -2.f;
			lastMousePos_ = mouse;

			if(event->buttons() & Qt::LeftButton) {
				camera_->transformation().rotation() += buw::Vector3f(-delta.x(), delta.y(), 0);
			}
			else if(event->buttons() & Qt::RightButton) {
			}
		}
		this->repaint();
	}

	void wheelEvent(QWheelEvent *event)
	{
		float factor = pow(1.1, event->delta() / -120.f);
		cameraController_->handleWheel(factor);

		QWidget::wheelEvent(event);

		// To avoid continuous rendering.
		if(!cameraController_->isCameraMoving()) {
			repaint();
		}
	}

	void resizeEvent(QResizeEvent *)
	{
		BLUE_LOG(debug) << "resize";
		if(renderSystem_) {
			renderSystem_->resize(width(), height());

			buw::texture2DDescription dsvTD;
			dsvTD.width = width();
			dsvTD.height = height();
			dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
			dsvTD.data = nullptr;
			dsvTD.useMSAA = true;
			depthStencil_->resize(dsvTD);

			viewport_->resize(buw::viewportDescription(width(), height()));

			camera_->frustum().width(width());
			camera_->frustum().height(height());
		}
	}

private:
	unsigned long lastTick_;
	buw::Vector2f lastMousePos_;
	buw::ReferenceCounted<buw::Camera> camera_;
	buw::ReferenceCounted<buw::CameraController> cameraController_;

	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_, viewportBuffer_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<BoxEffect> effect_;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferCube_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferCube_ = nullptr;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferOOBB_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferOOBB_ = nullptr;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferXAxis_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferXAxis_ = nullptr;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferYAxis_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferYAxis_ = nullptr;

	buw::ReferenceCounted<buw::IVertexBuffer> vertexBufferZAxis_ = nullptr;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBufferZAxis_ = nullptr;
};

#include "DrawBoundingBox.moc"

void runDrawBoundingBoxUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char *argv[] = { const_cast<char*>("DrawBoundingBox.exe") };
	QApplication app(argc, argv);
		
	BlueFramework::Core::initializeLogSystem(false, false);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	// app.exec();
	while(v.isVisible()) {
		app.processEvents();
		v.repaint();
	}
}

TEST(Engine, DrawBoundingBox_Direct3D11)
{
	runDrawBoundingBoxUnitTest(buw::eRenderAPI::Direct3D11);
}
TEST(Engine, DrawBoundingBox_Direct3D12)
{
	runDrawBoundingBoxUnitTest(buw::eRenderAPI::Direct3D12);
}