#include "User.hpp"


// typical USER command example
//
// USER guest 0 * : realname 


//TODO handle not enough argument error

User::User( Server *server, Client *client, std::string param){
	int socket = client->getFd();
	std::string	reply;
	if (server->getPassword() != client->getPass()){
		reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 464 " + client->getNickname() +  " :Password Incorrect\r\n";
		client->sendData(reply);
		return ;
	}
	if (client->getUsername() != ""){
		reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 462 " + client->getNickname() +  " :You may not register\r\n";
		client->sendData(reply);
		return ;
	}
	std::string	name = param.substr(0, param.find_first_of(" \n\r\t"));
	std::cout << "(" << socket << ") :USER " << param << std::endl;
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getUsername() == name || it->second->getNickname() == name)
			throw (std::runtime_error("Username already in use"));
	}
	client->setUsername(name);
	if (client->getNickname() == "")
		client->setNickname(name);
}

User::User( User const &obj){
	if (this != &obj)
		*this = obj;
}

User &User::operator= ( User const &obj){
	(void)obj;
	return (*this);
}

User::~User( void ){
}

std::ostream &operator << (std::ostream &out, const User &obj){
	out << "User";
	(void)obj;
	return (out);
}
