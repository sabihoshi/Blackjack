#pragma once

#include "Dealer.h"
#include "Hand.h"
#include "MainMenu.h"
#include "Player.h"

static constexpr int STARTING_CHIPS = 1000;
static constexpr int DECKS = 6;

class Game
{
public:
	Player Player;
	Dealer Dealer;

	void DoAction(GameAction action, class Player& player, bool isHidden = false);

	Game(const std::string& name, int chips);

	explicit Game(const User& user);

	int GetSplitPayout(const Hand& hand) const;

	int GetPayout(const Hand& hand) const;

	void UpdateState(GameAction action, class Player& player) const;

	void Hit(class Player& player, bool isHidden = false);

	void Hit(Hand& hand, bool isHidden = false);

	bool Play();

	void PromptAction(::Player& player);
};
