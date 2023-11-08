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
