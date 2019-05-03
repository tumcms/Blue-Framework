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

#include "BlueFramework/Rasterizer/Effect.h"
#include <BlueFramework/Core/memory.h>
#include <BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h>
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

		pipelineState_ = createPipelineState(buw::pipelineStateDescription(
			"Shader/ColorRamp.be",
			"",
			vertexLayout,
			buw::ePrimitiveTopology::TriangleList,
			{ buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
			false, false));

		buw::samplerStateDescription ssd = { buw::eFilter::Linear };
		sampler_ = renderSystem()->createSampler(ssd);

		// load texture
		auto img1 = buw::loadImage4b("Data/GradientRamp.png");

		buw::texture1DDescription td1;
		td1.width = img1.getWidth();
		td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		td1.data = img1.getData();

		texture_ = renderSystem()->createTexture1D(td1, buw::eTextureBindType::SRV);
	}

	void v_render() {
		setViewport(viewport_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, nullptr);

		setPipelineState(pipelineState_);
		setSampler(sampler_, "sampler_");
		setTexture(texture_, "colorRamp");

		setVertexBuffer(vertexBuffer_);
		draw(3);
	}

private:
	buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::ITexture1D> texture_;
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
		ss << "Texture1D Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		effect_ = buw::makeReferenceCounted<PositionTextureEffect>(renderSystem_.get(), viewport_);
		effect_->init();

		drawNextFrame();
	}

	~Viewport() {
		effect_ = nullptr;
		viewport_ = nullptr;
		renderSystem_ = nullptr; // Rendersystem always last, s.t. the other modules can still access it on destruction.
	}

	void paintEvent(QPaintEvent*) {
		float color[] = { 0.3f, 0.5f, 0.9f, 0.0f };

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

#include "Texture1D.moc"

void runTexture1DUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char* argv[] = { "Texture1D.exe" };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, true);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, Texture1D_Direct3D11) {
	runTexture1DUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, Texture1D_Direct3D12) {
	runTexture1DUnitTest(buw::eRenderAPI::Direct3D12);
}

TEST(Engine, Texture1D_OpenGL) {
	runTexture1DUnitTest(buw::eRenderAPI::OpenGL);
}
