// ReSharper disable CppClangTidyReadabilityStaticAccessedThroughInstance
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidGoto
// ReSharper disable CppClangTidyClangDiagnosticSwitchEnum
#include "Game.h"

#include <sstream>

#include "Dealer.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"

/**
 * \brief Creates a Game object.
 * \param name The name of the player.
 * \param chips The chips of the player.
 */
Game::Game(const std::string& name, const int chips) : Player(name)
{
	Player.Chips = chips;

	Dealer.AddDeck(DECKS);
	Dealer.ShuffleDeck();
}

/**
 * \brief Creates a Game object.
 * \param user The user to use the data of for the game.
 */
Game::Game(const User& user) : Game(user.Name, user.Chips) { }

/**
 * \brief Gets the payout for a split hand.
 * \param hand The hand.
 * \return An int containing the payout.
 */
int Game::GetSplitPayout(const Hand& hand) const
{
	const int total = hand.CountTotal();
	const auto dealerTotal = Dealer.FirstHand.CountTotal();

	if (total > dealerTotal) return hand.Bet * 2;
	if (total == dealerTotal) return hand.Bet;

	return 0;
}

/**
 * \brief Gets the payout for a hand.
 * \param hand The hand.
 * \return An int containing the payout.
 */
int Game::GetPayout(const Hand& hand) const
{
	if (hand.State == HandState::Bust)
		return 0;

	const int total = hand.CountTotal();
	const auto dealerTotal = Dealer.FirstHand.CountTotal();

	if (hand.Cards.size() == 2 && hand.State == HandState::Blackjack)
		return static_cast<int>(hand.Bet * 2.5);

	if (total > dealerTotal) return hand.Bet * 2;
	if (total == dealerTotal) return hand.Bet;

	return 0;
}

/**
 * \brief Starts the game.
 * \return A boolean whether they want to play again or not.
 */
bool Game::Play()
{
	Player.ResetState();
	Dealer.ResetState();

	Clear();
	PrintTable();

	DoAction(GameAction::None, Player);
	DoAction(GameAction::None, Dealer);

	Player.PromptBet();

	DoAction(GameAction::None, Player);
	DoAction(GameAction::None, Dealer);

	DoAction(GameAction::Hit, Dealer);
	DoAction(GameAction::Hit, Player);
	DoAction(GameAction::Hit, Dealer, true);
	DoAction(GameAction::Hit, Player);

PlayerTurn:
	switch (Player.State)
	{
		case PlayerState::Normal:
			PromptAction(Player);
			if (Player.Insured && Dealer.FirstHand.Cards[1].Value == 10)
				goto DealerTurn;

			goto PlayerTurn;

		case PlayerState::Stand:
			DoAction(GameAction::Reveal, Player);
			break;

		case PlayerState::Bust:
			return PlayAgainPrompt("You lost all what you've bet.");
	}

DealerTurn:
	while (true)
	{
		switch (Dealer.State)
		{
			case PlayerState::Normal:
				DoAction(Dealer.NextAction(), Dealer);
				goto DealerTurn;

			case PlayerState::Bust:
			{
				const auto total = Player.FirstHand.Bet + Player.SecondHand.Bet;
				Player.Chips += total * 2;

				return PlayAgainPrompt("Dealer busted!");
			}

			case PlayerState::Stand:
			{
				int total = Player.Split
					? GetSplitPayout(Player.FirstHand) + GetSplitPayout(Player.SecondHand)
					: GetPayout(Player.FirstHand);

				if (Dealer.FirstHand.CountTotal() == 21 && Player.Insured)
					total += Player.Insurance * 2;

				if (total == 0)
					return PlayAgainPrompt("You lost.");

				Player.Chips += total;
				return PlayAgainPrompt("You won a total of " + std::to_string(total) + " chips.");
			}
		}
	}
}

/**
 * \brief Prompts the user for the next action.
 * \param player The player to prompt from.
 */
void Game::PromptAction(class Player& player)
{
	std::string actions = "[S]tand";

	if (player.CanHit)
		actions += " | [H]it";
	if (player.CanDouble)
		actions += " | [D]ouble";
	if (player.CanSplit)
		actions += " | S[p]lit";
	if (player.CanInsurance)
		actions += " | [I]nsurance";

	DoAction(player.PromptAction(actions), player);
}

/**
 * \brief Does a specific action like hitting, splitting, etc.
 * \param action The GameAction to take.
 * \param player The Player that will do the action.
 * \param isHidden In case of hitting, whether the card is hidden or not.
 */
void Game::DoAction(const GameAction action, class Player& player, const bool isHidden)
{
	auto& hand = player.GetCurrentCollection();

	switch (action)
	{
		case GameAction::Hit:
		{
			Hit(player, isHidden);
			break;
		}

		case GameAction::Stand:
		{
			if (player.Split && player.IsFirstHand)
				player.IsFirstHand = false;
			else
				player.State = PlayerState::Stand;

			break;
		}

		case GameAction::Double:
		{
			player.Chips -= hand.Bet;
			hand.Bet += hand.Bet;
			hand.SinglePull = true;

			if (player.Split && player.IsFirstHand)
				player.IsFirstHand = false;

			Hit(player, player.Split);
			break;
		}

		case GameAction::Reveal:
		{
			const bool first = player.FirstHand.IsHidden();
			const bool second = player.SecondHand.IsHidden();

			if (!first && !second)
				return;

			player.FirstHand.Reveal();
			player.SecondHand.Reveal();

			break;
		}

		case GameAction::Split:
		{
			const auto& card = player.FirstHand.Cards.back();
			player.FirstHand.Cards.pop_back();

			player.SecondHand.Cards.push_back(card);
			player.SecondHand.Bet += player.FirstHand.Bet;
			player.Chips -= player.SecondHand.Bet;

			if (player.FirstHand.Cards[0].Rank == CardRank::Ace
				&& player.SecondHand.Cards[0].Rank == CardRank::Ace)
			{
				player.FirstHand.SinglePull = true;
				player.SecondHand.SinglePull = true;

				Hit(player.FirstHand, true);
				Hit(player.SecondHand, true);

				player.State = PlayerState::Stand;
			}

			player.Split = true;
			break;
		}

		case GameAction::Insurance:
		{
			player.PromptInsurance();
			break;
		}

		default: break;
	}

	UpdateState(action, player);
}

/**
 * \brief Updates the state of a user.
 * \param action The GameAction that triggered this update.
 * \param player The Player to update.
 */
void Game::UpdateState(const GameAction action, class Player& player) const
{
	const auto& hand = player.GetCurrentCollection();
	const auto& cards = hand.Cards;

	if (player.FirstHand.State == HandState::Bust && player.SecondHand.State == HandState::Bust)
	{
		player.State = PlayerState::Bust;
	}
	else if (!player.Split && player.FirstHand.State == HandState::Bust)
	{
		player.State = PlayerState::Bust;
	}
	else if (hand.State != HandState::Normal)
	{
		if (player.Split)
		{
			if (player.IsFirstHand)
				player.State = PlayerState::Stand;
			else
				player.IsFirstHand = false;
		}
		else
		{
			player.State = PlayerState::Stand;
		}
	}

	player.CanHit = hand.State == HandState::Normal && !hand.SinglePull;
	player.CanDouble = !player.Insured && hand.CanDouble();
	player.CanSplit = !player.Insured && !player.Split
		&& cards.size() == 2
		&& cards[0].Value == cards[1].Value;
	player.CanInsurance = !player.Insured
		&& Dealer.FirstHand.IsHidden()
		&& Dealer.FirstHand.Cards[0].Rank == CardRank::Ace;

	player.PrintChips();
	player.PrintCards();
	player.PrintAction(action);

	if (action != GameAction::None)
		Pause();
}

/**
 * \brief Hits a user and gives a card.
 * \param player The player to hit.
 * \param isHidden Whether the card is hidden or not.
 */
void Game::Hit(class Player& player, const bool isHidden)
{
	const auto card = Dealer.Pull(isHidden);
	player.GetCurrentCollection().AddCard(card);
}

/**
 * \brief Hits and gives a card to a hand.
 * \param hand The hand.
 * \param isHidden Whether the card is hidden or not.
 */
void Game::Hit(Hand& hand, const bool isHidden)
{
	const auto card = Dealer.Pull(isHidden);
	hand.AddCard(card);
}
