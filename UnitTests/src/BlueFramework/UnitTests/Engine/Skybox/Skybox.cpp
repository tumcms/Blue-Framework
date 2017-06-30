/*
This file is part of BlueFramework, a simple 3D engine.
Copyright (c) 2016-2017 Technical University of Munich
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
#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IIndexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IConstantBuffer.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/Resources/ITextureCube.h>
#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>

#include <BlueFramework/Rasterizer/vertex.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/Engine/ResourceManagment/download.h>
#include <BlueFramework/Engine/Camera/Camera.h>
#include <BlueFramework/Engine/Mesh/geometryGeneration.h>

#include <BlueFramework/Core/Stopwatch.h>
//#include <BlueFramework/Rasterizer/>

#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QThread>
#include <QTimer>
#include <QWidget>

#include <gtest/gtest.h>

struct WorldBuffer {
    buw::Matrix44f viewProjection;
    buw::Matrix44f projection;
    buw::Matrix44f view;
    buw::Matrix44f rotation;
    buw::Vector3f cam;
};

class SkyboxEffect : public buw::Effect {
public:
    SkyboxEffect(buw::IRenderSystem* renderSystem, buw::ReferenceCounted<buw::IViewport> viewport, buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer) : Effect(renderSystem), viewport_(viewport), worldBuffer_(worldBuffer) {
    }

    ~SkyboxEffect() {
        sampler_ = nullptr;
        texture_ = nullptr;
        viewport_ = nullptr;
        pipelineState_ = nullptr;
        vertexBuffer_ = nullptr;
    }

private:
    void v_init() {
        std::vector<buw::VertexPosition3Normal3Texture2> vertices;
        std::vector<unsigned int> indices;

        buw::createIndexedSphere(1, 180, 45, vertices, indices); 
        buw::VertexLayout vertexLayout = buw::VertexPosition3Normal3Texture2::getVertexLayout();

        buw::vertexBufferDescription vbd;
        vbd.data = &vertices[0];
        vbd.vertexCount = static_cast<int>(vertices.size());
        vbd.vertexLayout = vertexLayout;
        vertexBuffer_ = renderSystem()->createVertexBuffer(vbd);

        buw::indexBufferDescription ibd;
        ibd.data = &indices[0];
        ibd.indexCount = indices.size();
        ibd.format = buw::eIndexBufferFormat::UnsignedInt32;

        indexBuffer_ = renderSystem()->createIndexBuffer(ibd);

        pipelineState_ = createPipelineState(buw::pipelineStateDescription(
			"Shader/skybox.be",
			"",
            vertexLayout,
            buw::ePrimitiveTopology::TriangleList,
            { buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB },
            false, false)
        );

        buw::samplerStateDescription ssd = { buw::eFilter::Linear };
        sampler_ = renderSystem()->createSampler(ssd);

        // load texture
        auto img0 = buw::loadImage4b("Data/right.png");
        auto img1 = buw::loadImage4b("Data/left.png");
        auto img2 = buw::loadImage4b("Data/top.png");
        auto img3 = buw::loadImage4b("Data/bottom.png");
        auto img4 = buw::loadImage4b("Data/front.png");
        auto img5 = buw::loadImage4b("Data/back.png");

        buw::textureCubeDescription td1;
        td1.width = img1.getWidth();
        td1.height = img1.getHeight();
        td1.format = buw::eTextureFormat::R8G8B8A8_UnsignedNormalizedInt_SRGB;

        void* imageData[6];
        imageData[0] = img0.getData();
        imageData[1] = img1.getData();
        imageData[2] = img2.getData();
        imageData[3] = img3.getData();
        imageData[4] = img4.getData();
        imageData[5] = img5.getData();

        td1.data = (const void**) &imageData[0];

        texture_ = renderSystem()->createTextureCube(td1, buw::eTextureBindType::SRV);
    }

    void v_render() {
        setViewport(viewport_);

        buw::ReferenceCounted<buw::ITexture2D> renderTarget = renderSystem()->getBackBufferTarget();
        setRenderTarget(renderTarget, nullptr);

        setPipelineState(pipelineState_);
        setSampler(sampler_, "sampler_");
        setTexture(texture_, "texDiffuseMap");
        setConstantBuffer(worldBuffer_, "WorldBuffer");

        setVertexBuffer(vertexBuffer_);
        setIndexBuffer(indexBuffer_);
        drawIndexed(indexBuffer_->getIndexCount());
    }

private:
    buw::ReferenceCounted<buw::ISampler> sampler_;
    buw::ReferenceCounted<buw::ITextureCube> texture_;
    buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;
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
        setMouseTracking(true);


        camera_ = buw::makeReferenceCounted<buw::Camera>();
        camera_->frustum() = buw::CameraFrustum(width(), height(), 0.001f, 1000.f, buw::eProjectionType::Perspective);
        camera_->transformation().offset() = 10;
        camera_->transformation().yaw() = buw::constantsf::pi_over_4();
        cameraController_ = buw::makeReferenceCounted<buw::CameraController>(camera_);

        buw::renderSystemDescription rsd;
        rsd.width = width();
        rsd.height = height();
        rsd.windowId = (void*)winId();
		rsd.renderAPI = renderAPI;
        renderSystem_ = buw::createRenderSystem(rsd);

        std::stringstream ss;
        ss << "Skybox Unit Test (" << renderSystem_->getName() << ")";
        setWindowTitle(ss.str().c_str());

        viewport_ = renderSystem_->createViewport(buw::viewportDescription(width(), height()));

        buw::constantBufferDescription cbd1;
        cbd1.sizeInBytes = sizeof(WorldBuffer);
        cbd1.data = nullptr;
        worldBuffer_ = renderSystem_->createConstantBuffer(cbd1);

        effect_ = buw::makeReferenceCounted<SkyboxEffect>(renderSystem_.get(), viewport_, worldBuffer_);
        effect_->init();

        drawNextFrame();
    }

    ~Viewport() {
		worldBuffer_ = nullptr;
        effect_ = nullptr;
        viewport_ = nullptr;
        renderSystem_ = nullptr;
    }

    void paintEvent(QPaintEvent*) {
        float color[] = { 0.3f, 0.5f, 0.9f, 0.0f };
        std::chrono::nanoseconds current = std::chrono::high_resolution_clock::now().time_since_epoch();
        float delta = (float)((current - lastTick_).count() * std::chrono::nanoseconds::period::num / (double)std::chrono::nanoseconds::period::den);
        cameraController_->tick(delta);
        camera_->tick(delta);
        updateWorldBuffer();

        renderSystem_->clearRenderTarget(renderSystem_->getBackBufferTarget(), color);

        effect_->render();

        renderSystem_->present();
        lastTick_ = current;
    }

    void mousePressEvent(QMouseEvent *event) {
        if(event->buttons()) {
            buw::Vector2f mouse(event->x(), event->y());
            lastMousePos_ = mouse;
            //camera_->orbitCamera(M_PI);
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        if(event->buttons()) {
            // Normalize mouse movement
            buw::Vector2f mouse(event->x(), event->y());
            buw::Vector2f delta = lastMousePos_ - mouse;
            delta[0] /= width() / 2.f;
            delta[1] /= height() / -2.f;
            lastMousePos_ = mouse;
            if(event->buttons() & Qt::LeftButton) {
                camera_->transformation().rotation() += buw::Vector3f(-delta.x(), delta.y(), 0);
            }
            else if(event->buttons() & Qt::RightButton) {
            }
        }

        repaint();
    }

    void wheelEvent(QWheelEvent* event)
    {
        camera_->transformation().offset() *= pow(1.1, event->delta() / -120);

        repaint();
    }

    QPaintEngine* paintEngine() const {
        return nullptr;
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

    public Q_SLOTS:
    void drawNextFrame() {
        repaint();

        QThread::msleep(2);
        QTimer::singleShot(0, this, SLOT(drawNextFrame()));
    }

    void resizeEvent(QResizeEvent *) {
        if(renderSystem_) {
            renderSystem_->resize(width(), height());

            viewport_->resize(buw::viewportDescription(width(), height()));
        }
    }

private:
    buw::Vector2f lastMousePos_;
    std::chrono::nanoseconds lastTick_;

    buw::ReferenceCounted<buw::IViewport> viewport_;
    buw::ReferenceCounted<SkyboxEffect> effect_;
    buw::ReferenceCounted<buw::IRenderSystem> renderSystem_;
    buw::ReferenceCounted<buw::IConstantBuffer> worldBuffer_;

    buw::ReferenceCounted<buw::Camera> camera_;
    buw::ReferenceCounted<buw::CameraController> cameraController_;
};

#include "Skybox.moc"

void runSkyboxUnitTest(const buw::eRenderAPI renderAPI)
{
	int argc = 1;
	char* argv[] = { "Skybox.exe" };
	QApplication app(argc, argv);

	buw::loadWebResources("Data/resources.xml");
	BlueFramework::Core::initializeLogSystem(false, true);

	Viewport v(renderAPI);
	v.resize(640, 480);
	v.show();

	app.exec();
}

TEST(Engine, Skybox_Direct3D11) {
	runSkyboxUnitTest(buw::eRenderAPI::Direct3D11);
}
TEST(Engine, Skybox_Direct3D12) {
	runSkyboxUnitTest(buw::eRenderAPI::Direct3D12);
}