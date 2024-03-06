#include "Irc.hpp"


std::string Irc::trim( const std::string str ){
	int	beg=0, end=str.length()-1;
	for (; end > 0 && isspace(str[end]); end--);
	for (; beg < end && isspace(str[beg]); beg++);
	return (str.substr(beg, end+1));
}

Irc::Irc( const std::string &pw, const std::string &port ){
	std::string str;
	if (!MUTE)
		std::cout << "Irc default \033[32mconstructor\033[0m called!" << std::endl;
	std::stringstream ss;
	ss << trim(port);
	ss >> _port;
	if (_port < 0 || _port > 65535)
		throw (invalidPortException());
	if (_port < 1023)
		throw (reservedPortException());
	_pw = pw;
}

Irc::~Irc( void ){
	if (!MUTE)
		std::cout << "Irc \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Irc &obj){
	out << "Irc";
	(void)obj;
	return (out);
}

const char *Irc::invalidPortException::what() const throw(){
	return ("Invalid port value");
}

const char *Irc::reservedPortException::what() const throw(){
	return ("Port is already reserved");
}
