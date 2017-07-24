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

#pragma once
#ifndef BlueFramework_ImageProcessing_findSubimage_62d4f174_c811_4786_8b99_b0c2b521dd50_h
#define BlueFramework_ImageProcessing_findSubimage_62d4f174_c811_4786_8b99_b0c2b521dd50_h

#include "BlueFramework/ImageProcessing/Image.h"
#include "BlueFramework/ImageProcessing/namespace.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

bool checkSubimage(const Image3b& subimage, const Image3b& image, int x, int y);
bool findSubimage(const Image3b& subimage, const Image3b& image, int& x, int& y);
bool findSubimage(const char* subimageFilename, const char* imageFilename, int& x, int& y);
void drawRect(int x, int y, int widht, int height, Image3b& img);

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(findSubimage)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(drawRect)

#endif // end define BlueFramework_ImageProcessing_findSubimage_62d4f174_c811_4786_8b99_b0c2b521dd50_h
