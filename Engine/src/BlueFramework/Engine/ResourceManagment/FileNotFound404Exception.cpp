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

#include "FileNotFound404Exception.h"

#include <sstream>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

FileNotFound404Exception::FileNotFound404Exception(const std::string& uri) :
	buw::Exception("404 Not Found") {
	std::stringstream ss;
	ss << "404 Not Found (" <<  uri.c_str() << ")";

	errorMessage_ = ss.str();
}

FileNotFound404Exception::~FileNotFound404Exception() {

}

const char * FileNotFound404Exception::what() const {
	return errorMessage_.c_str();
}

BLUEFRAMEWORK_ENGINE_NAMESPACE_END
