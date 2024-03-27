#include "Message.hpp"


int	checkModes(Client *client, Channel *channel){
		if ((*channel)['l'] == true && static_cast<int>(channel->getClientMap().size()) >= channel->getClientLimit())
			return 471;
		std::map<std::string, bool >	invites = channel->getInvitesMap();
		if (((*channel)['i'] == true && invites[client->getUsername()] == false))
			return 473;

		return (0);
}

void Message::join(){
	std::string reply;
	std::string name;
	std::queue<std::string> nameQ;

	// push each channel passed in _param inside of queue
	size_t	nameDel = this->_param.find_first_of(", ");
	size_t	prev = 0;
	while (nameDel != std::string::npos && this->_param[nameDel] == ','){
		nameQ.push(this->_param.substr(prev, nameDel - prev));
		prev = nameDel + 1;
		nameDel = this->_param.find_first_of(", ", prev);
	}
	nameQ.push(this->_param.substr(prev, nameDel - prev));

	while (!nameQ.empty()){
		name = nameQ.front();
		nameQ.pop();
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

			int ret = checkModes(this->_client, channel);
			if (ret == 0){
				channel->addClient(this->_client);
				reply = ":" + this->_client->getNickname() + "!" + this->_client->getUsername() + "@localhost JOIN " + name;
				for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
					it->second->sendData(reply);
				for (std::map<std::string, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
					this->_client->sendData(getReply(353, it->second->getNickname(), " = ", name));
			}
			else
				return this->_client->sendData(getReply(ret, name));
		}
		this->_client->sendData(getReply(366,this->_client->getNickname(), name));
	}
}
