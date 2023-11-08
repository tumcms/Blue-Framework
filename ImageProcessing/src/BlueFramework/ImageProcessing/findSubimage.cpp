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