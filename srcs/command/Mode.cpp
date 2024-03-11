#include "Mode.hpp"

Mode::Mode( std::string command, std::string param, int socket ){
	(void)command;
	(void)socket;
	(void)param;
}

Mode::Mode( Mode const &obj){
	if (this != &obj)
		*this = obj;
}

Mode &Mode::operator= ( Mode const &obj){
	(void)obj;
	return (*this);
}

Mode::~Mode( void ){
}

std::ostream &operator << (std::ostream &out, const Mode &obj){
	out << "Mode";
	(void)obj;
	return (out);
}
