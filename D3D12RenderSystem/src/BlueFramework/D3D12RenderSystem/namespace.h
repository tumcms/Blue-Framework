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
#ifndef BlueFramework_D3D12EffectRenderSystem_namespace_596619e5_6a9f_405b_a079_393e1a14153c_h
#define BlueFramework_D3D12EffectRenderSystem_namespace_596619e5_6a9f_405b_a079_393e1a14153c_h

#define BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_BEGIN namespace BlueFramework { namespace D3D12RenderSystem {
#define BLUEFRAMEWORK_D3D12RENDERSYSTEM_NAMESPACE_END }}

#define BLUEFRAMEWORK_D3D12RENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(X)	\
namespace buw {																\
	using BlueFramework::D3D12RenderSystem::X;							    \
}

#endif // end define BlueFramework_D3D12EffectRenderSystem_namespace_596619e5_6a9f_405b_a079_393e1a14153c_h
