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
#ifndef BlueFramework_D3D11RenderSystem_D3D11ConstantBuffer_b5c78972_2c7a_499f_a739_742d16a0f433_h
#define BlueFramework_D3D11RenderSystem_D3D11ConstantBuffer_b5c78972_2c7a_499f_a739_742d16a0f433_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"
#include "BlueFramework/Rasterizer/Resources/IConstantBuffer.h"

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11ConstantBuffer : public buw::IConstantBuffer {
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	D3D11ConstantBuffer(D3D11RenderSystem* renderSystem, const buw::constantBufferDescription& cbd);

	ComPtr<ID3D11Buffer> getConstantBuffer() const { return constantBuffer_; }

	void uploadData(const buw::constantBufferDescription& cbd) override;

private:
	D3D11RenderSystem* renderSystem_;
	size_t constantBufferSize_;

	ComPtr<ID3D11Buffer> constantBuffer_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11ConstantBuffer_b5c78972_2c7a_499f_a739_742d16a0f433_h
