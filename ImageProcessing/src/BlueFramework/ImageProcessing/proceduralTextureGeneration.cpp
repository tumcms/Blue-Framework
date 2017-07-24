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

#include "proceduralTextureGeneration.h"
#include "BlueFramework/Core/Math/Vector.h"
#include "BlueFramework/ImageProcessing/ColorConverter.h"
#include <random>

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

#define IDX(x, y, w) idx(x, y, w)

unsigned int seed;
std::default_random_engine generator;

int idx(int x, int y, int w) {
	if (x >= w)
		x = (w - 1) - (x - w);
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	if (y >= w)
		y = (w - 1) - (y - w);

	int index = x + y * w;
	return index;
}
bool isEven(const int number) {
	return number % 2 == 0;
}

Image4b generateCheckerboardImage(const int width, const int height) {
	buw::Image4b img(width, height);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (isEven(x / 20)) {
				if (isEven(y / 20))
					img.setPixelColorStandardCartesian(x, y, buw::Color4b(255, 0, 0, 255));
				else
					img.setPixelColorStandardCartesian(x, y, buw::Color4b(255, 255, 255, 255));
			} else {
				if (isEven(y / 20))
					img.setPixelColorStandardCartesian(x, y, buw::Color4b(255, 255, 255, 255));
				else
					img.setPixelColorStandardCartesian(x, y, buw::Color4b(255, 0, 0, 255));
			}
		}
	}

	return img;
}

float normal_distributed_random(float mean, float sigma) {
	std::normal_distribution<float> distribution(mean, sigma);
	return distribution(generator);
}

float uniform_distributed_random(float roughness, int iteration) {
	float max = std::powf(roughness, iteration + 1);
	float min = -max;
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

void normalize(std::vector<float> &heightfield, int resolution) {
	float minimum = heightfield[0];
	float maximum = 0.0;

	for (int y = 0; y <= resolution; y++) {
		for (int x = 0; x <= resolution; x++) {
			if (heightfield[idx(x, y, resolution + 1)] < minimum)
				minimum = heightfield[idx(x, y, resolution + 1)];
		}
	}

	for (int y = 0; y <= resolution; y++) {
		for (int x = 0; x <= resolution; x++) {
			heightfield[idx(x, y, resolution + 1)] -= minimum;
		}
	}

	for (int y = 0; y <= resolution; y++) {
		for (int x = 0; x <= resolution; x++) {
			if (heightfield[idx(x, y, resolution + 1)] > maximum)
				maximum = heightfield[idx(x, y, resolution + 1)];
		}
	}

	for (int y = 0; y <= resolution; y++) {
		for (int x = 0; x <= resolution; x++) {
			heightfield[idx(x, y, resolution + 1)] /= maximum;
		}
	}
}

void normalize(std::vector<buw::Vector3f> &normalMap, int resolution) {
	for (int i = 0; i <= resolution; i++) {
		for (int j = 0; j <= resolution; j++) {
			normalMap[idx(j, i, resolution + 1)].x() += 1.0f;
			normalMap[idx(j, i, resolution + 1)].y() += 1.0f;
			normalMap[idx(j, i, resolution + 1)].z() += 1.0f;

			normalMap[idx(j, i, resolution + 1)].x() /= 2.0f;
			normalMap[idx(j, i, resolution + 1)].y() /= 2.0f;
			normalMap[idx(j, i, resolution + 1)].z() /= 2.0f;
		}
	}
}

void initialize(std::vector<float> &heightfield, int resolution, float mean, float sigma) {
	for (int i = 0; i <= resolution; i++) {
		for (int j = 0; j <= resolution; j++) {
			heightfield[idx(j, i, resolution + 1)] = 0.0;
		}
	}

	heightfield[idx(0, 0, resolution + 1)] = normal_distributed_random(mean, sigma);
	heightfield[idx(0, resolution, resolution + 1)] = normal_distributed_random(mean, sigma);
	heightfield[idx(resolution, 0, resolution + 1)] = normal_distributed_random(mean, sigma);
	heightfield[idx(resolution, resolution, resolution + 1)] = normal_distributed_random(mean, sigma);
}

void diamondStep(std::vector<float> &heightfield, int startx, int starty, int resolution, int iteration, float roughness) {
	int resolution_global = resolution * pow(2, iteration) + 1;

	float values[4] = {heightfield[idx(startx, starty, resolution_global)], heightfield[idx(startx + resolution, starty, resolution_global)],
	                   heightfield[idx(startx, starty + resolution, resolution_global)], heightfield[idx(startx + resolution, starty + resolution, resolution_global)]};

	float average = (values[0] + values[1] + values[2] + values[3]) / 4.0f;
	int pos = idx(startx + resolution / 2, starty + resolution / 2, resolution_global);
	heightfield[pos] = average + uniform_distributed_random(roughness, iteration);
}

void squareStep(std::vector<float> &heightfield, int startx, int starty, int resolution, int iteration, float roughness) {
	int resolution_global = resolution * pow(2, iteration) + 1;
	float values[9] = {heightfield[idx(startx, starty - resolution, resolution_global)],
	                   heightfield[idx(startx - (resolution / 2), starty - (resolution / 2), resolution_global)],
	                   heightfield[idx(startx + (resolution / 2), starty - (resolution / 2), resolution_global)],
	                   heightfield[idx(startx - resolution, starty, resolution_global)],
	                   heightfield[idx(startx, starty, resolution_global)],
	                   heightfield[idx(startx + resolution, starty, resolution_global)],
	                   heightfield[idx(startx - (resolution / 2), starty + (resolution / 2), resolution_global)],
	                   heightfield[idx(startx + (resolution / 2), starty + (resolution / 2), resolution_global)],
	                   heightfield[idx(startx, starty + resolution, resolution_global)]};

	int pos0 = idx(startx, starty - resolution / 2, resolution_global), pos1 = idx(startx + resolution / 2, starty, resolution_global),
	    pos2 = idx(startx, starty + resolution / 2, resolution_global), pos3 = idx(startx - resolution / 2, starty, resolution_global);

	float h0 = (values[0] + values[1] + values[2] + values[4]) / 4.0f, h1 = (values[2] + values[4] + values[5] + values[7]) / 4.0f,
	      h2 = (values[4] + values[6] + values[7] + values[8]) / 4.0f, h3 = (values[1] + values[3] + values[4] + values[6]) / 4.0f;

	heightfield[pos0] = h0 + uniform_distributed_random(roughness, iteration);
	heightfield[pos1] = h1 + uniform_distributed_random(roughness, iteration);
	heightfield[pos2] = h2 + uniform_distributed_random(roughness, iteration);
	heightfield[pos3] = h3 + uniform_distributed_random(roughness, iteration);
}

void diamondSquareIterative(std::vector<float> &heightfield, int resolution, float roughness) {
	int iteration = 0;
	while (resolution > 1) {
		for (int y = 0; y < resolution * pow(2, iteration); y += resolution) {
			for (int x = 0; x < resolution * pow(2, iteration); x += resolution) {
				diamondStep(heightfield, x, y, resolution, iteration, roughness);
			}
		}

		for (int y = 0; y < resolution * pow(2, iteration); y += resolution) {
			for (int x = 0; x < resolution * pow(2, iteration); x += resolution) {
				squareStep(heightfield, x + resolution / 2, y + resolution / 2, resolution, iteration, roughness);
			}
		}
		resolution = resolution / 2;
		iteration++;
	}
}

Image4b generateRandomHeightmap(const int lod, float roughness, float mean, float sigma) {
	seed = clock();
	generator.seed(seed);
	int resolution = std::pow(2, lod);
	std::vector<float> heightfield = std::vector<float>((resolution + 1) * (resolution + 1));

	initialize(heightfield, resolution, mean, sigma);
	diamondSquareIterative(heightfield, resolution, roughness);
	normalize(heightfield, resolution);
	buw::Image4b heightmap = buw::Image4b(resolution, resolution);

	for (int y = 0; y < resolution; y++) {
		for (int x = 0; x < resolution; x++) {
			float value = heightfield[idx(x, y, resolution + 1)];
			buw::Color1f grayColor1f(value);
			buw::Color4b grayColor4b = ColorConverter::convertTo<buw::Color4b>(grayColor1f);

			heightmap.setPixelColor((unsigned int)x, (unsigned int)y, grayColor4b);
		}
	}
	return heightmap;
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END