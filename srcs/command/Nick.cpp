#include "Nick.hpp"

Nick::Nick( std::string command, std::string param, int socket ){
	(void)command;
	(void)param;
}

Nick::Nick( Nick const &obj){
	if (this != &obj)
		*this = obj;
}

Nick &Nick::operator= ( Nick const &obj){
	(void)obj;
	return (*this);
}

Nick::~Nick( void ){
}

std::ostream &operator << (std::ostream &out, const Nick &obj){
	out << "Nick";
	(void)obj;
	return (out);
}
