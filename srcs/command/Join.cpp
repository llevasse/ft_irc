#include "Join.hpp"

Join::Join( std::string command, std::string param, int socket ){
	(void)command;
	(void)param;
}

Join::Join( Join const &obj){
	if (this != &obj)
		*this = obj;
}

Join &Join::operator= ( Join const &obj){
	(void)obj;
	return (*this);
}

Join::~Join( void ){
}

std::ostream &operator << (std::ostream &out, const Join &obj){
	out << "Join";
	(void)obj;
	return (out);
}
