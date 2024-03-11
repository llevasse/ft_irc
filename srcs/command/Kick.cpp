#include "Kick.hpp"

Kick::Kick( std::string command, std::string param, int socket ){
	(void)command;
	(void)socket;
	(void)param;
}

Kick::Kick( Kick const &obj){
	if (this != &obj)
		*this = obj;
}

Kick &Kick::operator= ( Kick const &obj){
	(void)obj;
	return (*this);
}

Kick::~Kick( void ){
}

std::ostream &operator << (std::ostream &out, const Kick &obj){
	out << "Kick";
	(void)obj;
	return (out);
}
