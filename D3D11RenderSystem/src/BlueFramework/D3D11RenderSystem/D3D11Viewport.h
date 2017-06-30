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
#ifndef BlueFramework_D3D11RenderSystem_D3D11Viewport_64e9ba8d_1b50_483b_9777_6faeec71733b_h
#define BlueFramework_D3D11RenderSystem_D3D11Viewport_64e9ba8d_1b50_483b_9777_6faeec71733b_h

#include "BlueFramework/D3D11RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IViewport.h"
#include "BlueFramework/D3D11RenderSystem/d3d11.h"


BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_BEGIN

class D3D11RenderSystem;

class D3D11Viewport : public buw::IViewport {
public:
	D3D11Viewport(const buw::viewportDescription& vpd);
	~D3D11Viewport();

	void resize(const buw::viewportDescription& vpd) override;


	const D3D11_VIEWPORT* viewport() const { return viewport_; }
	const D3D11_RECT* scissorRect() const { return scissorRect_; }

private:
	D3D11_VIEWPORT* viewport_;
	D3D11_RECT* scissorRect_;
};

BLUEFRAMEWORK_D3D11RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D11RenderSystem_D3D11Viewport_64e9ba8d_1b50_483b_9777_6faeec71733b_h
