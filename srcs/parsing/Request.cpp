#include "Request.hpp"

Request::Request( const std::string raw ){
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

Request::Request( Request const &obj){
	if (this != &obj)
		*this = obj;
}

Request &Request::operator= ( Request const &obj){
	(void)obj;
	return (*this);
}

Request::~Request( void ){
}

const	std::string	Request::getRaw()const { return _raw;}
const	std::string	Request::getContent()const { return _content;}
const	std::string	Request::getUsername()const { return _username;}
const	std::string	Request::getNickname()const { return _nickname;}
const	std::string	Request::getPassWord()const { return _passWord;}
const	std::string	Request::getChan() const{ return _chan;}
const	std::string	Request::getCmd() const{ return _cmd;}
const	std::string	Request::getHost() const{ return _host;}

std::ostream &operator << (std::ostream &out, const Request &obj){
	out << "Request : " << std::endl;
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
