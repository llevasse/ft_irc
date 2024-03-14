#ifndef NICK_HPP
# define NICK_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

# include "Message.hpp"

class Server;
class Client;

class Nick{
	public:
		Nick( Server *server, Client *client, std::string param);
		Nick( Nick const &obj );
		Nick &operator= ( Nick const &obj );
		~Nick( void );
};

std::ostream &operator << (std::ostream &out, const Nick &obj);
#endif
