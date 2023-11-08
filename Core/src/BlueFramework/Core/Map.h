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
#ifndef BlueFramework_Core_Map_6b14d240_f47b_4627_9021_abaacefee21b_h
#define BlueFramework_Core_Map_6b14d240_f47b_4627_9021_abaacefee21b_h

#include <BlueFramework/Core/namespace.h>
#include <map>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

// A simple std::map wrapper.
// For some reason the C++ committee did never manage to create a easy usable map.
template <typename Key, typename Value>
class Map : public std::map<Key, Value> {	// a C++20 like std::map
public:
	bool contains(const Key& key) {
		return this->find(key) != this->end(); // standard function of std::map in C++20
	}

	void insert(const Key& k, const Value& v) {
		(*this)[k] = v;
	}

	Value getValue(const Key& k) {
		return (*this)[k];
	}
};

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(Map)

#endif // end define BlueFramework_Core_Map_6b14d240_f47b_4627_9021_abaacefee21b_h