#include "Reply.hpp"

Reply::Reply( const std::string raw ){
	_raw = raw;

	if (_raw[0] == ':'){
		_nickname = _raw.substr(1, _raw.find("!") - 1);
		_username = _raw.substr(_raw.find("!") + 1, _raw.find("@") - 1 - _raw.find("!"));
		_host = _raw.substr(_raw.find("@") + 1, _raw.find(" ") - 1 - _raw.find("@"));
		_cmd = _raw.substr(_raw.find(" ") + 1, _raw.find(" ", _raw.find(" ") + 1) - 1 - _raw.find(" "));
		_chan = _raw.substr(_raw.find("#") + 1, _raw.find(" ", _raw.find("#") + 1) - 1 - _raw.find("#"));
		_content = _raw.substr(_raw.find(":", 2) + 1);
	}
}

Reply::Reply( Reply const &obj){
	if (this != &obj)
		*this = obj;
}

Reply &Reply::operator= ( Reply const &obj){
	(void)obj;
	return (*this);
}

Reply::~Reply( void ){
}

const	std::string	Reply::getRaw()const { return _raw;}
const	std::string	Reply::getContent()const { return _content;}
const	std::string	Reply::getUsername()const { return _username;}
const	std::string	Reply::getNickname()const { return _nickname;}
const	std::string	Reply::getPassWord()const { return _passWord;}
const	std::string	Reply::getChan() const{ return _chan;}
const	std::string	Reply::getCmd() const{ return _cmd;}
const	std::string	Reply::getHost() const{ return _host;}

std::ostream &operator << (std::ostream &out, const Reply &obj){
	out << "Reply : " << std::endl;
	out << "\t" << "raw : " << obj.getRaw() << std::endl; 
	out << "\t" << "content : " << obj.getContent() << std::endl; 
	out << "\t" << "username : " << obj.getUsername() << std::endl; 
	out << "\t" << "nickname : " << obj.getNickname() << std::endl; 
	out << "\t" << "password : " << obj.getPassWord() << std::endl; 
	out << "\t" << "chan : " << obj.getChan() << std::endl; 
	out << "\t" << "cmd : " << obj.getCmd() << std::endl; 
	out << "\t" << "host : " << obj.getHost(); 
	return (out);
}
