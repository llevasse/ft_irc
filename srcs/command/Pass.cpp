#include "Pass.hpp"

Pass::Pass( Server *server, Client *client, std::string param){
	std::string	pass = param.substr(0, param.find_first_of(" \n\r\t"));
	(void)server;
	bool found	= 0;
	std::string	reply = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost 461 " + client->getNickname() +  " :Not enough parameters\r\n";
	for (std::string::reverse_iterator rit=param.rbegin(); rit!=param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == param.rend()){
			client->sendData(reply);
			return ;
		}
	}
	if (!found){
		client->sendData(reply);
		return ;
	}
	client->setPass(pass);
}

Pass::Pass( Pass const &obj){
	if (this != &obj)
		*this = obj;
}

Pass &Pass::operator= ( Pass const &obj){
	(void)obj;
	return (*this);
}

Pass::~Pass( void ){
}

std::ostream &operator << (std::ostream &out, const Pass &obj){
	out << "Pass";
	(void)obj;
	return (out);
}
