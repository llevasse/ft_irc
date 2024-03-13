#include "Reply.hpp"

Reply::Reply( const std::string raw ){
	}
}

Reply::Reply( Reply const &obj){
	if (this != &obj)
		*this = obj;
}

Reply &Reply::operator= ( Reply const &obj){
	(void)obj;
	return (*this);
}

Reply::~Reply( void ){
}

std::ostream &operator << (std::ostream &out, const Reply &obj){
	(void)obj;
	return (out);
}
