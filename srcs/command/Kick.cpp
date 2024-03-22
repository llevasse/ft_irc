#include "Message.hpp"

void Message::kick(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg == std::string::npos){
			reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 403 " + _client->getNickname() +  " :No such channel.";
		_client->sendData(reply);
		return ;
	}
	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 442 " + _client->getNickname() +  " :Your not on that channel.";
	std::map<std::string, Channel *> channels = _server->getChannels();
	std::map<std::string, Client * >	clients = channels[name]->getClientMap();
//		std::cout << *channels[name] << std::endl;
	if (clients.find(_client->getUsername()) == clients.end()){
		_client->sendData(reply);
		return ;
	}
//	channels[name]->kick(_client, _param.substr(nameDel + 1));
}
