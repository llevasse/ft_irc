#include "Message.hpp"

Message::Message(Server *server, Client *client, const std::string message ){
	_server = server;
	int	sep = message.find(" ");
	_command = message.substr(0,sep);
	_param = message.substr(sep + 1);
	if (_command == "NICK")
		Nick(server, client, _param);
	else if (_command == "USER")
		UserCmd(server, client, _param);
/*	else if (_command == "PASS")
		Pass(_command, _param, socket);
	else if (_command == "JOIN")
		Join(_command, _param, socket);
	else if (_command == "PRIVMSG")
		Privmsg(_command, _param, socket);
	else if (_command == "KICK")
		Kick(_command, _param, socket);
	else if (_command == "INVITE")
		Invite(_command, _param, socket);
	else if (_command == "TOPIC")
		Topic(_command, _param, socket);
	else if (_command == "MODE")
		Mode(_command, _param, socket);
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
