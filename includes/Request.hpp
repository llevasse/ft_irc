#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>

class Request{
	private:
		std::string	_raw;
		std::string	_content;
		std::string	_username;
		std::string	_nickname;
		std::string	_passWord;
		std::string	_chan;
		std::string	_cmd;
		std::string _host;
		bool		_isOperator;

	public:
		Request( const std::string raw );
		Request( Request const &obj );
		Request &operator= ( Request const &obj );
		~Request( void );

		const	std::string	getRaw()const;
		const	std::string	getContent()const;
		const	std::string	getUsername()const;
		const	std::string	getNickname()const;
		const	std::string	getPassWord()const;
		const	std::string	getChan()const;
		const	std::string	getCmd()const;
		const	std::string	getHost()const;
};

std::ostream &operator << (std::ostream &out, const Request &obj);
#endif
