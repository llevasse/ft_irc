#include "Request.hpp"

Request::Request( const std::string raw ){
	_raw = raw;

	if (_raw[0] == ':'){
		_nickname = _raw.substr(1, _raw.find("!") - 1);
		std::cout << _nickname << std::endl;
	}
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
