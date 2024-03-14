#ifndef USERCMD_HPP
# define USERCMD_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

# include "Message.hpp"

class Server;
class Client;

class UserCmd{
	public:
		UserCmd( Server *server, Client *client, std::string param);
		UserCmd( UserCmd const &obj );
		UserCmd &operator= ( UserCmd const &obj );
		~UserCmd( void );
};

std::ostream &operator << (std::ostream &out, const UserCmd &obj);
#endif
