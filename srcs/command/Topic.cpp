#include "Topic.hpp"

Topic::Topic( void ){
	if (!MUTE)
		std::cout << "Topic default \033[32mconstructor\033[0m called!" << std::endl;
}

Topic::Topic( Topic const &obj){
	if (!MUTE)
		std::cout << "Topic copy \033[32mconstructor\033[0m called!" << std::endl;
	if (this != &obj)
		*this = obj;
}

Topic &Topic::operator= ( Topic const &obj){
	if (!MUTE)
		std::cout << "Topic copy assignment operator called!" << std::endl;
	(void)obj;
	return (*this);
}

Topic::~Topic( void ){
	if (!MUTE)
		std::cout << "Topic \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Topic &obj){
	out << "Topic";
	(void)obj;
	return (out);
}
