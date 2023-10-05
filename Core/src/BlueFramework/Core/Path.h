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
