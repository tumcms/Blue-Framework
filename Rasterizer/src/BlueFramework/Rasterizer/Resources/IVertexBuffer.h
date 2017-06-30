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
