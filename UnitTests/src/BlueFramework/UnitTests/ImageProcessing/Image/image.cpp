/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2020 Technical University of Munich
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

#include <gtest/gtest.h>
#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/colorConstants.h>

using namespace testing;

class ImageTest : public Test {

public:
	~ImageTest() override {
	}

protected:
	void SetUp() override {
	}

	void TearDown() override {
	}
};

TEST_F(ImageTest, GivenImage100x100x3f_AfterFill_AllPixelsHaveFillColor) {
	// Arrange
	const int width = 100;
	const int height = 100;

	const buw::Color3f fillColor = buw::ColorConstants3f::aliceBlue();
	
	buw::Image3f image = buw::Image3f(width, height);

	// Act
	image.fill(fillColor);

	// Assert
	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); ++y) {
			auto color = image.getPixelColor(x, y);
			EXPECT_EQ(color, fillColor);
			EXPECT_NE(color, buw::ColorConstants3f::antiqueWhite());
		}
	}

	// Annihilate
}

TEST_F(ImageTest, GivenEqualImages_OperatorEqual_ReturnsTrue) {
	// Arrange
	const int width = 100;
	const int height = 100;

	const buw::Color3f fillColor = buw::ColorConstants3f::aliceBlue();

	buw::Image3f first = buw::Image3f(width, height);
	buw::Image3f second = buw::Image3f(width, height);

	// Act
	first.fill(fillColor);
	second.fill(fillColor);

	// Assert
	EXPECT_EQ(first, second);

	// Annihilate
}

TEST_F(ImageTest, GivenNonEqualImages_OperatorEqual_ReturnsFalse) {
	// Arrange
	const int width = 100;
	const int height = 100;

	const buw::Color3f firstFillColor = buw::ColorConstants3f::aliceBlue();
	const buw::Color3f secondFillColor = buw::ColorConstants3f::antiqueWhite();

	buw::Image3f first = buw::Image3f(width, height);
	buw::Image3f second = buw::Image3f(width, height);

	// Act
	first.fill(firstFillColor);
	second.fill(secondFillColor);

	// Assert
	EXPECT_NE(first, second);

	// Annihilate
}