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

#include "SimpleEffect.h"

#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>
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

class Viewport : public QWidget {
	Q_OBJECT;

public:
	Viewport(const buw::eRenderAPI renderAPI) {
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
		setFocusPolicy(Qt::StrongFocus);

		camera_ = buw::makeReferenceCounted<buw::Camera>();
		camera_->frustum() = buw::CameraFrustum(width(), height(), 0.1f, 1000.f, buw::eProjectionType::Perspective);
		camera_->transformation().offset() = 10;
		camera_->transformation().yaw() = buw::constantsf::pi_over_4();

		buw::renderSystemDescription rsd;
		rsd.width = width();
		rsd.height = height();
		rsd.windowId = (void*)winId();
		rsd.forceWarpDevice = false; 
		rsd.enableMSAA = false;
		rsd.renderAPI = renderAPI;

		renderSystem_ = buw::createRenderSystem(rsd);

		std::stringstream ss;
		ss << "Testbed Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		// Load Images
		auto img1 = buw::loadImage4b("Data/ps.png");

		buw::texture2DDescription td1;
		td1.width = img1.getWidth();
		td1.height = img1.getHeight();
		td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td1.data = img1.getData();

		auto tex1 = renderSystem_->createTexture2D(td1, buw::eTextureBindType::SRV_RTV);

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		buw::texture2DDescription dsvTD;
		dsvTD.width = width();
		dsvTD.height = height();
		dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
		dsvTD.data = nullptr;
		depthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);

		effect_ = buw::makeReferenceCounted<SimpleEffect>(renderSystem_.get(), viewport_, depthStencil_);
		effect_->init();

		effect_->setDiffuse(tex1);
	}

	~Viewport() {
		depthStencil_ = nullptr;
		viewport_ = nullptr;
		effect_ = nullptr;
		renderSystem_ = nullptr;
	}

	void paintEvent(QPaintEvent *) {
		float color[] = { 0.3f, 0.5f, 0.9f, 0.0f };

		renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);
		renderSystem_->clearDepthStencilView(depthStencil_);

		auto vp = camera_->viewProjectionMatrix();
		effect_->setViewProjection(vp);

		effect_->render();
		renderSystem_->present();
	}

	QPaintEngine *paintEngine() const {
		return nullptr;
	}

public Q_SLOTS:
	void drawNextFrame() {
		this->repaint();

		QTimer::singleShot(0, this, SLOT(drawNextFrame()));
	}

	void mousePressEvent(QMouseEvent *event) {
		if (event->buttons()) {
			buw::Vector2f mouse(event->x(), event->y());
			lastMousePos_ = mouse;
		}
	}

	void mouseMoveEvent(QMouseEvent *event) {
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
		this->repaint();
	}

	void wheelEvent(QWheelEvent *event) {
		camera_->transformation().offset() *= pow(1.1, event->delta() / -120);
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

	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
	buw::ReferenceCounted<SimpleEffect> effect_;
};

#include "Testbed.moc"

void runTestbedUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char *argv[] = { const_cast<char*>("Testbed.exe") };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, false);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	// app.exec();
	while (v.isVisible()) {
		app.processEvents();
		v.repaint();
	}
}

TEST(Engine, Testbed_Direct3D11) {
	runTestbedUnitTest(buw::eRenderAPI::Direct3D11);
}
TEST(Engine, Testbed_Direct3D12) {
	runTestbedUnitTest(buw::eRenderAPI::Direct3D12);
}