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

#pragma once
#ifndef BlueFramework_Rasterizer_ITexture2D_ec93911a_3694_4bd1_8aa2_5c142e102f3c_h
#define BlueFramework_Rasterizer_ITexture2D_ec93911a_3694_4bd1_8aa2_5c142e102f3c_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class ITexture2D : public buw::NonCopyable {
public:
	ITexture2D() {}
	virtual ~ITexture2D() {}

	virtual int width() const = 0;
	virtual int height() const = 0;

	virtual bool hasShaderResourceView() const = 0;
	virtual bool hasRenderTargetView() const = 0;
	virtual bool hasDepthStencilView() const = 0;
    virtual bool isCPUReadable() const = 0;
	virtual bool isCPUWriteable() const = 0;
	virtual bool isMultisampled() const = 0;

    virtual void makeCPUReadable() = 0;
	virtual void makeCPUWriteable() = 0;

    virtual const buw::eTextureBindType getBindType() const = 0;

    virtual const buw::eTextureFormat getFormat() const = 0;

	virtual void resize(const buw::texture2DDescription&) = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(ITexture2D)

#endif // end define BlueFramework_Rasterizer_ITexture2D_ec93911a_3694_4bd1_8aa2_5c142e102f3c_h
