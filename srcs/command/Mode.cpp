#include "Mode.hpp"

Mode::Mode( void ){
	if (!MUTE)
		std::cout << "Mode default \033[32mconstructor\033[0m called!" << std::endl;
}

Mode::Mode( Mode const &obj){
	if (!MUTE)
		std::cout << "Mode copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Mode &Mode::operator= ( Mode const &obj){
	if (!MUTE)
		std::cout << "Mode copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Mode::~Mode( void ){
	if (!MUTE)
		std::cout << "Mode \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Mode &obj){
	out << "Mode";
	(void)obj;
	return (out);
}
