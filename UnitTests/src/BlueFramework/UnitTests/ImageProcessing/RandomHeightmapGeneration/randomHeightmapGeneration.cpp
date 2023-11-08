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

#include <BlueFramework/ImageProcessing/Image.h>
#include <BlueFramework/ImageProcessing/ImageFilter.h>
#include <BlueFramework/ImageProcessing/captureScreen.h>
#include <BlueFramework/ImageProcessing/io.h>
#include <BlueFramework/ImageProcessing/proceduralTextureGeneration.h>

#include <gtest/gtest.h>
#include <iostream>

TEST(ImageProcessing, RandomHeightmapGeneration) {	
	buw::Image4b heightmap = buw::generateRandomHeightmap(10, 0.5f, 0.0f, 1.0f);

	buw::Image4b filtered = buw::applyGaussian<uint8_t, 4Ui64, buw::eFilterSize::Medium>(heightmap, buw::Matrix22f::Identity());

	buw::storeImage("heightmap.png", heightmap);
	buw::storeImage("heightmap_smoothed.png", filtered);
}