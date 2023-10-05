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
#ifndef BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h
#define BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h

#include <BlueFramework/Core/namespace.h>
#include <boost/noncopyable.hpp>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

typedef boost::noncopyable NonCopyable;

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(NonCopyable)

#endif // end define BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h
