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

#ifndef __RENDERSYSTEM_H_ECA31C71216E4F62A69CAEE00C9C7A73__
#define __RENDERSYSTEM_H_ECA31C71216E4F62A69CAEE00C9C7A73__

#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/BackBufferRenderTarget.h>

#include <BlueFramework/Rasterizer/IRenderSystem.h>
#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include <BlueFramework/Rasterizer/Resources/IEffectCore.h>
#include <BlueFramework/Rasterizer/Resources/IVertexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IIndexBuffer.h>
#include <BlueFramework/Rasterizer/Resources/IConstantBuffer.h>
#include <BlueFramework/Rasterizer/Resources/ITexture1D.h>
#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>
#include <BlueFramework/Rasterizer/Resources/ITextureCube.h>
#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/Resources/IBlender.h>

#include <memory>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
	#define NOMINMAX
#endif

#include <Windows.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class RenderSystem : public buw::IRenderSystem
{
public:
	explicit RenderSystem(buw::renderSystemDescription const& rsd);
	virtual ~RenderSystem();

	buw::ReferenceCounted<buw::IEffectCore> createEffectCore() override;
	buw::ReferenceCounted<buw::IVertexBuffer> createVertexBuffer(buw::vertexBufferDescription const& vbd) override;
	buw::ReferenceCounted<buw::IIndexBuffer> createIndexBuffer(buw::indexBufferDescription const& ibd) override;
	buw::ReferenceCounted<buw::IConstantBuffer> createConstantBuffer(buw::constantBufferDescription const& cbd) override;
	buw::ReferenceCounted<buw::ITexture1D> createTexture1D(buw::texture1DDescription const& td, buw::eTextureBindType bindType) override;
	buw::ReferenceCounted<buw::ITexture2D> createTexture2D(buw::texture2DDescription const& td, buw::eTextureBindType bindType) override;
	buw::ReferenceCounted<buw::ITextureCube> createTextureCube(buw::textureCubeDescription const& td, buw::eTextureBindType bindType) override;
	buw::ReferenceCounted<buw::ISampler> createSampler(buw::samplerStateDescription const& ssd) override;
	buw::ReferenceCounted<buw::IBlender> createBlender(buw::blendStateDescription const& bsd) override;
	buw::ReferenceCounted<buw::IViewport> createViewport(buw::viewportDescription const& vpd) override;

	buw::ReferenceCounted<buw::ITexture2D> getBackBufferTarget() override;

	void clearRenderTarget(buw::ReferenceCounted<buw::ITexture2D> renderTarget, float const color[4] = nullptr) override;
	void clearRenderTargets(std::vector<buw::ReferenceCounted<buw::ITexture2D>> renderTargets, float const color[4] = nullptr) override;
	void clearDepthStencilView(buw::ReferenceCounted<buw::ITexture2D> depthStencil) override;

	void present() override;
	void resize(int width, int height) override;

	char const* getName() const override;

	bool const getMSAAEnabled() const override;
	bool hasMultiSampleBuffer() const;
	size_t getNumAASamplesPerPixel() const;

	void downloadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) override;
	void uploadTexture(buw::ReferenceCounted<buw::ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) override;

private:
	HWND _hWND;
	HDC _hDC;
	HGLRC _hGLRC;
	BackBufferRenderTarget _bb;

	void createRenderContext(buw::renderSystemDescription const& rsd);
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

BLUE_BLUEFRAMEWORK_GLRENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(RenderSystem)

extern "C" buw::IRenderSystem* createRenderSystem(buw::renderSystemDescription const& rsd);

#endif // __RENDERSYSTEM_H_ECA31C71216E4F62A69CAEE00C9C7A73__
