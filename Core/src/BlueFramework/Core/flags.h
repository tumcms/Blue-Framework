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
