#include "Message.hpp"

void Message::privmsg(){
	size_t del	= _param.find(" ");
	std::string	name = _param.substr(0, del);
	std::string mess = _param.substr(del + 1);

	for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
		if (it->second->getNickname() == name){
			it->second->sendData(mess);
			return ;
		}
	}
}
