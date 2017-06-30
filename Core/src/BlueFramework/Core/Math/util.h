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

#include "BlueFramework/Core/namespace.h"

#pragma once
#ifndef BlueFramework_Core_Math_util_6b3f6d1c_d23a_4641_b619_b13fbd3aa260_h
#define BlueFramework_Core_Math_util_6b3f6d1c_d23a_4641_b619_b13fbd3aa260_h

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

typedef float radianf;
typedef double radiand;
typedef float degreef;
typedef double degreed;

template <typename T>
inline bool isNotANumber(const T value) {
	return value != value;
}

template <typename T>
inline bool isNaN(const T value) {
	return value != value;
}

template <typename T>
inline bool isInfinite(const T value) {
	return std::numeric_limits<T>::has_infinity && (value == std::numeric_limits<T>::infinity());
}

// bool isPower2(int x)
//{
//	return ((x > 0) && ((x & (x - 1)) == 0));
//}

template <typename T>
T log2(const T value) {
	return log(value) / log(static_cast<T>(2));
}

template <typename T, typename ScalarType>
T lerp(const T &a, const T &b, const ScalarType t) {
	// Performs a linear interpolation between [a;b].
	//  P(t) = (1 - t)a + tb
	//       = a + t(b - a)
	//
	//  where
	//  t in range [0,1]
	return a + (b - a) * t;
}

template <typename T>
T smoothstep(const T a, const T b, T x) {
	// Returns a gradual transition of 'x' from 0 to 1 beginning at
	// threshold 'a' and ending at threshold 'b'.
	//
	// References:
	//  [1] http://www.rendermanacademy.com/docs/smoothstep.htm
	//  [2] http://www.brlcad.org/doxygen/d8/d33/noise_8c-source.html
	//  [3] Natalya Tatarchuk, "Efficient High-Level Shader Development",
	//      Game Developers Conference Europe, August 2003.

	if (x < a) {
		return 0.0f;
	} else if (x >= b) {
		return 1.0f;
	} else {
		x = (x - a) / (b - a);
		return x * x * (3.0f - 2.0f * x);
	}
}

// floating-point modulo operator,
// the quotient rounds towards negative infinity and the remainder has same sign as the divisor
// Mod(-3,4)= 1 while fmod(-3,4)= -3
template <typename T>
T mod(T x, T y) {
	static_assert(!std::numeric_limits<T>::is_exact, "Mod: floating-point type expected");

	if (0 == y)
		return x;

	return x - y * floor(x / y);
}

//! Converts degrees to radians
/*!
\param i_Degree	Angle in degrees.
\return	Angle in radians.
*/
template <typename T>
T degreeToRadian(T i_Degree) {
	static_assert(!std::numeric_limits<T>::is_exact, "degreeToRadian: floating-point type expected");

	return i_Degree * static_cast<T>(0.01745329251994329577);
}

//! Converts radians to degrees
/*!
\param i_Rad	Angle in radians.
\return	Angle in degrees.
*/
template <typename T>
T radianToDegree(T i_Rad) {
	return i_Rad * static_cast<T>(57.295779513082320876798154814105);
}

//! Clamps a value to a certain range
/*!
\param value	value that should be clamped.
\param lowerBound	lower bound of range.
\parma upperBound	upper bound of range.
\return	clamp value in the range [lowerBound;upperBound]
*/
template <typename T>
inline T clamp(const T value, const T lowerBound, const T upperBound) {
	if (value <= lowerBound)
		return lowerBound;
	else if (value >= upperBound)
		return upperBound;
	else
		return value;
}

#ifdef min
#undef min
#endif // min

#ifdef max
#undef max
#endif // max

template <typename T>
inline T min(const T x, const T y) {
	if (x < y)
		return x;
	else
		return y;
}

template <typename T>
inline T min(const T x, const T y, const T z) {
	return min(min(x, y), z);
}

template <typename T>
inline T max(const T x, const T y) {
	if (x < y)
		return y;
	else
		return x;
}

template <typename T>
inline T max(const T x, const T y, const T z) {
	return max(max(x, y), z);
}

template <typename T>
inline T ceil(T t) {
	return std::ceil(t);
}
template <typename T>
inline T floor(T t) {
	return std::floor(t);
}

double round(const double val, const int precision);

double factorial(const int n);

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(radianf)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(radiand)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(degreef)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(degreed)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(isNotANumber)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(isNaN)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(isInfinite)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(log2)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(lerp)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(smoothstep)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(mod)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(degreeToRadian)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(radianToDegree)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(clamp)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(min)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(max)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(ceil)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(floor)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(round)
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(factorial)

#endif // end define BlueFramework_Core_Math_util_6b3f6d1c_d23a_4641_b619_b13fbd3aa260_h
