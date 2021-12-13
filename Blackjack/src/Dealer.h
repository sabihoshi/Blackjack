#pragma once

#include <queue>

#include "Card.h"
#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();

	void AddDeck(int decks);

	void ShuffleDeck();

	std::deque<Card> Deck;

	GameAction NextAction() const;

	Card Pull(bool isHidden = false);
};
