#include "Dealer.h"

Card Dealer::Pull(const bool isHidden)
{
	auto card = Deck.front();
	card.IsHidden = isHidden;

	Deck.pop_front();

	return card;
}

Card Dealer::Hit(const bool isHidden)
{
	return Hit(*this, isHidden);
}

Card Dealer::Hit(Player& player, const bool isHidden)
{
	const auto card = Pull(isHidden);
	player.Cards.push_back(card);

	if (card.Symbol == CardSymbol::Ace)
		player.HasAce = true;

	player.UpdateState(GameAction::Hit);

	return card;
}

Dealer::Dealer() : Player(CursorDirection::Left)
{
	Name = "Dealer";
	CardsXY = {103, 6};
	TotalXY = {65, 16};
	PromptXY = {65, 18};
}

GameAction Dealer::NextAction() const
{
	if (Cards[1].IsHidden)
		return GameAction::Reveal;

	if (CardTotal > 17)
		return GameAction::Stand;

	return GameAction::Hit;
}

void Dealer::Reveal()
{
	Cards[1].IsHidden = false;
	UpdateState(GameAction::Reveal);
}
