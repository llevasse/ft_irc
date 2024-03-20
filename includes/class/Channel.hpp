#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "tools.hpp"
#include "Client.hpp"

class Channel
{
	private:
		std::string		_name;
		std::string		_password;
		std::string		_topic;
		bool			_pwd;
		bool			_topicmode;
		bool			_inviteonly;
		bool			_limit;
		std::string		_owner;
		std::map<std::string, Client * >	_clients;


	public:
		Channel( std::string name);
		Channel( std::string name, std::string password);
		Channel( Channel const &obj);
		Channel &operator= ( Channel const &obj);
		~Channel( void );

		std::string		getName( void ) const;
		std::string		getPassword( void ) const;
		std::string		getTopic( void ) const;
		const std::map<std::string, Client * > &getClientMap( void ) const;

		void 			mode(Client *client, std::string param);
		void 			topic(Client *client, std::string param);
};

#endif
