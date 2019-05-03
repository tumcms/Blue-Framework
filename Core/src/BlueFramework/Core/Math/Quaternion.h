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
#ifndef BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h
#define BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h

#include <BlueFramework/Core/namespace.h>
#include <Eigen/Dense>

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

typedef Eigen::Quaternion<float> Quaternionf;
typedef Eigen::Quaternion<double> Quaterniond;

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

#endif // end define BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h