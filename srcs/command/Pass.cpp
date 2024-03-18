#include "Pass.hpp"

Pass::Pass( Server *server, Client *client, std::string param){
	std::string	pass = param.substr(0, param.find_first_of(" \n\r\t"));
	(void)server;
	client->setPass(pass);
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
