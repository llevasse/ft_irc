#include "Message.hpp"

//either	TOPIC #channel topic
//or		TOPIC #channel

void Message::topic(){
	std::map<std::string, Channel *> channels = _server->getChannels();
	size_t		beg		= _param.find("#");
	if (beg == std::string::npos)
		return ;
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(beg + 1, nameDel - beg);
	channels[name]->topic(_client, _param.substr(nameDel + 1));
}
