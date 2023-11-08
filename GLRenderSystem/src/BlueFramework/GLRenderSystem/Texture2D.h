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

#ifndef __TEXTURE2D_H_2140CE5D02804BF7BC7F1FCD3AE4B5AC__
#define __TEXTURE2D_H_2140CE5D02804BF7BC7F1FCD3AE4B5AC__

#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/ITexture2D.h>
#include <BlueFramework/GLRenderSystem/Texture.h>

#include <BlueFramework/Rasterizer/renderDescriptors.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class Texture2D : public ITexture2D, public Texture
{
public:
	explicit Texture2D(buw::texture2DDescription const& td);
	virtual ~Texture2D();

	void clear(float const color[4] = nullptr) override;

	int width() const override;
	int height() const override;

	bool hasShaderResourceView() const override;
	bool hasRenderTargetView() const override;
	bool hasDepthStencilView() const override;

	bool isCPUReadable() const override;
	bool isCPUWriteable() const override;

    void makeCPUReadable() override;
	void makeCPUWriteable() override;

    buw::eTextureBindType const getBindType() const override;
    buw::eTextureFormat const getFormat() const override;

	void resize(buw::texture2DDescription const& td) override;
	bool isMultisampled() const override;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __TEXTURE2D_H_2140CE5D02804BF7BC7F1FCD3AE4B5AC__
