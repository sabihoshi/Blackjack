#include "User.h"

#include "Game.h"

/**
 * \brief Creates a User object.
 * \param name The name of the user.
 * \param username The username of the user.
 * \param password The password of the user.
 */
User::User(const std::string& name, const std::string& username, const std::string& password)
	: Chips(STARTING_CHIPS),
	  Name(name),
	  Username(username),
	  Password(password) { }
