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
