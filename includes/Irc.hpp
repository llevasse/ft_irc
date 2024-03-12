#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <sstream>
# include "User.hpp"
# include <vector>

class Irc{
	protected:
		std::vector<User *> _users;

		std::string	_pw;
		int			_port;

		bool		check_pw(const std::string &pw);
		std::string	trim(const std::string str);
	public:
		Irc(const std::string &port, const std::string &pw);
		Irc();
		~Irc( void );

		void createUser(int socket);
		User* getUserBySocket(int socket);
		User* getUserByIndex(unsigned long index);
		unsigned long getNbUsers();
};

std::ostream &operator << (std::ostream &out, const Irc &obj);
#endif
