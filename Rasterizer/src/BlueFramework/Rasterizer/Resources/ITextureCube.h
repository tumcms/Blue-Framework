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
