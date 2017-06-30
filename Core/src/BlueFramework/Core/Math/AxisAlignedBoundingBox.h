// Copied and modified code from "OGRE" library.
// This library is available under the MIT license. Original copyright notice:

// OGRE(www.ogre3d.org) is made available under the MIT License.
//
// Copyright(c) 2000 - 2015 Torus Knot Software Ltd
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// More details can be found in README.md file in the root directory.

#pragma once
#ifndef BlueFramework_BlueEngine_AxisAlignedBox_1a01f0c7_5af8_47ef_9330_5e91343a4f32_h
#define BlueFramework_BlueEngine_AxisAlignedBox_1a01f0c7_5af8_47ef_9330_5e91343a4f32_h

#include "BlueFramework/Core/Math/plane.h"
#include "BlueFramework/Core/Math/ray.h"
#include "BlueFramework/Core/Math/vector.h"
#include "BlueFramework/Core/assert.h"
#include <BlueFramework/Core/namespace.h>

#include "BlueFramework/Core/Noncopyable.h"

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

// http://www.ogre3d.org/docs/api/html/OgreAxisAlignedBox_8h_source.html
template <typename ScalarType>
class AxisAlignedBoundingBox3 {
public:
	typedef buw::Vector<ScalarType, 3> vector3;
	typedef buw::plane3<ScalarType> plane3;
	typedef buw::ray<ScalarType, vector3, vector3> ray;

	enum Extent { EXTENT_NULL, EXTENT_FINITE, EXTENT_INFINITE };

private:
	typedef AxisAlignedBoundingBox3<ScalarType> thistype;

	inline AxisAlignedBoundingBox3(Extent extent) : minimum_(0.0, 0.0, 0.0), maximum_(0.0, 0.0, 0.0), extent_(extent) {
	}

protected:
	vector3 minimum_;
	vector3 maximum_;
	Extent extent_;

public:
	/*
	   1-----2
	   /|    /|
	   / |   / |
	   5-----4  |
	   |  0--|--3
	   | /   | /
	   |/    |/
	   6-----7
	   */
	typedef enum {
		Far_Left_Bottom = 0,
		Far_Left_Top = 1,
		Far_Right_Top = 2,
		Far_Right_Bottom = 3,
		Near_Right_Bottom = 7,
		Near_Left_Bottom = 6,
		Near_Left_Top = 5,
		Near_Right_Top = 4
	} CornerEnum;

	typedef enum {
		Left_Side = 0,
		Right_Side = 1,
		Top_Side = 2,
		Bottom_Side = 3,
		Far_Side = 4,
		Near_Side = 5,
	} SideEnum;

	typedef enum {
		No_Intersection = 0,
		One_Intersection = 1,
		Two_Intersections = 2,
	} IntersectionType;

public:
	// Default to a null box
	inline AxisAlignedBoundingBox3() : AxisAlignedBoundingBox3(EXTENT_NULL) {
	}

	inline AxisAlignedBoundingBox3(const vector3& _min, const vector3& _max) {
		setExtents(_min, _max);
	}

	// Sets both minimum and maximum extents at once.
	inline void setExtents(const vector3& _min, const vector3& _max) {
		BLUE_ASSERT(_min.x() <= _max.x() && _min.y() <= _max.y() && _min.z() <= _max.z(), "The minimum corner of the box must be less than or equal to maximum corner");

		extent_ = EXTENT_FINITE;
		minimum_ = _min;
		maximum_ = _max;
	}

	/** Gets the minimum corner of the box.
	*/
	inline const vector3& getMinimum(void) const {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get minimum of a null or infinite AAB");

		return minimum_;
	}

	/** Gets a modifiable version of the minimum
	corner of the box.
	*/
	inline vector3& getMinimum(void) {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get minimum of a null or infinite AAB");

		return minimum_;
	}

	/** Gets the maximum corner of the box.
	*/
	inline const vector3& getMaximum(void) const {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get maximum of a null or infinite AAB");

		return maximum_;
	}

	/** Gets a modifiable version of the maximum
	corner of the box.
	*/
	inline vector3& getMaximum(void) {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get maximum of a null or infinite AAB");

		return maximum_;
	}

	inline void setMinimum(const vector3& vec) {
		extent_ = EXTENT_FINITE;
		minimum_ = vec;
	}

	inline void setMaximum(const vector3& vec) {
		extent_ = EXTENT_FINITE;
		maximum_ = vec;
	}

	/*
	inline void setMinimum( T x, T y, T z )
	{
	mExtent = EXTENT_FINITE;
	mMinimum = vector3(x, y, z);
	}

	inline void setMaximum(  T x, T y, T z )
	{
	mExtent = EXTENT_FINITE;
	mMaximum = vector3(x, y, z);
	}
	*/

	/** gets the position of one of the corners
	*/
	vector3 getCorner(CornerEnum cornerToGet) const {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get corners of a null or infinite AAB");
		switch (cornerToGet) {
		case Far_Left_Bottom: return minimum_;
		case Far_Left_Top: return vector3(minimum_.x(), maximum_.y(), minimum_.z());
		case Far_Right_Top: return vector3(maximum_.x(), maximum_.y(), minimum_.z());
		case Far_Right_Bottom: return vector3(maximum_.x(), minimum_.y(), minimum_.z());
		case Near_Right_Bottom: return vector3(maximum_.x(), minimum_.y(), maximum_.z());
		case Near_Left_Bottom: return vector3(minimum_.x(), minimum_.y(), maximum_.z());
		case Near_Left_Top: return vector3(minimum_.x(), maximum_.y(), maximum_.z());
		case Near_Right_Top: return maximum_;
		default: return vector3();
		}
	}

	plane3 getSide(SideEnum sideToGet) const {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get sides of a null or infinite AAB");
		switch (sideToGet) {
		case Left_Side: return plane3(getCorner(Far_Left_Bottom), getCorner(Near_Left_Bottom), getCorner(Near_Left_Top));
		case Right_Side: return plane3(getCorner(Far_Right_Bottom), getCorner(Near_Right_Bottom), getCorner(Near_Right_Top));
		case Top_Side: return plane3(getCorner(Near_Left_Top), getCorner(Near_Right_Top), getCorner(Far_Left_Top));
		case Bottom_Side: return plane3(getCorner(Near_Left_Bottom), getCorner(Near_Right_Bottom), getCorner(Far_Left_Bottom));
		case Far_Side: return plane3(getCorner(Far_Left_Bottom), getCorner(Far_Left_Top), getCorner(Far_Right_Top));
		case Near_Side: return plane3(getCorner(Near_Left_Bottom), getCorner(Near_Left_Top), getCorner(Near_Right_Top));
		default: return plane3();
		}
	}

	vector3 getCenter() const {
		BLUE_ASSERT((extent_ == EXTENT_FINITE), "Can't get center of a null or infinite AAB");

		return getMinimum() + static_cast<ScalarType>(0.5) * (getMaximum() - getMinimum());
	}

	static thistype Union(const thistype& x, const thistype& y) {
		// both null -> result also null
		if (x.extent_ == EXTENT_NULL && y.extent_ == EXTENT_NULL) {
			return thistype(EXTENT_NULL);
		}
		// one of them null -> result == the other
		if (x.extent_ == EXTENT_NULL) {
			return y;
		}
		if (y.extent_ == EXTENT_NULL) {
			return x;
		}
		// one of them infinite -> result infinite
		if (x.extent_ == EXTENT_INFINITE || y.extent_ == EXTENT_INFINITE) {
			return thistype(EXTENT_INFINITE);
		}
		// both finite -> union
		buw::vector3f pMin, pMax;
		pMin.x() = min(x.getMinimum().x(), y.getMinimum().x());
		pMin.y() = min(x.getMinimum().y(), y.getMinimum().y());
		pMin.z() = min(x.getMinimum().z(), y.getMinimum().z());
		pMax.x() = max(x.getMaximum().x(), y.getMaximum().x());
		pMax.y() = max(x.getMaximum().y(), y.getMaximum().y());
		pMax.z() = max(x.getMaximum().z(), y.getMaximum().z());
		return thistype(pMin, pMax);
	}

	bool Contains(const vector3& point) const {
		if (extent_ == EXTENT_NULL) {
			return false; // null-box contains nothing
		}
		if (extent_ == EXTENT_INFINITE) {
			return true; // infinite-box contains everything
		}
		// finite-box
		return minimum_.x() <= point.x() && point.x() <= maximum_.x() && minimum_.y() <= point.y() && point.y() <= maximum_.y() && minimum_.z() <= point.z()
		       && point.z() <= maximum_.z();
	}

	IntersectionType Intersect(const ray& ray, vector3 (&points)[2]) const {
		if (extent_ == EXTENT_NULL) {
			return No_Intersection; // null-box intersects nothing
		}
		if (extent_ == EXTENT_INFINITE) {
			return No_Intersection; // infinite-box intersects nothing
		}
		// finite-box
		int intersections = 0;
		// check planes
		SideEnum sides[] = {Left_Side, Right_Side, Top_Side, Bottom_Side, Far_Side, Near_Side};
		for (SideEnum s : sides) {
			if (buw::Intersect(ray, getSide(s), points[intersections])) {
				if (Contains(points[intersections])) {
					intersections++;
					if (intersections >= 2) {
						return Two_Intersections;
					}
				}
			}
		}
		if (intersections == 0) {
			return No_Intersection;
		}
		if (intersections == 1) {
			return One_Intersection;
		}
		if (intersections == 2) {
			return Two_Intersections;
		}
		BLUE_ASSERT(false, "Unexpected!");
		return No_Intersection;
	}
};

template <typename T>
AxisAlignedBoundingBox3<T> Union(const AxisAlignedBoundingBox3<T>& b, const AxisAlignedBoundingBox3<T>& b2) {
	return AxisAlignedBoundingBox3<T>::Union(b, b2);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const AxisAlignedBoundingBox3<T>& aabb) {
	os << "[";

	os << " " << aabb.getMinimum() << " " << aabb.getMaximum();

	os << " ]";

	return os;
}

typedef AxisAlignedBoundingBox3<float> AxisAlignedBoundingBox3f;
typedef AxisAlignedBoundingBox3<double> AxisAlignedBoundingBox3d;

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(AxisAlignedBoundingBox3f)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(AxisAlignedBoundingBox3d)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Union)

#endif // end define BlueFramework_BlueEngine_AxisAlignedBox_1a01f0c7_5af8_47ef_9330_5e91343a4f32_h