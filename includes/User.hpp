#ifndef USER_HPP
# define USER_HPP

# include <iostream>

# ifndef MUTE
#  define MUTE 0
# endif

class User{
	private:
		int	_socket;
		std::string _nickname;
		std::string _username;
	public:
		User( int _socket );
		User( User const &obj );
		User &operator= ( User const &obj );
		~User( void );

		int	getSocket();
		std::string	getNickname();
		std::string	getUsername();

		void	setNickname(std::string name);
		void	setUsername(std::string name);
};

std::ostream &operator << (std::ostream &out, const User &obj);
#endif
