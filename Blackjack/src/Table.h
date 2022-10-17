#pragma once

#include <vector>

#include "Card.h"
#include "Console.h"
#include "Player.h"

constexpr int DEFAULT_WIDTH = 120;
constexpr int DEFAULT_HEIGHT = 30;
constexpr int MAX_CARDS = 4;
constexpr int MAX_WIDTH = MAX_CARDS * Card::CARD_WIDTH;

void PrintTable();

void PrintCards(Card cards[], int offset);

void PrintCards(const std::vector<Card>& cards, CursorDirection direction = CursorDirection::Right);

void PrintCards(const Player& player);

void PrintStatus(const std::string& status);

template <typename T>
T Prompt(const std::string& prompt)
{
	XY(31, 26);
	std::cout << Center(prompt, 60);

	T input;
	std::cin >> input;

	return input;
}

bool PlayAgainPrompt(const std::string& message);
