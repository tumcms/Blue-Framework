/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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
#ifndef BlueFramework_Rasterizer_IConstantBuffer_4066c89e_260b_4712_9970_28182d437450_h
#define BlueFramework_Rasterizer_IConstantBuffer_4066c89e_260b_4712_9970_28182d437450_h

#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Rasterizer/renderDescriptors.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class IRenderSystem;

class IConstantBuffer : public buw::NonCopyable{
public:
	IConstantBuffer(IRenderSystem*, const buw::constantBufferDescription&) {}
	virtual ~IConstantBuffer() {}

	virtual void uploadData(const buw::constantBufferDescription&) = 0;
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(IConstantBuffer)

#endif // end define BlueFramework_Rasterizer_IConstantBuffer_4066c89e_260b_4712_9970_28182d437450_h
