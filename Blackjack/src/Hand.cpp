#include "Hand.h"

/**
 * \brief Adds a card to the hand.
 * \param card The Card to add.
 */
void Hand::AddCard(const Card card)
{
	Cards.push_back(card);
	const int total = CountTotal();

	if (total == 21) State = HandState::Blackjack;
	else if (total > 21) State = HandState::Bust;
}

/**
 * \brief Reveals the last card if it's hidden.
 */
void Hand::Reveal()
{
	if (Cards.empty())
		return;

	auto& card = Cards.back();
	card.IsHidden = false;
}

/**
 * \brief Determines if the last card is hidden or not.
 * \return True if the card is hidden, False if not.
 */
bool Hand::IsHidden() const
{
	if (Cards.size() < 2)
		return false;

	auto& card = Cards.back();
	return card.IsHidden;
}

/**
 * \brief Resets the state of the hand.
 */
void Hand::Reset()
{
	State = HandState::Normal;
	SinglePull = false;
	Cards.clear();
	Bet = 0;
}

/**
 * \brief Determines if the hand can double.
 * \return True if the hand can double, False if not.
 */
bool Hand::CanDouble() const
{
	const int total = CountTotal();
	return Cards.size() == 2
		&& total >= 9
		&& total <= 11;
}

/**
 * \brief Counts the total of the hand.
 * \return An int containing the total value of the hand.
 */
int Hand::CountTotal() const
{
	int total = 0;
	bool hasAce = false;
	for (const auto& card : Cards)
	{
		if (!card.IsHidden)
		{
			total += card.Value;

			if (card.Rank == CardRank::Ace)
				hasAce = true;
		}
	}

	if (!hasAce)
		return total;

	return total + 10 > 21 ? total : total + 10;
}
