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
#ifndef BlueFramework_Core_Map_6b14d240_f47b_4627_9021_abaacefee21b_h
#define BlueFramework_Core_Map_6b14d240_f47b_4627_9021_abaacefee21b_h

#include <BlueFramework/Core/namespace.h>
#include <map>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

// A simple std::map wrapper.
// For some reason the C++ committee did never manage to create a easy usable map.
template <typename Key, typename Value>
class Map : public std::map<Key, Value> {
public:
	bool contains(const Key& key) {
		return this->find(key) != this->end();
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