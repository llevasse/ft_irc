#ifndef MODE_HPP
# define MODE_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Mode{
	public:
		Mode( void );
		Mode( Mode const &obj );
		Mode &operator= ( Mode const &obj );
		~Mode( void );
};

std::ostream &operator << (std::ostream &out, const Mode &obj);
#endif
