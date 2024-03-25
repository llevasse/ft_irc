#include "Message.hpp"

std::string RPL_NAMREPLY( std::string arg1, std::string arg2, std::string arg3 ) { return ("353 " + arg1 + arg2 + arg3 + " :" + arg1);}
std::string RPL_ENDOFNAMES( std::string arg1, std::string arg2 ) { return ("366 " + arg1 + " " + arg2 + " :End of /NAMES list.");}


std::string ERR_NONICKNAMEGIVEN( std::string arg1 ) { return ("431 " + arg1 + ":No nickname given");}
std::string ERR_NOSUCHCHANNEL( std::string arg1, std::string arg2 ) { return ("403 " + arg1 + arg2 + ":No such channel");}
std::string ERR_NOTONCHANNEL( std::string arg1, std::string arg2 ) { return ("442 " + arg1 + arg2 + ":You're not on that channel");}
std::string ERR_ERRONEUSNICKNAME( std::string arg1 ) { return ("432 " + arg1 + " :Erroneus nickname");}
std::string ERR_NICKNAMEINUSE( std::string arg1 ) { return ("433 " + arg1 + " :Nickname is already in use");}
std::string ERR_NEEDMOREPARAMS( std::string arg1 ) { return ("461 " + arg1 + " :Not enough parameters");}
std::string ERR_ALREADYREGISTERED( std::string arg1 ) { return ("462 " + arg1 + ":You may not register");}
std::string ERR_PASSWDMISMATCH( std::string arg1 ) { return ("464 " + arg1 + ":Password incorrect");}

std::string Message::getReply(unsigned short code, std::string arg1, std::string arg2, std::string arg3){
	std::string prefix = ":";
	std::string name;
	if (_client->isRegistered() && _client->getNickname() != "" ){
		prefix += _client->getNickname() + "!" + _client->getUsername() + "@localhost ";
		name = _client->getNickname() + " ";
	}
	else{
		name = "* ";
		prefix += "localhost ";
	}

	switch (code){
		case 353:
			return (prefix + RPL_NAMREPLY(arg1, arg2, arg3));
		case 366:
			return (prefix + RPL_ENDOFNAMES(arg1, arg2));
		case 403:
			return (prefix + ERR_NOSUCHCHANNEL(name, arg1));
		case 431:
			return (prefix + ERR_NONICKNAMEGIVEN(name));
		case 432:
			return (prefix + ERR_ERRONEUSNICKNAME(name + arg1));
		case 433:
			return (prefix + ERR_NICKNAMEINUSE(name + arg1));
		case 442:
			return (prefix + ERR_NOTONCHANNEL(name, arg1));
		case 461:
			return (prefix + ERR_NEEDMOREPARAMS(name + arg1));
		case 462:
			return (prefix + ERR_ALREADYREGISTERED(name));
		case 464:
			return (prefix + ERR_PASSWDMISMATCH(name));
	}
	return ("NaC");

}

std::string Message::getReply(unsigned short code){ return (getReply(code, "", "", ""));}
std::string Message::getReply(unsigned short code, std::string arg1){ return (getReply(code, arg1, "", ""));}
std::string Message::getReply(unsigned short code, std::string arg1, std::string arg2){ return (getReply(code, arg1, arg2, ""));}
