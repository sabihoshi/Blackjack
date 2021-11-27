#pragma execution_character_set("utf-8")

#include "Console.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <Windows.h>

void ChangeColor(ConsoleColor color)
{
	const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

std::string Repeat(char character, int repeats)
{
	return Repeat(std::to_string(character), repeats);
}

std::string Repeat(const std::string& string, int repeats)
{
	std::ostringstream repeated;
	const auto iterator = std::ostream_iterator<std::string>(repeated);
	fill_n(iterator, repeats, string);
	return repeated.str();
}

std::string Center(const std::string& string, int length)
{
	const int left = length / 2 - string.length() / 2;
	return Repeat(" ", left) + string;
}

std::string Right(const std::string& string, const int length)
{
	const int repeat = length - string.length();
	return string + Repeat(" ", repeat);
}

std::string Left(const std::string& string, const int length)
{
	const int repeat = length - string.length();
	return Repeat(" ", repeat) + string;
}

void SetConsoleMode(int mode)
{
	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= mode;
	SetConsoleMode(hOut, dwMode);
}

COORD XY(short x, short y)
{
	return XY({x, y});
}

COORD MoveCursor(const CursorDirection direction, const short amount)
{
	const auto c = XY();
	switch (direction)
	{
		case CursorDirection::Up: XY(c.X, c.Y - amount);
			break;
		case CursorDirection::Down: XY(c.X, c.Y + amount);
			break;
		case CursorDirection::Right: XY(c.X + amount, c.Y);
			break;
		case CursorDirection::Left: XY(c.X - amount, c.Y);
			break;
	}
	return XY();
}

COORD WriteLine(const std::string& string)
{
	const auto p = XY();
	std::cout << string;
	XY(p);
	return MoveCursor(CursorDirection::Down);
}

void Clear(const ClearType type)
{
	switch (type)
	{
		case ClearType::Screen: std::system("cls"); // NOLINT(concurrency-mt-unsafe)
			break;
		case ClearType::Line: printf("\033[2K");
			break;
		case ClearType::Up: printf("\033[1J");
			break;
		case ClearType::Down: printf("\033[J");
			break;
		case ClearType::Right: printf("\033[K");
			break;
		case ClearType::Left: printf("\033[1K");
			break;
		case ClearType::EndOfLine: printf("\033K");
			break;
		case ClearType::EndOfScreen: printf("\033J");
			break;
	}
}

COORD XY(COORD c)
{
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, c);
	return c;
}

COORD XY()
{
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);
	return info.dwCursorPosition;
}

void Pause()
{
	XY(1, 28);
	system("pause");
}

void cinReset()
{
	std::cin.clear();
#pragma push_macro("max")
#undef max
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#pragma pop_macro("max")
}
