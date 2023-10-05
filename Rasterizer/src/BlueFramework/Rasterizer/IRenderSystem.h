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

#pragma once
#ifndef BlueFramework_Rasterizer_IRenderSystem_4da08a35_fca5_4045_91d0_4e22761ea7dc_h
#define BlueFramework_Rasterizer_IRenderSystem_4da08a35_fca5_4045_91d0_4e22761ea7dc_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/ImageProcessing/Image.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"
#include "BlueFramework/Rasterizer/Resources/IEffectCore.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IViewport;
class IConstantBuffer;
class IVertexBuffer;
class IIndexBuffer;
class ITexture1D;
class ITexture2D;
class ISampler;
class IBlender;

class IRenderSystem : public buw::NonCopyable {
public:
	IRenderSystem(const buw::renderSystemDescription&) {}
	virtual ~IRenderSystem() {}

	virtual buw::ReferenceCounted<IEffectCore> createEffectCore() = 0;

	virtual buw::ReferenceCounted<IVertexBuffer> createVertexBuffer(const buw::vertexBufferDescription& vbd) = 0;
	virtual buw::ReferenceCounted<IIndexBuffer> createIndexBuffer(const buw::indexBufferDescription& ibd) = 0;
	virtual buw::ReferenceCounted<IConstantBuffer> createConstantBuffer(const buw::constantBufferDescription& cbd) = 0;
	virtual buw::ReferenceCounted<ITexture1D> createTexture1D(const buw::texture1DDescription& td, buw::eTextureBindType bindType) = 0;
	virtual buw::ReferenceCounted<ITexture2D> createTexture2D(const buw::texture2DDescription& td, buw::eTextureBindType bindType) = 0;
    virtual buw::ReferenceCounted<ITextureCube> createTextureCube(const buw::textureCubeDescription& td, buw::eTextureBindType bindType) = 0;
	virtual buw::ReferenceCounted<ISampler> createSampler(const buw::samplerStateDescription& ssd) = 0;
    virtual buw::ReferenceCounted<IBlender> createBlender(const buw::blendStateDescription& bsd) = 0;
	virtual buw::ReferenceCounted<IViewport> createViewport(const buw::viewportDescription& vpd) = 0;

	virtual buw::ReferenceCounted<ITexture2D> getBackBufferTarget() = 0;

	virtual void clearRenderTarget(buw::ReferenceCounted<ITexture2D> renderTarget, const float color[4] = nullptr) = 0;
    virtual void clearRenderTargets(std::vector<buw::ReferenceCounted<ITexture2D>> renderTargets, const float color[4] = nullptr) = 0;
	virtual void clearDepthStencilView(buw::ReferenceCounted<ITexture2D> depthStencil) = 0;

    virtual void downloadTexture(buw::ReferenceCounted<ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) = 0;
	virtual void uploadTexture(buw::ReferenceCounted<ITexture2D> itexture, buw::Image4b &dest, const int x = 0, const int y = 0) = 0;

	virtual void present() = 0;
	virtual void resize(int width, int height) = 0;

	virtual const char* getName() const = 0;

    virtual const bool getMSAAEnabled() const = 0;

};

buw::ReferenceCounted<IRenderSystem> createRenderSystem(const buw::renderSystemDescription& rsd);

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IRenderSystem)
BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(createRenderSystem)

#endif // end define BlueFramework_Rasterizer_IRenderSystem_4da08a35_fca5_4045_91d0_4e22761ea7dc_h
