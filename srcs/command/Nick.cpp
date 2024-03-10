#include "Nick.hpp"

Nick::Nick( void ){
	if (!MUTE)
		std::cout << "Nick default \033[32mconstructor\033[0m called!" << std::endl;
}

Nick::Nick( Nick const &obj){
	if (!MUTE)
		std::cout << "Nick copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Nick &Nick::operator= ( Nick const &obj){
	if (!MUTE)
		std::cout << "Nick copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Nick::~Nick( void ){
	if (!MUTE)
		std::cout << "Nick \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Nick &obj){
	out << "Nick";
	(void)obj;
	return (out);
}
