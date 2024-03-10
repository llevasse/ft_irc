#include "Privmsg.hpp"

Privmsg::Privmsg( void ){
	if (!MUTE)
		std::cout << "Privmsg default \033[32mconstructor\033[0m called!" << std::endl;
}

Privmsg::Privmsg( Privmsg const &obj){
	if (!MUTE)
		std::cout << "Privmsg copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Privmsg &Privmsg::operator= ( Privmsg const &obj){
	if (!MUTE)
		std::cout << "Privmsg copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Privmsg::~Privmsg( void ){
	if (!MUTE)
		std::cout << "Privmsg \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Privmsg &obj){
	out << "Privmsg";
	(void)obj;
	return (out);
}
