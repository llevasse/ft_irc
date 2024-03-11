#include "UserCmd.hpp"

UserCmd::UserCmd( std::string command, std::string param, int socket ){
	(void)command;
	(void)param;
}

UserCmd::UserCmd( UserCmd const &obj){
	if (this != &obj)
		*this = obj;
}

UserCmd &UserCmd::operator= ( UserCmd const &obj){
	(void)obj;
	return (*this);
}

UserCmd::~UserCmd( void ){
}

std::ostream &operator << (std::ostream &out, const UserCmd &obj){
	out << "UserCmd";
	(void)obj;
	return (out);
}
