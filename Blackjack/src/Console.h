#pragma once

#include <string>
#include <Windows.h>

enum ConsoleColor
{
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	BrightWhite
};

enum class ClearType
{
	Screen,
	Line,
	Up,
	Down,
	Right,
	Left,
	EndOfLine,
	EndOfScreen
};

enum class CursorDirection
{
	Up,
	Down,
	Right,
	Left
};

enum class ScrollDirection
{
	Screen,
	Down,
	Up
};

enum class TableCharacter
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	TopEdge,
	BottomEdge,
	LeftEdge,
	RightEdge
};

void PrintXY(const std::string& string, int x, int y);

std::string Repeat(char character, int repeats);

std::string Repeat(const std::string& string, int repeats);

std::string Center(const std::string& string, int length);

std::string Right(const std::string& string, int length);

std::string Left(const std::string& string, int length);

std::string Reverse(const std::string& string);

void ChangeColor(ConsoleColor color);

/// <summary>
/// Moves the cursor position to the coordinates given.
/// </summary>
/// <param name="x">The x coordinate.</param>
/// <param name="y">The y coordinate.</param>
COORD XY(short x, short y);

COORD XY(COORD c);

COORD XY();

/// <summary>
/// Moves the cursor based on the <paramref name="direction"/> that <paramref name="amount"/> of times.
/// </summary>
/// <param name="direction">The direction where the cursor will move.</param>
/// <param name="amount">The distance the cursor should move to. Defaults to 1.</param>
COORD MoveCursor(CursorDirection direction, short amount = 1);

/// <summary>
/// Clears the text in the console based on the type.
/// </summary>
/// <param name="type">The kind of clear that will happen. Defaults to <c>Screen</c>.</param>
void Clear(ClearType type = ClearType::Screen);

COORD WriteLine(const std::string& string);

void SetConsoleMode(int mode);

void Pause();

void cinReset();
