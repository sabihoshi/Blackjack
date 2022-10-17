#include "Dealer.h"

#include <algorithm>
#include <random>

/**
 * \brief Pulls a Card from the deck.
 * \param isHidden Whether the card is hidden.
 * \return A Card that was pulled.
 */
Card Dealer::Pull(const bool isHidden)
{
	auto card = Deck.front();
	card.IsHidden = isHidden;
	Deck.pop_front();

	return card;
}

/**
 * \brief Adds a standard 52 deck.
 * \param decks The amount of decks to add.
 */
void Dealer::AddDeck(const int decks)
{
	for (int i = 0; i < decks; ++i)
	{
		for (int suit = 0; suit < 4; ++suit)
		{
			for (int rank = 0; rank < 13; ++rank)
			{
				Deck.emplace_back(
					static_cast<CardRank>(rank),
					static_cast<CardSuit>(suit)
				);
			}
		}
	}
}

/**
 * \brief Shuffles the deck.
 */
void Dealer::ShuffleDeck()
{
	std::shuffle(Deck.begin(), Deck.end(), std::mt19937(std::random_device()()));
}

/**
 * \brief The default constructor for the dealer.
 */
Dealer::Dealer() : Player("Dealer", CursorDirection::Left)
{
	Name = "Dealer";
	CardsXY = {103, 6};
	TotalXY = {65, 16};
	PromptXY = {65, 18};
}

/**
 * \brief Determines what the next action of the dealer.
 * \return The GameAction which is the next action of the dealer.
 */
GameAction Dealer::NextAction() const
{
	if (FirstHand.Cards.size() == 2 && FirstHand.Cards.back().IsHidden)
		return GameAction::Reveal;

	return FirstHand.CountTotal() >= 17
		? GameAction::Stand
		: GameAction::Hit;
}
