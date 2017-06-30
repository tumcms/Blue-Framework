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
