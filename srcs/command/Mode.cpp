#include "Message.hpp"

void Message::mode(){
	std::string	reply;
	size_t		beg		= _param.find("#");
	size_t		nameDel = _param.find(" ");
	std::string name = _param.substr(0, nameDel - beg);
	if (beg == std::string::npos){	//user mode
		if (name != _client->getNickname())
			return (_client->sendData(getReply(502)));
		for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
			if (it->second->getNickname() != name)
				return (_client->sendData(getReply(401, name)));
		}
		std::map<char, bool> modes = _client->getModesMap();
		if (_param.find_first_of("+-") != std::string::npos){
			for (std::string::iterator it = _param.begin() + nameDel; it != _param.end(); it++){
				if (*it == '+'){
					*it++;
					while (it != _param.end() && !isspace(*it) && *it != '-' && *it != '+'){
						modes[*it] = true;
						it++;
					}
				}
				if (*it == '-'){
					*it++;
					while (it != _param.end() && !isspace(*it) && *it != '-' && *it != '+'){
						modes[*it] = false;
						it++;
					}
				}
			}
		}
		else{
			std::string modeStr = "+";
			for (std::map<char,bool>::iterator it = modes.begin(); it != modes.end(); it++){
				if (it->second)
					modeStr += it->first;
			}
			_client->sendData(getReply(221, modeStr));
		}
	}
/*	else{	//channel mode
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
	}*/
}
