#ifndef USER_HPP
# define USER_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class User{
	public:
		User( void );
		User( User const &obj );
		User &operator= ( User const &obj );
		~User( void );
};

std::ostream &operator << (std::ostream &out, const User &obj);
#endif
