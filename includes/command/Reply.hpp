#ifndef REPLY_HPP
# define REPLY_HPP

# include <iostream>

class Reply{
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
		Reply( const std::string raw );
		Reply( Reply const &obj );
		Reply &operator= ( Reply const &obj );
		~Reply( void );

		const	std::string	getRaw()const;
		const	std::string	getContent()const;
		const	std::string	getUsername()const;
		const	std::string	getNickname()const;
		const	std::string	getPassWord()const;
		const	std::string	getChan()const;
		const	std::string	getCmd()const;
		const	std::string	getHost()const;
};

std::ostream &operator << (std::ostream &out, const Reply &obj);
#endif
