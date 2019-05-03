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

#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/IConstantBuffer.h>
#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>
#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>
#include <BlueFramework/Engine/ViewCube/ViewCube.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Rasterizer/util.h>
#include <BlueFramework/Rasterizer/vertex.h>

#include "SimpleEffect.h"

#include <QApplication>
#include <QMouseEvent>
#include <QThread>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>

#include <gtest/gtest.h>

#include <chrono>

struct WorldBuffer {
	buw::Matrix44f viewProjection;
	buw::Matrix44f projection;
	buw::Matrix44f view;
	buw::Matrix44f rotation;
	buw::Vector3f cam;
};

const std::map<int, buw::CameraController::eKey> keyMap = {
  {Qt::Key_W, buw::CameraController::eKey::MoveForward}, {Qt::Key_S, buw::CameraController::eKey::MoveBackward}, {Qt::Key_D, buw::CameraController::eKey::MoveRight},
  {Qt::Key_A, buw::CameraController::eKey::MoveLeft},    {Qt::Key_Q, buw::CameraController::eKey::MoveUp},       {Qt::Key_E, buw::CameraController::eKey::MoveDown},
  {Qt::Key_1, buw::CameraController::eKey::ViewForward}, {Qt::Key_3, buw::CameraController::eKey::ViewBackward}, {Qt::Key_4, buw::CameraController::eKey::ViewRight},
  {Qt::Key_6, buw::CameraController::eKey::ViewLeft},    {Qt::Key_7, buw::CameraController::eKey::ViewUp},       {Qt::Key_9, buw::CameraController::eKey::ViewDown},
};

class Viewport : public QWidget {
	Q_OBJECT;

public:
	Viewport(const buw::eRenderAPI renderAPI) : cpuReadBuffer_(1, 1) {
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
		setFocusPolicy(Qt::StrongFocus);
		setMouseTracking(true);

		camera_ = buw::makeReferenceCounted<buw::Camera>();
		camera_->frustum() = buw::CameraFrustum(width(), height(), 0.01f, 1000.f, buw::eProjectionType::Perspective);
		camera_->transformation().offset() = 10;
		camera_->transformation().yaw() = buw::constantsf::pi_over_4();
		cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);
		// uncomment following line for free navigation via WASD
		//cameraController_->setState(buw::CameraController::eState::Free);

		buw::renderSystemDescription rsd;
		rsd.width = width();
		rsd.height = height();
		rsd.windowId = (void*)winId();
		rsd.enableMSAA = true;
		rsd.forceWarpDevice = false;
		rsd.renderAPI = renderAPI;

		renderSystem_ = buw::createRenderSystem(rsd);

		// create stuff
		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		buw::texture2DDescription dsvTD;
		dsvTD.width = width();
		dsvTD.height = height();
		dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
		dsvTD.data = nullptr;
		dsvTD.isCpuReadable = false;
		dsvTD.useMSAA = rsd.enableMSAA;
		depthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

		dsvTD.useMSAA = false;
		pickDepthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

		buw::texture2DDescription pbTD;
		pbTD.width = width();
		pbTD.height = height();
		pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
		pbTD.data = nullptr;
		pbTD.isCpuReadable = true;
		pbTD.useMSAA = false;
		pickBuffer_ = renderSystem_->createTexture2D(pbTD, buw::eTextureBindType::RTV);

		buw::constantBufferDescription cbd1;
		cbd1.sizeInBytes = sizeof(WorldBuffer);
		cbd1.data = nullptr;
		worldBuffer_ = renderSystem_->createConstantBuffer(cbd1);

		viewCube_ = buw::makeReferenceCounted<buw::ViewCube>(renderSystem_, pickBuffer_, nullptr, cameraController_);

		// Load Images
		auto img1 = buw::loadImage4b("Data/ps.png");

		buw::texture2DDescription td1;
		td1.width = img1.getWidth();
		td1.height = img1.getHeight();
		td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td1.data = img1.getData();

		auto tex1 = renderSystem_->createTexture2D(td1, buw::eTextureBindType::SRV_RTV);

		effect_ = buw::makeReferenceCounted<SimpleEffect>(renderSystem_.get(), viewport_, depthStencil_);
		effect_->init();

		effect_->setDiffuse(tex1);

		lastTick_ = std::chrono::high_resolution_clock::now().time_since_epoch();

		std::stringstream ss;
		ss << "ViewCube Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		drawNextFrame();
	}

	~Viewport() {
		depthStencil_ = nullptr;
		pickDepthStencil_ = nullptr;

		viewport_ = nullptr;
		viewCube_ = nullptr;
		effect_ = nullptr;
		pickBuffer_ = nullptr;
		worldBuffer_ = nullptr;
		renderSystem_ = nullptr;
		camera_ = nullptr;
		cameraController_ = nullptr;
	}

	void paintEvent(QPaintEvent *) {
		std::chrono::nanoseconds current = std::chrono::high_resolution_clock::now().time_since_epoch();
		float delta = (float)((current - lastTick_).count() * std::chrono::nanoseconds::period::num / (double)std::chrono::nanoseconds::period::den);
		cameraController_->tick(delta);
		camera_->tick(delta);
		updateWorldBuffer();

		// std::cout << "Rendering." << std::endl;
		renderSystem_->clearRenderTargets({renderSystem_->getBackBufferTarget(), pickBuffer_});
		renderSystem_->clearDepthStencilView(depthStencil_);
		renderSystem_->clearDepthStencilView(pickDepthStencil_);

		auto vp = camera_->viewProjectionMatrix();
		effect_->setViewProjection(vp);

		effect_->render();
		viewCube_->render();

		renderSystem_->present();
		lastTick_ = current;
	}

	void Viewport::updateWorldBuffer() {
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

	QPaintEngine *paintEngine() const {
		return nullptr;
	}

public Q_SLOTS:
	void drawNextFrame() {
		repaint();

		QTimer::singleShot(0, this, SLOT(drawNextFrame()));
	}

	void mousePressEvent(QMouseEvent *event) {
		if (event->buttons()) {
			buw::Vector2f mouse(event->x(), event->y());
			lastMousePos_ = mouse;
			// camera_->orbitCamera(M_PI);
			viewCube_->mousePress();
		}
	}

	void mouseMoveEvent(QMouseEvent *event) {
		viewCube_->mouseMove(event->x(), event->y());

		if (event->buttons()) {
			// Normalize mouse movement
			buw::Vector2f mouse(event->x(), event->y());
			buw::Vector2f delta = lastMousePos_ - mouse;
			delta[0] /= width() / 2.f;
			delta[1] /= height() / -2.f;
			lastMousePos_ = mouse;
			if (event->buttons() & Qt::LeftButton) {
				camera_->transformation().rotation() += buw::Vector3f(-delta.x(), delta.y(), 0);
			} else if (event->buttons() & Qt::RightButton) {
			}
		}

		repaint();
	}

	void wheelEvent(QWheelEvent *event) {
		if (cameraController_->getState() == buw::CameraController::eState::Orbiting) {
			camera_->transformation().offset() *= pow(1.1, event->delta() / -120);
		} else {
			float factor = pow(1.1, event->delta() / -120.f);
			cameraController_->handleWheel(factor);
		}

		repaint();
	}

	void keyPressEvent(QKeyEvent *event) {
		if (!event->isAutoRepeat()) {
			if (keyMap.find(event->key()) != keyMap.end()) {
				buw::CameraController::eKey key = keyMap.at(event->key());
				cameraController_->handleKeyDown(key);
			}
		}
	}

	void keyReleaseEvent(QKeyEvent *event) {
		if (!event->isAutoRepeat()) {
			if (keyMap.find(event->key()) != keyMap.end()) {
				buw::CameraController::eKey key = keyMap.at(event->key());
				cameraController_->handleKeyUp(key);
			}
		}
	}
	
	void resizeEvent(QResizeEvent *) {
		BLUE_LOG(debug) << "resize";
		if (renderSystem_) {
			renderSystem_->resize(width(), height());

			buw::texture2DDescription dsvTD;
			dsvTD.width = width();
			dsvTD.height = height();
			dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
			dsvTD.data = nullptr;
			dsvTD.isCpuReadable = false;
			dsvTD.useMSAA = renderSystem_->getMSAAEnabled();
			depthStencil_->resize(dsvTD);

			dsvTD.useMSAA = false;
			pickDepthStencil_->resize(dsvTD);

			buw::texture2DDescription pbTD;
			pbTD.width = width();
			pbTD.height = height();
			pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
			pbTD.data = nullptr;
			pbTD.isCpuReadable = true;
			pbTD.useMSAA = false;
			pickBuffer_->resize(pbTD);

			viewport_->resize(buw::viewportDescription(width(), height()));
			viewCube_->resize(buw::viewportDescription(width(), height()));

			camera_->frustum().width(width());
			camera_->frustum().height(height());
		}
	}

private:
	std::chrono::nanoseconds lastTick_;
	buw::Vector2f lastMousePos_;
	buw::ReferenceCounted<buw::Camera> camera_;
	buw::ReferenceCounted<buw::CameraController> cameraController_;
	buw::ReferenceCounted<buw::ViewCube> viewCube_;
	buw::ReferenceCounted<SimpleEffect> effect_;
	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::IViewport> viewCubeViewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<buw::ITexture2D> pickBuffer_;
	buw::ReferenceCounted<buw::ITexture2D> pickDepthStencil_;
	buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;
	buw::Image4b cpuReadBuffer_;
};

#include "ViewCubeTest.moc"

void runViewCubeUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char *argv[] = { "ViewCube.exe" };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, true);
	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

// TEST(Engine, ViewCube_Direct3D11) {
// 	runViewCubeUnitTest(buw::eRenderAPI::Direct3D11);
// }

TEST(Engine, ViewCube_Direct3D12) {
	runViewCubeUnitTest(buw::eRenderAPI::Direct3D12);
}