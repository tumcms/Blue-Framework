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