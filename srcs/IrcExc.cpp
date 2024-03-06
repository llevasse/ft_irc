#include "IrcExc.hpp"

const char *IrcExc::invalidPortException::what() const throw(){
	return ("Invalid port value");
}

const char *IrcExc::reservedPortException::what() const throw(){
	return ("Port is already reserved");
}

const char *IrcExc::invalidPasswordException::what() const throw(){
	return ("Invalid password");
}
