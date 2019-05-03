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
#include <BlueFramework/D3D12RenderSystem/D3D12RenderSystem.h>

#include <BlueFramework/Core/memory.h>
#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>
#include <BlueFramework/Engine/ViewCube/ViewCube.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/Rasterizer/util.h>

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
    Viewport(const buw::eRenderAPI renderAPI) : cpuReadBuffer_(1, 1) {
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_MSWindowsUseDirect3D, true);
        setFocusPolicy(Qt::StrongFocus);

        camera_ = buw::makeReferenceCounted<buw::Camera>();
        cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);
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
		ss << "Copy Texture Region Test (" << renderSystem_->getName() << ")";
		setWindowTitle(ss.str().c_str());
		
        // create stuff
        viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

        buw::texture2DDescription dsvTD;
        dsvTD.width = width();
        dsvTD.height = height();
        dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
        dsvTD.data = nullptr;
        dsvTD.isCpuReadable = true;
        dsvTD.useMSAA = rsd.enableMSAA;
        depthStencil_ = renderSystem_->createTexture2D(dsvTD, buw::eTextureBindType::DSV);
        
        buw::texture2DDescription pbTD;
        pbTD.width = width();
        pbTD.height = height();
        pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
        pbTD.data = nullptr;
        pbTD.isCpuReadable = true;
        pbTD.useMSAA = false;
        pickBuffer_ = renderSystem_->createTexture2D(pbTD, buw::eTextureBindType::RTV);

        effect_ = buw::makeReferenceCounted<buw::Effect>(renderSystem_.get());

        effect_->init();
        
        buw::pipelineStateDescription psd;
		psd.effectFilename = "Shader/simple.be";
        psd.cullMode = buw::eCullMode::None;
        psd.fillMode = buw::eFillMode::Solid;
        psd.primitiveTopology = buw::ePrimitiveTopology::TriangleList;
        psd.vertexLayout = buw::VertexPosition3::getVertexLayout();
        psd.renderTargetFormats = { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB,buw::eTextureFormat::R32_UnsignedInt };
        psd.useDepth = true;
        psd.useMSAA = rsd.enableMSAA;

        pipelineState_ = effect_->createPipelineState(psd);

        std::vector<buw::VertexPosition3> vertices;
		vertices.push_back(buw::VertexPosition3(buw::Vector3f(0.75f, -0.75f, 0.0f)));
        vertices.push_back(buw::VertexPosition3(buw::Vector3f(-0.75f, -0.75f, 0.0f)));
		vertices.push_back(buw::VertexPosition3(buw::Vector3f(0.75f, 0.75f, 0.0f)));

        buw::VertexLayout vertexLayout;
        vertexLayout.add(buw::eVertexAttributeSemantic::Position, buw::eVertexAttributeFormat::Float3);

        buw::vertexBufferDescription vbd;
        vbd.data = &vertices[0];
        vbd.vertexCount = static_cast<int>(vertices.size());
        vbd.vertexLayout = vertexLayout;
        vertexBuffer_ = renderSystem_->createVertexBuffer(vbd);
     }

    ~Viewport() {
		vertexBuffer_ = nullptr;
		pipelineState_ = nullptr;
		effect_ = nullptr;
		depthStencil_ = nullptr;
		pickBuffer_ = nullptr;
		viewport_ = nullptr;
		renderSystem_ = nullptr;
		camera_ = nullptr;
    }

    void paintEvent(QPaintEvent *) {
        float black[4] = { 0, 0.0f, 0.0f, 1 };
        renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), black);
        renderSystem_->clearRenderTarget(pickBuffer_, black);
        renderSystem_->clearDepthStencilView(depthStencil_);

        effect_->preRender();
        effect_->setPipelineState(pipelineState_);
        effect_->setRenderTargets({ renderSystem_->getBackBufferTarget(),pickBuffer_ }, depthStencil_);
        effect_->setVertexBuffer(vertexBuffer_);
        effect_->setViewport(viewport_);
        effect_->draw(UINT(vertexBuffer_->getVertexCount()));
        effect_->postRender();

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
		
        if (true) {
            buw::Image4b depthStencilImage(width(), height());
            renderSystem_->downloadTexture(depthStencil_, depthStencilImage, 0, 0);
            buw::Color4b depthStencilColor = depthStencilImage.getPixelColor(event->x(), event->y());
            float depth;
            buw::convertD24ToF32(&depthStencilColor[0], depth);
            BLUE_LOG(info) << "Depth: " << std::to_string(depth);
        }

        if (true) {
            buw::Image4b backBufferImage(1, 1);
            buw::ReferenceCounted<buw::ITexture2D> backBuffer = renderSystem_->getBackBufferTarget();
            if (!backBuffer->isCPUReadable()) {
                backBuffer->makeCPUReadable();
            }
            renderSystem_->downloadTexture(backBuffer, backBufferImage, event->x(), event->y());
            buw::Color4b backBufferColor = backBufferImage.getPixelColor(0, 0);
            BLUE_LOG(info) << "BackBuffer: (" << std::to_string(backBufferColor[0]) << "," << std::to_string(backBufferColor[1]) << "," << std::to_string(backBufferColor[2]) << ")";
            //BLUE_LOG(info) << "Red:   " << std::to_string(backBufferColor[0]);
            //BLUE_LOG(info) << "Green: " << std::to_string(backBufferColor[1]);
            //BLUE_LOG(info) << "Blue:  " << std::to_string(backBufferColor[2]);
        }

        if(true) {
            buw::Image4b pickBufferImage(1, 1);
            renderSystem_->downloadTexture(pickBuffer_, pickBufferImage, event->x(), event->y());
            uint pickId = *(uint*)pickBufferImage.getData();
            BLUE_LOG(info) << "PickId: (" << std::to_string(pickId) << ")";
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
            }
            else if (event->buttons() & Qt::RightButton) {
            }
        }
        this->repaint();
    }
          
    void resizeEvent(QResizeEvent *)
    {
        BLUE_LOG(debug) << "resize";
        if (renderSystem_)
        {
            renderSystem_->resize(width(), height());

            buw::texture2DDescription dsvTD;
            dsvTD.width = width();
            dsvTD.height = height();
            dsvTD.format = buw::eTextureFormat::D24_UnsignedNormalizedInt_S8_UnsignedInt;
            dsvTD.data = nullptr;
            dsvTD.isCpuReadable = true;
            dsvTD.useMSAA = renderSystem_->getMSAAEnabled();
            depthStencil_->resize(dsvTD);

            buw::texture2DDescription pbTD;
            pbTD.width = width();
            pbTD.height = height();
            pbTD.format = buw::eTextureFormat::R32_UnsignedInt;
            pbTD.data = nullptr;
            pbTD.isCpuReadable = true;
            pbTD.useMSAA = false;
            pickBuffer_->resize(pbTD);

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
    buw::ReferenceCounted<buw::Effect> effect_;
    buw::ReferenceCounted<buw::IPipelineState> pipelineState_;
    buw::ReferenceCounted<buw::IVertexBuffer> vertexBuffer_;
    buw::ReferenceCounted<buw::ViewCube> viewCube_;

    buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
    buw::ReferenceCounted<buw::IViewport> viewport_;
    buw::ReferenceCounted<buw::ITexture2D> depthStencil_;
    buw::ReferenceCounted<buw::ITexture2D> pickBuffer_;
    buw::Image4b cpuReadBuffer_;
};

#include "CopyTextureRegion.moc"

void runCopyTextureRegionUnitTest(const buw::eRenderAPI renderAPI) {
	int argc = 1;
	char* argv[] = { "CopyTextureRegion.exe" };
	BlueFramework::Core::initializeLogSystem(false, true);

	QApplication app(argc, argv);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();
	app.exec();
}

TEST(Engine, CopyTextureRegion_Direct3D11) {
	runCopyTextureRegionUnitTest(buw::eRenderAPI::Direct3D11);
}

TEST(Engine, CopyTextureRegion_Direct3D12) {
	runCopyTextureRegionUnitTest(buw::eRenderAPI::Direct3D12);
}