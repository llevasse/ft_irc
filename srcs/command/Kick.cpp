#include "Message.hpp"

void Message::kick(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg == std::string::npos)
		return (_client->sendData(getReply(461, "KICK")));
	Channel *channel = _server->getChannel(name);
	std::map<std::string, Client * >	clients = channel->getClientMap();
//		std::cout << *channels[name] << std::endl;
	if (clients.find(_client->getUsername()) == clients.end())
		return (_client->sendData(getReply(442, name)));
//	channels[name]->kick(_client, _param.substr(nameDel + 1));
}
