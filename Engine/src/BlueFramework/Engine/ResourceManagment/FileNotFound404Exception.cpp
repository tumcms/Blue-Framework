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
