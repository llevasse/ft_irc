#pragma once

#include <iostream>
#include <string>

class Bot
{
	private:
		char	prefix = '!';
		void	ping();
		// Specification of the bot
		// Commands
	public:
		Bot();
		~Bot();
		Bot(const Bot &other);
		Bot &operator=(const Bot &other);

		void	executeCommand(std::string command);
};
