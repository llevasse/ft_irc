/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/21 18:37:37 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include "tools.hpp"
# include "Client.hpp"
# include "Message.hpp"
# include "Channel.hpp"

class Server
{
	private:

		u_short							_port;
		std::string						_password;
		sockaddr_in						_addr;
		std::map< int, Client * >		_clients;
		std::vector< pollfd > 			_pollfds;
		std::map<std::string, Channel *>	_channels;

		static bool					_loop;

	public:

		Server( const std::string &port, const std::string &password);
		~Server( void );

		Server	&operator=( const Server &src );

		unsigned int							getNbClients() const;
		const std::map<int, Client *>			&getClientsMap() const;
		const std::string						&getPassword() const;
		const std::map<std::string, Channel *>	&getChannels() const;
		Channel									*getChannel( const std::string &name ) const;

		void	newClient( void );
		void	removeClient( int fd, int index );
		void	newChannel( Client *client, const std::string &name );

		void	run( void );
		void	clientAction( int index );
		void	loop( void );
		void	clear( void );

		static void	stop( int signal );

		class BadPort : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class BadPassword : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class PasswordTooLong : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToCreateSocket : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToBindSocket : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToListenSocket : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToPoll : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
};

std::ostream &operator << (std::ostream &out, const Server &obj);

#endif
