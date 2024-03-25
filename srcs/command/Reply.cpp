#include "Message.hpp"

std::string ERR_NEEDMOREPARAMS( std::string arg1 ) { return ("461 " + arg1 + " :Not enough parameters");}
std::string ERR_NONICKNAMEGIVEN( std::string arg1 ) { return ("431 " + arg1 + " :No nickname given");}
std::string ERR_ERRONEUSNICKNAME( std::string arg1 ) { return ("432 " + arg1 + " :Erroneus nickname");}
std::string ERR_NICKNAMEINUSE( std::string arg1 ) { return ("433 " + arg1 + " :Nickname is already in use");}

std::string Message::getReply(unsigned short code, std::string arg1){
	std::string source = ":";
	if (_client->isRegistered() && _client->getNickname() != "" )
		source += _client->getNickname() + "!" + _client->getUsername() + "@localhost ";
	else
		source += "localhost ";

	switch (code){
		case 431:
			return (source + ERR_NONICKNAMEGIVEN(arg1));
		case 432:
			return (source + ERR_ERRONEUSNICKNAME(arg1));
		case 433:
			return (source + ERR_NICKNAMEINUSE(arg1));
		case 461:
			return (source + ERR_NEEDMOREPARAMS(arg1));
	}
	return ("NaC");

}
