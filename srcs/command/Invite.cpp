#include "Invite.hpp"

Invite::Invite( void ){
	if (!MUTE)
		std::cout << "Invite default \033[32mconstructor\033[0m called!" << std::endl;
}

Invite::Invite( Invite const &obj){
	if (!MUTE)
		std::cout << "Invite copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Invite &Invite::operator= ( Invite const &obj){
	if (!MUTE)
		std::cout << "Invite copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Invite::~Invite( void ){
	if (!MUTE)
		std::cout << "Invite \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Invite &obj){
	out << "Invite";
	(void)obj;
	return (out);
}
