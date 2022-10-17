#pragma once

#include <string>

#include "Console.h"

enum class CardRank
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

enum class CardSuit
{
	Clubs,
	Diamonds,
	Hearts,
	Spades
};

class Card
{
public:
	Card(CardRank rank, CardSuit suit);

	static constexpr int CARD_WIDTH = 13;
	static constexpr int CARD_HEIGHT = 9;

	void PrintCard() const;

	bool IsHidden = false;
	int Value = 0;
	CardRank Rank;
	CardSuit Suit;
private:
	std::string RankString() const;

	std::string SuitString() const;

	int RankValue() const;

	Color GetColor() const;
};
