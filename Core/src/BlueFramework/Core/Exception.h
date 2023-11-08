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
#ifndef BlueFramework_Core_Exception_62e1b939_f9a9_41a6_aa59_b782f03a45d6_h
#define BlueFramework_Core_Exception_62e1b939_f9a9_41a6_aa59_b782f03a45d6_h

#include "BlueFramework/Core/namespace.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "BlueFramework/Core/assert.h"

#include <tinyformat.h>
#include <StackWalker.h>
#include <stdexcept>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

class BlueStackWalker : public StackWalker {
public:
	BlueStackWalker();

	virtual ~BlueStackWalker() {
	}

protected:
	virtual void OnOutput(LPCSTR szText);
};

class Exception : public std::runtime_error {
public:
	//! Variadic template constructor to support printf-style arguments
	template <typename... Args>
	Exception(const char *fmt, const Args &... args) : std::runtime_error(tfm::format(fmt, args...)) {
		BLUE_LOG(error) << tfm::format(fmt, args...);
		BLUE_BREAKPOINT
		BlueStackWalker sw;
		sw.ShowCallstack();
	}

	virtual ~Exception(){};
};

//! This exception will be thrown if a file could not be found.
class FileNotFoundException : public Exception {
public:
	FileNotFoundException(std::string Filename);
	FileNotFoundException(const FileNotFoundException &src);

	friend std::ostream &operator<<(std::ostream &out, const FileNotFoundException &src);

	// Retrieve file that couldn't be found.
	std::string getFilename() const {
		return m_Filename;
	}

private:
	FileNotFoundException &operator=(const FileNotFoundException &src);

	std::string m_Filename; // Filename that does not exist
};

//! This exception should be thrown if a error during parsing a file occurs.
class InvalidFileFormatException : public FileNotFoundException {
public:
	InvalidFileFormatException(std::string filename);

	InvalidFileFormatException(const FileNotFoundException &src);
};

//! This exception should be thrown if a error during parsing a file occurs.
class NotImplementedYetException : public Exception {
public:
	NotImplementedYetException(std::string description);

	NotImplementedYetException(const NotImplementedYetException &src);

private:
	std::string m_Description;
}; // end class NotImplementedYetException

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(Exception)
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(FileNotFoundException)
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(NotImplementedYetException)

#endif // end define BlueFramework_Core_Exception_62e1b939_f9a9_41a6_aa59_b782f03a45d6_h
