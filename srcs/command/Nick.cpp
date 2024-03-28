#include "Message.hpp"

void Message::nick(){
	size_t del	= _param.find(" ");
	bool found	= 0;

	std::string reply;
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == _param.rend())
			return (_client->sendData(getReply(431)));
	}
	if (!found)
		return (_client->sendData(getReply(431)));
	std::string	name = _param.substr(0, del);
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
