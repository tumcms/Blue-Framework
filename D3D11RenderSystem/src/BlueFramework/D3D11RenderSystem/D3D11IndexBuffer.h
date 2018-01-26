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
#ifndef BlueFramework_D3D11RenderSystem_D3D11IndexBuffer_6d784b6b_0098_4863_9a26_293c3181e197_h
#define BlueFramework_D3D11RenderSystem_D3D11IndexBuffer_6d784b6b_0098_4863_9a26_293c3181e197_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"
#include "BlueFramework/Rasterizer/Resources/IIndexBuffer.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11IndexBuffer : public buw::IIndexBuffer {
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11IndexBuffer(D3D11RenderSystem* renderSystem, const buw::indexBufferDescription& ibd);

	ComPtr<ID3D11Buffer> getIndexBuffer() const { return indexBuffer_; }

	size_t getIndexCount() const override { return indexCount_; }
	buw::eIndexBufferFormat getFormat() const override { return format_; }
	size_t getIndexSize() const override;

	void uploadData(const buw::indexBufferDescription& ibd);

private:
	D3D11RenderSystem* renderSystem_;
	buw::eIndexBufferFormat format_;
	size_t indexCount_;

	ComPtr<ID3D11Buffer> indexBuffer_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11IndexBuffer_6d784b6b_0098_4863_9a26_293c3181e197_h
