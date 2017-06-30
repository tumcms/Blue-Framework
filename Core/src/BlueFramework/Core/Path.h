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
#ifndef BlueFramework_Core_Path_80a543c8_5f30_4cc8_8bb4_c3af8070a8c4_h
#define BlueFramework_Core_Path_80a543c8_5f30_4cc8_8bb4_c3af8070a8c4_h

#include "BlueFramework/Core/Noncopyable.h"
#include "BlueFramework/Core/memory.h"
#include "BlueFramework/Core/namespace.h"
#include <string>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

//! \class Path
//! \brief This class can be used to represent path to files and directories.
class Path {
public:
	//! Empty path.
	Path();

	Path(const char *path);

	Path(const std::string &path);

	// copy ctor
	Path(const Path &path);

	// assignment operator
	Path &operator=(const Path &other);

	// assignment operator
	Path &operator=(const char *path);

	virtual ~Path();

	//! Get path as string
	std::string getString() const;

	//! Get filename
	std::string getStem() const;

	//! Get file extension as string
	std::string getExtension() const;

	//! Get file name and extension as String
	std::string getFilename() const;

	//! Checks if the path does exist
	bool doesExist() const;

	bool hasExtension(const char *extension) const;

private:
	class PathImpl;                        // Forward declaration of internal class
	buw::ReferenceCounted<PathImpl> impl_; // Opaque pointer to implementation
};                                         // end class Path

BLUEFRAMEWORK_CORE_NAMESPACE_END

std::ostream &operator<<(std::ostream &out, const BlueFramework::Core::Path &path);

namespace buw {
	using BlueFramework::Core::Path;
}

#endif // end define BlueFramework_Core_Path_80a543c8_5f30_4cc8_8bb4_c3af8070a8c4_h
