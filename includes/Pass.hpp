#ifndef PASS_HPP
# define PASS_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif
# include "Server.hpp"
# include "Client.hpp"

class Server;
class Client;

class Pass{
	public:
		Pass( Server *server, Client *client, std::string param);
		Pass( Pass const &obj );
		Pass &operator= ( Pass const &obj );
		~Pass( void );
};

std::ostream &operator << (std::ostream &out, const Pass &obj);
#endif
