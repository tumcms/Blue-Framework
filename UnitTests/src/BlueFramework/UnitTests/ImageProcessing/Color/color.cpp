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