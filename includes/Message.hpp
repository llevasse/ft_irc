#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

class Message{
	private:
		const std::string _command;
		const std::string _param;
	public:
		Message( const std::string message );
		Message( Message const &obj );
		Message &operator= ( Message const &obj );
		~Message( void );
};

std::ostream &operator << (std::ostream &out, const Message &obj);
#endif
