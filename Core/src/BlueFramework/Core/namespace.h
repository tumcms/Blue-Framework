/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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
#ifndef BlueFramework_Core_namespace_93b0b319_5918_4662_8c60_2fc98af6e538_h
#define BlueFramework_Core_namespace_93b0b319_5918_4662_8c60_2fc98af6e538_h

#define BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN \
	namespace BlueFramework {                   \
		namespace Core {
#define BLUEFRAMEWORK_CORE_NAMESPACE_END \
	}                                         \
	}

#define BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN \
	namespace BlueFramework {                        \
		namespace Core {                             \
			namespace Math {
#define BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END \
	}                                              \
	}                                              \
	}

#define BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(X) \
	\
namespace buw {                                             \
		using BlueFramework::Core::X;                       \
	\
}

#define BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(X) \
	\
namespace buw {                                                  \
		using BlueFramework::Core::Math::X;                      \
	\
}

#endif // end define BlueFramework_Core_namespace_93b0b319_5918_4662_8c60_2fc98af6e538_h
