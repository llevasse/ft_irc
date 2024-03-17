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
	public:
		User( Server *server, Client *client, std::string param);
		User( User const &obj );
		User &operator= ( User const &obj );
		~User( void );
};

std::ostream &operator << (std::ostream &out, const User &obj);
#endif
