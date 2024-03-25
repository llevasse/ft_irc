#include "Bot.hpp"

Bot::Bot(const std::string &adress, const std::string &port, const std::string &password): prefix('!')
{
	long	portInt = std::strtol(port.c_str(), NULL, 10);

	if (portInt < 1024 || portInt > std::numeric_limits<unsigned short>::max())
		throw Bot::BadPort();

	if (password.size() > 32)
		throw Bot::PasswordTooLong();

	for (std::string::const_iterator it = password.begin(); it != password.end(); it++)
	{
		if (!std::isprint(*it))
			throw Bot::BadPassword();
	}

	this->_pass = password;

	this->_addr.sin_port = htons(portInt);
	this->_addr.sin_family = PF_INET;
	this->_addr.sin_addr.s_addr = inet_addr(adress.c_str());

	signal(SIGINT, this->stop);
}

void	Bot::connection()
{
	this->_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (this->_fd == -1)
	{
		std::cerr << "Failed to create socket" << std::endl;
		exit(1);
	}

	if (connect(this->_fd, reinterpret_cast<sockaddr *>(&this->_addr), sizeof(this->_addr)) == -1)
	{
		std::cerr << "Failed to connect" << std::endl;
		exit(1);
	}
}

void	Bot::loop(void)
{
	while (this->_loop)
	{
		std::string cmd = this->receiveData();
		if (cmd.size() > 0 && cmd.at(0) == prefix)
			this->executeCommand(cmd);
		sendData(cmd);
	}
}

Bot::~Bot(void)
{
}

void	Bot::stop( int signal )
{
	static_cast<void>(signal);

	Bot::_loop = false;

	std::cout << std::endl << "Bot stopped" << std::endl;
}

void	Bot::executeCommand(std::string command)
{
	if (command[0] == prefix)
	{
		command.erase(0, 1);
		if (command == "ping")
			//ping();
			std::cout << "Pong" << std::endl;
		else
			std::cout << "Command not found" << std::endl;
	}
	else
		std::cout << "Not a command" << std::endl;
}

const char	*Bot::BadPort::what() const throw()
{
	return ("invalid port");
}

const char	*Bot::BadPassword::what() const throw()
{
	return ("invalid password");
}

const char	*Bot::PasswordTooLong::what() const throw()
{
	return ("Password too long");
}

bool	Bot::_loop = true;
