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

#include "BlueFramework/Rasterizer/Effect.h"
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h>
#include <BlueFramework/Rasterizer/vertex.h>

#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

class SimpleEffect : public buw::Effect {
public:
	SimpleEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport) : Effect(renderSystem), viewport_(viewport) {
	}

private:
	void v_init() {
		std::vector<buw::VertexPosition3> vertices;
		vertices.push_back(buw::VertexPosition3(buw::Vector3f(-0.75f, -0.75f, 0.0f)));
		vertices.push_back(buw::VertexPosition3(buw::Vector3f(0.75f, -0.75f, 0.0f)));
		vertices.push_back(buw::VertexPosition3(buw::Vector3f(0.75f, 0.75f, 0.0f)));

		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices[0];
		vbd.vertexCount = static_cast<int>(vertices.size());
		vbd.vertexLayout = vertexLayout;
		vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
		        
		buw::pipelineStateDescription psd;
		psd.effectFilename = "Shader/simple.be";
		psd.pipelineStateName = "";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = false;

		pipelineState_ = createPipelineState(psd);
	}

	void v_render() {
		setViewport(viewport_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, nullptr);

		setPipelineState(pipelineState_);
		setVertexBuffer(vertexBuffer_);
		draw(3);
	}

private:
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
};

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
		ss << "Draw Triangle Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		effect_ = buw::makeReferenceCounted<SimpleEffect>(renderSystem_.get(), viewport_);
		effect_->init();

		drawNextFrame();
	}

	~Viewport() {
        effect_ = nullptr;
        viewport_ = nullptr;
		renderSystem_ = nullptr; // render system always last, s.t. the other modules can still access it on destruction.
	}

	void paintEvent(QPaintEvent*) {
		float color[] = {0.3f, 0.5f, 0.9f, 0.0f};

		renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);

		effect_->render();

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

	void resizeEvent(QResizeEvent *) {
		if (renderSystem_ && false) {
			renderSystem_->resize(width(), height());
			
			viewport_->resize(buw::viewportDescription(width(), height()));
		}
	}

private:
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<SimpleEffect> effect_;
	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
};

#include "DrawTriangle.moc"

void runDrawTriangleUnitTest(const buw::eRenderAPI renderAPI) {
	int argc = 1;
	char* argv[] = {const_cast<char*>("DrawTriangle.exe")};
	QApplication app(argc, argv);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, DrawTriangle_Direct3D11) {
	runDrawTriangleUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, DrawTriangle_Direct3D12) {
	runDrawTriangleUnitTest(buw::eRenderAPI::Direct3D12);
}

TEST(Engine, DrawTriangle_OpenGL) {
	runDrawTriangleUnitTest(buw::eRenderAPI::OpenGL);
}
