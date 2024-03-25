#pragma once

#include "Client.hpp"

class Bot: public Client
{
	private:
		std::string	_pass;
		const char	prefix;
		static bool	_loop;
		sockaddr_in _addr;

	public:
		Bot(const std::string &adress, const std::string &port, const std::string &password);
		~Bot();

		void	connection(void);
		void	loop(void);
		static void	stop(int signal);

		void	executeCommand(std::string command);

		class BadPort : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class BadPassword : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class PasswordTooLong : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

};
