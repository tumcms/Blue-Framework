/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2018 Technical University of Munich
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
#ifndef BlueFramework_ImageProcessing_io_051ab0f1_8710_431c_b183_30837a96c751_h
#define BlueFramework_ImageProcessing_io_051ab0f1_8710_431c_b183_30837a96c751_h

#include "BlueFramework/ImageProcessing/namespace.h"
#include "BlueFramework/ImageProcessing/Image.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

Image3b loadImage3b(const std::string& filename);
Image4b loadImage4b(const std::string& filename);

void storeImage(const std::string& filename, const Image3b& img);
void storeImage(const std::string& filename, const Image4b& img);

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(loadImage3b)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(loadImage4b)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(storeImage)

#endif // end define BlueFramework_ImageProcessing_io_051ab0f1_8710_431c_b183_30837a96c751_h
