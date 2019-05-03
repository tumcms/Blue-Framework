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