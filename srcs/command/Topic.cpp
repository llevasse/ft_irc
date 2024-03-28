#include "Message.hpp"

//either	TOPIC #channel topic
//or		TOPIC #channel

void Message::topic(){
	size_t		beg		= _param.find("#");

	if (beg == std::string::npos)
		return (_client->sendData(getReply(461, "TOPIC")));


	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(beg + 1, nameDel - beg);
	Channel *channel = _server->getChannel(name);

	if (!channel)
		return (_client->sendData(getReply(403, name)));

	std::map<std::string, Client * >	clients = channel->getClientMap();

	if (clients.find(_client->getUsername()) == clients.end())
		return (_client->sendData(getReply(442, name)));

	channel->topic(_client, _param.substr(nameDel + 1));
}
