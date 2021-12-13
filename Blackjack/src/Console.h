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
	EndOfScreen,
	Color
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

enum class GroundType
{
	Fore,
	Back
};

struct Color
{
	int R;
	int G;
	int B;
};

void PrintXY(const std::string& string, int x, int y);

std::string Repeat(char character, int repeats);

std::string Repeat(const std::string& string, int repeats);

std::string Center(const std::string& string, int length);

std::string Right(const std::string& string, int length);

std::string Left(const std::string& string, int length);

std::string Reverse(const std::string& string);

void ChangeColor(ConsoleColor color);

void ResetColor();

void SwapColors();

std::string ChangeColor(Color color, GroundType type = GroundType::Fore);

std::string ChangeColor(const std::string& string, Color color, GroundType type = GroundType::Fore);

void SetColor(Color color, GroundType type = GroundType::Fore);

COORD XY(short x, short y);

COORD XY(COORD c);

COORD XY();

COORD MoveCursor(CursorDirection direction, short amount = 1);

void Clear(ClearType type = ClearType::Screen);

COORD WriteLine(const std::string& string);

void SetConsoleMode(int mode);

void Pause();

void CinReset();
