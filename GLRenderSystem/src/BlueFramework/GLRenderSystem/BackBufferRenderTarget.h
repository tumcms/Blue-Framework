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
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __BACKBUFFERRENDERTARGET_H_8FEFB0A63F244519B663623E839FF93A__
