#include "Message.hpp"


// typical USER command example
//
// USER guest 0 * : realname 


void Message::user(){

	std::string	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 461 " + _client->getNickname() +  " :Not enough _parameters\r\n";

	size_t 		nameDel = _param.find(" ");
	size_t		modeDel = _param.find(" ", nameDel + 1);
	size_t		unusedDel = _param.find(" ", modeDel + 1);
	size_t		realnameDel = _param.find(":");
	std::string _name = _param.substr(0, nameDel);
	std::string _mode = _param.substr(nameDel + 1, modeDel - nameDel - 1);
	std::string _unused = _param.substr(modeDel + 1, unusedDel - modeDel - 1);
	if ((_name.length() == 1 && isdigit(_name[0])) || (_mode.length() > 1 || !isdigit(_mode[0])) || (_unused[0] == ':')){
		_client->sendData(reply);
		return ;
	}
	if (nameDel == std::string::npos || modeDel == std::string::npos || unusedDel == std::string::npos || realnameDel == std::string::npos){
		_client->sendData(reply);
		return ;
	}
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit) && *rit != ':')
			break ;
		else if (*rit == ':'){
			_client->sendData(reply);
			return;
		}
	}
	//check for correct password
	if (_server->getPassword() != _client->getPass()){
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 464 " + _client->getNickname() +  " :Password Incorrect\r\n";
		_client->sendData(reply);
		return ;
	}
	//check if user is already registered
	if (_client->getUsername() != ""){
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 462 " + _client->getNickname() +  " :You may not register\r\n";
		_client->sendData(reply);
		return ;
	}

	//check if username is already taken
	for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
		if (it->second->getUsername() == _name){
			reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 462 " + _client->getNickname() +  " :Username already in use\r\n";
			_client->sendData(reply);
		}
	}
	//set username
	_client->setUsername(_name);
}
