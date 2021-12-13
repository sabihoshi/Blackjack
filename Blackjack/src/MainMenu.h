#pragma once
#include <string>
#include <vector>

#include "Console.h"
#include "User.h"

const std::string LOGIN_PATH = "logins.json";
constexpr COORD INPUT_TITLE_XY = {37, 14};
constexpr COORD INPUT_XY = {41, 15};
constexpr int INPUT_WIDTH = 46;

class MainMenu
{
public:
	MainMenu();

	void Save();

	std::vector<User> Users;

	bool UserExists(const std::string& username) const;

	User& GetUser(const std::string& username);

	void PrintBorders(COORD position, int width, int height) const;

	User& Register();

	User& Login();

	std::string Prompt(const std::string& prompt) const;

	static void Exit();

	User& Start();

	void PrintTitle() const;
};
