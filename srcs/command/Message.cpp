#include "Message.hpp"

Message::Message(Server *server, Client *client, const std::string &message ){
	_server = server;
	_client = client;
	size_t	sep = message.find(" ");
	size_t	returnSep = message.find_first_of("\r\n");
	if (message[returnSep] == '\r' || message[returnSep] == '\n')
		returnSep--;
	if (sep == std::string::npos)
		sep = returnSep;
	_command = message.substr(0, sep);
	if (message.find(" ") != std::string::npos){
		size_t prev = message.find_first_not_of(" \r\n", sep);
		sep = message.find_first_of(" \r\n", prev + 1);
		if (prev != std::string::npos){
			if (message[prev] == ':')
				sep = std::string::npos;
			while (sep != std::string::npos){
				if (message[prev] == ':'){
					sep = message.length();
					break ;
				}
				_params.push_back(message.substr(prev, sep - prev));
				prev = message.find_first_not_of(" \r\n", sep + 1);
				sep = message.find_first_of(" \r\n", prev + 1);
			}
			_params.push_back(message.substr(prev, sep - prev));
		}
	}
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
	else if (_command == "KICK")
		this->kick();
	/*else if (_command == "INVITE")
		Invite(_command, _param, socket);
*/
}

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
