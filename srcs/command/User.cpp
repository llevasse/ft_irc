#include "User.hpp"


// typical USER command example
//
// USER guest 0 * : realname 


//TODO handle not enough argument error

User::User( Server *server, Client *client, std::string param){
	int socket = client->getFd();
	std::string	reply;

	if (this->split(client, param))
		return ;
	//check for correct password
	if (server->getPassword() != client->getPass()){
		reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 464 " + client->getNickname() +  " :Password Incorrect\r\n";
		client->sendData(reply);
		return ;
	}
	//check if user is already registered
	if (client->getUsername() != ""){
		reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 462 " + client->getNickname() +  " :You may not register\r\n";
		client->sendData(reply);
		return ;
	}

	std::cout << "(" << socket << ") :USER " << param << std::endl;
	//check if username is already taken
	for (std::map< int, Client * >::iterator it = server->getClientsMap().begin(); it != server->getClientsMap().end(); it++){
		if (it->second->getUsername() == _name){
			reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 462 " + client->getNickname() +  " :Username already in use\r\n";
			client->sendData(reply);
		}
	}
	//set username
	client->setUsername(_name);
	if (client->getNickname() != ""){
		reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost NICK :" + client->getNickname();
		client->sendData(reply);
	}
}

int	User::split(Client *client, std::string param){
	std::string	reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 461 " + client->getNickname() +  " :Not enough parameters\r\n";

	size_t 	nameDel = param.find(" ");
	size_t	modeDel = param.find(" ", nameDel + 1);
	size_t	unusedDel = param.find(" ", modeDel + 1);
	size_t	realnameDel = param.find(":");
	_name = param.substr(0, nameDel);
	_mode = param.substr(nameDel + 1, modeDel - nameDel - 1);
	_unused = param.substr(modeDel + 1, unusedDel - modeDel - 1);
	if (_name.length() == 1 && isdigit(_name[0]))
		_name = "";
	if (_mode.length() > 1 || !isdigit(_mode[0]))
		_mode = "";
	if (_unused[0] == ':')
		_unused = "";
	if (nameDel == std::string::npos || modeDel == std::string::npos || unusedDel == std::string::npos || realnameDel == std::string::npos || \
		_name == "" || _mode == "" || _unused == ""){
		client->sendData(reply);
		return (1);
	}
	unusedDel = 0;
	for (std::string::reverse_iterator rit=param.rbegin(); rit!=param.rend(); rit++){
		if (!isspace(*rit) && *rit != ':')
			break ;
		else if (*rit == ':'){
			client->sendData(reply);
			return (1);
		}
	}
	return (0);
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
