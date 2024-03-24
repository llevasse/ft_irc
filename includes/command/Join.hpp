#ifndef JOIN_HPP
# define JOIN_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Join{
	public:
		Join( std::string command, std::string param, int socket );
		Join( Join const &obj );
		Join &operator= ( Join const &obj );
		~Join( void );
};

std::ostream &operator << (std::ostream &out, const Join &obj);
#endif
