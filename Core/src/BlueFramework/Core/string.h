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
#ifndef BlueFramework_Core_string_46cdc01a_d415_4763_92ce_24f0b18a1999_h
#define BlueFramework_Core_string_46cdc01a_d415_4763_92ce_24f0b18a1999_h

#include "BlueFramework/Core/namespace.h"
#include <string>
#include <vector>

// Useful to turn defines into strings. Example:
// #define MY_MACRO 7
// BLUE_STRINGIFY(MY_MACRO) -> "MY_MACRO"
// BLUE_STRINGIFY_VALUE(MY_MACRO) -> "7"
#define BLUE_STRINGIFY_VALUE(a) BLUE_STRINGIFY(a)
#define BLUE_STRINGIFY(a) #a

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& results);
bool startsWith(const std::string& str, const std::string& start);
bool endsWith(const std::string& str, const std::string& ending);
std::string firstLetterToUpercase(const std::string&  str);

//! Replace each occurrence of from in context with to
/*!
    \param[inout]	context		A string that should be modified.
    \param[in]		from		Text that should be replaced.
    \param[in]		to			New text.
*/
std::string replace(const std::string& str, const std::string& findWhat, const std::string& replaceWith);

//! \brief Handles strings using wchar_t internally. The class is used to handle memory management issues accross different CRTs.
//! Todo: Will be modified in the future to use char and UTF8 internally.
class String {
public:
	//! Default constructor.
	String();
	String(const char* string);
	String(const wchar_t* string);
	String(const std::string& string);
	String(const std::wstring& string);

	//! Assignment operator.
	/*
	\param[in] source	The source object that should be assigned.
	*/
	String& operator=(const String& source);

	//! Copy constructor from being called.
	/*
	\param[in] source	The source object that should be copied.
	*/
	String(const String& source);

	// TODO: Make functions out of static methods
	//! converts a std::wstring to std::string
	static std::string toStdString(const std::wstring& src);

	//! converts a std::string to std::wstring
	static std::wstring toWStdString(const std::string& src);

	//! Converts an integer to an string value
	explicit String(const int value);

	virtual ~String();

	bool endsWith(const String& suffix) const;
	bool startsWith(const String& prefix) const;

	int length() const;

	std::string toStdString() const;
	const char* toCString() const;
	std::wstring toWStdString() const;

	//! Returns a lowercase copy of the string.
	String toLower() const;

	bool empty() const;

private:
	// debug-only member function
	std::wstring debugString_;

	class StringImpl;  // Forward declaration of internal class
	StringImpl* impl_; // Opaque pointer to implementation
};                     // end class String

//! Compares two strings
bool operator!=(const String& lhs, const String& rhs);

//! Compares two strings
bool operator==(const String& lhs, const String& rhs);

//! Combine two strings
String operator+(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& stream, const String& text);

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(split);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(startsWith);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(endsWith);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(replace);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(firstLetterToUpercase);
BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(String);

#endif // end define BlueFramework_Core_string_46cdc01a_d415_4763_92ce_24f0b18a1999_h
