/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h
#define BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h

#include <BlueFramework/Core/namespace.h>
#include <boost/noncopyable.hpp>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

typedef boost::noncopyable NonCopyable;

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(NonCopyable)

#endif // end define BlueFramework_Core_NonCopyable_a0cf67e4_7ac1_4439_b4e5_e06079269294_h
