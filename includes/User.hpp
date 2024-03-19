#ifndef USERCMD_HPP
# define USERCMD_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

# include "Message.hpp"

class Server;
class Client;

class User{
	private:
		std::string _name;
		std::string _mode;
		std::string _unused;
		std::string _realname;
	public:
		User( Server *server, Client *client, std::string param);
		User( User const &obj );
		User &operator= ( User const &obj );
		~User( void );
		int split(Client *client, std::string param);
};

std::ostream &operator << (std::ostream &out, const User &obj);
#endif
