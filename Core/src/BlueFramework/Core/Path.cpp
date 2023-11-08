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

#include "Path.h"

#include <boost/filesystem.hpp>
#include <cassert>

class BlueFramework::Core::Path::PathImpl : private buw::NonCopyable {
public:
	//! Default constructor.
	PathImpl() {
	}

	PathImpl(const char* path) {
		path_ = path;
	}

	PathImpl(const std::string& path) {
		path_ = path;
	}

	// copy ctor
	PathImpl(const PathImpl& path) {
		path_ = path.path_;
	}

	// assignment operator
	PathImpl& operator=(const PathImpl& other) {
		path_ = other.path_;
	}

	PathImpl& operator=(const char* path) {
		path_ = path;
		return *this;
	}

	virtual ~PathImpl() {
	}

	std::string getString() const {
		return std::string(path_.string().c_str());
	}

	std::string getStem() const {
		return path_.stem().string();
	}

	std::string getExtension() const {
		return path_.extension().string();
	}

	bool doesExist() const {
		return boost::filesystem::exists(path_);
	}

	std::string getFilename() const {
		return path_.filename().string();
	}

private:
	boost::filesystem::path path_;
};

BlueFramework::Core::Path::Path() : impl_(new PathImpl()) {
}

BlueFramework::Core::Path::Path(const char* path) : impl_(new PathImpl(path)) {
}

BlueFramework::Core::Path::Path(const std::string& path) : impl_(new PathImpl(path)) {
}

BlueFramework::Core::Path::Path(const Path& path) : impl_(new PathImpl(*path.impl_.get())) {
}

BlueFramework::Core::Path& BlueFramework::Core::Path::operator=(const BlueFramework::Core::Path& other) {
	impl_ = other.impl_;
	return *this;
}

BlueFramework::Core::Path& BlueFramework::Core::Path::operator=(const char* path) {
	*impl_ = path;
	return *this;
}

BlueFramework::Core::Path::~Path() {
}

std::string BlueFramework::Core::Path::getString() const {
	return impl_->getString();
}

std::string BlueFramework::Core::Path::getStem() const {
	return impl_->getStem();
}

std::string BlueFramework::Core::Path::getExtension() const {
	return impl_->getExtension();
}

bool BlueFramework::Core::Path::doesExist() const {
	return impl_->doesExist();
}

bool BlueFramework::Core::Path::hasExtension(const char* extension) const {
	return getExtension() == std::string(extension);
}

std::string BlueFramework::Core::Path::getFilename() const {
	return impl_->getFilename();
}

std::ostream& operator<<(std::ostream& out, const BlueFramework::Core::Path& path) {
	out << path.getString();
	return out;
}
