#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

class Message{
	public:
		Message( const std::string raw );
		Message( Message const &obj );
		Message &operator= ( Message const &obj );
		~Message( void );
};

std::ostream &operator << (std::ostream &out, const Message &obj);
#endif
