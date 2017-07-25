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
#ifndef BlueFramework_ImageProcessing_difference_91e49169_661c_4f4c_9c07_6588d56c1f01_h
#define BlueFramework_ImageProcessing_difference_91e49169_661c_4f4c_9c07_6588d56c1f01_h

#include "BlueFramework/ImageProcessing/Image.h"
#include "BlueFramework/ImageProcessing/namespace.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

bool areEqual(const Image4f& a, const Image4f& b);
Image3b highlightDifferences(const Image3b& a, const Image3b& b, const Color3b color);

Image4f createDifferenceImage(const Image4f& a, const Image4f& b, const float Color[4]);
Image3b createDifferenceImage(const Image3b& a, const Image3b& b, const Color3b& color);
Image3b createDifferenceImage(const Image3b& a, const Image3b& b, const std::uint8_t color[3]);
Image4b createDifferenceImage(const Image4b& a, const Image4b& b, const Color4b& color);
Image4b createDifferenceImage(const Image4b& a, const Image4b& b, const std::uint8_t color[4]);

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(highlightDifferences)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(createDifferenceImage)

#endif // end define BlueFramework_ImageProcessing_difference_91e49169_661c_4f4c_9c07_6588d56c1f01_h
