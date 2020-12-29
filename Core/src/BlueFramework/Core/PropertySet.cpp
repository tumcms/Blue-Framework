// Copied and modified code from "Nori".
// This library is available under the GPL v3 license. Original copyright notice:

/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// More details can be found in README.md file in the root directory.

#include "PropertySet.h"

#include "Diagnostics/log.h"
#include "Exception.h"
#include "string.h"

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

#define DEFINE_PROPERTY_ACCESSOR(Type, TypeName, XmlName)                                                                                        \
	void PropertySet::add##TypeName(const std::string& name, const Type& value) {                                                                \
		if (properties_.find(name) != properties_.end())                                                                                         \
			BLUE_LOG(error) << "Property \"" << name << "\" was specified multiple times!";                                                      \
		properties_[name] = value;                                                                                                               \
	}                                                                                                                                            \
                                                                                                                                                 \
	void PropertySet::set##TypeName(const std::string& name, const Type& value) {                                                                \
		if (properties_.find(name) == properties_.end())                                                                                         \
			BLUE_LOG(error) << "Property \"" << name << "\" Use add instead of set. Adding properties by set will be deprecated in the future."; \
		properties_[name] = value;                                                                                                               \
	}                                                                                                                                            \
                                                                                                                                                 \
	Type PropertySet::get##TypeName(const std::string& name) const {                                                                             \
		std::map<std::string, Property>::const_iterator it = properties_.find(name);                                                             \
		if (it == properties_.end())                                                                                                             \
			throw buw::Exception("Property '%1' is missing!");                                                                                   \
		const Type* result = boost::get<Type>(&it->second);                                                                                      \
		if (!result)                                                                                                                             \
			throw buw::Exception(                                                                                                                \
			  "Property '%1' has the wrong type! "                                                                                               \
			  "(expected <" #XmlName ">)!");                                                                                                     \
		return (Type)*result;                                                                                                                    \
	}                                                                                                                                            \
                                                                                                                                                 \
	Type PropertySet::get##TypeName(const std::string& name, const Type& defVal) const {                                                         \
		std::map<std::string, Property>::const_iterator it = properties_.find(name);                                                             \
		if (it == properties_.end())                                                                                                             \
			return defVal;                                                                                                                       \
		const Type* result = boost::get<Type>(&it->second);                                                                                      \
		if (!result)                                                                                                                             \
			throw buw::Exception(                                                                                                                \
			  "Property '%1' has the wrong type! "                                                                                               \
			  "(expected <" #XmlName ">)!");                                                                                                     \
		return (Type)*result;                                                                                                                    \
	}

DEFINE_PROPERTY_ACCESSOR(bool, Boolean, boolean)
DEFINE_PROPERTY_ACCESSOR(int, Integer, integer)
DEFINE_PROPERTY_ACCESSOR(float, Float, float)
DEFINE_PROPERTY_ACCESSOR(double, Double, double)
DEFINE_PROPERTY_ACCESSOR(std::string, String, std::string)
DEFINE_PROPERTY_ACCESSOR(std::wstring, WString, std::wstring)
DEFINE_PROPERTY_ACCESSOR(buw::Vector2i, Vector2i, buw::Vector2i)
DEFINE_PROPERTY_ACCESSOR(buw::Vector2f, Vector2f, buw::Vector2f)
DEFINE_PROPERTY_ACCESSOR(buw::Vector2d, Vector2d, buw::Vector2d)
DEFINE_PROPERTY_ACCESSOR(buw::Vector3i, Vector3i, buw::Vector3i)
DEFINE_PROPERTY_ACCESSOR(buw::Vector3f, Vector3f, buw::Vector3f)
DEFINE_PROPERTY_ACCESSOR(buw::Vector3d, Vector3d, buw::Vector3d)
DEFINE_PROPERTY_ACCESSOR(buw::Vector4i, Vector4i, buw::Vector4i)
DEFINE_PROPERTY_ACCESSOR(buw::Vector4f, Vector4f, buw::Vector4f)
DEFINE_PROPERTY_ACCESSOR(buw::Vector4d, Vector4d, buw::Vector4d)

PropertySet::PropertySet() {
}

PropertySet::~PropertySet() {
}

void PropertySet::clear() {
	properties_.clear();
}

bool PropertySet::contains(const std::string& name) const {
	return properties_.find(name) != properties_.end();
}

struct determine_type : public boost::static_visitor<buw::ePropertyType> {
	buw::ePropertyType operator()(const bool /*value*/) const {
		return ePropertyType::Boolean;
	}
	buw::ePropertyType operator()(const int /*value*/) const {
		return ePropertyType::Integer;
	}
	buw::ePropertyType operator()(const float /*value*/) const {
		return ePropertyType::Float;
	}
	buw::ePropertyType operator()(const double /*value*/) const {
		return ePropertyType::Double;
	}
	buw::ePropertyType operator()(const std::string& /*value*/) const {
		return ePropertyType::String;
	}
	buw::ePropertyType operator()(const std::wstring& /*value*/) const {
		return ePropertyType::WideString;
	}
	buw::ePropertyType operator()(const buw::Vector2i& /*value*/) const {
		return ePropertyType::Vector2i;
	}
	buw::ePropertyType operator()(const buw::Vector2f& /*value*/) const {
		return ePropertyType::Vector2f;
	}
	buw::ePropertyType operator()(const buw::Vector2d& /*value*/) const {
		return ePropertyType::Vector2d;
	}
	buw::ePropertyType operator()(const buw::Vector3i& /*value*/) const {
		return ePropertyType::Vector3i;
	}
	buw::ePropertyType operator()(const buw::Vector3f& /*value*/) const {
		return ePropertyType::Vector3f;
	}
	buw::ePropertyType operator()(const buw::Vector3d& /*value*/) const {
		return ePropertyType::Vector3d;
	}
	buw::ePropertyType operator()(const buw::Vector4i& /*value*/) const {
		return ePropertyType::Vector4i;
	}
	buw::ePropertyType operator()(const buw::Vector4f& /*value*/) const {
		return ePropertyType::Vector4f;
	}
	buw::ePropertyType operator()(const buw::Vector4d& /*value*/) const {
		return ePropertyType::Vector4d;
	}

	determine_type() = default;
};

ePropertyType PropertySet::getPropertyType(const std::string& name) const {
	auto it = properties_.find(name);

	if (it != properties_.end()) {
		return boost::apply_visitor(determine_type{}, it->second);
	}

	return ePropertyType::Invaild;
}

size_t PropertySet::getPropertyCount() const {
	return properties_.size();
}

std::vector<std::string> PropertySet::getPropertyNames() const {
	std::vector<std::string> names;

	for (auto it = properties_.begin(); it != properties_.end(); it++) {
		names.push_back(it->first);
	}

	return names;
}

bool PropertySet::isEmpty() const {
	if (properties_.size() == 0) {
		return true;
	}

	return false;
}

void PropertySet::add(const PropertySet& ps) {
	for (auto it = ps.properties_.begin(); it != ps.properties_.end(); it++) {
		if (properties_.find(it->first) != properties_.end()) {
			throw buw::Exception("Property exists already");
		} else {
			properties_[it->first] = it->second;
		}
	}
}

void PropertySet::addValue(const std::string& name, const bool& value) {
	addBoolean(name, value);
}

void PropertySet::addValue(const std::string& name, const float& value) {
	addFloat(name, value);
}

void PropertySet::addValue(const std::string& name, const int& value) {
	addInteger(name, value);
}

std::ostream& operator<<(std::ostream& os, const PropertySet& ps) {
	std::vector<std::string> names = ps.getPropertyNames();

	for (std::string name : names) {
		switch (ps.getPropertyType(name)) {
		case ePropertyType::Boolean: os << name.c_str() << " " << ps.getBoolean(name) << std::endl; break;
		case ePropertyType::Integer: os << name.c_str() << " " << ps.getInteger(name) << std::endl; break;
		case ePropertyType::Float: os << name.c_str() << " " << ps.getFloat(name) << std::endl; break;
		case ePropertyType::Double: os << name.c_str() << " " << ps.getDouble(name) << std::endl; break;
		case ePropertyType::String: os << name.c_str() << " " << ps.getString(name).c_str() << std::endl; break;
		case ePropertyType::WideString: os << name.c_str() << " " << buw::String::toStdString(ps.getWString(name)).c_str() << std::endl; break;
		case ePropertyType::Vector2i: os << name.c_str() << " " << ps.getVector2i(name) << std::endl; break;
		case ePropertyType::Vector2f: os << name.c_str() << " " << ps.getVector2f(name) << std::endl; break;
		case ePropertyType::Vector2d: os << name.c_str() << " " << ps.getVector2d(name) << std::endl; break;
		case ePropertyType::Vector3i: os << name.c_str() << " " << ps.getVector3i(name) << std::endl; break;
		case ePropertyType::Vector3f: os << name.c_str() << " " << ps.getVector3f(name) << std::endl; break;
		case ePropertyType::Vector3d: os << name.c_str() << " " << ps.getVector3d(name) << std::endl; break;
		case ePropertyType::Vector4i: os << name.c_str() << " " << ps.getVector4i(name) << std::endl; break;
		case ePropertyType::Vector4f: os << name.c_str() << " " << ps.getVector4f(name) << std::endl; break;
		case ePropertyType::Vector4d: os << name.c_str() << " " << ps.getVector4d(name) << std::endl; break;
		default: os << "Unknown property." << std::endl; break;
		}
	}

	return os;
}

BLUEFRAMEWORK_CORE_NAMESPACE_END