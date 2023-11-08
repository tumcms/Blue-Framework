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

#include "BlueFramework/ImageProcessing/difference.h"
#include "BlueFramework/ImageProcessing/Color.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

bool areEqual(const Image4f& a, const Image4f& b) {
	BLUE_ASSERT(a.getWidth() == b.getWidth(), "different widths");
	BLUE_ASSERT(a.getHeight() == b.getHeight(), "different heights");

	if (a.getWidth() != b.getWidth() || a.getHeight() != b.getHeight()) {
		return false;
	}

	int width = a.getWidth();
	int height = a.getHeight();

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (a.getPixelColor(x, y) != b.getPixelColor(x, y))
				return false;
		}
	}

	return true;
}

Image3b createDifferenceImage(const Image3b& a, const Image3b& b, const std::uint8_t color[3]) {
	Image3b tmp(a.getWidth(), b.getHeight());

	for (int y = 0; y < a.getHeight(); y++) {
		for (int x = 0; x < a.getWidth(); x++) {
			if (a.getPixelColor(x, y) != b.getPixelColor(x, y)) {
				if (color) {
					tmp.setPixelColor(x, y, buw::Color3b(color[0], color[1], color[2]));
				} else {
					tmp.setPixelColor(x, y, buw::Color3b(255, 0, 0));
				}

			} else {
				tmp.setPixelColor(x, y, a.getPixelColor(x, y));
			}
		}
	}

	return tmp;
}

Image3b createDifferenceImage(const Image3b& a, const Image3b& b, const Color3b& color) {
	return createDifferenceImage(a, b, &color[0]);
}

void foo() {}
Image4b createDifferenceImage(const Image4b& a, const Image4b& b, const std::uint8_t color[4]) {
	Image4b tmp(a.getWidth(), b.getHeight());

	for (int y = 0; y < a.getHeight(); y++) {
		for (int x = 0; x < a.getWidth(); x++) {
			auto ca = a.getPixelColor(x, y);
			auto cb = b.getPixelColor(x, y);
			auto diff = ca - cb;

			if (ca != cb) {
				tmp.setPixelColor(x, y, Color4b(color[0], color[1], color[2], color[3]));
			}
		}
	}

	return tmp;
}

Image4b createDifferenceImage(const Image4b& a, const Image4b& b, const Color4b& color) {
	return createDifferenceImage(a, b, &color[0]);
}

Image4f createDifferenceImage(const Image4f& a, const Image4f& b, const float color[4]) {
	Image4f tmp(a.getWidth(), b.getHeight());

	for (int y = 0; y < a.getHeight(); y++) {
		for (int x = 0; x < a.getWidth(); x++) {
			auto ca = a.getPixelColor(x, y);
			auto cb = b.getPixelColor(x, y);
			auto diff = ca - cb;

			if (ca != cb) {
				tmp.setPixelColor(x, y, Color4f(color[0], color[1], color[2], color[3]));
			}

			// diff = Color4f(std::abs(diff.r), std::abs(diff.g), std::abs(diff.b), 1.0f);
			// tmp->setPixelColor(x, y, diff);
		}
	}

	return tmp;
}

Image3b highlightDifferences(const Image3b& a, const Image3b& b, const Color3b color) {
	Image3b tmp(a.getWidth(), b.getHeight());

	for (int y = 0; y < a.getHeight(); y++) {
		for (int x = 0; x < a.getWidth(); x++) {
			if (a.getPixelColor(x, y) != b.getPixelColor(x, y)) {
				tmp.setPixelColor(x, y, color);
			} else {
				tmp.setPixelColor(x, y, Color3b(0, 0, 0));
			}
		}
	}

	return tmp;
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END