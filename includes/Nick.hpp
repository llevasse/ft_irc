#ifndef NICK_HPP
# define NICK_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

# include "Irc.hpp"

class Nick{
	public:
		Nick( Irc *server, std::string command, std::string param, int socket );
		Nick( Nick const &obj );
		Nick &operator= ( Nick const &obj );
		~Nick( void );
};

std::ostream &operator << (std::ostream &out, const Nick &obj);
#endif
