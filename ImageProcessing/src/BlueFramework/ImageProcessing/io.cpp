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

#include "BlueFramework/ImageProcessing/io.h"
#include "BlueFramework/Core/Exception.h"

#pragma warning(push)
#pragma warning(disable : 4127)

#include <QImage>
#include <QImageReader>

#pragma warning(pop)

#include <boost/filesystem.hpp>

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN

Image4b loadImage4b(const std::string& filename) {
	if (!boost::filesystem::exists(filename)) {
		throw buw::Exception("Image file %s does not exist.", filename.c_str());
	}
	
	QImage qimg(filename.c_str());
	Image4b img(qimg.width(), qimg.height());

	for (int y = 0; y < qimg.height(); ++y)
		for (int x = 0; x < qimg.width(); ++x)	{
			auto c = qimg.pixelColor(x, y);
			img.setPixelColor(x, y, Color4b(
				static_cast<unsigned char>(c.red()), 
				static_cast<unsigned char>(c.green()), 
				static_cast<unsigned char>(c.blue()),
				static_cast<unsigned char>(c.alpha())));
		}
	
	return img;
}

Image3b loadImage3b(const std::string& filename) {
	if (!boost::filesystem::exists(filename)) {
		throw buw::Exception("Image file %s does not exist.", filename.c_str());
	}

	QImage qimg(filename.c_str());
	Image3b img(qimg.width(), qimg.height());

	for (int y = 0; y < qimg.height(); ++y)
		for (int x = 0; x < qimg.width(); ++x) {
			auto c = qimg.pixelColor(x, y);
			img.setPixelColor(x, y, Color3b(
				static_cast<unsigned char>(c.red()),
				static_cast<unsigned char>(c.green()),
				static_cast<unsigned char>(c.blue())));
		}

	return img;
}

void storeImage(const std::string& filename, const Image3b& img) {
	QImage image((const uchar *)img.getData(), img.getWidth(), img.getHeight(), QImage::Format_RGB888);
	image.save(filename.c_str());
}

void storeImage(const std::string& filename, const Image4b& img) {
	QImage image((const uchar *)img.getData(), img.getWidth(), img.getHeight(), QImage::Format_RGBA8888);
	image.save(filename.c_str());
}

BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END