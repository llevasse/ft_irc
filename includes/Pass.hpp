#ifndef PASS_HPP
# define PASS_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Pass{
	public:
		Pass( std::string command, std::string param, int socket );
		Pass( Pass const &obj );
		Pass &operator= ( Pass const &obj );
		~Pass( void );
};

std::ostream &operator << (std::ostream &out, const Pass &obj);
#endif
