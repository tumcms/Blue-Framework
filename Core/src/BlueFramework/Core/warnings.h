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

// This one is tricky. It cannot be enclosed by push/pop but must be disabled for the
// whole compilation unit. Disables
// warning C4714: function 'boost::log::v2s_mt_nt6::aux::attribute_set_reference_proxy::operator boost::log::v2s_mt_nt6::aux::attribute_set_reference_proxy::mapped_type(void) noexcept const' marked as __forceinline not inlined
#define WARN_BOOST_INLINE_DISABLE __pragma(warning(disable: 4714))

#define WARN_QT_PUSH \
	__pragma(warning(push)) \
	__pragma(warning(disable: 4127))

#define WARN_POP __pragma(warning(pop))
