#pragma once

#include "Player.h"
#include <utility>

// TODO
void Player::Double() {}

void Player::PrintCards()
{
	XY(CardsXY);
	for (auto& i : Cards)
	{
		const auto p = XY();
		i.PrintCard();
		XY(p);

		MoveCursor(Direction, Card::CARD_WIDTH);
	}

	XY(TotalXY);
	std::cout << Name << "'s total is " << CountTotal();
}

void Player::PrintChips() const
{
	if (ChipsXY.X == 0 && ChipsXY.Y == 0)
		return;

	XY(ChipsXY);
	std::cout << Repeat(" ", 52);

	XY(ChipsXY);
	std::cout << "Chips: " << Chips
		<< " | " << "Bet: " << Bet;
}

int Player::CountTotal() const
{
	int total = 0;
	for (const auto& card : Cards)
	{
		if (!card.IsHidden)
			total += card.Value;
	}
	return HasAce && total + 10 < 21 ? total + 10 : total;
}

Player::Player(const CursorDirection direction) : Direction(direction) { }

Player::Player(std::string name) : Player(CursorDirection::Right)
{
	Name = std::move(name);

	CardsXY = {4, 6};
	TotalXY = {4, 16};
	PromptXY = {4, 18};
	ChipsXY = {4, 21};
}

void Player::PromptBet()
{
	Bet = Prompt<int>("How much do you want to bet?");
	Chips -= Bet;

	UpdateState();
}

GameAction Player::PromptAction(const std::string& prompt) const
{
	while (true)
	{
		XY(PromptXY);

		const auto xy = WriteLine(prompt);
		WriteLine(Repeat(" ", 54) + "║  ║" + Repeat(" ", 57) + "║");

		XY(xy);
		std::cout << "~> ";

		char c;
		std::cin >> c;

		if (!std::cin)
		{
			cinReset();
		}
		else
		{
			const auto action = GetAction(c);
			if (action != GameAction::None)
				return action;
		}
	}
}

std::string Player::ActionString(const GameAction action)
{
	switch (action)
	{
		case GameAction::Hit: return "Hits";
		case GameAction::Stand: return "Stands";
		case GameAction::Double: return "Doubles";
		case GameAction::Reveal: return "Reveals";
		default: return {};
	}
}

GameAction Player::GetAction(const char c)
{
	switch (c)
	{
		case 'h':
		case 'H': return GameAction::Hit;
		case 's':
		case 'S': return GameAction::Stand;
		case 'd':
		case 'D': return GameAction::Double;
		default: return GameAction::None;
	}
}

void Player::Stand()
{
	State = PlayerState::Stand;
	UpdateState(GameAction::Stand);
}

void Player::PrintAction(const GameAction action) const
{
	XY(PromptXY);
	std::cout << Repeat(" ", 52);

	XY(PromptXY);
	std::cout << Name << " " << ActionString(action);
}

void Player::UpdateState(const GameAction action)
{
	CardTotal = CountTotal();

	if (Cards.size() == 2 && Cards[0].Symbol == Cards[1].Symbol)
		CanSplit = true;

	if (CardTotal == 21) State = PlayerState::Blackjack;
	else if (CardTotal > 21) State = PlayerState::Bust;
	else State = PlayerState::Normal;

	PrintChips();
	PrintCards();
	PrintAction(action);
	Pause();
}
