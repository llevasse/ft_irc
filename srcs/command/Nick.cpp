#include "Nick.hpp"

Nick::Nick( Server *server, Client *client, std::string param){
	int socket = client->getFd();
	std::string	name = param.substr(0, param.find_first_of(" \n\r\t"));
	std::string reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost NICK :" + param;
	std::cout << "(" << socket << ") :NICK " << param << std::endl;
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getNickname() == name)
			throw (std::runtime_error("Nickname already in use"));
	}
	std::cout << reply << std::endl;
	server->getClientsMap()[socket]->setNickname(name);
	client->sendData(reply);
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
