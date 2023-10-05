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

#ifndef __BACKBUFFERRENDERTARGET_H_8FEFB0A63F244519B663623E839FF93A__
#define __BACKBUFFERRENDERTARGET_H_8FEFB0A63F244519B663623E839FF93A__

#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/ITexture2D.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class BackBufferRenderTarget : public ITexture2D
{
public:
	explicit BackBufferRenderTarget();
	virtual ~BackBufferRenderTarget();

	int width() const override;
	int height() const override;
    
	bool hasShaderResourceView() const override;
	bool hasRenderTargetView() const override;
	bool hasDepthStencilView() const override;
    bool isCPUReadable() const override;

    void makeCPUReadable() override;

    const buw::eTextureBindType getBindType() const override;

    const buw::eTextureFormat getFormat() const override;

	void resize(const buw::texture2DDescription& td) override;

	void clear(float const color[4]); // Clears only color buffer.
	void clearDepthBuffer();
	void clearStencilBuffer();

	bool isCPUWriteable() const override;
	void makeCPUWriteable() override;
	bool isMultisampled() const override;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __BACKBUFFERRENDERTARGET_H_8FEFB0A63F244519B663623E839FF93A__
