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
#ifndef BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h
#define BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h

#include <BlueFramework/Core/namespace.h>
#include <Eigen/Dense>

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_BEGIN

typedef Eigen::Quaternion<float> Quaternionf;
typedef Eigen::Quaternion<double> Quaterniond;

BLUEFRAMEWORK_CORE_MATH_NAMESPACE_END

#endif // end define BlueFramework_Core_Math_Quaternion_0b79f25c_df68_44ac_911d_b385c0d51e55_h