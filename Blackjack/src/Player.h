#pragma once

#include <iostream>

#include "Console.h"
#include "Hand.h"

enum class PlayerState
{
	Normal,
	Bust,
	Stand
};

enum class GameAction
{
	None,
	Hit,
	Stand,
	Double,
	Reveal,
	Split,
	Insurance
};

class Player
{
public:
	explicit Player(std::string name, CursorDirection direction = CursorDirection::Right);

	Hand FirstHand;
	Hand SecondHand;
	int Chips = 0;
	int Insurance = 0;
	bool Insured = false;
	bool CanInsurance = false;
	bool Split = false;
	bool CanHit = true;
	bool CanSplit = false;
	bool CanDouble = false;
	bool IsFirstHand = true;

	PlayerState State = PlayerState::Normal;

	void ResetState();

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
				CinReset();

			return input;
		}
	}

	void Stand();

	void PromptBet();

	void PromptInsurance();

	GameAction PromptAction(const std::string& prompt) const;

	CursorDirection Direction;
	std::string Name;
	COORD CardsXY{0, 0};
	COORD TotalXY{0, 0};
	COORD PromptXY{0, 0};
	COORD ChipsXY{0, 0};

	Hand& GetCurrentCollection();

	void PrintChips() const;

	void PrintCards() const;

	void PrintAction(GameAction action) const;

private:
	void ClearCards() const;

	void PrintCards(const Hand& hand, int maxWidth, COORD position) const;

	static GameAction GetAction(char c);

	static std::string ActionString(GameAction action);
};
