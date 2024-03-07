#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>

class Request{
	private:
		std::string	_raw;
		std::string	_mess;
		std::string	_username;
		std::string	_nickname;
		std::string	_passWord;
		std::string	_chan;
		std::string	_cmd;
		bool		_isOperator;

	public:
		Request( const std::string raw );
		Request( Request const &obj );
		Request &operator= ( Request const &obj );
		~Request( void );
};

std::ostream &operator << (std::ostream &out, const Request &obj);
#endif
