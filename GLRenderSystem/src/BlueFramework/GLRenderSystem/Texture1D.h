
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

#ifndef __TEXTURE1D_H_6A7F13BAAE4849E7849649C7FDF2CEE6__
#define __TEXTURE1D_H_6A7F13BAAE4849E7849649C7FDF2CEE6__

#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/Texture.h>

#include <BlueFramework/Rasterizer/Resources/ITexture1D.h>
#include <BlueFramework/Rasterizer/renderDescriptors.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class Texture1D : public buw::ITexture1D, public Texture
{
public:
	explicit Texture1D(buw::texture1DDescription const& td);
	virtual ~Texture1D();
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __TEXTURE1D_H_6A7F13BAAE4849E7849649C7FDF2CEE6__
