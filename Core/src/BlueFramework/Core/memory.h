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
