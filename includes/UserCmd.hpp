#ifndef USERCMD_HPP
# define USERCMD_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class UserCmd{
	public:
		UserCmd( std::string command, std::string param );
		UserCmd( UserCmd const &obj );
		UserCmd &operator= ( UserCmd const &obj );
		~UserCmd( void );
};

std::ostream &operator << (std::ostream &out, const UserCmd &obj);
#endif
