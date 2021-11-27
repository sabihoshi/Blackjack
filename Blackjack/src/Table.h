#pragma once

#include <vector>
#include "Card.h"
#include "Console.h"
#include "Player.h"

const int DEFAULT_WIDTH = 120;
const int DEFAULT_HEIGHT = 30;

void PrintTable(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

void PrintCards(Card cards[], int offset);

void PrintCards(const std::vector<Card>& cards, CursorDirection direction = CursorDirection::Right);

void PrintCards(const Player& player);

void PrintStatus(const std::string& status);

template <typename T>
T PromptStatus(const std::string& prompt)
{
	XY(31, 26);
	std::cout << Center(prompt, 60);

	T input;
	std::cin >> input;

	return input;
}

bool PlayAgainPrompt(const std::string& message);
