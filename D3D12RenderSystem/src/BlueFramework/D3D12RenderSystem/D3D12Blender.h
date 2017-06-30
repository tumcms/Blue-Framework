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
#ifndef BlueFramework_D3D12RenderSystem_D3D12Blender_711dfc90_64d1_45e9_a989_c0a4ca62c6b0_h
#define BlueFramework_D3D12RenderSystem_D3D12Blender_711dfc90_64d1_45e9_a989_c0a4ca62c6b0_h

#include "BlueFramework/D3D12RenderSystem/namespace.h"
#include "BlueFramework/Rasterizer/Resources/IBlender.h"
#include "BlueFramework/D3D12RenderSystem/d3d12.h"

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN

class D3D12Blender : public buw::IBlender {
public:
    D3D12Blender(buw::blendStateDescription bsd);

    virtual ~D3D12Blender() {}

    void setBlendDescriptionForRenderTarget(int at, buw::blendStateDescription bsd);
private:
    D3D12_BLEND mapBlendValue(buw::eBlendValue blendValue);
    D3D12_BLEND_OP mapBlendOperation(buw::eBlendOperation blendOperation);
    D3D12_LOGIC_OP mapLogicOperation(buw::eLogicOperation logicOperation);
    void mapRenderTargetBlendDesc(buw::renderTargetBlendDescription from, D3D12_RENDER_TARGET_BLEND_DESC &to);
private:
    D3D12_BLEND_DESC blendDesc_;
};

BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END

#endif // end define BlueFramework_D3D12RenderSystem_D3D12Blender_711dfc90_64d1_45e9_a989_c0a4ca62c6b0_h
