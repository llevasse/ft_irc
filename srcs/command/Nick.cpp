#include "Message.hpp"

void Message::nick(){
	size_t del	= _param.find_first_of(" \r\n");
	bool found	= 0;

	std::string	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 461 " + _client->getNickname() +  " :Not enough _parameters\r\n";
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == _param.rend()){
			_client->sendData(reply);
			return ;
		}
	}
	if (!found){
		_client->sendData(reply);
		return ;
	}
	std::string	name = _param.substr(0, del);
	//check if nickname is already in use
	for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
		if (it->second->getNickname() == name){
			reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 432 " + _client->getNickname() + " " + name + " :Nickname already in use\r\n";
			_client->sendData(reply);
			return ;
		}
	}
	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost NICK " + name + "\r\n";
	_client->setNickname(name);
	if (_client->getUsername() != ""){
		_client->sendData(reply);
	}
}
