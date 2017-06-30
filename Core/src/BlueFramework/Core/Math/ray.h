// Copied and modified code from "Nori Version 2".
// This library is available under the GPL v3. Original copyright notice:

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

#include "BlueFramework/Core/Math/vector.h"

/* "Ray epsilon": relative error threshold for ray intersection computations */
#define BLUEFAMEWORK_RAY_EPSILON 1e-4f

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

template <typename ScalarType, typename PointType, typename VectorType>
struct ray {
	PointType origin;               ///< Ray origin.
	VectorType direction;           ///< Ray direction (not necessarily unit-length).
	VectorType directionReciprocal; ///< Component wise reciprocals of the ray direction.
	ScalarType mint;                ///<  Minimum position on the ray segment (inclusive).
	ScalarType maxt;                ///<  Maximum position on the ray segment (exclusive).

	//! Construct a new ray
	inline ray() : mint(BLUEFAMEWORK_RAY_EPSILON), maxt(std::numeric_limits<ScalarType>::infinity()) {
	}

	//! Construct a new ray
	inline ray(const PointType &o, const VectorType &d) : origin(o), direction(d), mint(BLUEFAMEWORK_RAY_EPSILON), maxt(std::numeric_limits<ScalarType>::infinity()) {
		update();
	}

	//! Construct a new ray
	inline ray(const PointType &origin, const VectorType &d, const ScalarType mint, const ScalarType maxt) : origin(origin), direction(d), mint(mint), maxt(maxt) {
		update();
	}

	//! Copy constructor
	inline ray(const ray &ray) : origin(ray.origin), direction(ray.direction), directionReciprocal(ray.directionReciprocal), mint(ray.mint), maxt(ray.maxt) {
	}

	//! Copy a ray, but change the covered segment of the copy
	inline ray(const ray &ray, const ScalarType mint, const ScalarType maxt)
	    : origin(ray.origin), direction(ray.direction), directionReciprocal(ray.directionReciprocal), mint(mint), maxt(maxt) {
	}

	//! Update the reciprocal ray directions after changing 'd'
	inline void update() {
		directionReciprocal = direction.cwiseInverse();
	}

	//! Return the position of a point along the ray.
	inline PointType operator()(const ScalarType t) const {
		return origin + t * direction;
	}

	//! Return a ray that points into the opposite direction.
	inline ray reverse() const {
		ray result;
		result.orgin = origin;
		result.direction = -direction;
		result.directionReciprocal = -directionReciprocal;
		result.mint = mint;
		result.maxt = maxt;
		return result;
	}
}; // end struct ray

template <typename ScalarType, typename PointType, typename VectorType>
inline std::ostream &operator<<(std::ostream &os, const ray<ScalarType, PointType, VectorType> &r) {
	os << "[";

	os << "ray: origin " << r.origin << " direction " << r.direction;

	os << "]";

	return os;
}

typedef ray<float, Vector<float, 3>, Vector<float, 3>> ray3f;
typedef ray<double, Vector<double, 3>, Vector<double, 3>> ray3d;

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(ray)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(ray3f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(ray3d)
