#pragma execution_character_set("utf-8")

#include "Card.h"

#include "Console.h"

/**
 * \brief Prints the current card to the screen.
 * \note The position is dependent on where the cursor is on the screen.
 */
void Card::PrintCard() const
{
	if (IsHidden)
	{
		WriteLine("╭╼╼╼╼╼╼╼╼╼╼╼╮");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▓▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╽▒▒▒▒▒▒▒▒▒▒▒╽");
		WriteLine("╰╾╾╾╾╾╾╾╾╾╾╾╯");
	}
	else
	{
		const auto rank = RankString();
		const auto suit = SuitString();
		const auto color = GetColor();
		WriteLine("╭╼╼╼╼╼╼╼╼╼╼╼╮");
		WriteLine("╽ " + ChangeColor(Right(rank, 2), color) + "        ╽");
		WriteLine("╽           ╽");
		WriteLine("╽           ╽");
		WriteLine("╽     " + ChangeColor(suit, color) + "     ╽");
		WriteLine("╽           ╽");
		WriteLine("╽           ╽");
		WriteLine("╽        " + ChangeColor(Left(rank, 2), color) + " ╽");
		WriteLine("╰╾╾╾╾╾╾╾╾╾╾╾╯");
	}
}

/**
 * \brief Returns the corresponding string value of the suit.
 * \return A string containing the suit.
 */
std::string Card::SuitString() const
{
	switch (Suit)
	{
		case CardSuit::Clubs: return "♣";
		case CardSuit::Diamonds: return "♦";
		case CardSuit::Hearts: return "♥";
		case CardSuit::Spades: return "♠";
	}
}

/**
 * \brief Returns the corresponding string value of the rank/
 * \return A string containing the rank.
 */
std::string Card::RankString() const
{
	switch (Rank)
	{
		case CardRank::Ace: return "A";
		case CardRank::Two: return "2";
		case CardRank::Three: return "3";
		case CardRank::Four: return "4";
		case CardRank::Five: return "5";
		case CardRank::Six: return "6";
		case CardRank::Seven: return "7";
		case CardRank::Eight: return "8";
		case CardRank::Nine: return "9";
		case CardRank::Ten: return "10";
		case CardRank::Jack: return "J";
		case CardRank::Queen: return "Q";
		case CardRank::King: return "K";
	}
}

/**
 * \brief Returns the value of the corresponding rank.
 * \return An int containing the value of the rank.
 */
int Card::RankValue() const
{
	switch (Rank)
	{
		case CardRank::Ace: return 1;
		case CardRank::Two: return 2;
		case CardRank::Three: return 3;
		case CardRank::Four: return 4;
		case CardRank::Five: return 5;
		case CardRank::Six: return 6;
		case CardRank::Seven: return 7;
		case CardRank::Eight: return 8;
		case CardRank::Nine: return 9;
		case CardRank::Ten:
		case CardRank::Jack:
		case CardRank::Queen:
		case CardRank::King: return 10;
	}
}

/**
 * \brief Gets the color of the card.
 * \return A Color containing the color of the card.
 */
Color Card::GetColor() const
{
	switch (Suit)
	{
		case CardSuit::Clubs:
		case CardSuit::Spades: return {-1, -1, -1};
		case CardSuit::Diamonds:
		case CardSuit::Hearts: return {200, 0, 0};
	}
}

/**
 * \brief Creates a Card object.
 * \param rank The rank of the card.
 * \param suit The suit of the card.
 */
Card::Card(const CardRank rank, const CardSuit suit)
{
	Rank = rank;
	Suit = suit;
	Value = RankValue();
}
