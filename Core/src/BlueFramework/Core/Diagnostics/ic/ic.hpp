#pragma once

#ifdef _WIN32	
    #include "ic_Windows.hpp"
#else

//#include <wstring>
#include <string>

// https://stackoverflow.com/questions/8621578/do-windows-console-color-values-have-official-names-constants-associated-with/49929936#49929936
/*Enum to store Foreground colors*/
typedef enum FG_COLORS
{
    FG_BLACK = 0,
    FG_BLUE = 1,
    FG_GREEN = 2,
    FG_CYAN = 3,
    FG_RED = 4,
    FG_MAGENTA = 5,
    FG_BROWN = 6,
    FG_LIGHTGRAY = 7,
    FG_GRAY = 8,
    FG_LIGHTBLUE = 9,
    FG_LIGHTGREEN = 10,
    FG_LIGHTCYAN = 11,
    FG_LIGHTRED = 12,
    FG_LIGHTMAGENTA = 13,
    FG_YELLOW = 14,
    FG_WHITE = 15
}FG_COLORS;

/*Enum to store Background colors*/
typedef enum BG_COLORS
{
    BG_NAVYBLUE = 16,
    BG_GREEN = 32,
    BG_TEAL = 48,
    BG_MAROON = 64,
    BG_PURPLE = 80,
    BG_OLIVE = 96,
    BG_SILVER = 112,
    BG_GRAY = 128,
    BG_BLUE = 144,
    BG_LIME = 160,
    BG_CYAN = 176,
    BG_RED = 192,
    BG_MAGENTA = 208,
    BG_YELLOW = 224,
    BG_WHITE = 240
}BG_COLORS;

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.

namespace ic {
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
        //void clear (Color color = FG_WHITE | BG_BLACK, WCHAR character = L' ');

        // Fill console
        void fillColor (Color color = FG_WHITE | BG_BLACK);
        //void fillCharacter (WCHAR character = L' ');

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


    };

    namespace shorties
    {
        // Default conio.h contents
        //inline void clrscr (Color color = FG_WHITE | BG_BLACK, WCHAR character = L' ') {  }
        inline void gotoxy (int x, int y) { }
        inline int wherex () {  }
        inline int wherey () {  }
        inline void textcolor (TextColor color) {  }
        inline void textbackground (BackgroundColor color) {  }

        // djgpp conio.h extensions
        inline void delline () {  }
        inline void insline () { }
        inline void movetext (int left, int top, int right, int bottom, int destLeft, int destTop) {  }
        //inline void setcursortype (CursorType type) {  }
        inline void textattr (Color color) {  }
        inline void window (int left, int top, int right, int bottom) { }
        // More shorties
        inline void hide () {  }
        inline void show () {  }

        inline void minimize () {  }
        inline void maximize () {  }
        inline void restore () {  }

        inline void clrcol (Color color) {  }
        //inline void clrchr (WCHAR character) { ; }

        inline void home () {  }
        inline void cursize (int size) {  }

        inline void title (const std::wstring& title) {  }
    }
}
	// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
#endif