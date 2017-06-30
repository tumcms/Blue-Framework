/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016-2017 Technical University of Munich
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
