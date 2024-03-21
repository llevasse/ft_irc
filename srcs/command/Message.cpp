#include "Message.hpp"

Message::Message(Server *server, Client *client, const std::string message ){
	_server = server;
	_client = client;
	size_t	sep = message.find(" ");
	size_t	returnSep = message.find_last_not_of("\r\n");
	if (sep == std::string::npos)
		sep = returnSep;
	_command = message.substr(0, sep);
	_param = message.substr(sep + 1, returnSep - sep);
	if (_command == "NICK")
		this->nick();
	else if (_command == "USER")
		this->user();
	else if (_command == "PASS")
		this->pass();
	else if (_command == "PRIVMSG")
		this->privmsg();
	else if (_command == "TOPIC")
		this->topic();
	else if (_command == "MODE")
		this->mode();
	else if (_command == "JOIN")
		this->join();
/*	else if (_command == "KICK")
		Kick(_command, _param, socket);
	else if (_command == "INVITE")
		Invite(_command, _param, socket);
*/}

Message::Message( Message const &obj){
	if (this != &obj)
		*this = obj;
}

Message &Message::operator= ( Message const &obj){
	(void)obj;
	return (*this);
}

Message::~Message( void ){
}

std::ostream &operator << (std::ostream &out, const Message &obj){
	(void)obj;
	return (out);
}
