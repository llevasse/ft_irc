#include "Irc.hpp"
#include "IrcExc.hpp"

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

Irc::Irc( const std::string &pw, const std::string &port ){
	std::string str;
	if (!MUTE)
		std::cout << "Irc default \033[32mconstructor\033[0m called!" << std::endl;
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
	if (!MUTE)
		std::cout << "Irc \033[31mdestructor\033[0m called!" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Irc &obj){
	out << "Irc";
	(void)obj;
	return (out);
}
