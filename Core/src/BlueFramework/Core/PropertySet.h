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

#pragma once
#ifndef BlueFramework_Core_PropertySet_b2c91733_b42e_4165_9bf0_707085cb3d3c_h
#define BlueFramework_Core_PropertySet_b2c91733_b42e_4165_9bf0_707085cb3d3c_h

#include "BlueFramework/Core/Math/vector.h"
#include "BlueFramework/Core/namespace.h"
#include <boost/variant.hpp>
#include <map>
#include <ostream>
#include <string>
#include <vector>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

enum class ePropertyType { Boolean, Integer, Float, Double, String, WideString, Vector2i, Vector2f, Vector2d, Vector3i, Vector3f, Vector3d, Vector4i, Vector4f, Vector4d, Invaild };

template <typename T>
struct PropertySetItem {
    PropertySetItem(const std::string& name, const T* val, int nValues = 1);

    const std::string name;
    const std::unique_ptr<T[]> values;
    const int nValues;
    mutable bool lookedUp = false;
};

//! \brief Provides a container for properties. Each property has a unique name.
//! Properties with the same name but different types are not allowed. A new property
//! can be added to the property set using the corresponding add method. A property
//! value can be updated by calling the corresponding set method.
class PropertySet {
public:
    PropertySet();

    virtual ~PropertySet();

    //! Clears the property set
    void clear();

    //! Checks if a certain property is available
    bool contains(const std::string& name) const;

    //! Determines the type of property
    ePropertyType getPropertyType(const std::string& name) const;

    //! Get the number of properties contained in this property set
    size_t getPropertyCount() const;

    //! Checks if this property set is empty.
    bool isEmpty() const;

    //! Retrieve the names of all containing properties.
    std::vector<std::string> getPropertyNames() const;

    //! Add all properties of the given one to to current one.
    void add(const PropertySet& ps);

    //---------------------------------------------------------------------------//
    // Add/set/get properties
    //---------------------------------------------------------------------------//

    void addBoolean(const std::string& name, const bool& value);
    void addInteger(const std::string& name, const int& value);
    void addFloat(const std::string& name, const float& value);
    void addDouble(const std::string& name, const double& value);
    void addString(const std::string& name, const std::string& value);
    void addWString(const std::string& name, const std::wstring& value);
    void addVector2i(const std::string& name, const buw::Vector2i& value);
    void addVector2f(const std::string& name, const buw::Vector2f& value);
    void addVector2d(const std::string& name, const buw::Vector2d& value);
    void addVector3i(const std::string& name, const buw::Vector3i& value);
    void addVector3f(const std::string& name, const buw::Vector3f& value);
    void addVector3d(const std::string& name, const buw::Vector3d& value);
    void addVector4i(const std::string& name, const buw::Vector4i& value);
    void addVector4f(const std::string& name, const buw::Vector4f& value);
    void addVector4d(const std::string& name, const buw::Vector4d& value);

    void addValue(const std::string& name, const bool& value);
    void addValue(const std::string& name, const int& value);
    void addValue(const std::string& name, const float& value);

    void setBoolean(const std::string& name, const bool& value);
    void setInteger(const std::string& name, const int& value);
    void setFloat(const std::string& name, const float& value);
    void setDouble(const std::string& name, const double& value);
    void setString(const std::string& name, const std::string& value);
    void setWString(const std::string& name, const std::wstring& value);
    void setVector2i(const std::string& name, const buw::Vector2i& value);
    void setVector2f(const std::string& name, const buw::Vector2f& value);
    void setVector2d(const std::string& name, const buw::Vector2d& value);
    void setVector3i(const std::string& name, const buw::Vector3i& value);
    void setVector3f(const std::string& name, const buw::Vector3f& value);
    void setVector3d(const std::string& name, const buw::Vector3d& value);
    void setVector4i(const std::string& name, const buw::Vector4i& value);
    void setVector4f(const std::string& name, const buw::Vector4f& value);
    void setVector4d(const std::string& name, const buw::Vector4d& value);

    bool getBoolean(const std::string& name) const;
    int getInteger(const std::string& name) const;
    float getFloat(const std::string& name) const;
    double getDouble(const std::string& name) const;
    std::string getString(const std::string& name) const;
    std::wstring getWString(const std::string& name) const;
    buw::Vector2i getVector2i(const std::string& name) const;
    buw::Vector2f getVector2f(const std::string& name) const;
    buw::Vector2d getVector2d(const std::string& name) const;
    buw::Vector3i getVector3i(const std::string& name) const;
    buw::Vector3f getVector3f(const std::string& name) const;
    buw::Vector3d getVector3d(const std::string& name) const;
    buw::Vector4i getVector4i(const std::string& name) const;
    buw::Vector4f getVector4f(const std::string& name) const;
    buw::Vector4d getVector4d(const std::string& name) const;

    bool getBoolean(const std::string& name, const bool& defaultValue) const;
    int getInteger(const std::string& name, const int& defaultValue) const;
    float getFloat(const std::string& name, const float& defaultValue) const;
    double getDouble(const std::string& name, const double& defaultValue) const;
    std::string getString(const std::string& name, const std::string& defaultValue) const;
    std::wstring getWString(const std::string& name, const std::wstring& defaultValue) const;
    buw::Vector2i getVector2i(const std::string& name, const buw::Vector2i& defaultValue) const;
    buw::Vector2f getVector2f(const std::string& name, const buw::Vector2f& defaultValue) const;
    buw::Vector2d getVector2d(const std::string& name, const buw::Vector2d& defaultValue) const;
    buw::Vector3i getVector3i(const std::string& name, const buw::Vector3i& defaultValue) const;
    buw::Vector3f getVector3f(const std::string& name, const buw::Vector3f& defaultValue) const;
    buw::Vector3d getVector3d(const std::string& name, const buw::Vector3d& defaultValue) const;
    buw::Vector4i getVector4i(const std::string& name, const buw::Vector4i& defaultValue) const;
    buw::Vector4f getVector4f(const std::string& name, const buw::Vector4f& defaultValue) const;
    buw::Vector4d getVector4d(const std::string& name, const buw::Vector4d& defaultValue) const;

private:
    typedef boost::variant<bool,
                           int,
                           float,
                           double,
                           std::string,
                           std::wstring,
                           buw::Vector2i,
                           buw::Vector2f,
                           buw::Vector2d,
                           buw::Vector3i,
                           buw::Vector3f,
                           buw::Vector3d,
                           buw::Vector4i,
                           buw::Vector4f,
                           buw::Vector4d>
      Property;

    std::map<std::string, Property> properties_;
}; // end class PropertySet

std::ostream& operator<<(std::ostream& os, const PropertySet& ps);

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(PropertySet);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(ePropertyType);

#endif // end define BlueFramework_Core_PropertySet_b2c91733_b42e_4165_9bf0_707085cb3d3c_h
