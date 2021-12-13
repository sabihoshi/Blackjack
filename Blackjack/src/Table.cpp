#pragma execution_character_set("utf-8")

#include "Table.h"

#include <conio.h>
#include <iostream>
#include <string>

#include "Console.h"
#include "Player.h"

/**
 * \brief Prints the table to the console.
 */
void PrintTable()
{
	constexpr Color yellow = {242, 187, 36};

	Clear();
	std::cout << "                    ╩══════════════════════╦                                ╦══════════════════════╩                    " << std::endl;
	std::cout << "╳══════════════════════════════════════════╩╗        " << ChangeColor("Welcome to the", yellow) << "        ╔╩══════════════════════════════════════════╳" << std::endl;
	std::cout << "║                                           ╚╗      " << ChangeColor("Blackjack Casino", yellow) << "      ╔╝                                           ║" << std::endl;
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

/**
 * \brief Clears the prompt at the bottom center.
 */
void ClearPrompt()
{
	XY(31, 25);
	WriteLine(Repeat(" ", 60));
	WriteLine(Repeat(" ", 60));
}

/**
 * \brief A template for prompts.
 * \param prompt The prompt.
 * \return A character that the user pressed.
 */
template <>
char Prompt<char>(const std::string& prompt)
{
	XY(31, 26);
	std::cout << Center(prompt, 60);
	return _getch();
}

/**
 * \brief Prompts the user if they want to play again.
 * \param message The message to tell the user.
 * \return True if the user wants to play again, False if not.
 */
bool PlayAgainPrompt(const std::string& message)
{
	ClearPrompt();

	XY(31, 25);
	WriteLine(Center(message, 60));
	while (true)
	{
		const auto prompt = Prompt<char>("Do you want to play again, [Y]es or [N]o? ~>");
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
