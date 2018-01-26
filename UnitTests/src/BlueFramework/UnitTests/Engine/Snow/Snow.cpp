/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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
#include <BlueFramework/Core/Stopwatch.h>
//#include <BlueFramework/Rasterizer/>

#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

class PositionTextureEffect : public buw::Effect {
public:
	struct ShaderVaribales {
		BlueFramework::Rasterizer::Unaligned::Float2 resolution;
		BlueFramework::Rasterizer::Unaligned::Float2 mouse;
		BlueFramework::Rasterizer::Unaligned::Float time; float p31, p32, p33;
	};

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
		std::vector<buw::VertexPosition3Texture2> vertices;
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(-1.0f, -1.0f, 0.0f), buw::Vector2f(0.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(1.0f, -1.0f, 0.0f), buw::Vector2f(1.0f, 0.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(-1.0f, 1.0f, 0.0f), buw::Vector2f(0.0f, 1.0f)));
		vertices.push_back(buw::VertexPosition3Texture2(buw::Vector3f(1.0f, 1.0f, 0.0f), buw::Vector2f(1.0f, 1.0f)));

		buw::VertexLayout vertexLayout;
		vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);
		vertexLayout.add(buw::eVertexAttributeSemantic::Uv, buw::eVertexAttributeFormat::Float2);

		buw::vertexBufferDescription vbd;
		vbd.data = &vertices[0];
		vbd.vertexCount = static_cast<int>(vertices.size());
		vbd.vertexLayout = vertexLayout;
		vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);
		        
		pipelineState_ = createPipelineState(buw::pipelineStateDescription(
		    "Shader/positionTexture.be",
			"",
		    vertexLayout,
		    buw::ePrimitiveTopology::TriangleStrip,
		    { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
		    false, false)
		);

		std::vector<std::uint32_t> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);

		buw::indexBufferDescription ibd;
		ibd.data = &indices[0];
		ibd.format = buw::eIndexBufferFormat::UnsignedInt32;
		ibd.indexCount = 4;
		indexBuffer_ = renderSystem()->createIndexBuffer(ibd);

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

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(ShaderVaribales);
		cbd.data = nullptr;
		constantBuffer_ = renderSystem()->createConstantBuffer(cbd);
        lastTick_ = std::chrono::high_resolution_clock::now().time_since_epoch();
	}

	void v_render() {
        std::chrono::nanoseconds current = std::chrono::high_resolution_clock::now().time_since_epoch();
        //float delta = (float)((current - lastTick_).count() * std::chrono::nanoseconds::period::num / (double)std::chrono::nanoseconds::period::den);
        //lastTick_ = current;
		setViewport(viewport_);

		buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
		setRenderTarget(renderTarget, nullptr);

		setPipelineState(pipelineState_);

		ShaderVaribales buffer;
        long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(current - lastTick_).count();
        float s = ms / 1000;
        s += (float)(ms % 1000) / 1000.0f;
        buffer.time = s;
		buffer.resolution = buw::Vector2f(1.0f,1.0f);
		buffer.mouse = buw::Vector2f(0.5f, 0.5f);

		buw::constantBufferDescription cbd;
		cbd.sizeInBytes = sizeof(ShaderVaribales);
		cbd.data = &buffer;
		constantBuffer_->uploadData(cbd);
        setConstantBuffer(constantBuffer_, "ShaderVariables");

		//setSampler(sampler_, "sampler_");
		//setTexture(texture_, "texDiffuseMap");
				
		setIndexBuffer(indexBuffer_);
		setVertexBuffer(vertexBuffer_);
		drawIndexed(4);
	}

private:
    std::chrono::nanoseconds lastTick_;
    buw::ReferenceCounted<buw::ISampler> sampler_;
	buw::ReferenceCounted<buw::ITexture2D> texture_;
	buw::ReferenceCounted<buw::IConstantBuffer> constantBuffer_;
	buw::ReferenceCounted<buw::IViewport> viewport_;
	buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
	buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
	buw::ReferenceCounted<buw::IIndexBuffer> indexBuffer_;
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
		ss << "Snow Unit Test (" << renderSystem_->getName() << ")";
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

#include "Snow.moc"

void runSnowUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char* argv[] = { "Snow.exe" };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, true);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, Snow_Direct3D11) {
	runSnowUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, Snow_Direct3D12) {
	runSnowUnitTest(buw::eRenderAPI::Direct3D12);
}