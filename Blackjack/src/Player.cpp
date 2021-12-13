#include "Player.h"

#include <conio.h>
#include <iostream>
#include <utility>

#include "Table.h"

/**
 * \brief Gets the current active collection useful for when the hand is split.
 * \return The hand that should be used.
 */
Hand& Player::GetCurrentCollection()
{
	if (!Split) return FirstHand;
	return IsFirstHand ? FirstHand : SecondHand;
}

/**
 * \brief Blanks the cards that is seen on the screen.
 */
void Player::ClearCards() const
{
	XY(CardsXY);
	for (int c = 0; c < MAX_CARDS; c++)
	{
		const auto p = XY();
		for (int h = 0; h < Card::CARD_HEIGHT; h++)
		{
			WriteLine(Repeat(" ", Card::CARD_WIDTH));
		}
		XY(p);

		MoveCursor(Direction, Card::CARD_WIDTH);
	}
}

/**
 * \brief Prints the cards of the user.
 * \param hand The hand to print.
 * \param maxWidth The max width that the cards can occupy.
 * \param position The coordinates that the cards will start to print.
 */
void Player::PrintCards(const Hand& hand, const int maxWidth, const COORD position) const
{
	auto& cards = hand.Cards;
	const unsigned long long count = cards.size();
	if (count == 0) return;

	const unsigned long long cardWidth = count * Card::CARD_WIDTH;
	const unsigned long long width = min(maxWidth, cardWidth);
	unsigned long long jump = width / count;

	if (jump * (count - 1) + Card::CARD_WIDTH > MAX_WIDTH)
		jump--;

	XY(position);
	for (auto& card : cards)
	{
		const auto p = XY();
		card.PrintCard();
		XY(p);

		MoveCursor(Direction, static_cast<short>(jump));
	}

	XY(position);
	MoveCursor(CursorDirection::Down, Card::CARD_HEIGHT);

	if (Direction == CursorDirection::Left)
		MoveCursor(Direction, Card::CARD_WIDTH);

	std::cout << "Total: " << hand.CountTotal()
		<< " | " << "Bet: " << hand.Bet;
}

/**
 * \brief Prints all of the active hands that the user has.
 */
void Player::PrintCards() const
{
	ClearCards();

	if (Split)
	{
		constexpr int width = MAX_WIDTH / 3;
		const auto x = static_cast<short>(CardsXY.X + MAX_WIDTH / 2);
		PrintCards(FirstHand, width, CardsXY);
		PrintCards(SecondHand, width, {x, CardsXY.Y});
	}
	else
	{
		PrintCards(FirstHand, MAX_WIDTH, CardsXY);
	}
}

/**
 * \brief Prints the chips the user has.
 */
void Player::PrintChips() const
{
	if (Chips == 0)
		return;

	XY(ChipsXY);
	std::cout << Repeat(" ", 52);

	XY(ChipsXY);
	std::cout << "Chips: " << Chips;

	if (Insured) std::cout << " | Insurance: " << Insurance;
}

/**
 * \brief Creates a Player object.
 * \param name The name of the player.
 * \param direction The direction in which the cards will print.
 */
Player::Player(std::string name, const CursorDirection direction) : Direction(direction), Name(std::move(name))
{
	CardsXY = {4, 6};
	TotalXY = {4, 16};
	PromptXY = {4, 18};
	ChipsXY = {4, 21};
}

/**
 * \brief Resets the state of the player.
 */
void Player::ResetState()
{
	State = PlayerState::Normal;

	IsFirstHand = true;
	Split = false;

	Insured = false;
	Insurance = 0;
	CanInsurance = false;

	CanHit = true;
	CanSplit = false;
	CanDouble = false;

	FirstHand.Reset();
	SecondHand.Reset();
}

/**
 * \brief Prompts the user for the amount of bet.
 */
void Player::PromptBet()
{
	const int bet = Prompt<int>("How much do you want to bet?");
	Chips -= bet;

	FirstHand.Bet = bet;
}

/**
 * \brief Prompts the user for the amount of insurance.
 */
void Player::PromptInsurance()
{
	if (Chips == 0)
		return;

	while (true)
	{
		const int bet = Prompt<int>("How much do you want to insure?");
		if (bet > 0 && bet <= FirstHand.Bet / 2)
		{
			Insured = true;
			Insurance = bet;
			Chips -= bet;
			break;
		}
	}
}

/**
 * \brief Prompts the user of the action to take.
 * \param prompt The prompt message.
 * \return A GameAction containing the action the user chose.
 */
GameAction Player::PromptAction(const std::string& prompt) const
{
	while (true)
	{
		XY(PromptXY);
		WriteLine(Repeat(" ", 52));
		WriteLine(Repeat(" ", 52));

		XY(PromptXY);
		WriteLine(prompt);
		std::cout << "~> ";

		const char c = _getch();
		const auto action = GetAction(c);
		if (action != GameAction::None)
			return action;
	}
}

/**
 * \brief A string representation of the action that is pluralized.
 * \param action The action the user took.
 * \return The string containing the action.
 */
std::string Player::ActionString(const GameAction action)
{
	switch (action)
	{
		case GameAction::Hit: return "Hits";
		case GameAction::Stand: return "Stands";
		case GameAction::Double: return "Doubles";
		case GameAction::Reveal: return "Reveals";
		case GameAction::Split: return "Splits";
		case GameAction::Insurance: return "Insures";
		default: return {};
	}
}

/**
 * \brief Converts a character input into a GameAction.
 * \param c The character input.
 * \return A GameAction that the user has taken.
 */
GameAction Player::GetAction(const char c)
{
	switch (c)
	{
		case 'h': return GameAction::Hit;
		case 's': return GameAction::Stand;
		case 'd': return GameAction::Double;
		case 'p': return GameAction::Split;
		case 'i': return GameAction::Insurance;
		default: return GameAction::None;
	}
}

/**
 * \brief Prints the action that the user took on the console.
 * \param action The GameAction that the user took.
 */
void Player::PrintAction(const GameAction action) const
{
	XY(PromptXY);
	std::cout << Repeat(" ", 52);

	XY(PromptXY);
	std::cout << Name << " " << ActionString(action);
}
