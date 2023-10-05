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
#ifndef BlueFramework_Rasterizer_IVertexBuffer_3a5c332a_b6bb_4a09_8412_ae36f7e05a5a_h
#define BlueFramework_Rasterizer_IVertexBuffer_3a5c332a_b6bb_4a09_8412_ae36f7e05a5a_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"
#include "BlueFramework/Rasterizer/VertexLayout.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IRenderSystem;

class IVertexBuffer : public buw::NonCopyable
{
public:
	IVertexBuffer(IRenderSystem*, const buw::vertexBufferDescription&) {}

	virtual ~IVertexBuffer() {}

	virtual size_t getVertexCount() const = 0;
	virtual size_t getVertexSize() const = 0;
	virtual void uploadData(const buw::vertexBufferDescription&) = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IVertexBuffer)

#endif // end define BlueFramework_Rasterizer_IVertexBuffer_3a5c332a_b6bb_4a09_8412_ae36f7e05a5a_h
