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

#include "BlueFramework/ImageProcessing/findSubimage.h"
#include "BlueFramework/ImageProcessing/io.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

bool checkSubimage(const Image3b& subimage, const Image3b& image, int x, int y) {
	for (int ix = 0; ix < subimage.getWidth(); ++ix) {
		for (int iy = 0; iy < subimage.getHeight(); ++iy) {
			if (image.getPixelColor(x + ix, y + iy) != subimage.getPixelColor(ix, iy)) {
				return false;
			}
		}
	}

	return true;
}

bool findSubimage(const Image3b& subimage, const Image3b& image, int& x, int& y) {
	for (int ix = 0; ix < image.getWidth() - subimage.getWidth(); ix++) {
		for (int iy = 0; iy < image.getHeight() - subimage.getHeight(); iy++) {
			if (checkSubimage(subimage, image, ix, iy)) {
				x = ix;
				y = iy;
				return true;
			}
		}
	}

	x = 0;
	y = 0;
	return false;
}

void drawRect(int x, int y, int widht, int height, Image3b& img) {
	for (int tx = x; tx < x + widht; tx++) {
		img.setPixelColor(tx, y, Color3b(255, 0, 0));
		img.setPixelColor(tx, y + height, Color3b(255, 0, 0));
	}

	for (int ty = y; ty < y + height; ty++) {
		img.setPixelColor(x, ty, Color3b(255, 0, 0));
		img.setPixelColor(x + widht, ty, Color3b(255, 0, 0));
	}
}

bool findSubimage(const char* subimageFilename, const char* imageFilename, int& x, int& y) {
	Image3b img = loadImage3b(imageFilename);
	Image3b subimage = loadImage3b(subimageFilename);

	if (findSubimage(subimage, img, x, y)) {
		return true;
	}

	return false;
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END