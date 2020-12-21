// IMPROVED CONSOLE 5.0 LICENCSE
// == == == == == == == == == == == == == == =
// 
// To say it in the words of the original author :
// 
// Use it how you want - private or commercial, anything allowed.But no warranty
// for function and errors of this peace of code.And don't say you built it if
// you're a student at a school or university ... instead say "I found it in the
// web" ;-]

#include "ic.hpp"

#include <codecvt>
#include <locale>

#include <algorithm>

namespace ic
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	auto converter = std::wstring_convert<convert_type, wchar_t>();

	const COORD Console::origin = {0, 0};

	Console::Console ()
		: hWnd(GetConsoleWindow())
		, hConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE))
		, bufferedMode(false)
	{
		setBufferedMode(false);
		setWindowSize(80, 25);
		clear();
	}

	Console::~Console ()
	{
		setBufferedMode(true);
	}

	Console& Console::getInstance ()
	{
		static Console instance;
		return instance;
	}

	void Console::hide ()
	{
		ShowWindow(hWnd, SW_HIDE);
	}

	void Console::show ()
	{
		ShowWindow(hWnd, SW_SHOW);
	}

	void Console::minimize ()
	{
		ShowWindow(hWnd, SW_MINIMIZE);
	}
	
	void Console::maximize ()
	{
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	void Console::restore ()
	{
		ShowWindow(hWnd, SW_NORMAL);
	}

	bool Console::isFullscreen () const
	{
		DWORD flags = 0;
		GetConsoleDisplayMode(&flags);
		return (flags & CONSOLE_FULLSCREEN) != 0;
	}

	bool Console::isFullscreenSupported () const
	{
		CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
		csbiex.cbSize = sizeof(csbiex);
		GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbiex);
		return csbiex.bFullscreenSupported != 0;
	}

	void Console::setFullscreen (bool enabled)
	{
		DWORD flags = enabled ? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE;
		SetConsoleDisplayMode(hConsoleOutput, flags, NULL);
	}

	bool Console::isBufferedMode () const
	{
		return bufferedMode;
	}

	void Console::setBufferedMode (bool enabled)
	{
		DWORD additionalModes = 0;
		
		if(enabled)
		{
			additionalModes = ENABLE_WRAP_AT_EOL_OUTPUT;
		}
		else
		{
			setBufferSizeNoModeCheck(getWindowWidth(), getWindowHeight());
		}

		SetConsoleMode(hConsoleOutput, ENABLE_PROCESSED_OUTPUT | additionalModes);
		bufferedMode = enabled;
	}

	void Console::clear (Color color, WCHAR character)
	{
		fillColor(color);
		fillCharacter(character);
	}

	void Console::fillColor (Color color)
	{
		DWORD length = getBufferWidth() * getBufferHeight();
		DWORD attrsWritten;
		FillConsoleOutputAttribute(hConsoleOutput, static_cast<WORD>(color), length, origin, &attrsWritten);
	}

	void Console::fillCharacter (WCHAR character)
	{
		DWORD length = getBufferWidth() * getBufferHeight();
		DWORD charsWritten;
		FillConsoleOutputCharacter(hConsoleOutput, character, length, origin, &charsWritten);
	}

	TextColor Console::getTextColor () const
	{
		return extractTextColor(getColor());
	}

	void Console::setTextColor (TextColor color)
	{
		SetConsoleTextAttribute(hConsoleOutput,  static_cast<WORD>(color | getBackgroundColor()));
	}

	BackgroundColor Console::getBackgroundColor () const
	{
		return extractBackgroundColor(getColor());
	}

	void Console::setBackgroundColor (BackgroundColor color)
	{
		SetConsoleTextAttribute(hConsoleOutput,  static_cast<WORD>(getTextColor() | color));
	}

	Color Console::getColor () const
	{
		return getCSBI().wAttributes;
	}

	void Console::setColor (Color color)
	{
		SetConsoleTextAttribute(hConsoleOutput,  static_cast<WORD>(color));
	}

	int Console::getCursorPositionX () const
	{
		return getCSBI().dwCursorPosition.X;
	}

	int Console::getCursorPositionY () const
	{
		return getCSBI().dwCursorPosition.Y;
	}

	void Console::setCursorPosition (int x, int y)
	{
		COORD position;
		position.X = static_cast<SHORT>(x);
		position.Y = static_cast<SHORT>(y);
		SetConsoleCursorPosition(hConsoleOutput, position);
	}

	int Console::getCursorSize () const
	{
		CONSOLE_CURSOR_INFO cci = getCCI();
		return cci.bVisible ? cci.dwSize : 0;
	}

	void Console::setCursorSize (int size)
	{
		CONSOLE_CURSOR_INFO cci;
		cci.bVisible = size > 0;
		cci.dwSize = cci.bVisible ? size : 100;
		SetConsoleCursorInfo(hConsoleOutput, &cci);
	}

	int Console::getWindowPositionX () const
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.left;
	}

	int Console::getWindowPositionY () const
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		return rect.top;
	}

	void Console::setWindowPosition (int x, int y)
	{
		SetWindowPos(hWnd, 0, x, y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
	}

	int Console::getBufferWidth () const
	{
		return getCSBI().dwSize.X;
	}

	int Console::getBufferHeight () const
	{
		return getCSBI().dwSize.Y;
	}

	void Console::setBufferSize (int width, int height)
	{
		// Allow screen buffer size changes in buffered mode only
		if(!bufferedMode)
			return;

		setBufferSizeNoModeCheck(width, height);
	}

	int Console::getWindowWidth () const
	{
		return getCSBI().srWindow.Right - getCSBI().srWindow.Left + 1;
	}

	int Console::getWindowHeight () const
	{
		return getCSBI().srWindow.Bottom - getCSBI().srWindow.Top + 1;
	}

	void Console::setWindowSize (int width, int height)
	{
		// Make sure the screen buffer is at least as large as the window
		int newBufferWidth = std::max(width, getBufferWidth());
		int newBufferHeight = std::max(height, getBufferHeight());
		setBufferSizeNoModeCheck(newBufferWidth, newBufferHeight);

		SMALL_RECT rect;
		rect.Top = 0;
		rect.Left = 0;
		rect.Right = static_cast<SHORT>(width - 1);
		rect.Bottom = static_cast<SHORT>(height - 1);
		SetConsoleWindowInfo(hConsoleOutput, TRUE, &rect);

		if(!bufferedMode)
		{
			// Make sure the screen buffer has exactly the same size as the window
			setBufferSizeNoModeCheck(width, height);
		}
	}

	int Console::getMaxWindowWidth () const
	{
		return GetLargestConsoleWindowSize(hConsoleOutput).X;
	}

	int Console::getMaxWindowHeight () const
	{
		return GetLargestConsoleWindowSize(hConsoleOutput).Y;
	}

	int Console::getViewportX ()
	{
		return getCSBI().srWindow.Left;
	}

	int Console::getViewportY ()
	{
		return getCSBI().srWindow.Top;
	}

	void Console::setViewport (int x, int y, int width, int height)
	{
		if(!bufferedMode)
			return;

		// Make sure to stay within the bounds of the screen buffer
		SMALL_RECT rect;
		rect.Bottom = static_cast<SHORT>(std::min(y + height, getBufferHeight()) - 1);
		rect.Right = static_cast<SHORT>(std::min(x + width, getBufferWidth()) - 1);
		rect.Left = static_cast<SHORT>(rect.Right - width + 1);
		rect.Top = static_cast<SHORT>(rect.Bottom - height + 1);
		SetConsoleWindowInfo(hConsoleOutput, TRUE, &rect);
	}

	void Console::move (int x, int y, int width, int height, int destX, int destY)
	{
		SMALL_RECT rect;
		rect.Left = static_cast<SHORT>(x);
		rect.Right = static_cast<SHORT>(x + width - 1);
		rect.Top = static_cast<SHORT>(y);
		rect.Bottom = static_cast<SHORT>(y + height - 1);

		COORD destinationOrigin;
		destinationOrigin.X = static_cast<SHORT>(destX);
		destinationOrigin.Y = static_cast<SHORT>(destY);

		CHAR_INFO fill;
		fill.Attributes = static_cast<WORD>(getColor());
		fill.Char.UnicodeChar = L' ';

		ScrollConsoleScreenBuffer(hConsoleOutput, &rect, NULL, destinationOrigin, &fill);
	}

	std::wstring Console::getTitle () const
	{
		const int MAX_TITLE_LEN = 64 * 1024; // 64K, see MSDN

		WCHAR title [MAX_TITLE_LEN];
#ifdef UNICODE
		GetConsoleTitle(title, MAX_TITLE_LEN);
#else
		GetConsoleTitle(converter.to_bytes(title).data(), MAX_TITLE_LEN);
#endif
		
		return title;
	}

	void Console::setTitle (const std::wstring& title)
	{
#ifdef UNICODE
		SetConsoleTitle(title.c_str());
#else
		SetConsoleTitle(converter.to_bytes(title).c_str());
#endif
	}

	CONSOLE_CURSOR_INFO Console::getCCI () const
	{
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(hConsoleOutput, &cci);
		return cci;
	}

	CONSOLE_SCREEN_BUFFER_INFO Console::getCSBI () const
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
		return csbi;
	}

	void Console::setBufferSizeNoModeCheck (int width, int height)
	{
		COORD size;
		size.X = static_cast<SHORT>(width);
		size.Y = static_cast<SHORT>(height);
		SetConsoleScreenBufferSize(hConsoleOutput, size);
	}

	Console& con = Console::getInstance();
}
