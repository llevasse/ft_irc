#include "User.hpp"

User::User( int socket ){
	_socket = socket;
}

User::User( User const &obj){
	if (this != &obj)
		*this = obj;
}

User &User::operator= ( User const &obj){
	(void)obj;
	return (*this);
}

int	User::getSocket(){ return _socket;}
std::string User::getNickname(){ return _nickname;}
std::string User::getUsername(){ return _username;}

User::~User( void ){
}

std::ostream &operator << (std::ostream &out, const User &obj){
	out << "User";
	(void)obj;
	return (out);
}
