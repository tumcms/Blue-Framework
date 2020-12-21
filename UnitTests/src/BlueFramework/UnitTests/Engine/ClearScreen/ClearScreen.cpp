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
