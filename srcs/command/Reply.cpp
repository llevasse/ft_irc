#include "Message.hpp"

std::string ERR_NEEDMOREPARAMS( std::string arg1 ) { return ("461 " + arg1 + " :Not enough parameters");}

std::string Message::getReply(unsigned short code, std::string arg1){
	std::string source = ":";
	if (_client->isRegistered() && _client->getNickname() != "" )
		source += _client->getNickname() + "!" + _client->getUsername() + "@localhost ";
	else
		source += "localhost ";

	switch (code){
		case 461:
			return (source + ERR_NEEDMOREPARAMS(arg1));
	}
	return ("NaC");

}
