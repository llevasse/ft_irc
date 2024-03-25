#include "Message.hpp"

std::string ERR_NEEDMOREPARAMS( std::string arg1 ) { return ("461 " + arg1 + " :Not enough parameters");}
std::string ERR_NONICKNAMEGIVEN( std::string arg1 ) { return ("431 " + arg1 + " :No nickname given");}
std::string ERR_ERRONEUSNICKNAME( std::string arg1 ) { return ("432 " + arg1 + " :Erroneus nickname");}
std::string ERR_NICKNAMEINUSE( std::string arg1 ) { return ("433 " + arg1 + " :Nickname is already in use");}

std::string Message::getReply(unsigned short code, std::string arg1){
	std::string prefix = ":";
	std::string name;
	if (_client->isRegistered() && _client->getNickname() != "" ){
		prefix += _client->getNickname() + "!" + _client->getUsername() + "@localhost ";
		name = _client->getNickname() " ";
	}
	else{
		name = "* ";
		prefix += "localhost ";
	}

	switch (code){
		case 431:
			return (prefix + ERR_NONICKNAMEGIVEN(name));
		case 432:
			return (prefix + ERR_ERRONEUSNICKNAME(name + arg1));
		case 433:
			return (prefix + ERR_NICKNAMEINUSE(name + arg1));
		case 461:
			return (prefix + ERR_NEEDMOREPARAMS(name + arg1));
	}
	return ("NaC");

}
