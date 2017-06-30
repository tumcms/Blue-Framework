// Copied and modified code from http://www.codeproject.com/KB/string/UtfConverter.aspx.
// This project is available under the Code Project Open License (CPOL) 1.02.

#pragma once

#include <string>

namespace UtfConverter {
	std::wstring FromUtf8(const std::string& utf8string);
	std::string ToUtf8(const std::wstring& widestring);
}
