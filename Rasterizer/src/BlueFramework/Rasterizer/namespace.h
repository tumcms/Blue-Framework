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
#ifndef BlueFramework_Core_namespace_bb860aea_2b4b_4fe1_9f0e_f03ad00af30f_h
#define BlueFramework_Core_namespace_bb860aea_2b4b_4fe1_9f0e_f03ad00af30f_h

#define BLUEFRAMEWORK_RASTERIZER_NAMESPACE_BEGIN namespace BlueFramework { namespace Rasterizer {
#define BLUEFRAMEWORK_RASTERIZER_NAMESPACE_END }}

#define BLUE_BLUEFRAMEWORK_RASTERIZER_EMBED_INTO_BUW_NAMESPACE(X) \
namespace buw {                                              \
	using BlueFramework::Rasterizer::X;                      \
}

#endif // end define BlueFramework_Core_namespace_bb860aea_2b4b_4fe1_9f0e_f03ad00af30f_h
