#pragma execution_character_set("utf-8")

#include "MainMenu.h"

#include <conio.h>
#include <fstream>

#include "Table.h"
#include "lib/json.hpp"

/**
 * \brief Creates a MainMenu object.
 */
MainMenu::MainMenu()
{
	Clear();
	std::ifstream file(LOGIN_PATH);
	nlohmann::json j;
	file >> j;

	Users = j.get<std::vector<User>>();
}

/**
 * \brief Saves the data to the json file.
 */
void MainMenu::Save()
{
	std::ofstream file(LOGIN_PATH);
	const nlohmann::json j = Users;
	file << j;
}

/**
 * \brief Checks if a user of the same name exists.
 * \param username The username of the user.
 * \return
 */
bool MainMenu::UserExists(const std::string& username) const
{
	return std::any_of(Users.begin(), Users.end(), [&](const User& user)
	{
		return user.Username == username;
	});
}

/**
 * \brief Gets a specific user with the specified username.
 * \param username The username of the user.
 * \return A User that matches the username.
 */
User& MainMenu::GetUser(const std::string& username)
{
	for (auto& user : Users)
	{
		if (user.Username == username)
			return user;
	}
}

/**
 * \brief Prints a square border.
 * \param position The starting coordinates of the border.
 * \param width The width of the border.
 * \param height The height of the border.
 */
void MainMenu::PrintBorders(const COORD position, const int width, const int height) const
{
	XY(position);
	const int widthRepeats = width - 2;
	WriteLine("╔" + Repeat("═", widthRepeats) + "╗");
	for (int i = 0; i < height - 2; ++i)
	{
		WriteLine("║" + Repeat(" ", widthRepeats) + "║");
	}
	WriteLine("╚" + Repeat("═", widthRepeats) + "╝");
}

/**
 * \brief Registers a user.
 * \return The user that registered.
 */
User& MainMenu::Register()
{
	PrintTitle();
	XY(INPUT_TITLE_XY);

	WriteLine(Center("ENTER A NAME, USERNAME, AND PASSWORD", INPUT_WIDTH));

	XY(INPUT_XY);
	std::string name = Prompt("Name: ");
	std::string username = Prompt("Username: ");
	std::string password = Prompt("Password: ");

	auto user = User(name, username, password);
	Users.push_back(user);
	Save();

	return user;
}

/**
 * \brief Logs in a user.
 * \return The user that logged in.
 */
User& MainMenu::Login()
{
	while (true)
	{
		PrintTitle();
		XY(INPUT_TITLE_XY);

		WriteLine(Center("LOG INTO AN EXISTING ACCOUNT", INPUT_WIDTH));

		XY(INPUT_XY);
		const std::string username = Prompt("Username: ");
		const std::string password = Prompt("Password: ");

		if (!UserExists(username))
			continue;

		auto& compare = GetUser(username);
		if (password == compare.Password)
			return compare;
	}
}

/**
 * \brief Prompts the user.
 * \param prompt The prompt that will be used.
 * \return The input of the user.
 */
std::string MainMenu::Prompt(const std::string& prompt) const
{
	const auto xy = XY();
	XY(INPUT_TITLE_XY.X, xy.Y);
	std::cout << Repeat(" ", INPUT_WIDTH);

	XY(xy);
	std::cout << prompt;

	const auto inputXY = XY();
	constexpr short end = INPUT_TITLE_XY.X + INPUT_WIDTH - 4;
	const short repeat = end - inputXY.X;

	SwapColors();
	std::cout << Repeat(" ", repeat);
	const short promptX = static_cast<short>(inputXY.X + 1);
	XY(promptX, inputXY.Y);

	std::string input;
	std::cin >> input;
	ResetColor();

	XY(xy);
	MoveCursor(CursorDirection::Down);

	return input;
}

/**
 * \brief Exits the program.
 */
void MainMenu::Exit()
{
	exit(0); // NOLINT(concurrency-mt-unsafe)
}

/**
 * \brief Starts the main menu.
 * \return A user that logged in.
 */
User& MainMenu::Start()
{
	PrintTitle();

	XY(INPUT_TITLE_XY);
	WriteLine(Center("MAIN MENU", INPUT_WIDTH));

	XY(52, 15);
	WriteLine("[1] - Register");
	WriteLine("[2] - Login");
	WriteLine("[3] - Exit");

	while (true)
	{
		const char c = _getch();
		switch (c)
		{
			case '1':
				return Register();
			case '2':
				return Login();
			case '3':
				Exit();
				break;
		}
	}
}

/**
 * \brief Prints the title screen.
 */
void MainMenu::PrintTitle() const
{
	ResetColor();
	system("cls");

	constexpr int width = 82;
	PrintBorders({20, 4}, width, 20);
	PrintBorders({36, 13}, 48, 6);

	XY(26, 6);
	Color b = {11, 117, 60};
	Color j = {128, 3, 3};
	WriteLine(ChangeColor("██████╗ ██╗      █████╗  ██████╗██╗  ██╗", b) + ChangeColor("     ██╗ █████╗  ██████╗██╗  ██╗", j));
	WriteLine(ChangeColor("██╔══██╗██║     ██╔══██╗██╔════╝██║ ██╔╝", b) + ChangeColor("     ██║██╔══██╗██╔════╝██║ ██╔╝", j));
	WriteLine(ChangeColor("██████╔╝██║     ███████║██║     █████╔╝ ", b) + ChangeColor("     ██║███████║██║     █████╔╝ ", j));
	WriteLine(ChangeColor("██╔══██╗██║     ██╔══██║██║     ██╔═██╗ ", b) + ChangeColor("██   ██║██╔══██║██║     ██╔═██╗ ", j));
	WriteLine(ChangeColor("██████╔╝███████╗██║  ██║╚██████╗██║  ██╗", b) + ChangeColor("╚█████╔╝██║  ██║╚██████╗██║  ██╗", j));
	WriteLine(ChangeColor("╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝", b) + ChangeColor(" ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝", j));
	ResetColor();
}
