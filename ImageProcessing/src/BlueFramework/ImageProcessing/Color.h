// Copied and modified code from "appleseed" library.
// This library is available under the MIT license. Original copyright notice:

//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2011 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// More details can be found in README.md file in the root directory.

#pragma once
#ifndef BlueFramework_ImageProcessing_Color_a6e437c4_de88_4d75_acb1_70d78886fbe5_h
#define BlueFramework_ImageProcessing_Color_a6e437c4_de88_4d75_acb1_70d78886fbe5_h

#include <algorithm>
#include <boost/math/special_functions/fpclassify.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "BlueFramework/ImageProcessing/namespace.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

//
// N-dimensional color class and operations.
//
template <typename T, size_t N>
class Color {
public:
	// Value type and number of components.
	typedef T ValueType;
	static const size_t Components = N;

	// Constructors.
	Color();                              // leave all components uninitialized
	explicit Color(const ValueType* rhs); // initialize with array of N scalars
	explicit Color(const ValueType val);  // set all components to 'val'

	// Construct a color from another color of a different type.
	template <typename U>
	explicit Color(const Color<U, N>& rhs);

	// Set all components to a given value.
	void set(const ValueType val);

	// Unchecked array subscripting.
	ValueType& operator[](const size_t i);
	const ValueType& operator[](const size_t i) const;

	// Checks if all color values are valid (non-infinite, non-negative, non-NAN)
	bool isValid() const {
		for (size_t i = 0; i < N; ++i) {
			T value = comp_[i];
			int cl = boost::math::fpclassify(value);

			if (value < 0 || cl == FP_INFINITE || cl == FP_NAN)
				return false;
		}
		return true;
	}

// swizzle functions
#include "Color2Swizzles.inc"
#include "Color3Swizzles.inc"
#include "Color4Swizzles.inc"

private:
	// Color components.
	ValueType comp_[N];
};

// Exact inequality and equality tests.
template <typename T, size_t N>
bool operator!=(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
bool operator==(const Color<T, N>& lhs, const Color<T, N>& rhs);

// Approximate equality tests.
template <typename T, size_t N>
bool feq(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
bool feq(const Color<T, N>& lhs, const Color<T, N>& rhs, const T eps);

// Approximate zero tests.
template <typename T, size_t N>
bool fz(const Color<T, N>& c);
template <typename T, size_t N>
bool fz(const Color<T, N>& c, const T eps);

// Color arithmetic.
template <typename T, size_t N>
Color<T, N> operator+(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N> operator-(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N> operator-(const Color<T, N>& lhs);
template <typename T, size_t N>
Color<T, N> operator*(const Color<T, N>& lhs, const T rhs);
template <typename T, size_t N>
Color<T, N> operator*(const T lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N> operator*(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N> operator/(const Color<T, N>& lhs, const T rhs);
template <typename T, size_t N>
Color<T, N> operator/(const Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N>& operator+=(Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N>& operator-=(Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N>& operator*=(Color<T, N>& lhs, const T rhs);
template <typename T, size_t N>
Color<T, N>& operator*=(Color<T, N>& lhs, const Color<T, N>& rhs);
template <typename T, size_t N>
Color<T, N>& operator/=(Color<T, N>& lhs, const T rhs);
template <typename T, size_t N>
Color<T, N>& operator/=(Color<T, N>& lhs, const Color<T, N>& rhs);

// Clamp the argument to [min, max].
template <typename T, size_t N>
Color<T, N> clamp(const Color<T, N>& c, const T min, const T max);

// Clamp the argument to [0,1].
template <typename T, size_t N>
Color<T, N> saturate(const Color<T, N>& c);

// Return the smallest or largest signed component of a color.
template <typename T, size_t N>
T min_value(const Color<T, N>& c);
template <typename T, size_t N>
T max_value(const Color<T, N>& c);

// Return the index of the smallest or largest signed component of a color.
template <typename T, size_t N>
size_t min_index(const Color<T, N>& c);
template <typename T, size_t N>
size_t max_index(const Color<T, N>& c);

// Return the index of the smallest or largest component of a color, in absolute value.
template <typename T, size_t N>
size_t min_abs_index(const Color<T, N>& c);
template <typename T, size_t N>
size_t max_abs_index(const Color<T, N>& c);

// Return the average value of a color.
template <typename T, size_t N>
T average_value(const Color<T, N>& c);

//
// RGB color class of arbitrary type.
//

template <typename T>
struct Color<T, 1> {
	// Value type and number of components.
	typedef T ValueType;
	static const size_t Components = 1;

	// Color components.
	ValueType g; // grayvalue

	// Constructors.
	Color();                                   // leave all components uninitialized
	explicit Color(const ValueType* rhs);      // initialize with array of 1 scalars
	explicit Color(const ValueType grayvalue); // set individual components

	// Construct a color from another color of a different type.
	template <typename U>
	explicit Color(const Color<U, 1>& rhs);

	// Set all components to a given value.
	void set(const ValueType val);

	// Unchecked array subscripting.
	ValueType& operator[](const size_t i);
	const ValueType& operator[](const size_t i) const;

	ValueType grayvalue() const {
		return (*this)[0];
	}
};

//
// RGB color class of arbitrary type.
//

template <typename T>
struct Color<T, 3> {
	// Value type and number of components.
	typedef T ValueType;
	static const size_t Components = 3;

	// Color components.
	ValueType r, g, b;

	// Constructors.
	Color();                              // leave all components uninitialized
	explicit Color(const ValueType* rhs); // initialize with array of 3 scalars
	explicit Color(const ValueType val);  // set all components to 'val'
	Color(                                // set individual components
	  const ValueType r,
	  const ValueType g,
	  const ValueType b);

	// Construct a color from another color of a different type.
	template <typename U>
	explicit Color(const Color<U, 3>& rhs);

	// Set all components to a given value.
	void set(const ValueType val);

	// Unchecked array subscripting.
	ValueType& operator[](const size_t i);
	const ValueType& operator[](const size_t i) const;

	ValueType red() const {
		return (*this)[0];
	}

	ValueType green() const {
		return (*this)[1];
	}

	ValueType blue() const {
		return (*this)[2];
	}

	// other color spaces
	double getAlpha() const {
		return -1.0;
	}

	double getBeta() const {
		return -1.0;
	}

	double getHue() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;
		double max = std::max(std::max(r, g), b);
		double min = std::min(std::min(r, g), b);

		if (max == min) {
			return 0;
		} else if (max == r) {
			return 60 * ((g - b) / (max - min));
		} else if (max == g) {
			return 60 * (2 + (b - r) / (max - min));
		} else {
			return 60 * (4 + (r - g) / (max - min));
		}
	}

	double getSaturation() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;
		double max = std::max(std::max(r, g), b);
		double min = std::min(std::min(r, g), b);

		if (max == 0) {
			return 0;
		} else {
			return (max - min) / max;
		}
	}

	double getBrightness() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;

		return std::max(std::max(r, g), b);
	}

	// needed for conversion from XYZ to sRGB
	// does not need to be accessible for the user
	double gammaEncoding(double t) {
		if (t > 0.0031308) {
			return 1.055 * pow(t, 1.0 / 2.4) - 0.055;
		} else {
			return 12.92 * t;
		}
	}

	// needed for conversion from sRGB to XYZ
	// does not need to be accessible for the user
	double inverseGammaEncoding(double t) {
		if (t > 0.04045) {
			return pow((t + 0.055) / 1.055, 2.4);
		} else {
			return t / 12.92;
		}
	}

	// get the X-Value of XYZ from sRGB value
	double getXYZ_X() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.4124564 * r + 0.3575761 * g + 0.1804375 * b;
	}

	// get the Y-Value of XYZ from sRGB value
	double getXYZ_Y() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.2126729 * r + 0.7151522 * g + 0.0721750 * b;
	}

	// get the Z-Value of XYZ from sRGB value
	double getXYZ_Z() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.0193339 * r + 0.1191920 * g + 0.9503041 * b;
	}

	// just a helper function that's needed for the L*ab-conversion
	// needn't to be accessible for the user
	double LAB_helperFunction(double t) {
		if (t > 0.008856) {
			return pow(t, 1.0 / 3.0);
		} else {
			return 7.78704 * t + 0.137931;
		}
	}

	// get the L-value of L*ab from sRGB value
	double getLAB_L() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double Y = getXYZ_Y(red, green, blue);
		std::cout << Y << std::endl;
		return 116 * LAB_helperFunction(Y) - 16;
	}

	// get the a-value of L*ab from sRGB value
	double getLAB_a(double x, double y) {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		const double Yn = 1;
		const double Xn = x * (Yn / y);
		double X = getXYZ_X(red, green, blue);
		double Y = getXYZ_Y(red, green, blue);
		return 500 * (LAB_helperFunction(X / Xn) - LAB_helperFunction(Y / Yn));
	}

	// get the b-value of L*ab from sRGB value
	double getLAB_b(double x, double y) {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		const double Yn = 1;
		const double Zn = (1 - x - y) * (Yn / y);
		double Z = getXYZ_Z(red, green, blue);
		double Y = getXYZ_Y(red, green, blue);
		return 200 * (LAB_helperFunction(Y / Yn) - LAB_helperFunction(Z / Zn));
	}

	// Checks if all color values are valid (non-infinite, non-negative, non-NAN)
	bool isValid() const {
		for (int i = 0; i < 3; ++i) {
			T value = (*this)[i];
			int cl = boost::math::fpclassify(value);

			if (value < 0 || cl == FP_INFINITE || cl == FP_NAN)
				return false;
		}
		return true;
	}

	static Color<T, 3> fromRGB(const int red, const int green, const int blue) {
		return Color<T, 3>(static_cast<T>(red) / 255, static_cast<T>(green) / 255, static_cast<T>(blue) / 255);
	}

// swizzle functions
#include "Color2Swizzles.inc"
#include "Color3Swizzles.inc"
#include "Color4Swizzles.inc"
};

//
// RGBA color class of arbitrary type.
//

template <typename T>
struct Color<T, 4> {
	// Value type and number of components.
	typedef T ValueType;
	static const size_t Components = 4;

	// Color components.
	ValueType r, g, b, a;

	// Constructors.
	Color();                              // leave all components uninitialized
	explicit Color(const ValueType* rhs); // initialize with array of 4 scalars
	explicit Color(const ValueType val);  // set all components to 'val'
	Color(const Color<T, 3>& rgb, const ValueType a);
	Color( // set individual components
	  const ValueType r,
	  const ValueType g,
	  const ValueType b,
	  const ValueType a);

	// Construct a color from another color of a different type.
	template <typename U>
	explicit Color(const Color<U, 4>& rhs);

	explicit Color(const Color<T, 3>& rhs) {
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		a = 1.0;
	}

	// Set all components to a given value.
	void set(const ValueType val);

	// Access the color as a 3-component color.
	// color<ValueType, 3>& rgb();
	// const color<ValueType, 3>& rgb() const;

	// Unchecked array subscripting.
	ValueType& operator[](const size_t i);
	const ValueType& operator[](const size_t i) const;

	ValueType red() const {
		return (*this)[0];
	}

	ValueType green() const {
		return (*this)[1];
	}

	ValueType blue() const {
		return (*this)[2];
	}

	ValueType alpha() const {
		return (*this)[3];
	}

	// other color spaces
	double getAlpha() const {
		return -1.0;
	}

	double getBeta() const {
		return -1.0;
	}

	double getHue() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;
		double max = std::max(std::max(r, g), b);
		double min = std::min(std::min(r, g), b);

		if (max == min) {
			return 0;
		} else if (max == r) {
			return 60 * ((g - b) / (max - min));
		} else if (max == g) {
			return 60 * (2 + (b - r) / (max - min));
		} else {
			return 60 * (4 + (r - g) / (max - min));
		}
	}

	double getSaturation() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;
		double max = std::max(std::max(r, g), b);
		double min = std::min(std::min(r, g), b);

		if (max == 0) {
			return 0;
		} else {
			return (max - min) / max;
		}
	}

	double getBrightness() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = (double)red / 255;
		double g = (double)green / 255;
		double b = (double)blue / 255;

		return std::max(std::max(r, g), b);
	}

	// needed for conversion from XYZ to sRGB
	// does not need to be accessable for the user
	double gammaEncoding(double t) {
		if (t > 0.0031308) {
			return 1.055 * pow(t, 1.0 / 2.4) - 0.055;
		} else {
			return 12.92 * t;
		}
	}

	// needed for conversion from sRGB to XYZ
	// does not need to be accessable for the user
	double inverseGammaEncoding(double t) {
		if (t > 0.04045) {
			return pow((t + 0.055) / 1.055, 2.4);
		} else {
			return t / 12.92;
		}
	}

	// get the X-Value of XYZ from sRGB value
	double getXYZ_X() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.4124564 * r + 0.3575761 * g + 0.1804375 * b;
	}

	// get the Y-Value of XYZ from sRGB value
	double getXYZ_Y() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.2126729 * r + 0.7151522 * g + 0.0721750 * b;
	}

	// get the Z-Value of XYZ from sRGB value
	double getXYZ_Z() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double r = inverseGammaEncoding((double)red / 255);
		double g = inverseGammaEncoding((double)green / 255);
		double b = inverseGammaEncoding((double)blue / 255);
		return 0.0193339 * r + 0.1191920 * g + 0.9503041 * b;
	}

	// just a helper function that's needed for the L*ab-conversion
	// needn't to be accessable for the user
	double LAB_helperFunction(double t) {
		if (t > 0.008856) {
			return pow(t, 1.0 / 3.0);
		} else {
			return 7.78704 * t + 0.137931;
		}
	}

	// get the L-value of L*ab from sRGB value
	double getLAB_L() {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		double Y = getXYZ_Y(red, green, blue);
		std::cout << Y << std::endl;
		return 116 * LAB_helperFunction(Y) - 16;
	}

	// get the a-value of L*ab from sRGB value
	double getLAB_a(double x, double y) {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		const double Yn = 1;
		const double Xn = x * (Yn / y);
		double X = getXYZ_X(red, green, blue);
		double Y = getXYZ_Y(red, green, blue);
		return 500 * (LAB_helperFunction(X / Xn) - LAB_helperFunction(Y / Yn));
	}

	// get the b-value of L*ab from sRGB value
	double getLAB_b(double x, double y) {
		int red = (*this)[0];
		int green = (*this)[1];
		int blue = (*this)[2];

		const double Yn = 1;
		const double Zn = (1 - x - y) * (Yn / y);
		double Z = getXYZ_Z(red, green, blue);
		double Y = getXYZ_Y(red, green, blue);
		return 200 * (LAB_helperFunction(Y / Yn) - LAB_helperFunction(Z / Zn));
	}

// swizzle functions
#include "Color2Swizzles.inc"
#include "Color3Swizzles.inc"
#include "Color4Swizzles.inc"
};

//
// Full specializations for colors of type int, float and double.
//

typedef Color<std::uint8_t, 1> Color1b;
typedef Color<float, 1> Color1f;
typedef Color<double, 1> Color1d;
typedef Color<std::uint8_t, 2> Color2b;
typedef Color<float, 2> Color2f;
typedef Color<double, 2> Color2d;
typedef Color<std::uint8_t, 3> Color3b;
typedef Color<float, 3> Color3f;
typedef Color<double, 3> Color3d;
typedef Color<std::uint8_t, 4> Color4b;
typedef Color<float, 4> Color4f;
typedef Color<double, 4> Color4d;

//
// N-dimensional color implementation.
//

template <typename T, size_t N>
inline Color<T, N>::Color() {
}

template <typename T, size_t N>
inline Color<T, N>::Color(const ValueType* rhs) {
	assert(rhs);

	for (size_t i = 0; i < N; ++i)
		comp_[i] = rhs[i];
}

template <typename T, size_t N>
inline Color<T, N>::Color(const ValueType val) {
	set(val);
}

template <typename T, size_t N>
template <typename U>
inline Color<T, N>::Color(const Color<U, N>& rhs) {
	for (size_t i = 0; i < N; ++i)
		comp_[i] = static_cast<ValueType>(rhs.comp_[i]);
}

template <typename T, size_t N>
inline void Color<T, N>::set(const ValueType val) {
	for (size_t i = 0; i < N; ++i)
		comp_[i] = val;
}

template <typename T, size_t N>
inline T& Color<T, N>::operator[](const size_t i) {
	assert(i < Components);
	return comp_[i];
}

template <typename T, size_t N>
inline const T& Color<T, N>::operator[](const size_t i) const {
	assert(i < Components);
	return comp_[i];
}

template <typename T, size_t N>
inline bool operator!=(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i) {
		if (lhs[i] != rhs[i])
			return true;
	}

	return false;
}

template <typename T, size_t N>
inline bool operator==(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	return !(lhs != rhs);
}

template <typename T, size_t N>
inline bool feq(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i) {
		if (!feq(lhs[i], rhs[i]))
			return false;
	}

	return true;
}

template <typename T, size_t N>
inline bool feq(const Color<T, N>& lhs, const Color<T, N>& rhs, const T eps) {
	for (size_t i = 0; i < N; ++i) {
		if (!feq(lhs[i], rhs[i], eps))
			return false;
	}

	return true;
}

template <typename T, size_t N>
inline bool fz(const Color<T, N>& v) {
	for (size_t i = 0; i < N; ++i) {
		if (!fz(v[i]))
			return false;
	}

	return true;
}

template <typename T, size_t N>
inline bool fz(const Color<T, N>& v, const T eps) {
	for (size_t i = 0; i < N; ++i) {
		if (!fz(v[i], eps))
			return false;
	}

	return true;
}

template <typename T, size_t N>
inline Color<T, N> operator+(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = lhs[i] + rhs[i];

	return col;
}

template <typename T, size_t N>
inline Color<T, N> operator-(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = lhs[i] - rhs[i];

	return col;
}

template <typename T, size_t N>
inline Color<T, N> operator-(const Color<T, N>& lhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = -lhs[i];

	return col;
}

template <typename T, size_t N>
inline Color<T, N> operator*(const Color<T, N>& lhs, const T rhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = lhs[i] * rhs;

	return col;
}

template <typename T, size_t N>
inline Color<T, N> operator*(const T lhs, const Color<T, N>& rhs) {
	return rhs * lhs;
}

template <typename T, size_t N>
inline Color<T, N> operator*(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = lhs[i] * rhs[i];

	return col;
}

template <typename T, size_t N>
inline Color<T, N> operator/(const Color<T, N>& lhs, const T rhs) {
	return lhs * (T(1.0) / rhs);
}

template <typename T, size_t N>
inline Color<T, N> operator/(const Color<T, N>& lhs, const Color<T, N>& rhs) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = lhs[i] / rhs[i];

	return col;
}

template <typename T, size_t N>
inline Color<T, N>& operator+=(Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i)
		lhs[i] += rhs[i];

	return lhs;
}

template <typename T, size_t N>
inline Color<T, N>& operator-=(Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i)
		lhs[i] -= rhs[i];

	return lhs;
}

template <typename T, size_t N>
inline Color<T, N>& operator*=(Color<T, N>& lhs, const T rhs) {
	for (size_t i = 0; i < N; ++i)
		lhs[i] *= rhs;

	return lhs;
}

template <typename T, size_t N>
inline Color<T, N>& operator*=(Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i)
		lhs[i] *= rhs[i];

	return lhs;
}

template <typename T, size_t N>
inline Color<T, N>& operator/=(Color<T, N>& lhs, const T rhs) {
	return lhs *= (T(1.0) / rhs);
}

template <typename T, size_t N>
inline Color<T, N>& operator/=(Color<T, N>& lhs, const Color<T, N>& rhs) {
	for (size_t i = 0; i < N; ++i)
		lhs[i] /= rhs[i];

	return lhs;
}

template <typename T, size_t N>
inline Color<T, N> clamp(const Color<T, N>& c, const T min, const T max) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = buw::clamp(c[i], min, max);

	return col;
}

template <typename T, size_t N>
inline Color<T, N> saturate(const Color<T, N>& c) {
	Color<T, N> col;

	for (size_t i = 0; i < N; ++i)
		col[i] = saturate(c[i]);

	return col;
}

template <typename T, size_t N>
inline T min_value(const Color<T, N>& c) {
	T value = c[0];

	for (size_t i = 1; i < N; ++i) {
		if (value > c[i])
			value = c[i];
	}

	return value;
}

template <typename T, size_t N>
inline T max_value(const Color<T, N>& c) {
	T value = c[0];

	for (size_t i = 1; i < N; ++i) {
		if (value < c[i])
			value = c[i];
	}

	return value;
}

template <typename T, size_t N>
inline size_t min_index(const Color<T, N>& c) {
	size_t index = 0;
	T value = c[0];

	for (size_t i = 1; i < N; ++i) {
		const T x = c[i];

		if (value > x) {
			value = x;
			index = i;
		}
	}

	return index;
}

template <typename T, size_t N>
inline size_t max_index(const Color<T, N>& c) {
	size_t index = 0;
	T value = c[0];

	for (size_t i = 1; i < N; ++i) {
		const T x = c[i];

		if (value < x) {
			value = x;
			index = i;
		}
	}

	return index;
}

template <typename T, size_t N>
inline size_t min_abs_index(const Color<T, N>& c) {
	size_t index = 0;
	T value = std::abs(c[0]);

	for (size_t i = 1; i < N; ++i) {
		const T x = std::abs(c[i]);

		if (value > x) {
			value = x;
			index = i;
		}
	}

	return index;
}

template <typename T, size_t N>
inline size_t max_abs_index(const Color<T, N>& c) {
	size_t index = 0;
	T value = std::abs(c[0]);

	for (size_t i = 1; i < N; ++i) {
		const T x = std::abs(c[i]);

		if (value < x) {
			value = x;
			index = i;
		}
	}

	return index;
}

template <typename T, size_t N>
inline T average_value(const Color<T, N>& c) {
	T average = c[0];

	for (size_t i = 1; i < N; ++i)
		average += c[i];

	return average * (T(1.0) / N);
}

//
// grayvalue color implementation.
//

template <typename T>
inline Color<T, 1>::Color() {
}

template <typename T>
inline Color<T, 1>::Color(const ValueType* rhs) {
	assert(rhs);
	grayvalue = rhs[0];
}

template <typename T>
inline Color<T, 1>::Color(const ValueType grayvalue) : g(grayvalue) {
}

template <typename T>
template <typename U>
inline Color<T, 1>::Color(const Color<U, 1>& rhs) : g(static_cast<ValueType>(rhs.g)) {
}

template <typename T>
inline void Color<T, 1>::set(const ValueType val) {
	g = val;
}

template <typename T>
inline T& Color<T, 1>::operator[](const size_t i) {
	assert(i < Components);
	return (&g)[i];
}

template <typename T>
inline const T& Color<T, 1>::operator[](const size_t i) const {
	assert(i < Components);
	return (&g)[i];
}

//
// RGB color implementation.
//

template <typename T>
inline Color<T, 3>::Color() {
}

template <typename T>
inline Color<T, 3>::Color(const ValueType* rhs) {
	assert(rhs);
	r = rhs[0];
	g = rhs[1];
	b = rhs[2];
}

template <typename T>
inline Color<T, 3>::Color(const ValueType val) : r(val), g(val), b(val) {
}

template <typename T>
inline Color<T, 3>::Color(const ValueType r_, const ValueType g_, const ValueType b_) : r(r_), g(g_), b(b_) {
}

template <typename T>
template <typename U>
inline Color<T, 3>::Color(const Color<U, 3>& rhs) : r(static_cast<ValueType>(rhs.r)), g(static_cast<ValueType>(rhs.g)), b(static_cast<ValueType>(rhs.b)) {
}

template <typename T>
inline void Color<T, 3>::set(const ValueType val) {
	r = g = b = val;
}

template <typename T>
inline T& Color<T, 3>::operator[](const size_t i) {
	assert(i < Components);
	return (&r)[i];
}

template <typename T>
inline const T& Color<T, 3>::operator[](const size_t i) const {
	assert(i < Components);
	return (&r)[i];
}

//
// RGBA color implementation.
//

template <typename T>
inline Color<T, 4>::Color() {
}

template <typename T>
inline Color<T, 4>::Color(const ValueType* rhs) {
	assert(rhs);
	r = rhs[0];
	g = rhs[1];
	b = rhs[2];
	a = rhs[3];
}

template <typename T>
inline Color<T, 4>::Color(const ValueType val) : r(val), g(val), b(val), a(val) {
}

template <typename T>
inline Color<T, 4>::Color(const Color<T, 3>& rgb, const ValueType a_) : r(rgb.r), g(rgb.g), b(rgb.b), a(a_) {
}

template <typename T>
inline Color<T, 4>::Color(const ValueType r_, const ValueType g_, const ValueType b_, const ValueType a_) : r(r_), g(g_), b(b_), a(a_) {
}

template <typename T>
template <typename U>
inline Color<T, 4>::Color(const Color<U, 4>& rhs)
    : r(static_cast<ValueType>(rhs.r)), g(static_cast<ValueType>(rhs.g)), b(static_cast<ValueType>(rhs.b)), a(static_cast<ValueType>(rhs.a)) {
}

template <typename T>
inline void Color<T, 4>::set(const ValueType val) {
	r = g = b = a = val;
}

// template <typename T>
// inline color<T, 3>& color<T, 4>::rgb()
// {
// 	return *reinterpret_cast<color<T, 3>*>(&r);
// }
//
// template <typename T>
// inline const color<T, 3>& color<T, 4>::rgb() const
// {
// 	return *reinterpret_cast<const color<T, 3>*>(&r);
// }

template <typename T>
inline T& Color<T, 4>::operator[](const size_t i) {
	assert(i < Components);
	return (&r)[i];
}

template <typename T>
inline const T& Color<T, 4>::operator[](const size_t i) const {
	assert(i < Components);
	return (&r)[i];
}

// helper/util functions
// applies game correction to a given color
template <typename T>
Color<T, 3> gammaCorrect(const Color<T, 3>& c, T gamma) {
	T power = 1.0f / gamma;

	Color<T, 3> temp = c;
	temp[0] = pow(temp.red(), power);
	temp[1] = pow(temp.green(), power);
	temp[2] = pow(temp.blue(), power);
	return temp;
}

template <typename ElementType, size_t Size>
inline std::ostream& operator<<(std::ostream& os, const Color<ElementType, Size>& v) {
	for (size_t i = 0; i < v.Components; ++i) {
		os << "[";

		os << " " << v[i];

		os << " ]";
	}
	return os;
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

//
// Overload std::min() and std::max() for component-wise min/max operations on colors.
//

// namespace std
//{
//
// template <typename T, size_t N>
// inline foundation::Color<T, N> min(const foundation::Color<T, N>& lhs, const foundation::Color<T, N>& rhs)
//{
//    foundation::Color<T, N> col;
//
//    for (size_t i = 0; i < N; ++i)
//        col[i] = min(lhs[i], rhs[i]);
//
//    return col;
//}
//
// template <typename T, size_t N>
// inline foundation::Color<T, N> max(const foundation::Color<T, N>& lhs, const foundation::Color<T, N>& rhs)
//{
//    foundation::Color<T, N> col;
//
//    for (size_t i = 0; i < N; ++i)
//        col[i] = max(lhs[i], rhs[i]);
//
//    return col;
//}
//
//}       // namespace std

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color1b)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color3b)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color4b)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color1f)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color3f)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color4f)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color1d)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color3d)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(Color4d)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(gammaCorrect)

#endif // end define BlueFramework_ImageProcessing_Color_a6e437c4_de88_4d75_acb1_70d78886fbe5_h
