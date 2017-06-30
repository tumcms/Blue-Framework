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

#pragma once
#ifndef BlueFramework_ImageProcessing_ImageFilter_01b74518_66c3_44bd_bde8_68720fa5d1f2_h
#define BlueFramework_ImageProcessing_ImageFilter_01b74518_66c3_44bd_bde8_68720fa5d1f2_h

#include "BlueFramework/ImageProcessing/namespace.h"
#include "BlueFramework/ImageProcessing/Image.h"

#include "BlueFramework/Core/Math/Matrix.h"
#include "BlueFramework/Core/Math/Vector.h"

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

enum ePaddingStrategy {
    Mirror
};

enum eFilterSize {
    Small = 3,
    Medium = 5,
    Large = 7
};

struct filterDescription {
    eFilterSize filterSize;
    ePaddingStrategy strategy;
};

template<typename T, size_t N, int S> inline buw::Image<buw::Color<T, N>> applyGaussian(buw::Image<buw::Color<T, N>> image, buw::Matrix22f sigma)
	{
		auto square = [](float x) { return x * x; };

		buw::Vector2f mean = buw::Vector2f(S / 2, S / 2);
		eFilterSize filterSize = (eFilterSize) S;
		float amplitude = 1.0f / std::sqrtf(square(2.0f*M_PI)* sigma.determinant());

		buw::Matrix<float, S, S> matrix;

		float sum = 0.0f;

		for(int y = 0; y < filterSize; y++) {
			for(int x = 0; x < filterSize; x++) {
				buw::Vector2f pos = buw::Vector2f(x, y);
				matrix(x, y) = amplitude * std::expf(-0.5f*((pos-mean).transpose()*(sigma.inverse())*(pos - mean))[0]);
				sum += matrix(x, y);
			}
		}
		matrix /= sum;
		

		buw::Image<buw::Color<T, N>> filteredImage = buw::Image<buw::Color<T, N>>(image.getWidth(), image.getHeight());
		buw::Image<buw::Color<T, N>> paddedImage = createPaddedImage<T, N>(image, filterSize);
		int offset = 2;
		switch(filterSize) {
		case eFilterSize::Small:
			offset = 2;
			break;
		case eFilterSize::Medium:
			offset = 1;
			break;
		case eFilterSize::Large:
			offset = 0;
			break;
		default:
			offset = 2;
			break;
		}
#pragma omp parallel for
		for(int y = offset; y < filteredImage.getHeight() + offset; y++) {
			for(int x = offset; x < filteredImage.getWidth() + offset; x++) {
				buw::Vector<float, N> value;
				value.setZero();
				for(int i = 0; i < filterSize; i++) {
					for(int j = 0; j < filterSize; j++) {
						buw::Color<T, N> color = paddedImage.getPixelColor(x + i - offset, y + j - offset);
						for(int idx = 0; idx < N; idx++) {
							value[idx] += (float)color[idx] * matrix(i, j);
						}
					}
				}
				buw::Color<T, N> color;
				for(int idx = 0; idx < N; idx++)
					color[idx] = (T)value[idx];

				filteredImage.setPixelColor(x - offset, y - offset, color);
			}
		}
		return filteredImage;
	}

template<typename T, size_t N> inline buw::Image<buw::Color<T, N>> createPaddedImage(buw::Image<buw::Color<T, N>> image, eFilterSize filterSize)
	{
		buw::Image<buw::Color<T, N>> paddedImage(image.getWidth() + filterSize - 1, image.getHeight() + filterSize - 1);

		for(int y = 0; y < (filterSize - 1) / 2; y++) {
#pragma omp parallel for
			for(int x = 0; x < image.getWidth(); x++) {
				buw::Color<T, N> color = image.getPixelColor(x, y);
				paddedImage.setPixelColor(x + ((filterSize - 1) / 2), ((filterSize - 1) / 2) - 1 - y, color);

				color = image.getPixelColor(x, image.getHeight() - 1 - y);
				paddedImage.setPixelColor(x + ((filterSize - 1) / 2), image.getHeight() + y, color);
			}
		}

#pragma omp parallel for
		for(int y = 0; y < image.getHeight(); y++) {
			for(int x = 0; x < (filterSize - 1) / 2; x++) {
				buw::Color<T, N> color = image.getPixelColor(x, y);
				paddedImage.setPixelColor(((filterSize - 1) / 2) - 1 - x, y + ((filterSize - 1) / 2), color);

				color = image.getPixelColor(image.getWidth() - 1 - x, y);
				paddedImage.setPixelColor(image.getWidth() + x, y + ((filterSize - 1) / 2), color);
			}
		}

		for(int y = 0; y < (filterSize - 1) / 2; y++) {
			for(int x = 0; x < (filterSize - 1) / 2; x++) {
				buw::Color<T, N> color = image.getPixelColor(x, y);
				paddedImage.setPixelColor(((filterSize - 1) / 2) - 1 - x, ((filterSize - 1) / 2) - 1 - y, color);

				color = image.getPixelColor(image.getWidth() - 1 - x, y);
				paddedImage.setPixelColor(image.getWidth() + x, ((filterSize - 1) / 2) - 1 - y, color);

				color = image.getPixelColor(x, image.getHeight() - 1 - y);
				paddedImage.setPixelColor(((filterSize - 1) / 2) - 1 - x, image.getHeight() + y, color);

				color = image.getPixelColor(image.getWidth() - 1 - x, image.getHeight() - 1 - y);
				paddedImage.setPixelColor(image.getWidth() + x, image.getHeight() + y, color);
			}
		}

#pragma omp parallel for
		for(int y = 0; y < image.getHeight(); y++) {
			for(int x = 0; x < image.getWidth(); x++) {
				paddedImage.setPixelColor(x + (filterSize - 1) / 2, y + (filterSize - 1) / 2, image.getPixelColor(x, y));
			}
		}

		return paddedImage;
	}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END

BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(filterDescription);
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(eFilterSize);
BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(ePaddingStrategy);

#endif // end define BlueFramework_ImageProcessing_ImageFilter_01b74518_66c3_44bd_bde8_68720fa5d1f2_h