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
