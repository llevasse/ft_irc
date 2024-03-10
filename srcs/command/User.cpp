#include "User.hpp"

User::User( void ){
	if (!MUTE)
		std::cout << "User default \033[32mconstructor\033[0m called!" << std::endl;
}

User::User( User const &obj){
	if (!MUTE)
		std::cout << "User copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

User &User::operator= ( User const &obj){
	if (!MUTE)
		std::cout << "User copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

User::~User( void ){
	if (!MUTE)
		std::cout << "User \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const User &obj){
	out << "User";
	(void)obj;
	return (out);
}
