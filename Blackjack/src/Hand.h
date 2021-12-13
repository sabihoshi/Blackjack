#pragma once

#include <vector>

#include "Card.h"

enum class HandState
{
	Normal,
	Bust,
	Blackjack
};

class Hand
{
public:
	int Bet = 0;

	void AddCard(Card card);

	std::vector<Card> Cards;
	HandState State = HandState::Normal;
	bool SinglePull = false;

	void Reveal();

	bool IsHidden() const;

	void Reset();

	bool CanDouble() const;

	int CountTotal() const;
};
