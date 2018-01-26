/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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

#include "string.h"

#include "UtfConverter/UtfConverter.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <sstream>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

std::string firstLetterToUpercase(const std::string&  str) {
	std::string s = str;

	if (s.length() != 0) {
		s[0] = static_cast<char>(toupper(s[0]));
	}

	return s;
}

void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& results) {
	boost::split(results, str, boost::is_any_of(delimiter));
}

bool startsWith(const std::string& str, const std::string& start) {
	return boost::starts_with(str, start);
}

bool endsWith(const std::string& str, const std::string& ending) {
	return boost::ends_with(str, ending);
}

std::string replace(const std::string& str, const std::string& findWhat, const std::string& replaceWith) {
	std::string context = str;
	size_t lookHere = 0;
	size_t foundHere;
	while ((foundHere = context.find(findWhat, lookHere)) != std::string::npos) {
		context.replace(foundHere, findWhat.size(), replaceWith);
		lookHere = foundHere + replaceWith.size();
	}
	return context;
}

class String::StringImpl {
public:
	StringImpl() {
		cstring_ = nullptr;
	}

	virtual ~StringImpl() {
		delete[] cstring_;
	}

	StringImpl(const char* string) {
		cstring_ = nullptr;
		string_ = UtfConverter::FromUtf8(string);
	}

	StringImpl(const wchar_t* string) {
		cstring_ = nullptr;
		string_ = string;
	}

	StringImpl(const std::string& string) {
		cstring_ = nullptr;
		string_ = UtfConverter::FromUtf8(string);
	}

	StringImpl(const std::wstring& string) {
		cstring_ = nullptr;
		string_ = string;
	}

	StringImpl(const int value) {
		cstring_ = nullptr;
		std::wstringstream ss;
		ss << value;
		string_ = ss.str();
	}

	StringImpl(const StringImpl& source) {
		cstring_ = nullptr;
		string_ = source.string_;
	}

	StringImpl& operator=(const StringImpl& source) {
		string_ = source.string_;
		return *this;
	}

	bool endsWith(const String& suffix) const {
		if (string_.length() > suffix.length()) {
			return (0 == string_.compare(string_.length() - suffix.length(), suffix.length(), suffix.impl_->string_));
		} else {
			return false;
		}
	}

	bool startsWith(const String& prefix) const {
		if (string_.length() > prefix.length()) {
			return (0 == string_.compare(string_.length() - prefix.length(), prefix.length(), prefix.impl_->string_));
		} else {
			return false;
		}
	}

	int length() const {
		return static_cast<int>(string_.length());
	}

	std::string toStdString() const {
		return UtfConverter::ToUtf8(string_);
	}

	const char* toCString() const {
		if (cstring_) {
			delete[] cstring_;
		}

		std::string data = UtfConverter::ToUtf8(string_);

		cstring_ = new char[data.length() + 1];
		// std::copy(data.begin(), data.end(), cstring_);
		if (data.length() > 0) {
			memcpy(cstring_, data.c_str(), data.length());
		}

		cstring_[data.length()] = '\0';
		return cstring_;
	}

	std::wstring toWStdString() const {
		return string_;
	}

	static std::string toStdString(const std::wstring& src) {
		return UtfConverter::ToUtf8(src);
	}

	static std::wstring toWStdString(const std::string& src) {
		return UtfConverter::FromUtf8(src);
	}

	String toLower() const {
		std::string data = toStdString();
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		return String(data.c_str());
	}

	bool empty() const {
		return string_.empty();
	}

private:
	std::wstring string_;
	mutable char* cstring_;
};

String::String() {
	impl_ = new StringImpl;

	debugString_ = L"";
}

String::String(const char* string) {
	impl_ = new StringImpl(string);

	debugString_ = toWStdString(string);
}

String::String(const wchar_t* string) {
	impl_ = new StringImpl(string);

	debugString_ = string;
}

String::String(const String& source) {
	impl_ = new StringImpl(*source.impl_);

	debugString_ = source.debugString_;
}

String::String(const int value) {
	impl_ = new StringImpl(value);

	std::wstringstream ss;
	ss << value;
	debugString_ = ss.str();
}

String::String(const std::string& string) {
	impl_ = new StringImpl(string);

	debugString_ = toWStdString(string);
}

String::String(const std::wstring& string) {
	impl_ = new StringImpl(string);

	debugString_ = string;
}

String::~String() {
	delete impl_;
}

bool String::startsWith(const String& prefix) const {
	return impl_->startsWith(prefix);
}

bool String::endsWith(const String& suffix) const {
	return impl_->endsWith(suffix);
}

int String::length() const {
	return impl_->length();
}

std::string String::toStdString() const {
	return impl_->toStdString();
}

std::string String::toStdString(const std::wstring& src) {
	return String::StringImpl::toStdString(src);
}

std::wstring String::toWStdString(const std::string& src) {
	return String::StringImpl::toWStdString(src);
}

const char* String::toCString() const {
	return impl_->toCString();
}

std::wstring String::toWStdString() const {
	return impl_->toWStdString();
}

String& String::operator=(const String& source) {
	this->debugString_ = source.debugString_;
	*impl_ = *source.impl_;
	return *this;
}

String operator+(const String& lhs, const String& rhs) {
	std::wstringstream ss;
	ss << lhs.toWStdString() << rhs.toWStdString();
	String combined(ss.str().c_str());
	return combined;
}

String String::toLower() const {
	return impl_->toLower();
}

bool String::empty() const {
	return impl_->empty();
}

//////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& stream, const String& text) {
	stream << text.toCString();
	return stream;
}

bool operator!=(const String& lhs, const String& rhs) {
	return lhs.toWStdString() != rhs.toWStdString();
}

bool operator==(const String& lhs, const String& rhs) {
	return lhs.toWStdString() == rhs.toWStdString();
}

BLUEFRAMEWORK_CORE_NAMESPACE_END