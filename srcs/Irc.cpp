#include "Irc.hpp"

Irc::Irc( void ){
	if (!MUTE)
		std::cout << "Irc default \033[32mconstructor\033[0m called!" << std::endl;
}

Irc::Irc( Irc const &obj){
	if (!MUTE)
		std::cout << "Irc copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Irc &Irc::operator= ( Irc const &obj){
	if (!MUTE)
		std::cout << "Irc copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
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
