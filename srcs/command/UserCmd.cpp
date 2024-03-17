#include "UserCmd.hpp"


// typical USER command example
//
// USER guest 0 * : realname 

UserCmd::UserCmd( Server *server, Client *client, std::string param){
	int socket = client->getFd();
	std::string	reply;
	if (server->getCliensMap()[socket]->getUsername() != ""){
		reply = "" 
		client->sendData(reply);
	}
	std::string	name = param.substr(0, param.find_first_of(" \n\r\t"));
	std::cout << "(" << socket << ") :USER " << param << std::endl;
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getUsername() == name || it->second->getNickname() == name)
			throw (std::runtime_error("Username already in use"));
	}
	server->getClientsMap()[socket]->setUsername(name);
	server->getClientsMap()[socket]->setNickname(name);
}

UserCmd::UserCmd( UserCmd const &obj){
	if (this != &obj)
		*this = obj;
}

UserCmd &UserCmd::operator= ( UserCmd const &obj){
	(void)obj;
	return (*this);
}

UserCmd::~UserCmd( void ){
}

std::ostream &operator << (std::ostream &out, const UserCmd &obj){
	out << "UserCmd";
	(void)obj;
	return (out);
}
