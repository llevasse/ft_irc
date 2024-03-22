#include "Message.hpp"

void Message::mode(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg == std::string::npos){	//user mode
		if (name != _client->getNickname()){
			reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 502 " + _client->getNickname() + " MODE " + name + " :Cant change mode for other users";
			_client->sendData(reply);
			return ;
		}
		for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
			if (it->second->getNickname() == name){
				reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 401 " + _client->getNickname() + " MODE " + name + " :No such nickname";
				_client->sendData(reply);
				return ;
			}
		}
	}
	else{	//channel mode
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 403 " + _client->getNickname() +  " :No such channel.";
		std::map<std::string, Channel *> channels = _server->getChannels();
		if (channels.find(name) == channels.end()){
			_client->sendData(reply);
			return ;
		}
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 442 " + _client->getNickname() +  " :Your not on that channel.";
		std::map<std::string, Client * >	clients = channels[name]->getClientMap();
//		std::cout << *channels[name] << std::endl;
		if (clients.find(_client->getUsername()) == clients.end()){
			_client->sendData(reply);
			return ;
		}
		
		channels[name]->mode(_client, _param.substr(nameDel + 1));
	}
}
