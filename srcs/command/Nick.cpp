#include "Nick.hpp"

Nick::Nick( Server *server, Client *client, std::string param){
	int socket	= client->getFd();
	size_t del	= param.find_first_of(" \r\n");
	bool found	= 0;
	
	std::cout << "(" << socket << ") :NICK " << param;
	std::string	reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 461 " + client->getNickname() +  " :Not enough parameters\r\n";
	for (std::string::reverse_iterator rit=param.rbegin(); rit!=param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == param.rend()){
			client->sendData(reply);
			return ;
		}
	}
	if (!found){
		client->sendData(reply);
		return ;
	}
	std::string	name = param.substr(0, del);
	reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost NICK :" + param;
	//check if nickname is already in use
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getNickname() == name){
			reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 432 " + client->getNickname() + " " + name + " :Nickname already in use\r\n";
			client->sendData(reply);
			return ;
		}
	}
	client->setNickname(name);
	if (client->getUsername() != ""){
		std::cout << reply << std::endl;
		client->sendData(reply);
	}
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
