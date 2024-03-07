#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>

class Request{
	public:
		Request( void );
		Request( Request const &obj );
		Request &operator= ( Request const &obj );
		~Request( void );
};

std::ostream &operator << (std::ostream &out, const Request &obj);
#endif
