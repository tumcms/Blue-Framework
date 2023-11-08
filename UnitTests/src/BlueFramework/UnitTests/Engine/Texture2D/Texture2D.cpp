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

#include <BlueFramework/Rasterizer/Effect.h>
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>

#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

class PositionTextureEffect : public buw::Effect {
public:
	PositionTextureEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport) : Effect(renderSystem), viewport_(viewport) {
	}

    ~PositionTextureEffect() {
        sampler_ = nullptr;
        texture_ = nullptr;
        viewport_ = nullptr;
        pipelineState_ = nullptr;
        vertexBuffer_ = nullptr;
    }

private:
	void v_init() {
		BLUE_LOG(trace) << "Creating Shaders...";
		std::vector<buw::VertexPosition3Texture2> vertices;
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(-0.8f, -0.8f, 0.0f), buw::Vector2f(0.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(0.8f, -0.8f, 0.0f), buw::Vector2f(1.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(0.0f, 0.8f, 0.0f), buw::Vector2f(0.5f, 0.5f)));

		buw::VertexLayout const& vertexLayout = buw::VertexPosition3Texture2::getVertexLayout();

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices[0];
		vbd.vertexCount = static_cast<int>(vertices.size());
		vbd.vertexLayout = vertexLayout;
		vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
		        
		pipelineState_ = createPipelineState(buw::pipelineStateDescription(
		    "Shader/positionTexture.be",
		    "",
			vertexLayout,
		    buw::ePrimitiveTopology::TriangleList,
		    { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
		    false, false)
		);

		buw::samplerStateDescription ssd = { buw::eFilter::Linear };
		sampler_ = renderSystem()->createSampler(ssd);

		// load texture
		auto img1 = buw::loadImage4b("Data/ps.png");

		buw::texture2DDescription td1;
		td1.width = img1.getWidth();
		td1.height = img1.getHeight();
		td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td1.data = img1.getData();

		texture_ = renderSystem()->createTexture2D(td1, buw::eTextureBindType::SRV);
	}

	void v_render() {
		setViewport(viewport_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, nullptr);

		setPipelineState(pipelineState_);
		setSampler(sampler_, "sampler_");
		setTexture(texture_, "texDiffuseMap");
				
		setVertexBuffer(vertexBuffer_);
		draw(3);
	}

private:
	buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::ITexture2D> texture_;
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
		ss << "Texture2D Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		effect_ = buw::makeReferenceCounted<PositionTextureEffect>(renderSystem_.get(), viewport_);
		effect_->init();

		drawNextFrame();
	}

	~Viewport() {
        effect_ = nullptr;
        viewport_ = nullptr;
		renderSystem_ = nullptr;
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
		if (renderSystem_) {
			renderSystem_->resize(width(), height());
			
			viewport_->resize(buw::viewportDescription(width(), height()));
		}
	}

private:
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<PositionTextureEffect> effect_;
	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
};

#include "Texture2D.moc"

void runTexture2DUnitTest(const buw::eRenderAPI renderAPI) {
	int argc = 1;
	char* argv[] = { const_cast<char*>("Texture2D.exe") };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, true);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, Texture2D_Direct3D11) {
	runTexture2DUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, Texture2D_Direct3D12) {
	runTexture2DUnitTest(buw::eRenderAPI::Direct3D12);
}

TEST(Engine, Texture2D_OpenGL) {
	runTexture2DUnitTest(buw::eRenderAPI::OpenGL);
}
