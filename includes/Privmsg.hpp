#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Privmsg{
	public:
		Privmsg( std::string command, std::string param, int socket );
		Privmsg( Privmsg const &obj );
		Privmsg &operator= ( Privmsg const &obj );
		~Privmsg( void );
};

std::ostream &operator << (std::ostream &out, const Privmsg &obj);
#endif
