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
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __TEXTURE2D_H_2140CE5D02804BF7BC7F1FCD3AE4B5AC__
