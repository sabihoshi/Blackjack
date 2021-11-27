#pragma execution_character_set("utf-8")

#include "Card.h"
#include "Console.h"

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
		const auto symbol = SymbolString(Symbol);
		const auto suit = SuitString(Suit);
		WriteLine("╭╼╼╼╼╼╼╼╼╼╼╼╮");
		WriteLine("╽ " + Right(symbol, 2) + "        ╽");
		WriteLine("╽           ╽");
		WriteLine("╽           ╽");
		WriteLine("╽     " + suit + "     ╽");
		WriteLine("╽           ╽");
		WriteLine("╽           ╽");
		WriteLine("╽        " + Left(symbol, 2) + " ╽");
		WriteLine("╰╾╾╾╾╾╾╾╾╾╾╾╯");
	}
}

std::string Card::SuitString(CardSuit suit)
{
	switch (suit)
	{
		case CardSuit::Clubs: return "♦";
		case CardSuit::Diamonds: return "♣";
		case CardSuit::Hearts: return "♥";
		case CardSuit::Spades: return "♠";
	}
}

std::string Card::SymbolString(CardSymbol symbol)
{
	switch (symbol)
	{
		case CardSymbol::Ace: return "A";
		case CardSymbol::Two: return "2";
		case CardSymbol::Three: return "3";
		case CardSymbol::Four: return "4";
		case CardSymbol::Five: return "5";
		case CardSymbol::Six: return "6";
		case CardSymbol::Seven: return "7";
		case CardSymbol::Eight: return "8";
		case CardSymbol::Nine: return "9";
		case CardSymbol::Ten: return "10";
		case CardSymbol::Jack: return "J";
		case CardSymbol::Queen: return "Q";
		case CardSymbol::King: return "K";
	}
}

int Card::SymbolValue(CardSymbol symbol)
{
	switch (symbol)
	{
		case CardSymbol::Ace: return 1;
		case CardSymbol::Two: return 2;
		case CardSymbol::Three: return 3;
		case CardSymbol::Four: return 4;
		case CardSymbol::Five: return 5;
		case CardSymbol::Six: return 6;
		case CardSymbol::Seven: return 7;
		case CardSymbol::Eight: return 8;
		case CardSymbol::Nine: return 9;
		case CardSymbol::Ten:
		case CardSymbol::Jack:
		case CardSymbol::Queen:
		case CardSymbol::King: return 10;
	}
}

Card Card::Random()
{
	auto symbol = static_cast<CardSymbol>(rand() % 12);
	auto suit = static_cast<CardSuit>(rand() % 3);
	return {symbol, suit};
}

Card::Card(CardSymbol symbol, CardSuit suit)
{
	Symbol = symbol;
	Suit = suit;
	Value = SymbolValue(symbol);
}
