// Copied and modified code from "API DESIGN FOR C++" library.
// This library is available under the MIT license. Original copyright notice:

/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.

// More details can be found in README.md file in the root directory.

#include "Version.h"

#include <set>
#include <sstream>
#include <string>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

Version::~Version() {
}

int Version::getMajor() {
	return int(BLUEFRAMEWORK_API_MAJOR);
}

int Version::getMinor() {
	return int(BLUEFRAMEWORK_API_MINOR);
}

int Version::getPatch() {
	return int(BLUEFRAMEWORK_API_PATCH);
}

int Version::getTweak() {
	return int(BLUEFRAMEWORK_API_TWEAK);
}

std::string Version::getVersion() {
	static std::string version("");

	if (version.empty()) {
		// cache the version string
		std::ostringstream stream;
		stream << BLUEFRAMEWORK_API_MAJOR << "." << BLUEFRAMEWORK_API_MINOR << "." << BLUEFRAMEWORK_API_PATCH << "." << BLUEFRAMEWORK_API_TWEAK;
		version = stream.str();
	}

	return version;
}

bool Version::isAtLeast(const int major, const int minor, const int patch) {
	if (BLUEFRAMEWORK_API_MAJOR < major)
		return false;
	if (BLUEFRAMEWORK_API_MAJOR > major)
		return true;
	if (BLUEFRAMEWORK_API_MINOR < minor)
		return false;
	if (BLUEFRAMEWORK_API_MINOR > minor)
		return true;
	if (BLUEFRAMEWORK_API_PATCH < patch)
		return false;
	return true;
}

BLUEFRAMEWORK_CORE_NAMESPACE_END