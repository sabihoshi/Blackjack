#include "Console.h"
#include "Game.h"
#include "MainMenu.h"

/**
 * \brief The main program. This is where execution starts.
 * \return The exit code of the program.
 */
int main()
{
	// Setting the title
	SetConsoleTitleA("Blackjack Game by sabihoshi");

	// https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
	SetConsoleOutputCP(65001);

	// https://docs.microsoft.com/en-us/windows/console/setconsolemode
	SetConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	MainMenu menu;
	while (true)
	{
		User& user = menu.Start();
		Game game(user);

		// Game Loop
		bool replay;
		do
		{
			replay = game.Play();
			user.Chips = game.Player.Chips;
			menu.Save();
		}
		while (replay);
	}
}
