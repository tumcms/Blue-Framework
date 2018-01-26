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
#ifndef BlueFramework_Core_memory_d3d47a66_cc9e_4d18_bbd7_7fb027400bef_h
#define BlueFramework_Core_memory_d3d47a66_cc9e_4d18_bbd7_7fb027400bef_h

#include <BlueFramework/Core/namespace.h>
#include <memory>

// please consider to use the safeDelete function instead of this macro
#define BLUE_SAFE_DELETE(p) \
	{                       \
		if (p) {            \
			delete (p);     \
			(p) = nullptr;  \
		}                   \
	}
#define BLUE_SAFE_DELETE_ARRAY(p) \
	{                             \
		if (p) {                  \
			delete[](p);          \
			(p) = nullptr;        \
		}                         \
	}
#define BLUE_SAFE_RELEASE(p) \
	{                        \
		if (p) {             \
			(p)->Release();  \
			(p) = nullptr;   \
		}                    \
	}

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

template <typename T>
using ReferenceCounted = std::shared_ptr<T>;

template <typename T>
ReferenceCounted<T> claimOwnership(T* object) {
	return ReferenceCounted<T>(object);
}

template <typename T, typename... Args>
ReferenceCounted<T> makeReferenceCounted(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
void safeDelete(T* memory) {
	if (memory) {
		delete memory;
		memory = nullptr;
	}
}

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(ReferenceCounted)
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(claimOwnership)
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(makeReferenceCounted)
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(safeDelete)

#endif // end define BlueFramework_Core_memory_d3d47a66_cc9e_4d18_bbd7_7fb027400bef_h
