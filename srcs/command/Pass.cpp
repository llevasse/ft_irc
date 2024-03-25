#include "Message.hpp"

void Message::pass(){
	std::string	pass = _param.substr(0, _param.find_first_of(" "));
	bool found	= 0;
	for (std::string::reverse_iterator rit=_param.rbegin(); rit!=_param.rend(); rit++){
		if (!isspace(*rit)){
			found = 1;
			break ;
		}
		else if (rit == _param.rend())
			return (_client->sendData(getReply(461, "PASS")));
	}
	if (!found)
		return (_client->sendData(getReply(461, "PASS")));
	_client->setPass(pass);
}
