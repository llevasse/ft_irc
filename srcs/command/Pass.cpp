#include "Pass.hpp"

Pass::Pass( std::string command, std::string param ){
	(void)command;
	(void)param;
}

Pass::Pass( Pass const &obj){
	if (this != &obj)
		*this = obj;
}

Pass &Pass::operator= ( Pass const &obj){
	(void)obj;
	return (*this);
}

Pass::~Pass( void ){
}

std::ostream &operator << (std::ostream &out, const Pass &obj){
	out << "Pass";
	(void)obj;
	return (out);
}
