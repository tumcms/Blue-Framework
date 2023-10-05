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

#include <BlueFramework/ImageProcessing/Color.h>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

using namespace std;

namespace
{
	TEST(Color3f, Color3f_add_test) {
		buw::Color3f a(0.3f, 0.3f, 0.3f);
		buw::Color3f b(0.1f, 0.1f, 0.1f);
		auto c = a + b;

		EXPECT_TRUE(c.red() == 0.4f);
		EXPECT_TRUE(c.green() == 0.4f);
		EXPECT_TRUE(c.blue() == 0.4f);
	}
}