#include "Message.hpp"

void Message::pass(){
	std::string	pass = _param.substr(0, _param.find_first_of(" \n\r\t"));
	bool found	= 0;
	std::string	reply = ":" + _client->getNickname() + "!" + _client->getUsername() + "@localhost 461 " + _client->getNickname() +  " :Not enough _parameters\r\n";
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == _param.rend()){
			_client->sendData(reply);
			return ;
		}
	}
	if (!found){
		_client->sendData(reply);
		return ;
	}
	_client->setPass(pass);
}
