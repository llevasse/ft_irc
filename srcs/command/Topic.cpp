#include "Message.hpp"

//either	TOPIC #channel topic
//or		TOPIC #channel

void Message::topic(){
	std::string	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 403 " + _client->getNickname() +  " :No such channel.";
	std::map<std::string, Channel *> channels = _server->getChannels();
	size_t		beg		= _param.find("#");
	if (beg == std::string::npos){
		_client->sendData(reply);
		return ;
	}
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(beg + 1, nameDel - beg);
	if (channels.find(name) == channels.end()){
		_client->sendData(reply);
		return ;
	}
	channels[name]->topic(_client, _param.substr(nameDel + 1));
}
