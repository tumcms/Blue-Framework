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
