#include "Join.hpp"

Join::Join( void ){
	if (!MUTE)
		std::cout << "Join default \033[32mconstructor\033[0m called!" << std::endl;
}

Join::Join( Join const &obj){
	if (!MUTE)
		std::cout << "Join copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Join &Join::operator= ( Join const &obj){
	if (!MUTE)
		std::cout << "Join copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Join::~Join( void ){
	if (!MUTE)
		std::cout << "Join \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Join &obj){
	out << "Join";
	(void)obj;
	return (out);
}
