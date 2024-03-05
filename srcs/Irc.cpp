#include "Irc.hpp"


std::string Irc::trim( const std::string str ){
	int	beg=0, end=str.length()-1;
	for (; end > 0 && !isalnum(str[end]); end--);
	for (; beg < end && !isalnum(str[beg]); beg++);
	return (str.substr(beg, end+1));
}

Irc::Irc( const std::string &pw, const std::string &port ){
	std::string p;
	if (!MUTE)
		std::cout << "Irc default \033[32mconstructor\033[0m called!" << std::endl;
	try{
		p = trim(port);	
	}
	catch (std::exception &e){
		e.what();
	}
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
