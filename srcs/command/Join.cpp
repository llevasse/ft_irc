#include "Message.hpp"

void Message::join(){
	std::string reply;
	std::string name = this->_param.substr(0, this->_param.find(" "));
	Channel *channel = this->_server->getChannel(name);

	if (channel == NULL){
		this->_server->newChannel(this->_client, name);
		reply = ":" + this->_client->getNickname() + "!" + this->_client->getUsername() + "@localhost JOIN " + name;
		this->_client->sendData(reply);
		this->_client->sendData(getReply(353, this->_client->getNickname(), " = ", name));
	}
	else{
		//need implement reply 332 && 333
		const std::map<std::string, Client * >	&clients = channel->getClientMap();

		channel->addClient(this->_client);
		reply = ":" + this->_client->getNickname() + "!" + this->_client->getUsername() + "@localhost JOIN " + name;
		for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
			it->second->sendData(reply);
		for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++){
			if ((*it->second)['i'] == false)
				this->_client->sendData(getReply(353, it->second->getNickname(), " = ", name));
		}
	}
	this->_client->sendData(getReply(366,this->_client->getNickname(), name));
}
