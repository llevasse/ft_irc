#include "User.hpp"


// typical USER command example
//
// USER guest 0 * : realname 


//TODO handle not enough argument error

User::User( Server *server, Client *client, std::string param){
	int socket = client->getFd();
	size_t nameDel = param.find(" ");
	size_t	modeDel = param.find(" ", nameDel + 1);
	size_t	unusedDel = param.find(" ", modeDel + 1);
	std::string	reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 461 " + client->getNickname() +  " :Not enough parameters\r\n";
	if (nameDel == std::string::npos || modeDel == std::string::npos || unusedDel == std::string::npos){
		client->sendData(reply);
		return ;
	}
	unusedDel = 0;
	for (std::string::reverse_iterator rit=param.rbegin(); rit!=param.rend(); rit++){
		if (!isspace(*rit) && *rit != ':')
			break ;
		else if (*rit == ':'){
			client->sendData(reply);
			return ;
		}
	}
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
	std::string	name = param.substr(0, nameDel);
	std::cout << "(" << socket << ") :USER " << param << std::endl;
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getUsername() == name){
			reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 462 " + client->getNickname() +  " :Username already in use\r\n";
			client->sendData(reply);
		}
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
