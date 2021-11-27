#pragma once

#include <queue>
#include "Card.h"
#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();

	Card Hit(Player& player, bool isHidden = false);

	Card Hit(bool isHidden = false);

	void Reveal();

	Card Pull(bool isHidden = false);

	std::deque<Card> Deck;

	GameAction NextAction() const;
};
