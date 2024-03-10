#ifndef INVITE_HPP
# define INVITE_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Invite{
	public:
		Invite( void );
		Invite( Invite const &obj );
		Invite &operator= ( Invite const &obj );
		~Invite( void );
};

std::ostream &operator << (std::ostream &out, const Invite &obj);
#endif