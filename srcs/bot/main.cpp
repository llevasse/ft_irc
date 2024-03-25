#include "Bot.hpp"

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Usage: ./bot [adress] [port] [password]" << std::endl;
		return (1);
	}
	Bot bot(av[1], av[2], av[3]);
	bot.connection();
	bot.loop();
	return (0);
}
