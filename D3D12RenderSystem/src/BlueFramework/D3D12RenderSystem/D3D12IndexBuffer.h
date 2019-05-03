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
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12IndexBuffer_b8dbb997_e8ed_4704_95f1_7d03ea68c63b_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12IndexBuffer_b8dbb997_e8ed_4704_95f1_7d03ea68c63b_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IIndexBuffer.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12IndexBuffer : public buw::IIndexBuffer
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D12IndexBuffer(D3D12RenderSystem* renderSystem, const buw::indexBufferDescription& ibd);


	D3D12_INDEX_BUFFER_VIEW getIndexBufferView() const;

	size_t getIndexCount() const override { return indexCount_; }
	buw::eIndexBufferFormat getFormat() const { return format_; }
	size_t getIndexSize() const;

private:
	buw::eIndexBufferFormat format_;
	size_t indexCount_;

	void setIndexCount(size_t val);

	ComPtr<ID3D12Resource> indexBuffer_;
	D3D12_INDEX_BUFFER_VIEW indexBufferView_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12IndexBuffer_b8dbb997_e8ed_4704_95f1_7d03ea68c63b_h
