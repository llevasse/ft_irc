#include "Topic.hpp"

Topic::Topic( std::string command, std::string param, int socket ){
	(void)command;
	(void)socket;
	(void)param;
}

Topic::Topic( Topic const &obj){
	if (this != &obj)
		*this = obj;
}

Topic &Topic::operator= ( Topic const &obj){
	(void)obj;
	return (*this);
}

Topic::~Topic( void ){
}

std::ostream &operator << (std::ostream &out, const Topic &obj){
	out << "Topic";
	(void)obj;
	return (out);
}