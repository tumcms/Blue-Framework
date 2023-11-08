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
#ifndef BlueFramework_Core_Math_matrix_03fa61ff_050c_4932_908b_93ffcd5c17a7_h
#define BlueFramework_Core_Math_matrix_03fa61ff_050c_4932_908b_93ffcd5c17a7_h

#include <BlueFramework/Core/namespace.h>
#include <Eigen/Dense>

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

template <typename T, int R, int C>
using Matrix = Eigen::Matrix<T, R, C>;

typedef Eigen::Matrix4i Matrix44i;
typedef Eigen::Matrix4f Matrix44f;
typedef Eigen::Matrix4d Matrix44d;

typedef Eigen::Matrix3i Matrix33i;
typedef Eigen::Matrix3f Matrix33f;
typedef Eigen::Matrix3d Matrix33d;

typedef Eigen::Matrix2i Matrix22i;
typedef Eigen::Matrix2f Matrix22f;
typedef Eigen::Matrix2d Matrix22d;

template <typename T>
Matrix<T, 4, 4> createScalingMatrix(const Matrix<T, 3, 1> &scale) {
	Matrix<T, 4, 4> m = Matrix<T, 4, 4>::Identity();
	m(0, 0) = scale[0];
	m(1, 1) = scale[1];
	m(2, 2) = scale[2];
	m(3, 3) = 1.0;

	return m;
}

template <typename T>
Matrix<T, 4, 4> createScalingMatrix(const T x, const T y, const T z) {
	Matrix<T, 4, 4> m = Matrix<T, 4, 4>::Identity();
	m(0, 0) = x;
	m(1, 1) = y;
	m(2, 2) = z;
	m(3, 3) = 1.0;

	return m;
}

template <typename T>
Matrix<T, 4, 4> createInverseMatrix(const Matrix<T, 4, 4> &m) {
	return m.inverse();
}

template <typename T>
Matrix<T, 4, 4> createTranslationMatrix(const T x, const T y, const T z) {
	Matrix<T, 4, 4> m = Matrix<T, 4, 4>::Identity();
	m.col(3).block<3, 1>(0, 0) = Matrix<T, 3, 1>(x, y, z);

	return m;
}

template <typename T>
Matrix<T, 4, 4> createTranslationMatrix(const Matrix<T, 3, 1> &translation) {
	Matrix<T, 4, 4> m = Matrix<T, 4, 4>::Identity();
	m.col(3).block<3, 1>(0, 0) = translation;

	return m;
}

template <typename T>
T det(Matrix<T, 2, 2> const& m) {
	return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
}

template <typename T>
Matrix<T, 2, 2> createRotationMatrix(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 2, 2> m;
	m.row(0) = Eigen::Matrix<T, 2, 1>(c, -s);
	m.row(1) = Eigen::Matrix<T, 2, 1>(s, c);

	return m;
}

// Creates efficiently a 2D rotation matrix, that is defined by rotating by the angle enclosed
// between (1,0) and targetDirection or in other words by rotating (1,0) until targetDirection.
template <typename T>
Matrix<T, 2, 2> createRotationMatrix(Matrix<T, 2, 1> const& targetDirection) {
	T const cosAlpha = Matrix<T, 2, 1>(1, 0).dot(targetDirection.normalized());
	T const sinAlpha = sqrt(1 - cosAlpha*cosAlpha);
	Matrix<T, 2, 2> rotation;
	auto& row0 = rotation.row(0), row1 = rotation.row(1);
	row0[0] = row1[1] = cosAlpha;
	row0[1] = -sinAlpha;
	row1[0] = sinAlpha;
	return rotation;
}

template <typename T>
Matrix<T, 4, 4> createRotationMatrixX(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 4, 4> m;
	m.row(0) = Eigen::Matrix<T, 4, 1>(1, 0, 0, 0);
	m.row(1) = Eigen::Matrix<T, 4, 1>(0, c, -s, 0);
	m.row(2) = Eigen::Matrix<T, 4, 1>(0, s, c, 0);
	m.row(3) = Eigen::Matrix<T, 4, 1>(0, 0, 0, 1);

	return m;
}

template <typename T>
Matrix<T, 4, 4> createRotationMatrixY(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 4, 4> m;
	m.row(0) = Eigen::Matrix<T, 4, 1>(c, 0, s, 0);
	m.row(1) = Eigen::Matrix<T, 4, 1>(0, 1, -0, 0);
	m.row(2) = Eigen::Matrix<T, 4, 1>(-s, 0, c, 0);
	m.row(3) = Eigen::Matrix<T, 4, 1>(0, 0, 0, 1);

	return m;
}

template <typename T>
Matrix<T, 4, 4> createRotationMatrixZ(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 4, 4> m;
	m.row(0) = Eigen::Matrix<T, 4, 1>(c, -s, 0, 0);
	m.row(1) = Eigen::Matrix<T, 4, 1>(s, c, 0, 0);
	m.row(2) = Eigen::Matrix<T, 4, 1>(0, 0, 1, 0);
	m.row(3) = Eigen::Matrix<T, 4, 1>(0, 0, 0, 1);

	return m;
}

template <typename T>
Matrix<T, 3, 3> createRotationMatrix3TX(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 3, 3> m;
	m.row(0) = Eigen::Matrix<T, 3, 1>(1, 0, 0);
	m.row(1) = Eigen::Matrix<T, 3, 1>(0, c, -s);
	m.row(2) = Eigen::Matrix<T, 3, 1>(0, s, c);

	return m;
}

template <typename T>
Matrix<T, 3, 3> createRotationMatrix3TY(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 3, 3> m;
	m.row(0) = Eigen::Matrix<T, 3, 1>(c, 0, s);
	m.row(1) = Eigen::Matrix<T, 3, 1>(0, 1, -0);
	m.row(2) = Eigen::Matrix<T, 3, 1>(-s, 0, c);

	return m;
}

template <typename T>
Matrix<T, 3, 3> createRotationMatrix3TZ(const T &angle) {
	T s = sin(angle);
	T c = cos(angle);

	Matrix<T, 3, 3> m;
	m.row(0) = Eigen::Matrix<T, 3, 1>(c, -s, 0);
	m.row(1) = Eigen::Matrix<T, 3, 1>(s, c, 0);
	m.row(2) = Eigen::Matrix<T, 3, 1>(0, 0, 1);

	return m;
}

template <typename T>
Matrix<T, 4, 4> createPerspectiveProjectionMatrixRH(T fieldOfViewY, T aspectRation, T nearPlane, T farPlane) {
	T y = 1 / tan(fieldOfViewY / 2);
	T x = y / aspectRation;

	T d1 = farPlane / (farPlane - nearPlane);
	T d2 = -nearPlane * farPlane / (farPlane - nearPlane);

	Matrix<T, 4, 4> m;
	m.row(0) = Eigen::Matrix<T, 4, 1>(x, 0, 0, 0);
	m.row(1) = Eigen::Matrix<T, 4, 1>(0, y, 0, 0);
	m.row(2) = Eigen::Matrix<T, 4, 1>(0, 0, d1, d2);
	m.row(3) = Eigen::Matrix<T, 4, 1>(0, 0, 1, 0);

	return m;
}

template <typename T>
Matrix<T, 4, 4> createOrthographicProjectionMatrixRH(T width, T height, T nearPlane, T farPlane) {
	T x = 2 / width;
	T y = 2 / height;

	T d1 = 1 / (farPlane - nearPlane);
	T d2 = -nearPlane / (farPlane - nearPlane);

	Matrix<T, 4, 4> m;
	m.row(0) = Eigen::Matrix<T, 4, 1>(x, 0, 0, 0);
	m.row(1) = Eigen::Matrix<T, 4, 1>(0, y, 0, 0);
	m.row(2) = Eigen::Matrix<T, 4, 1>(0, 0, d1, d2);
	m.row(3) = Eigen::Matrix<T, 4, 1>(0, 0, 0, 1);

	return m;
}

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix44i);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix44f);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix44d);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix33i);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix33f);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix33d);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix22i);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix22f);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(Matrix22d);

BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createTranslationMatrix);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(det);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrix);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrixX);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrixY);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrixZ);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrix3TX);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrix3TY);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createRotationMatrix3TZ);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createScalingMatrix);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createInverseMatrix);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createPerspectiveProjectionMatrixRH);
BLUEFRAMEWORK_CORE_MATH_EMBED_INTO_BUW_NAMESPACE(createOrthographicProjectionMatrixRH);

#endif // end define BlueFramework_Core_Math_matrix_03fa61ff_050c_4932_908b_93ffcd5c17a7_h
