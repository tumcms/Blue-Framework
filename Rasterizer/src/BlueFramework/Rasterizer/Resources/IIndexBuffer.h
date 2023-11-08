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
#ifndef BlueFramework_Rasterizer_IIndexBuffer_61eeeeeb_906d_4e12_9d48_169029b43de8_h
#define BlueFramework_Rasterizer_IIndexBuffer_61eeeeeb_906d_4e12_9d48_169029b43de8_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IRenderSystem;

class IIndexBuffer : public buw::NonCopyable {
public:
	IIndexBuffer(IRenderSystem*, const buw::indexBufferDescription&) {}
	virtual ~IIndexBuffer() {}

	virtual size_t getIndexCount() const = 0;
	virtual size_t getIndexSize() const = 0;
	virtual buw::eIndexBufferFormat getFormat() const = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IIndexBuffer)

#endif // end define BlueFramework_Rasterizer_IIndexBuffer_61eeeeeb_906d_4e12_9d48_169029b43de8_h
