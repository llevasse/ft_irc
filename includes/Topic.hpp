#ifndef TOPIC_HPP
# define TOPIC_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class Topic{
	public:
		Topic( std::string command, std::string param, int socket );
		Topic( Topic const &obj );
		Topic &operator= ( Topic const &obj );
		~Topic( void );
};

std::ostream &operator << (std::ostream &out, const Topic &obj);
#endif
