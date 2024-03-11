#include "Irc.hpp"

std::string Irc::trim( const std::string str ){
	int	beg=0, end=str.length()-1;
	for (; end > 0 && isspace(str[end]); end--);
	for (; beg < end && isspace(str[beg]); beg++);
	return (str.substr(beg, end+1));
}

bool Irc::check_pw( const std::string &pw ){

	if (pw.length() < 5)
		return (false);

	for (size_t i = 0; i < pw.length(); i++ )
	{
		if (!isalnum(pw[i]))
			return (false);
	}
	return (true);
}

Irc::Irc( const std::string &port, const std::string &pw ){
	std::string str;
	std::stringstream ss;
	ss << trim(port);
	ss >> _port;
	if (check_pw(pw) == false)
		throw (std::runtime_error("Invalid password"));
	if (_port < 0 || _port > 65535)
		throw (std::runtime_error("Invalid port value"));
	if (_port < 1023)
		throw (std::runtime_error("Port is already reserved"));
	_pw = pw;
}

Irc::~Irc( void ){
}

void	Irc::createUser(int socket){
	_users.push_back(User(socket));
}

User Irc::getUser(int socket){
	for (unsigned long i=0; i< _users.size(); i++){
		if (_users[i].getSocket() == socket)
			return (_users[i]);
	}
	throw (std::runtime_error("User not found"));
}


std::ostream &operator << (std::ostream &out, const Irc &obj){
	out << "Irc";
	(void)obj;
	return (out);
}
