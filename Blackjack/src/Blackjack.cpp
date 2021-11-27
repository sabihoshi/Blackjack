// ReSharper disable CppClangTidyReadabilityStaticAccessedThroughInstance
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidGoto
// ReSharper disable CppClangTidyClangDiagnosticSwitchEnum
#include <iostream>
#include <Windows.h>

#include "Dealer.h"
#include "Table.h"

GameAction Action(Player& player, Dealer& dealer, GameAction action = GameAction::None)
{
	while (true)
	{
		if (action == GameAction::None)
			action = player.PromptAction("Do you want to [H]it, [S]tand");

		switch (action)
		{
			case GameAction::Hit:
			{
				dealer.Hit(player);
				break;
			}
			case GameAction::Stand:
			{
				player.Stand();
				break;
			}
			case GameAction::Reveal:
			{
				dealer.Reveal();
				break;
			}
			default: continue;
		}

		return action;
	}
}

int main()
{
	// SetConsoleTitleA(L"Blackjack Game");

	// https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
	SetConsoleOutputCP(65001);

	// https://docs.microsoft.com/en-us/windows/console/setconsolemode
	SetConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	GameAction action = GameAction::None;
	Player player("Player");
	Dealer dealer;

	player.Chips = 10000;
	for (int i = 0; i < 50; ++i)
	{
		dealer.Deck.push_back(Card::Random());
	}

Start:
	player.Cards.clear();
	dealer.Cards.clear();

	Clear();
	PrintTable();

	player.UpdateState();
	dealer.UpdateState();

	player.PromptBet();

	dealer.Hit();
	dealer.Hit(player);
	dealer.Hit(true);
	dealer.Hit(player);

	while (true)
	{
		do
		{
			switch (player.State)
			{
				case PlayerState::Normal:
				{
					action = Action(player, dealer);
					break;
				}

				case PlayerState::Blackjack:
				{
					goto DealerTurn;
				}

				case PlayerState::Bust:
				{
					if (PlayAgainPrompt("BUSTED! Game over."))
						goto Start;

					goto End;
				}

				default: break;
			}
		}
		while (action != GameAction::Stand);

	DealerTurn:
		do
		{
			switch (dealer.State)
			{
				case PlayerState::Normal:
				{
					if (dealer.CardTotal > player.CardTotal)
					{
						if (PlayAgainPrompt("You lost."))
							goto Start;
					}

					action = Action(dealer, dealer, dealer.NextAction());
					break;
				}

				case PlayerState::Blackjack:
				{
					if (player.State != PlayerState::Blackjack)
					{
						if (PlayAgainPrompt("You lost."))
							goto Start;
					}
					else
					{
						if (PlayAgainPrompt("Tie. No one wins."))
						{
							player.Chips += player.Bet;
							goto Start;
						}
					}
					break;
				}

				case PlayerState::Bust:
				{
					if (PlayAgainPrompt("DEALER BUSTED! You won."))
					{
						player.Chips += player.Bet * 2;
						goto Start;
					}

					return 0;
				}

				default: break;
			}
		}
		while (action != GameAction::Stand);
	}

End:
	Pause();
}
