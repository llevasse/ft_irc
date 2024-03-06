#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <sstream>

# ifndef MUTE
#  define MUTE 0
# endif

class Irc{
	private:
		std::string	_pw;
		int			_port;

		bool		check_pw(const std::string &pw);
		std::string	trim(const std::string str);
	public:
		Irc(const std::string &pw, const std::string &port);
		~Irc( void );
};


std::ostream &operator << (std::ostream &out, const Irc &obj);
#endif
