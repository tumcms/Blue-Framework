// Copied and modified code from "API DESIGN FOR C++" library.
// This library is available under the MIT license. Original copyright notice:

/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.

// More details can be found in README.md file in the root directory.

#pragma once
#ifndef BlueFramework_Core_Version_0d5235dd_e6f7_4d51_987b_17b25be8c700_h
#define BlueFramework_Core_Version_0d5235dd_e6f7_4d51_987b_17b25be8c700_h

#include <BlueFramework/Core/namespace.h>
#include <string>

#define BLUEFRAMEWORK_API_MAJOR 3
#define BLUEFRAMEWORK_API_MINOR 1
#define BLUEFRAMEWORK_API_PATCH 1
#define BLUEFRAMEWORK_API_TWEAK 87

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

class Version {
public:
	virtual ~Version();

	/// Return the major version number, e.g., 1 for "1.2.3.4"
	static int getMajor();
	/// Return the minor version number, e.g., 2 for "1.2.3.4"
	static int getMinor();
	/// Return the patch version number, e.g., 3 for "1.2.3.4"
	static int getPatch();
	/// Return the patch version number, e.g., 3 for "1.2.3.4"
	static int getTweak();

	/// Return the full version number as a string, e.g., "1.2.3.4"
	static std::string getVersion();

	/// Return true if the current version >= (major, minor, patch, tweak)
	static bool isAtLeast(const int major, const int minor, const int patch, const int tweak);
};

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(Version);

#endif // end define BlueFramework_Core_Version_0d5235dd_e6f7_4d51_987b_17b25be8c700_h