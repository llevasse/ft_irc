#include "Kick.hpp"

Kick::Kick( void ){
	if (!MUTE)
		std::cout << "Kick default \033[32mconstructor\033[0m called!" << std::endl;
}

Kick::Kick( Kick const &obj){
	if (!MUTE)
		std::cout << "Kick copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Kick &Kick::operator= ( Kick const &obj){
	if (!MUTE)
		std::cout << "Kick copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Kick::~Kick( void ){
	if (!MUTE)
		std::cout << "Kick \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Kick &obj){
	out << "Kick";
	(void)obj;
	return (out);
}
