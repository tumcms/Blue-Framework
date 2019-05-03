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
#ifndef BlueFramework_Core_Math_plane333_13d2064d_8e50_415a_b3c1_8f327f714c5f_h
#define BlueFramework_Core_Math_plane333_13d2064d_8e50_415a_b3c1_8f327f714c5f_h

#include "BlueFramework/Core/Math/matrix.h"
#include "BlueFramework/Core/Math/ray.h"
#include "BlueFramework/Core/Math/vector.h"

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

//! \brief Plane stored in the form ax + by + cz + d = 0
//!
//! Let n(a, b, c) be a normal vector of the plane. x(x,y,z) is a vector of a arbitrary point and
template <typename T>
struct plane3 {
	//! coefficents a, b, c and d a stored here (ax + by + cz + d = 0)
	Vector<T, 4> coefficents;

	//! Creates a plane.
	plane3();

	//! A plane can be defined by its normal vector an a point that lies on the plane.
	/*!
	    \param normal	unit normal vector of the plane
	    \param p		a point on the plane
	*/
	plane3(const Vector<T, 3> &normal, const Vector<T, 3> &p);

	//! A plane in the form in the form ax + by + cz + d = 0
	plane3(T A, T B, T C, T D);

	//! Construct from point vectors
	plane3(const Vector<T, 3> &v0, const Vector<T, 3> &v1, const Vector<T, 3> &v2);

	//! Unit normal vector of plane
	Vector<T, 3> normal() const;

	Vector<T, 3> getPoint() const {
		float x = coefficents.x() == 0 ? 0 : -coefficents.w() / coefficents.x();
		float y = coefficents.y() == 0 ? 0 : -coefficents.w() / coefficents.y();
		float z = coefficents.z() == 0 ? 0 : -coefficents.w() / coefficents.z();

		return Vector<T, 3>(x, y, z);
	}

	T d() const {
		return coefficents.w();
	}

	//! Calculates the distance from a homogeneous point (x, y, z, w) to the plane.
	/*!
	    \param p	A homogeneous point.
	    \return	Distance between point and plane.
	*/
	T calculateDistance(const Vector<T, 4> &p) const;
}; // end struct plane3

typedef plane3<float> plane3f;
typedef plane3<double> plane3d;

plane3f operator*(const Matrix44f &m, const plane3f &p);

template <typename T>
bool Intersect(const ray<T, Vector<T, 3>, Vector<T, 3>> &ray, const plane3<T> &plane, Vector<T, 3> &result) {
	T denom = ray.direction * plane.normal();
	if (std::abs(denom) < 0.0001) {
		// no intersection, ray is parallel
		return false; // fixme - ray could be also in the plane
	}
	T t = -(ray.origin * plane.normal() + plane.coefficents.w()) / denom;
	result = ray.origin + t * ray.direction;
	return true;
}

template <typename T>
Vector<T, 3> Intersect(const ray<T, Vector<T, 3>, Vector<T, 3>> &ray, const plane3<T> &plane) {
	Vector<T, 3> ret;
	if (Intersect(ray, plane, ret)) {
		return ret;
	} else {
		return Vector<T, 3>(0, 0, 0);
	}
}

template <typename T>
std::ostream &operator<<(std::ostream &o, const plane3<T> &p) {
	return o << "(" << p.coefficents << ")";
}

template <typename T>
plane3<T>::plane3() {
	coefficents = Vector<T, 4>(0, 1, 0, 0);
}

template <typename T>
plane3<T>::plane3(const Vector<T, 3> &normal, const Vector<T, 3> &p) {
	coefficents.x() = normal.x();
	coefficents.y() = normal.y();
	coefficents.z() = normal.z();
	coefficents.w() = -normal * p;
}

template <typename T>
plane3<T>::plane3(T A, T B, T C, T D) : coefficents(A, B, C, D) {
}

template <typename T>
plane3<T>::plane3(const Vector<T, 3> &v0, const Vector<T, 3> &v1, const Vector<T, 3> &v2) {
	Vector<T, 3> normal = ((v1 - v0) ^ (v2 - v0)).normalize();

	coefficents.x() = normal.x();
	coefficents.y() = normal.y();
	coefficents.z() = normal.z();
	coefficents.w() = -normal * v1;
}

template <typename T>
Vector<T, 3> plane3<T>::normal() const {
	return Vector<T, 3>(coefficents.x(), coefficents.y(), coefficents.z());
}

template <typename T>
T plane3<T>::calculateDistance(const Vector<T, 4> &p) const {
	return coefficents * p;
}

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(plane3)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(plane3f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(plane3d)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(operator*)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Intersect)

#endif // end define BlueFramework_Core_Math_plane333_13d2064d_8e50_415a_b3c1_8f327f714c5f_h