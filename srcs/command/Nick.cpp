#include "Message.hpp"

void Message::nick(){
	std::string reply;
	if (_params.size() == 0)
		return (_client->sendData(getReply(431)));
	std::string	name = _params[0];
	//check if nickname is already in use
	if (_server->getClient(name)){
		if (_client->getNickname() != "")
			return (_client->sendData(getReply(433, _client->getNickname() + " " + name)));
		return (_client->sendData(getReply(433, "* " + name)));
	}
	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost NICK :" + name;
	_client->setNickname(name);
	if (_client->getUsername() != ""){
		_client->sendData(reply);
	}
}
