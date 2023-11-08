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

#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Core/memory.h>

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QThread>

#include <gtest/gtest.h>

class Viewport : public QWidget {
	Q_OBJECT;

public:
	Viewport(const buw::eRenderAPI renderAPI) {
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
		setFocusPolicy(Qt::StrongFocus);

		buw::renderSystemDescription rsd;
		rsd.width = width();
		rsd.height = height();
		rsd.windowId = (void*)winId();
		rsd.renderAPI = renderAPI;

		renderSystem_ = buw::createRenderSystem(rsd);

		std::stringstream ss;
		ss << "Clear Screen Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		drawNextFrame();
	}

	~Viewport() {
		renderSystem_ = nullptr;
	}

	void paintEvent(QPaintEvent *) {
		float color[] = { 0.3f, 0.5f, 0.9f, 1.0f };

		renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);

		renderSystem_->present();
	}

	QPaintEngine* paintEngine() const {
		return nullptr;
	}

public Q_SLOTS:
	void drawNextFrame() {
		repaint();

		QThread::msleep(2);
		QTimer::singleShot(0, this, SLOT(drawNextFrame()));
	}

private:
	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
};

#include "ClearScreen.moc"

void runClearScreenUnitTest(const buw::eRenderAPI renderAPI) {
	int argc = 1;
	char* argv[] = {const_cast<char*>("ClearScreen.exe")};
	QApplication app(argc, argv);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, ClearScreen_Direct3D11) {
	runClearScreenUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, ClearScreen_Direct3D12) {
	runClearScreenUnitTest(buw::eRenderAPI::Direct3D12);
}

TEST(Engine, ClearScreen_OpenGL) {
	runClearScreenUnitTest(buw::eRenderAPI::OpenGL);
}
