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
