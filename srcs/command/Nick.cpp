#include "Nick.hpp"

Nick::Nick( Server *server, std::string command, std::string param, int socket ){
	std::cout << "(" << socket << ") :" << command << " " << param << std::endl;
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getNickname() == param)
			throw (std::runtime_error("Nickname already in use"));
	}
	server->getClientsMap()[socket]->setNickname(param);
}

Nick::Nick( Nick const &obj){
	if (this != &obj)
		*this = obj;
}

Nick &Nick::operator= ( Nick const &obj){
	(void)obj;
	return (*this);
}

Nick::~Nick( void ){
}

std::ostream &operator << (std::ostream &out, const Nick &obj){
	out << "Nick";
	(void)obj;
	return (out);
}
