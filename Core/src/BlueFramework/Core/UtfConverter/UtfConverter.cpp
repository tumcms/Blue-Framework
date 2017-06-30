// Copied and modified code from http://www.codeproject.com/KB/string/UtfConverter.aspx.
// This project is available under the Code Project Open License (CPOL) 1.02.

#include "UtfConverter.h"

#include "ConvertUTF.h"
#include <stdexcept>
#include <string>

#pragma warning(push)
#pragma warning(disable : 4127)


namespace UtfConverter {

	std::wstring FromUtf8(const std::string& utf8string) {
#if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS
		size_t widesize = utf8string.length();
		if (sizeof(wchar_t) == 2) {
			wchar_t* widestringnative = new wchar_t[widesize + 1];
			const UTF8* sourcestart = reinterpret_cast<const UTF8*>(utf8string.c_str());
			const UTF8* sourceend = sourcestart + widesize;
			UTF16* targetstart = reinterpret_cast<UTF16*>(widestringnative);
			UTF16* targetend = targetstart + widesize + 1;
			ConversionResult res = ConvertUTF8toUTF16(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
			if (res != conversionOK) {
				delete[] widestringnative;
				throw std::runtime_error("La falla!");
			}
			*targetstart = 0;
			std::wstring resultstring(widestringnative);
			delete[] widestringnative;
			return resultstring;
		} else if (sizeof(wchar_t) == 4) {
			wchar_t* widestringnative = new wchar_t[widesize];
			const UTF8* sourcestart = reinterpret_cast<const UTF8*>(utf8string.c_str());
			const UTF8* sourceend = sourcestart + widesize;
			UTF32* targetstart = reinterpret_cast<UTF32*>(widestringnative);
			UTF32* targetend = targetstart + widesize;
			ConversionResult res = ConvertUTF8toUTF32(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
			if (res != conversionOK) {
				delete[] widestringnative;
				throw std::runtime_error("La falla!");
			}
			*targetstart = 0;
			std::wstring resultstring(widestringnative);
			delete[] widestringnative;
			return resultstring;
		} else {
			throw std::runtime_error("La falla!");
		}
#else
		//	TODO: do it properly
		std::wstring ws;
		ws.assign(utf8string.begin(), utf8string.end());
		return ws;
#endif
	}

	std::string ToUtf8(const std::wstring& widestring) {
#if BLUE_PLATFORM == BLUE_PLATFORM_WINDOWS
		size_t widesize = widestring.length();

		if (sizeof(wchar_t) == 2) {
			size_t utf8size = 3 * widesize + 1;
			char* utf8stringnative = new char[utf8size];
			const UTF16* sourcestart = reinterpret_cast<const UTF16*>(widestring.c_str());
			const UTF16* sourceend = sourcestart + widesize;
			UTF8* targetstart = reinterpret_cast<UTF8*>(utf8stringnative);
			UTF8* targetend = targetstart + utf8size;
			ConversionResult res = ConvertUTF16toUTF8(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
			if (res != conversionOK) {
				delete[] utf8stringnative;
				throw std::runtime_error("La falla!");
			}
			*targetstart = 0;
			std::string resultstring(utf8stringnative);
			delete[] utf8stringnative;
			return resultstring;
		} else if (sizeof(wchar_t) == 4) {
			size_t utf8size = 4 * widesize + 1;
			char* utf8stringnative = new char[utf8size];
			const UTF32* sourcestart = reinterpret_cast<const UTF32*>(widestring.c_str());
			const UTF32* sourceend = sourcestart + widesize;
			UTF8* targetstart = reinterpret_cast<UTF8*>(utf8stringnative);
			UTF8* targetend = targetstart + utf8size;
			ConversionResult res = ConvertUTF32toUTF8(&sourcestart, sourceend, &targetstart, targetend, strictConversion);
			if (res != conversionOK) {
				delete[] utf8stringnative;
				throw std::runtime_error("La falla!");
			}
			*targetstart = 0;
			std::string resultstring(utf8stringnative);
			delete[] utf8stringnative;
			return resultstring;
		} else {
			throw std::runtime_error("La falla!");
		}
#else
		//	TODO: do it properly
		std::string s;
		s.assign(widestring.begin(), widestring.end());
		return s;
#endif
	}
}

#pragma warning(pop)