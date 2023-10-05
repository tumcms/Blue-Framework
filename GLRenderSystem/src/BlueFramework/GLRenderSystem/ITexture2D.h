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

#ifndef __ITEXTURE2D_H_E45932C9D04847198E54435DE27814A6__
#define __ITEXTURE2D_H_E45932C9D04847198E54435DE27814A6__

#include <BlueFramework/Rasterizer/Resources/ITexture2D.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class ITexture2D : public buw::ITexture2D
{
public:
	virtual void clear(float const color[4] = nullptr) = 0;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __ITEXTURE2D_H_E45932C9D04847198E54435DE27814A6__
