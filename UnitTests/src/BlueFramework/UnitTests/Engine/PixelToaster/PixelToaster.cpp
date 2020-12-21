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

#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

class DrawBackbufferEffect : public buw::Effect {
public:
	DrawBackbufferEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport) : Effect(renderSystem), viewport_(viewport) {
	}

	~DrawBackbufferEffect()
	{
		pipelineState_ = nullptr;
		sampler_ = nullptr;
		indexBuffer_ = nullptr;
		vertexBuffer_ = nullptr;
		viewport_ = nullptr;
	}

	void setAlbedoTexture(buw::ReferenceCounted<buw::ITexture2D> texture) {
		BLUE_ASSERT(texture != nullptr, "Not assuming a nullptr texture.");
		texture_ = texture;
	}

private:
	void v_init() {
		std::vector<buw::VertexPosition3Texture2> vertices;
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(1.0f, -1.0f, 0.0f), buw::Vector2f(1.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(1.0f, 1.0f, 0.0f), buw::Vector2f(1.0f, 1.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(-1.0f, -1.0f, 0.0f), buw::Vector2f(0.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(-1.0f, 1.0f, 0.0f), buw::Vector2f(0.0f, 1.0f)));

		buw::VertexLayout vertexLayout = buw::VertexPosition3Texture2::getVertexLayout();

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices[0];
		vbd.vertexCount = static_cast<int>(vertices.size());
		vbd.vertexLayout = vertexLayout;
		vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
		        
		std::vector<std::uint16_t> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);

		buw::indexBufferDescription ibd;
		ibd.format = buw::eIndexBufferFormat::UnsignedInt16;
		ibd.data = &indices[0];
		ibd.indexCount = indices.size();
		indexBuffer_ = renderSystem()->createIndexBuffer(ibd);

		buw::pipelineStateDescription psd;
		psd.effectFilename = "Shader/simple.be";
		psd.pipelineStateName = "";
		psd.vertexLayout = vertexLayout;
		psd.primitiveTopology = buw::ePrimitiveTopology::TriangleStrip;
		psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB };
		psd.useDepth = false;
		psd.cullMode = buw::eCullMode::None;

		pipelineState_ = createPipelineState(psd);

		buw::samplerStateDescription ssd = { buw::eFilter::Linear };
		sampler_ = renderSystem()->createSampler(ssd);
	}

	void v_render() {
		setViewport(viewport_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, nullptr);

		setPipelineState(pipelineState_);
		setVertexBuffer(vertexBuffer_);
		setIndexBuffer(indexBuffer_);
		setSampler(sampler_, "sampler_");
		setTexture(texture_, "texDiffuseMap");

		drawIndexed(4);
	}

private:
	buw::ReferenceCounted<buw::ITexture2D> texture_;

	buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;
};

class Viewport : public QWidget {
	Q_OBJECT;

public:
	Viewport(const buw::eRenderAPI renderAPI) : backBuffer_(0,0) {
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
		ss << "PixelToaster Unit Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());

		viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

		effect_ = buw::makeReferenceCounted<DrawBackbufferEffect>(renderSystem_.get(), viewport_);
		effect_->init();

		drawNextFrame();

		createBackbuffer();
		
		
	}

	~Viewport() {
		effect_ = nullptr;
		backbufferTexture_ = nullptr;
		viewport_ = nullptr;
		renderSystem_ = nullptr;
	}

	void paintEvent(QPaintEvent*) {
		float color[] = {0.3f, 0.5f, 0.9f, 0.0f};

		renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);

		for (int x = 0; x < backBuffer_.getWidth(); x++)
		{
			for (int y = 0; y < backBuffer_.getHeight(); y++)
			{
				backBuffer_.setPixelColor(x, y, buw::Color4b(rand() % 255, rand() % 255, rand() % 255, 255));
			}
		}

		effect_->setAlbedoTexture(backbufferTexture_);
		renderSystem_->uploadTexture(backbufferTexture_, backBuffer_);
		effect_->render();

		renderSystem_->present();
	}

	QPaintEngine* paintEngine() const {
		return nullptr;
	}

	void createBackbuffer()
	{
		buw::texture2DDescription t2d;
		t2d.width = this->width();
		t2d.height = this->height();
		t2d.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;
		t2d.data = nullptr;
		t2d.isCpuWriteable = true;

		backbufferTexture_ = renderSystem_->createTexture2D(t2d, buw::eTextureBindType::SRV);

		backBuffer_.resize(width(), height());
	}

	void setPixelColor(const int x, const int y, const buw::Vector4f& color)
	{
		std::uint8_t r = static_cast<std::uint8_t>(std::min(color.x() * 255, 255.0f));
		std::uint8_t g = static_cast<std::uint8_t>(std::min(color.y() * 255, 255.0f));
		std::uint8_t b = static_cast<std::uint8_t>(std::min(color.z() * 255, 255.0f));
		std::uint8_t a = static_cast<std::uint8_t>(std::min(color.w() * 255, 255.0f));

		backBuffer_.setPixelColor(x, y, buw::Color4b(r, g, b, a));
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

		createBackbuffer();
	}

private:
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<DrawBackbufferEffect> effect_;
	buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;

	buw::Image4b backBuffer_;
	buw::ReferenceCounted<buw::ITexture2D>	backbufferTexture_;

};

#include "PixelToaster.moc"

void runPixelToasterUnitTest(const buw::eRenderAPI renderAPI) {
	int argc = 1;
	char* argv[] = {const_cast<char*>("PixelToaster.exe")};
	QApplication app(argc, argv);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

 TEST(Engine, PixelToaster_Direct3D11) {
 	runPixelToasterUnitTest(buw::eRenderAPI::Direct3D11);
 }

 TEST(Engine, PixelToaster_Direct3D12) {
 	runPixelToasterUnitTest(buw::eRenderAPI::Direct3D12);
 }