#include "Nick.hpp"

Nick::Nick( Irc *server, std::string command, std::string param, int socket ){
	std::cout << "(" << socket << ") :" << command << " " << param << std::endl;
	for (unsigned long i = 0; i < server->getNbUsers(); i++){
		if (server->getUserByIndex(i)->getNickname() == param)
			throw (std::runtime_error("Nickname already in use"));
	}
	server->getUserBySocket(socket)->setNickname(param);
}

Nick::Nick( Nick const &obj){
	if (this != &obj)
		*this = obj;
}

Nick &Nick::operator= ( Nick const &obj){
	(void)obj;
	return (*this);
}

Nick::~Nick( void ){
}

std::ostream &operator << (std::ostream &out, const Nick &obj){
	out << "Nick";
	(void)obj;
	return (out);
}
