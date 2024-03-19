#ifndef KICK_HPP
# define KICK_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Kick{
	public:
		Kick( std::string command, std::string param, int socket );
		Kick( Kick const &obj );
		Kick &operator= ( Kick const &obj );
		~Kick( void );
};

std::ostream &operator << (std::ostream &out, const Kick &obj);
#endif