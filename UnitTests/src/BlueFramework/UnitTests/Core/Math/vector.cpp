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

#include <BlueFramework/Core/Math/vector.h>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

using namespace std;

namespace {
	TEST(Vector3f, Vector3f_array_ctor) {
		float va[3] = { 1, 2, 3 };
		
		BlueFramework::Core::Math::Vector3f v(va);

		EXPECT_TRUE(v.x() == 1);
		EXPECT_TRUE(v.y() == 2);
		EXPECT_TRUE(v.z() == 3);
	}

	TEST(Vector2f, Vector2f_add_test_2f) {
		BlueFramework::Core::Math::Vector2f v2a(1, 2);
		BlueFramework::Core::Math::Vector2f v2b = v2a;

		BlueFramework::Core::Math::Vector2f v2c = v2a + v2b;

		EXPECT_TRUE(v2c.x() == 2);
		EXPECT_TRUE(v2c.y() == 4);
	}

	TEST(Vector2f, Vector2f_subtract_test_2f) {
		BlueFramework::Core::Math::Vector2f v2a(1, 2);
		BlueFramework::Core::Math::Vector2f v2b = v2a;

		BlueFramework::Core::Math::Vector2f v2c = v2a - v2b;

		EXPECT_TRUE(v2c.x() == 0);
		EXPECT_TRUE(v2c.y() == 0);
	}

	TEST(Vector3i, Vector3i_add_test_3i) {
		buw::Vector3i a(3, 1, 2);
		buw::Vector3i b(3, 1, 2);

		buw::Vector3i c = a + b;

		EXPECT_TRUE(c.x() == 6);
		EXPECT_TRUE(c.y() == 2);
		EXPECT_TRUE(c.z() == 4);
	}

	TEST(Vector3i, Vector3i_subtraction_test_3i) {
		buw::Vector3i a(3, 1, 2);
		buw::Vector3i b(3, 1, 2);

		buw::Vector3i c = a - b;

		EXPECT_TRUE(c.x() == 0);
		EXPECT_TRUE(c.y() == 0);
		EXPECT_TRUE(c.z() == 0);
	}

	TEST(Vector3f, Vector3f_add_test_3f) {
		BlueFramework::Core::Math::Vector3f v3a(1, 2, 3);
		BlueFramework::Core::Math::Vector3f v3b = v3a;

		BlueFramework::Core::Math::Vector3f v3c = v3a + v3b;

		EXPECT_TRUE(v3c.x() == 2);
		EXPECT_TRUE(v3c.y() == 4);
		EXPECT_TRUE(v3c.z() == 6);
	}

	TEST(Vector3f, Vector3f_subtract_test_3f) {
		BlueFramework::Core::Math::Vector3f v3a(1, 2, 3);
		BlueFramework::Core::Math::Vector3f v3b = v3a;

		BlueFramework::Core::Math::Vector3f v3c = v3a - v3b;

		EXPECT_TRUE(v3c.x() == 0);
		EXPECT_TRUE(v3c.y() == 0);
		EXPECT_TRUE(v3c.z() == 0);
	}

	TEST(Vector4f, Vector4f_add_test_4f) {
		BlueFramework::Core::Math::Vector4f v4a(1, 2, 3, 4);
		BlueFramework::Core::Math::Vector4f v4b = v4a;

		BlueFramework::Core::Math::Vector4f v4c = v4a + v4b;

		EXPECT_TRUE(v4c.x() == 2);
		EXPECT_TRUE(v4c.y() == 4);
		EXPECT_TRUE(v4c.z() == 6);
		EXPECT_TRUE(v4c.w() == 8);
	}

	TEST(Vector4f, Vector4f_subtract_test_4f) {
		BlueFramework::Core::Math::Vector4f v4a(1.f, 2.f, 3.f, 4.f);
		BlueFramework::Core::Math::Vector4f v4b = v4a;

		BlueFramework::Core::Math::Vector4f v4c = v4a - v4b;

		EXPECT_TRUE(v4c.x() == 0);
		EXPECT_TRUE(v4c.y() == 0);
		EXPECT_TRUE(v4c.z() == 0);
		EXPECT_TRUE(v4c.w() == 0);
	}
}