#include "Message.hpp"


// typical USER command example
//
// USER guest 0 * : realname 


void Message::user(){
	std::string	reply;
	size_t 		nameDel = _param.find(" ");
	size_t		modeDel = _param.find(" ", nameDel + 1);
	size_t		unusedDel = _param.find(" ", modeDel + 1);
	size_t		realnameDel = _param.find(":");
	std::string _name = _param.substr(0, nameDel);
	std::string _mode = _param.substr(nameDel + 1, modeDel - nameDel - 1);
	std::string _unused = _param.substr(modeDel + 1, unusedDel - modeDel - 1);
	if ((_name.length() == 1 && isdigit(_name[0])) || (_mode.length() > 1 || !isdigit(_mode[0])) || (_unused[0] == ':'))
		return (_client->sendData(getReply(461, "USER")));
	if (nameDel == std::string::npos || modeDel == std::string::npos || unusedDel == std::string::npos || realnameDel == std::string::npos)
		return (_client->sendData(getReply(461, "USER")));
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit) && *rit != ':')
			break ;
		else if (*rit == ':')
			return (_client->sendData(getReply(461, "USER")));
	}
	//check for correct password
	if (_server->getPassword() != _client->getPass())
		return (_client->sendData(getReply(464)));
	//check if user is already registered
	if (_client->getUsername() != "")
		return (_client->sendData(getReply(462)));

	//check if username is already taken
	for (std::map< int, Client * >::const_iterator it = _server->getClientsMap().begin(); it != _server->getClientsMap().end(); it++){
		if (it->second->getUsername() == _name)
			return (_client->sendData(getReply(462)));
	}
	//set username
	_client->setUsername(_name);
	_client->setAsRegistered();
	reply = ":localhost NICK :" + _client->getNickname();
	if (_client->getNickname() != ""){
		_client->sendData(reply);
	}
}
