#include "Irc.hpp"

Irc::Irc( const std::string &pw, const int port ) : _pw(pw), _port(port){
	if (!MUTE)
		std::cout << "Irc default \033[32mconstructor\033[0m called!" << std::endl;
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
