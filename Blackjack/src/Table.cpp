#pragma execution_character_set("utf-8")

#include "Table.h"
#include <iostream>
#include <string>
#include "Console.h"
#include "Player.h"

void PrintTable(int width, int height)
{
	Clear();
	std::cout << "                    ╩══════════════════════╦                                ╦══════════════════════╩                    " << std::endl;
	std::cout << "╳══════════════════════════════════════════╩╗        Welcome to the        ╔╩══════════════════════════════════════════╳" << std::endl;
	std::cout << "║                                           ╚╗      Blackjack Casino      ╔╝                                           ║" << std::endl;
	std::cout << "║   Your cards                                ╚═╗                      ╔═╝                            Dealer's cards   ║" << std::endl;
	std::cout << "║                                                ╚════════╦  ╦════════╝                                                ║" << std::endl;
	for (int i = 0; i < 18; i++)
	{
		std::cout << "║" << Repeat(" ", 57) << "║  ║" << Repeat(" ", 57) << "║" << std::endl;
	}
	std::cout << "╳═════════════════════════════════════════════════════════╩  ╩═════════════════════════════════════════════════════════╳" << std::endl;
	std::cout << "                              ╔════════════════════════════════════════════════════════════╗                            " << std::endl;
	std::cout << "                              ║                                                            ║                            " << std::endl;
	std::cout << "                              ║                                                            ║                            " << std::endl;
	std::cout << "                              ╚════════════════════════════════════════════════════════════╝                            " << std::endl;
	XY(4, 17);
	std::cout << Repeat("╌", 51);
	XY(65, 17);
	std::cout << Repeat("╌", 51);
}

void PrintTotal(Player& player)
{
	XY(player.TotalXY);
	std::cout << player.Name << "'s total is " << player.CardTotal;
}

bool PlayAgainPrompt(const std::string& message)
{
	XY(31, 25);
	WriteLine(Center(message, 60));
	while (true)
	{
		const auto prompt = PromptStatus<char>("Do you want to play again, [Y]es or [N]o? ~>");
		switch (prompt)
		{
			case 'y':
			case 'Y':
				return true;
			case 'n':
			case 'N':
				return false;
			default: break;
		}
	}
}
