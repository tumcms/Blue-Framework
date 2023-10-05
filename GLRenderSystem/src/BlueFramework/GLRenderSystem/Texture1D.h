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
