#include "Message.hpp"

void Message::mode(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg != std::string::npos){	//user mode
		std::map<std::string, Channel *> channels = _server->getChannels();
		if (channels.find(name) == channels.end())
			return (_client->sendData(getReply(403, name)));
		std::map<std::string, Client * >	clients = channels[name]->getClientMap();
		if (clients.find(_client->getUsername()) == clients.end())
			return (_client->sendData(getReply(442, name)));
		std::string::iterator it = _param.begin() + nameDel;
		while (it != _param.end()){
			if (*it == '+'){
				it++;
				if (*it == 'l'){
					(*channels[name])[*it++] = true;
					std::stringstream ss;
					ss << _param.substr(it - _param.begin());
					int limit;
					ss >> limit;
					channels[name]->setClientLimit(limit);
				}
				else if (*it == 'i')
					(*channels[name])[*it] = true;
			}
			else if (*it == '-'){
				it++;
				while (*it == 'i' || *it == 't' || *it == 'k' || *it == 'o' || *it == 'l')
					(*channels[name])[*it++] = false;
			}
			else
				it++;
		}
	}
}
