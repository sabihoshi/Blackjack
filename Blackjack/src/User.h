#pragma once
#include <string>

#include "lib/json.hpp"

class User
{
public:
	User() = default;

	User(const std::string& name, const std::string& username, const std::string& password);

	int Chips;
	std::string Name;
	std::string Username;
	std::string Password;
};

// ReSharper disable once CppInconsistentNaming
inline void to_json(nlohmann::json& j, const User& s)
{
	j["name"] = s.Name;
	j["username"] = s.Username;
	j["password"] = s.Password;
	j["chips"] = s.Chips;
}

// ReSharper disable once CppInconsistentNaming
inline void from_json(const nlohmann::json& j, User& s)
{
	j.at("name").get_to(s.Name);
	j.at("username").get_to(s.Username);
	j.at("password").get_to(s.Password);
	j.at("chips").get_to(s.Chips);
}
