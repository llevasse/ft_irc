#include "Message.hpp"

void Message::join(){
	std::map<std::string, Channel *>	channels;
	std::map<std::string, Client * >	clients;
	std::string reply;

	std::string name = _param.substr(0, _param.find(" "));

	channels = _server->getChannels();
	if (channels.find(name) == channels.end()){
		_server->newChannel(name);
		channels = _server->getChannels();
		channels[name]->addClient(_client);
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost JOIN " + name;
		_client->sendData(reply);
		reply = ":localhost 353 " + _client->getNickname() + " = " + name + " :@" + _client->getNickname();
		_client->sendData(reply);
		reply = ":localhost 366 " + _client->getNickname() + " " + name + " :End of /NAMES list.";
		_client->sendData(reply);
	}
	else{
		channels[name]->addClient(_client);
		reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost JOIN " + name;
		_client->sendData(reply);
		for (std::map< std::string, Client * >::const_iterator it = clients.begin(); it != clients.end(); it++){
			reply = ":localhost 353 " + it->second->getNickname() + " = " + name + " :@" + it->second->getNickname();
			_client->sendData(reply);
		}
		reply = ":localhost 366 " + _client->getNickname() + " " + name + " :End of /NAMES list.";
		_client->sendData(reply);
	}
	std::cout << *channels[name] << std::endl;
//	std::cout << *_server << std::endl;
}
