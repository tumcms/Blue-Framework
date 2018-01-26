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
