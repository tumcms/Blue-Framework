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

#include "BlueFramework/Core/namespace.h"

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

// http://stackoverflow.com/questions/3199761/define-bit0-bit1-bit2-etc-without-define by User Cogwheel
// Can I reuse your bit template in a commercial project(the 5 lines of code of your first code snippet) ? � Vertexwahn yesterday
// @Vertexwahn Sure thing!Edit: I release this code to anyone for any use with no warranty.� Cogwheel 18 hours ago

template <int BitN>
struct bit {
	static const int value = (1 << BitN);
};

BLUEFRAMEWORK_CORE_NAMESPACE_END
