/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
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