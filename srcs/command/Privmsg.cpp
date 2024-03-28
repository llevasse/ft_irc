#include "Message.hpp"

void Message::privmsg(){
	size_t del	= _param.find(" ");
	std::string	name = _param.substr(0, del);
	std::string mess = _param.substr(del + 1);

	Client *target = _server->getClient(name);
	if (target){
		std::string reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost PRIVMSG " + name + " " + mess;
		target->sendData(reply);
		return ;
	}
	if (name[0] == '#'){
		Channel *channel = this->_server->getChannel(name);
		std::string reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost PRIVMSG " + name + " " + mess;
		if (channel){
			const std::map<std::string, Client * >	&clients = channel->getClientMap();
			for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++){
				if (it->second->getUsername() != this->_client->getUsername())
					it->second->sendData(reply);
			}
		}
	}
}
