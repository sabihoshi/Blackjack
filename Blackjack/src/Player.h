#pragma once

#include <vector>
#include "Card.h"
#include "Console.h"

enum class PlayerState
{
	Normal,
	Blackjack,
	Bust,
	Stand
};

enum class GameAction
{
	None,
	Hit,
	Stand,
	Double,
	Reveal
};

class Player
{
public:
	explicit Player(std::string name);

	std::vector<Card> Cards;
	int Chips = 0;
	int Bet = 0;
	bool CanHit = true;
	bool CanSplit = false;
	bool HasAce = false;
	int CardTotal;
	PlayerState State;

	void UpdateState(GameAction action = GameAction::None);

	void Double();

	template <typename T>
	T Prompt(const std::string& prompt)
	{
		while (true)
		{
			XY(PromptXY);
			WriteLine(Repeat(" ", 52));
			WriteLine(Repeat(" ", 52));

			XY(PromptXY);
			WriteLine(prompt);
			std::cout << "~> ";

			T input;
			std::cin >> input;

			if (!std::cin)
				cinReset();

			return input;
		}
	}

	void Stand();

	void PromptBet();

	GameAction PromptAction(const std::string& prompt) const;

	CursorDirection Direction;
	std::string Name;
	COORD CardsXY{0, 0};
	COORD TotalXY{0, 0};
	COORD PromptXY{0, 0};
	COORD ChipsXY{0, 0};
protected:
	explicit Player(CursorDirection direction);

private:
	void PrintCards();

	void PrintChips() const;

	void PrintAction(GameAction action) const;

	int CountTotal() const;

	static GameAction GetAction(char c);

	static std::string ActionString(GameAction action);
};
