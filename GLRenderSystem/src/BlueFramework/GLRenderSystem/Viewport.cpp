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

#include <BlueFramework/GLRenderSystem/Viewport.h>
#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/renderDescriptors.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

Viewport::Viewport(buw::viewportDescription const& vd)
	: buw::IViewport(vd)
{
}

Viewport::~Viewport()
{
}

void Viewport::resize(buw::viewportDescription const&)
{
	// No use for this class in OpenGL.
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
