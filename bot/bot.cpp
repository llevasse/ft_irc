#include "bot.hpp"

Bot::Bot()
{
}

Bot::~Bot()
{
}

Bot::Bot(const Bot &other)
{
	*this = other;
}

Bot &Bot::operator=(const Bot &other)
{
	return *this;
}

void	Bot::executeCommand(std::string command)
{
	if (command[0] == prefix)
	{
		command.erase(0, 1);
		if (command == "ping")
			ping();
		else
			std::cout << "Command not found" << std::endl;
	}
	else
		std::cout << "Not a command" << std::endl;
}

void	Bot::ping()
{
	std::cout << "Pong" << std::endl;
}
