#include "Message.hpp"

void Message::join(){
	std::map<std::string, Channel *>	channels;
	std::map<std::string, Client * >	clients;
	std::string reply;

	std::string name = _param.substr(0, _param.find(" "));

	channels = _server->getChannels();
	if (channels.find(name) == channels.end()){
		channels[name] = new Channel(name);
		clients = channels[name]->getClientMap();
		clients[_client->getUsername()] = _client;
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost JOIN " + name;
		_client->sendData(reply);
		reply = ":localhost 353 " + _client->getNickname() + " = " + name + " :@" + _client->getNickname();
		_client->sendData(reply);
		reply = ":localhost 366 " + _client->getNickname() + " " + name + " :End of /NAMES list.";
		_client->sendData(reply);
	}
}
