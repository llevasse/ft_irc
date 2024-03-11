#include "Invite.hpp"

Invite::Invite( std::string command, std::string param, int socket ){
	(void)command;
	(void)socket;
	(void)param;
}

Invite::Invite( Invite const &obj){
	if (this != &obj)
		*this = obj;
}

Invite &Invite::operator= ( Invite const &obj){
	(void)obj;
	return (*this);
}

Invite::~Invite( void ){
}

std::ostream &operator << (std::ostream &out, const Invite &obj){
	out << "Invite";
	(void)obj;
	return (out);
}
