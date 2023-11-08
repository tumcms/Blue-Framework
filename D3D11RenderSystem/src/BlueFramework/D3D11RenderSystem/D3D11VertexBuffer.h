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
#ifndef BlueFramework_D3D11RenderSystem_D3D11VertexBuffer_4fcfe2d8_9184_4721_a196_5c1e02dc0efa_h
#define BlueFramework_D3D11RenderSystem_D3D11VertexBuffer_4fcfe2d8_9184_4721_a196_5c1e02dc0efa_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IVertexBuffer.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11VertexBuffer : public buw::IVertexBuffer {

	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11VertexBuffer(D3D11RenderSystem* renderSystem, const buw::vertexBufferDescription& vbd);

	const buw::VertexLayout& getVertexLayout() { return vertexLayout_; }
	ComPtr<ID3D11Buffer> getVertexBuffer() const { return vertexBuffer_; }

	size_t getVertexCount() const override { return vertexCount_; }
	size_t getVertexSize() const override { return vertexSize_; }

	void uploadData(const buw::vertexBufferDescription& vbd) override;

private:
	D3D11RenderSystem* renderSystem_;
	const buw::VertexLayout vertexLayout_;
	size_t vertexCount_, vertexSize_;

	ComPtr<ID3D11Buffer> vertexBuffer_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11VertexBuffer_4fcfe2d8_9184_4721_a196_5c1e02dc0efa_h
