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
