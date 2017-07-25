/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016 Technical University of Munich
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

#include "BlueFramework/ImageProcessing/difference.h"
#include "BlueFramework/ImageProcessing/Color.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

bool areEqual(const Image4f& a,
	const Image4f& b)
{
	BLUE_ASSERT(a.getWidth() == b.getWidth(), "different widths");
	BLUE_ASSERT(a.getHeight() == b.getHeight(), "different heights");

	if (a.getWidth() != b.getWidth() ||
		a.getHeight() != b.getHeight())
	{
		return false;
	}

	int width = a.getWidth();
	int height = a.getHeight();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
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

			//diff = Color4f(std::abs(diff.r), std::abs(diff.g), std::abs(diff.b), 1.0f);
			//tmp->setPixelColor(x, y, diff);
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