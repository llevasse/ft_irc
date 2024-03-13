#include "Nick.hpp"

Nick::Nick( Irc *server, std::string command, std::string param, int socket ){
	std::cout << "(" << socket << ") :" << command << " " << param << std::endl;
	User *user = server->getUserBySocket(socket);
	for (unsigned long i = 0; i < server->getNbUsers(); i++){
		if (server->getUserByIndex(i)->getNickname() == param){
			std::cout << ":" << user->getNickname() << "!" << user->getUsername() << "@localhost 433" << user->getNickname() << " " << param << " :Nickname is already in use" << std::endl;
			throw (std::runtime_error("Nickname already in use"));
		}
	}
	std::cout << ":" << user->getNickname() << "!" << user->getUsername() << "@localhost " << command << " :" << param << std::endl;
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
