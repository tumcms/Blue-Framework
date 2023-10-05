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
#ifndef BlueFramework_Rasterizer_ITexture1D_2c67f62a_b024_4dbc_92f8_cb6747c9df6a_h
#define BlueFramework_Rasterizer_ITexture1D_2c67f62a_b024_4dbc_92f8_cb6747c9df6a_h

#include "BlueFramework/Rasterizer/namespace.h"
#include "BlueFramework/Core/NonCopyable.h"

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN

class ITexture1D : public buw::NonCopyable {
public:
	ITexture1D() {}
	virtual ~ITexture1D() {}
};

BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END

BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(ITexture1D)

#endif // end define BlueFramework_Rasterizer_ITexture1D_2c67f62a_b024_4dbc_92f8_cb6747c9df6a_h
