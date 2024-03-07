#include "Request.hpp"

Request::Request( void ){
}

Request::Request( Request const &obj){
	if (this != &obj)
		*this = obj;
}

Request &Request::operator= ( Request const &obj){
	(void)obj;
	return (*this);
}

Request::~Request( void ){
}

std::ostream &operator << (std::ostream &out, const Request &obj){
	out << "Request";
	(void)obj;
	return (out);
}
