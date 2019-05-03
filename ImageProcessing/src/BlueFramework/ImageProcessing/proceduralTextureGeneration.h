/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_ImageProcessing_proceduralTextureGeneration_fb971c8e_c331_4e5d_b444_a1e6fc789732_h
#define BlueFramework_ImageProcessing_proceduralTextureGeneration_fb971c8e_c331_4e5d_b444_a1e6fc789732_h

#include "BlueFramework/ImageProcessing/namespace.h"
#include "BlueFramework/ImageProcessing/proceduralTextureGeneration.h"
#include "BlueFramework/ImageProcessing/Image.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

Image4b generateCheckerboardImage(const int width, const int height);

Image4b generateRandomHeightmap(const int lod, float roughness, float mean, float sigma);

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(generateCheckerboardImage)
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(generateRandomHeightmap)

#endif // end define BlueFramework_ImageProcessing_proceduralTextureGeneration_fb971c8e_c331_4e5d_b444_a1e6fc789732_h
