#pragma once

#include <iostream>
#include <string>

enum class CardSymbol
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

enum class CardSuit
{
	Clubs,
	Diamonds,
	Hearts,
	Spades
};

class Card
{
public:
	Card(CardSymbol symbol, CardSuit suit);

	static const int CARD_WIDTH = 13;
	static const int CARD_HEIGHT = 8;

	static Card Random();

	void PrintCard() const;

	bool IsHidden = false;
	int Value = 0;
	CardSymbol Symbol;
	CardSuit Suit;
private:
	static std::string SymbolString(CardSymbol symbol);

	static std::string SuitString(CardSuit suit);

	static int SymbolValue(CardSymbol symbol);
};
