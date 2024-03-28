#include "Message.hpp"

void Message::mode(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg != std::string::npos){
		Channel *	channel = _server->getChannel(name);

		if (!channel)
			return (_client->sendData(getReply(403, name)));

		std::map<std::string, Client * >	clients = channel->getClientMap();
		if (clients.find(_client->getUsername()) == clients.end())
			return (_client->sendData(getReply(442, name)));
		std::string::iterator it = _param.begin() + nameDel;
		while (it != _param.end()){
			if (*it == '+'){
				it++;
				if (*it == 'l'){
					(*channel)[*it++] = true;
					std::stringstream ss;
					ss << _param.substr(it - _param.begin());
					int limit;
					ss >> limit;
					channel->setClientLimit(limit);
				}
				else if (*it == 'i')
					(*channel)[*it] = true;
				else if (*it == 'k'){
					beg = _param.find_first_not_of(" ", it - _param.begin() + 1);
					(*channel)[*it] = true;
					channel->setPassword(_param.substr(beg));
				}
			}
			else if (*it == '-'){
				it++;
				while (*it == 'i' || *it == 't' || *it == 'k' || *it == 'o' || *it == 'l')
					(*channel)[*it++] = false;
			}
			else
				it++;
		}
	}
}
