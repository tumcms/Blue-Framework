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

#pragma once
#ifndef BlueFramework_Rasterizer_ITextureCube_ad5bafcd_4fcd_437d_a28d_9bc2f09a3b16_h
#define BlueFramework_Rasterizer_ITextureCube_ad5bafcd_4fcd_437d_a28d_9bc2f09a3b16_h

#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IRenderSystem;

class ITextureCube: public buw::NonCopyable {
public:
	ITextureCube() {
	}
	virtual ~ITextureCube() {}

    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual bool hasShaderResourceView() const = 0;

    virtual const buw::eTextureFormat getFormat() const = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(ITextureCube)

#endif // end define BlueFramework_Rasterizer_ICubeTexture_ad5bafcd_4fcd_437d_a28d_9bc2f09a3b16_h
