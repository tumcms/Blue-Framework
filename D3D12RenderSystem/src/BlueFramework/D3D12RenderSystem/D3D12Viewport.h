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
#ifndef BlueFramework_D3D12EffectRenderSystem_D3D12Viewport_6016cdb5_4c77_4eaa_92eb_cdca07ec8253_h
#define BlueFramework_D3D12EffectRenderSystem_D3D12Viewport_6016cdb5_4c77_4eaa_92eb_cdca07ec8253_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IViewport.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12RenderSystem;

class D3D12Viewport : public buw::IViewport {
public:
	D3D12Viewport(const buw::viewportDescription& vpd);
	~D3D12Viewport();

	void resize(const buw::viewportDescription& vpd) override;


	const D3D12_VIEWPORT* viewport() const { return viewport_; }
	const D3D12_RECT* scissorRect() const { return scissorRect_; }

private:
	D3D12_VIEWPORT* viewport_;
	D3D12_RECT* scissorRect_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12EffectRenderSystem_D3D12Viewport_6016cdb5_4c77_4eaa_92eb_cdca07ec8253_h
