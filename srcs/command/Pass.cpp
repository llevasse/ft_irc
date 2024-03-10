#include "Pass.hpp"

Pass::Pass( void ){
	if (!MUTE)
		std::cout << "Pass default \033[32mconstructor\033[0m called!" << std::endl;
}

Pass::Pass( Pass const &obj){
	if (!MUTE)
		std::cout << "Pass copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Pass &Pass::operator= ( Pass const &obj){
	if (!MUTE)
		std::cout << "Pass copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Pass::~Pass( void ){
	if (!MUTE)
		std::cout << "Pass \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Pass &obj){
	out << "Pass";
	(void)obj;
	return (out);
}
