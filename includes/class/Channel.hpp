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
		int				_clientLimit;
		std::map<std::string, Client * >	_clients;
		std::map<std::string, bool >	_invites;
		std::map<char, bool>	_modes;


	public:
		Channel( std::string name);
		Channel( Client *client, std::string name, std::string password);
		Channel( Channel const &obj);
		~Channel( void );

		const std::string		&getName( void ) const;
		const std::string		&getPassword( void ) const;
		const std::string		&getTopic( void ) const;
		const std::map<std::string, Client * > &getClientMap( void ) const;
		const std::map<char, bool>	&getModesMap( void ) const;
		const std::map<std::string, bool>	&getInvitesMap( void ) const;
		const int	&getClientLimit(void) const;

		void			setClientLimit(int limit);

		void			addClient( Client *client );

		void			topic(Client *client, std::string param);
		void			kick(Client *client, std::string param);

		void			error(Client *client, std::string code, std::string msg, std::string channel);

		// return ref to _modes element with key c
		bool	&operator [] (char c);
};
std::ostream &operator << (std::ostream &out, const Channel &obj);

#endif
