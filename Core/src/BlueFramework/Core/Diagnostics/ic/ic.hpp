// IMPROVED CONSOLE 5.0 LICENCSE
// == == == == == == == == == == == == == == =
// 
// To say it in the words of the original author :
// 
// Use it how you want - private or commercial, anything allowed.But no warranty
// for function and errors of this peace of code.And don't say you built it if
// you're a student at a school or university ... instead say "I found it in the
// web" ;-]

#ifndef INCLUDE_GUARD_IC_HPP
#define INCLUDE_GUARD_IC_HPP

#include <string>
#include <Windows.h>

namespace ic
{
	// Enumeration containing all possible foreground colors (text colors)
	enum TextColor
	{
		FG_BLACK			= 0,
		FG_BLUE				= FOREGROUND_BLUE,
		FG_GREEN			= FOREGROUND_GREEN,
		FG_CYAN				= FOREGROUND_BLUE | FOREGROUND_GREEN,
		FG_RED				= FOREGROUND_RED,
		FG_MAGENTA			= FOREGROUND_BLUE | FOREGROUND_RED,
		FG_BROWN			= FOREGROUND_GREEN | FOREGROUND_RED,
		FG_LIGHTGRAY		= FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
		FG_DARKGRAY			= FG_BLACK | FOREGROUND_INTENSITY,
		FG_LIGHTBLUE		= FG_BLUE | FOREGROUND_INTENSITY,
		FG_LIGHTGREEN		= FG_GREEN | FOREGROUND_INTENSITY,
		FG_LIGHTCYAN		= FG_CYAN | FOREGROUND_INTENSITY,
		FG_LIGHTRED			= FG_RED | FOREGROUND_INTENSITY,
		FG_LIGHTMAGENTA		= FG_MAGENTA | FOREGROUND_INTENSITY,
		FG_YELLOW			= FG_BROWN | FOREGROUND_INTENSITY,
		FG_WHITE			= FG_LIGHTGRAY | FOREGROUND_INTENSITY
	};

	// Enumeration containing all possible background colors
	enum BackgroundColor
	{
		BG_BLACK			= 0,
		BG_BLUE				= BACKGROUND_BLUE,
		BG_GREEN			= BACKGROUND_GREEN,
		BG_CYAN				= BACKGROUND_BLUE | BACKGROUND_GREEN,
		BG_RED				= BACKGROUND_RED,
		BG_MAGENTA			= BACKGROUND_BLUE | BACKGROUND_RED,
		BG_BROWN			= BACKGROUND_GREEN | BACKGROUND_RED,
		BG_LIGHTGRAY		= BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,
		BG_DARKGRAY			= BG_BLACK | BACKGROUND_INTENSITY,
		BG_LIGHTBLUE		= BG_BLUE | BACKGROUND_INTENSITY,
		BG_LIGHTGREEN		= BG_GREEN | BACKGROUND_INTENSITY,
		BG_LIGHTCYAN		= BG_CYAN | BACKGROUND_INTENSITY,
		BG_LIGHTRED			= BG_RED | BACKGROUND_INTENSITY,
		BG_LIGHTMAGENTA		= BG_MAGENTA | BACKGROUND_INTENSITY,
		BG_YELLOW			= BG_BROWN | BACKGROUND_INTENSITY,
		BG_WHITE			= BG_LIGHTGRAY | BACKGROUND_INTENSITY
	};

	// Used for combinations of one foreground and one background color
	typedef int Color;

	// Enumeration of common cursor sizes
	enum CursorType
	{
		CURSOR_HIDDEN = 0,
		CURSOR_NORMAL = 10,
		CURSOR_INSERT = 10,
		CURSOR_SOLID = 100,
		CURSOR_OVERWRITE = 100
	};

	class Console
	{
		// Constructors
		Console ();
	public:
		~Console ();

		// Singleton access
		static Console& getInstance ();

		// Hide/Show console
		void hide ();
		void show ();

		// Minimize/Maximize/Restore console
		void minimize ();
		void maximize ();
		void restore ();

		// Enable/Disable fullscreen
		//	Not supported in Windows 7 or higher.
		bool isFullscreen () const;
		bool isFullscreenSupported () const;
		void setFullscreen (bool enabled);

		// Enable/Disable buffered mode
		//	Disabled (default): Screen buffer has exactly the same size as the window, no scrolling.
		//	Enabled: Screen buffer may be larger than the window, scrolling enabled.
		//	Note: Only buffered mode enables "wrap output at end of line" behavior.
		bool isBufferedMode () const;
		void setBufferedMode (bool enabled);

		// Clear console
		void clear (Color color = FG_WHITE | BG_BLACK, WCHAR character = L' ');

		// Fill console
		void fillColor (Color color = FG_WHITE | BG_BLACK);
		void fillCharacter (WCHAR character = L' ');

		// Get/Set active text color
		TextColor getTextColor () const;
		void setTextColor (TextColor color);

		// Get/Set active background color
		BackgroundColor getBackgroundColor () const;
		void setBackgroundColor (BackgroundColor color);

		// Get/Set active color
		//	Must be combination of one foreground and one background color.
		Color getColor () const;
		void setColor (Color color);

		// Get/Set cursor position
		//	Range: 0/0 to width-1/height-1
		int getCursorPositionX () const;
		int getCursorPositionY () const;
		void setCursorPosition (int x, int y);

		// Get/Set cursor size
		//	Range: 0 (hidden) to 100
		//	Hint: Use CursorType enumeration values.
		int getCursorSize () const;
		void setCursorSize (int size);

		// Get/Set window position
		int getWindowPositionX () const;
		int getWindowPositionY () const;
		void setWindowPosition (int x, int y);

		// Get/Set screen buffer size (buffered mode only)
		//	Must be at least as large as the window.
		//	Note: There is a minimum size as well - resulting out of Windows' minimum window size. Interestingly, you
		//	can (programmatically) downsize the window further, still, the buffer's minimum size remains in effect!
		//	Experienced data: 14/1 on normal font size, 28/1 on smallest font size (Windows 7, 1920x1080).
		int getBufferWidth () const;
		int getBufferHeight () const;
		void setBufferSize (int width, int height);

		// Get/Set window size
		//	If buffered mode is disabled (default) you have to keep minimum buffer sizes in mind (see setBufferSize).
		int getWindowWidth () const;
		int getWindowHeight () const;
		void setWindowSize (int width, int height);

		// Get maximum window size
		int getMaxWindowWidth () const;
		int getMaxWindowHeight () const;

		// Sets the console viewport (buffered mode only)
		//	Defines the visible area of the screen buffer. If the new viewport differs in size, the window is resized.
		//	Keep minimum buffer sizes in mind (see setBufferSize).
		int getViewportX ();
		int getViewportY ();
		void setViewport (int x, int y, int width, int height);

		// Scrolling (buffered mode only)
		//	Moves the viewport without changing its size.
		inline void scroll (int x, int y) { setViewport(x, y, getWindowWidth(), getWindowHeight()); }
		inline void scrollRelative (int columns, int rows) { scroll(getViewportX() + columns, getViewportY() + rows); }

		// Move screen buffer contents
		//	Moves a rectangular area of the screen buffer.
		void move (int x, int y, int width, int height, int destX, int destY);

		// Get/Set console title
		//	Maximum length: 65536 characters
		std::wstring getTitle () const;
		void setTitle (const std::wstring& title);

	private:
		// General helpers
		CONSOLE_CURSOR_INFO getCCI () const;
		CONSOLE_SCREEN_BUFFER_INFO getCSBI () const;

		// Helpers for getTextColor() & getBackgroundColor()
		inline TextColor extractTextColor (Color color) const { return static_cast<TextColor>(color & 0x0F); }
		inline BackgroundColor extractBackgroundColor (Color color) const { return static_cast<BackgroundColor>(color & 0xF0); }

		// Helpers for setBufferSize() & setWindowSize()
		void setBufferSizeNoModeCheck (int width, int height);

		// Non-copyable
		Console (const Console&);
		Console& operator= (const Console&);

	private:
		// Handle to console window
		HWND hWnd;
		// Handle to console output device (the active console screen buffer)
		HANDLE hConsoleOutput;
		// Buffered mode active?
		bool bufferedMode;

		// Origin of the console's coordinate system
		static const COORD origin;
	};

	// Singleton reference
	extern Console& con;

	namespace shorties
	{
		// Default conio.h contents
		inline void clrscr (Color color = FG_WHITE | BG_BLACK, WCHAR character = L' ') { con.clear(color, character); }
		inline void gotoxy (int x, int y) { con.setCursorPosition(x, y); }
		inline int wherex () { return con.getCursorPositionX(); }
		inline int wherey () { return con.getCursorPositionY(); }
		inline void textcolor (TextColor color) { con.setTextColor(color); }
		inline void textbackground (BackgroundColor color) { con.setBackgroundColor(color); }

		// djgpp conio.h extensions
		inline void delline () { con.move(0, con.getCursorPositionY() + 1, con.getBufferWidth(), con.getBufferHeight() - con.getCursorPositionY() + 1, 0, con.getCursorPositionY()); }
		inline void insline () { con.move(0, con.getCursorPositionY(), con.getBufferWidth(), con.getBufferHeight() - con.getCursorPositionY() + 2, 0, con.getCursorPositionY() + 1); }
		inline void movetext (int left, int top, int right, int bottom, int destLeft, int destTop) { con.move(left, top, right - left + 1, bottom - top + 1, destLeft, destTop); }
		inline void setcursortype (CursorType type) { con.setCursorSize(type); }
		inline void textattr (Color color) { con.setColor(color); }
		inline void window (int left, int top, int right, int bottom) { con.setViewport(left, top, right - left + 1, bottom - top + 1); }

		// More shorties
		inline void hide () { con.hide(); }
		inline void show () { con.show(); }

		inline void minimize () { con.minimize(); }
		inline void maximize () { con.maximize(); }
		inline void restore () { con.restore(); }

		inline void clrcol (Color color) { con.fillColor(color); }
		inline void clrchr (WCHAR character) { con.fillCharacter(character); }
		
		inline void home () { con.setCursorPosition(0, 0); }
		inline void cursize (int size) { con.setCursorSize(size); }
		
		inline void title (const std::wstring& title) { con.setTitle(title); }
	}
}

#endif // INCLUDE_GUARD_IC_HPP
