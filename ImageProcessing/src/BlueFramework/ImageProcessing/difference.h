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
