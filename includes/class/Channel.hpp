#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "tools.hpp"
#include "Client.hpp"
#include <string>

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
		int				_limitnum;
		std::string		_owner;
		std::map<std::string, Client * >	_clients;


	public:
		Channel( std::string name);
		Channel( std::string name, std::string password);
		Channel( Channel const &obj);
		~Channel( void );

		std::string		getName( void ) const;
		std::string		getPassword( void ) const;
		std::string		getTopic( void ) const;

		void 			mode(Client *client, std::string param);
		void 			topic(Client *client, std::string param);
		void 			kick(Client *client, std::string param);

		void 			error(Client *client, std::string code, std::string msg, std::string channel);
};

#endif
