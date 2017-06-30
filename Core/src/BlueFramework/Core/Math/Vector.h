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
#ifndef BlueFramework_Core_Math_vector_3459a866_f342_45fc_909e_d6464f71a9e7_h
#define BlueFramework_Core_Math_vector_3459a866_f342_45fc_909e_d6464f71a9e7_h

#include <BlueFramework/Core/Math/constants.h>
#include <BlueFramework/Core/namespace.h>
#include <Eigen/Dense>

namespace Eigen {
#define EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)   \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, Size> Matrix##SizeSuffix##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix;

#define EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, Size)         \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Size, Dynamic> Matrix##Size##X##TypeSuffix;  \
/** \ingroup matrixtypedefs */                                    \
typedef Matrix<Type, Dynamic, Size> Matrix##X##Size##TypeSuffix;

#define EIGEN_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4) \
EIGEN_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 2) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 3) \
EIGEN_MAKE_FIXED_TYPEDEFS(Type, TypeSuffix, 4)

EIGEN_MAKE_TYPEDEFS_ALL_SIZES(std::uint8_t, b)  // Proposed extension for Eigen

#undef EIGEN_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGEN_MAKE_TYPEDEFS
#undef EIGEN_MAKE_FIXED_TYPEDEFS

} // end namespace Eigen

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

template <typename Scalar, int RowsAtCompileTime>
using Vector = Eigen::Matrix<Scalar, RowsAtCompileTime, 1>;

typedef Eigen::Vector2b Vector2b;
typedef Eigen::Vector2i Vector2i;
typedef Eigen::Vector2f Vector2f;
typedef Eigen::Vector2d Vector2d;

typedef Eigen::Vector3b Vector3b;
typedef Eigen::Vector3i Vector3i;
typedef Eigen::Vector3f Vector3f;
typedef Eigen::Vector3d Vector3d;

typedef Eigen::Vector4b Vector4b;
typedef Eigen::Vector4i Vector4i;
typedef Eigen::Vector4f Vector4f;
typedef Eigen::Vector4d Vector4d;

template <typename Scalar>
Scalar minimalComponent(const Vector<Scalar, 3>& v) {
	return std::min(std::min(v.x(), v.y()), v.z());
}

template <typename Scalar>
Vector<Scalar, 3> minimizedVector(const Vector<Scalar, 3>& a, const Vector<Scalar, 3>& b) {
	Vector<Scalar, 3> r;

	r.x() = std::min(a.x(), b.x());
	r.y() = std::min(a.y(), b.y());
	r.z() = std::min(a.z(), b.z());

	return r;
}

template <typename Scalar>
Vector<Scalar, 3> maximizedVector(const Vector<Scalar, 3>& a, const Vector<Scalar, 3>& b) {
	Vector<Scalar, 3> r;

	r.x() = std::max(a.x(), b.x());
	r.y() = std::max(a.y(), b.y());
	r.z() = std::max(a.z(), b.z());

	return r;
}

template <typename Scalar>
Scalar calculateAngleBetweenVectorsHalfCircle(const Vector<Scalar, 3>& v1, const Vector<Scalar, 3>& v2) {
	if (v1 == Vector<Scalar, 3>(0, 0, 0) || v2 == Vector<Scalar, 3>(0, 0, 0)) {
		return 0.0; // Invalid vector
	}

	Scalar a = v1.squaredNorm();
	Scalar b = v2.squaredNorm();

	if (a * b == 0) {
		return 0; // Invalid vector
	}

	if (a > 0 && b > 0) {
		float sign = minimalComponent(v1.cross(v2));

		// prevent division by 0
		if (a * b == 0) {
			return 0;
		}

		if (sign < 0)
			return -acos(v1.dot(v2) / sqrtf(a * b));
		else
			return acos(v1.dot(v2) / sqrtf(a * b));
	}

	return 0;
}

template <typename Scalar>
Scalar calculateAngleBetweenVectors(const Vector<Scalar, 3>& v1, const Vector<Scalar, 3>& v2) {
	Scalar angle = calculateAngleBetweenVectorsHalfCircle(v1, v2);

	if (angle < 0)
		angle += 2.0 * buw::constants<Scalar>::pi();

	return static_cast<float>(angle);
}

template <typename Scalar>
Scalar calculateAngleBetweenVectors(const Vector<Scalar, 2>& v1, const Vector<Scalar, 2>& v2) {
	Scalar angle = calculateAngleBetweenVectorsHalfCircle(Vector<Scalar, 3>(v1.x(), v1.y(), 0), Vector<Scalar, 3>(v2.x(), v2.y(), 0));

	if (angle < 0)
		angle += 2.0 * buw::constants<Scalar>::pi();

	return static_cast<float>(angle);
}

template <typename Scalar, int RowsAtCompileTime>
Scalar distance(const Vector<Scalar, RowsAtCompileTime>& v1, const Vector<Scalar, RowsAtCompileTime>& v2) {
	return (v1 - v2).norm();
}

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector2b)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector2d)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector2f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector2i)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector3b)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector3d)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector3f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector3i)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector4b)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector4d)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector4f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Vector4i)

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(calculateAngleBetweenVectors)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(distance)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(maximizedVector)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(minimizedVector)

#endif // end define BlueFramework_Core_Math_vector_3459a866_f342_45fc_909e_d6464f71a9e7_h
