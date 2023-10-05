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
