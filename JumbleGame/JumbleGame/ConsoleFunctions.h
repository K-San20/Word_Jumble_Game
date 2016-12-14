#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <Windows.h>
namespace KSUN
{

	// Colors - can be used as Foreground or Background
	enum ConsoleColor
	{
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		Gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkGray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
		Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	};

	class Console
	{
		// Data Members
		static HANDLE out;
		static WORD defColors;
		static HWND hwnd;
		// Display a Unicode symbol.
		static void Show(wchar_t symbol);
		static void Show(int x, int y, wchar_t symbol);

	public:
		/////////////////////////////////////
		//         COLOR FUNCTIONS         //
		/////////////////////////////////////

		// Get the current foreground color
		static WORD ForegroundColor();
		// Change the foreground color
		static void ForegroundColor(WORD attr);

		// Get the current background color
		static WORD BackgroundColor();
		// Change the background color
		static void BackgroundColor(WORD attr);

		// Set the colors back to the defaults (usually gray on black)
		static void ResetColor();



		/////////////////////////////////////
		//         WINDOW FUNTIONS         //
		/////////////////////////////////////

		// Get the width of the window in cells (characters)
		static int WindowWidth();

		// Get the height of the window in cells (characters)
		static int WindowHeight();

		// Change the size of the window
		static void SetWindowSize(int columns, int rows);

		// Change the size of the buffer
		static void SetBufferSize(int columns, int rows);

		// Do or don't scroll when printing to the lower-right cell.
		static void EOLWrap(bool on);



		/////////////////////////////////////
		//         CURSOR FUNTIONS         //
		/////////////////////////////////////

		// Change the position of the cursor
		static void SetCursorPosition(int left, int top);

		// Set the visibility of the cursor
		static void CursorVisible(bool visible);



		/////////////////////////////////////
		//         SCREEN FUNTIONS         //
		/////////////////////////////////////

		// Clear the screen
		static void Clear();

		// For animation and/or to reduce flickering
		static void Lock(bool lock);

		// Display a rectangle in the window.
		static void DrawBox(int left, int top, int width, int height, bool dbl);
	};

}
#endif