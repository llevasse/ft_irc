/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/21 10:23:08 by llevasse         ###   ########.fr       */
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
	public:

		Server( const std::string &port, const std::string &password);
		~Server( void );

		Server	&operator=( const Server &src );

		/* return size of _clients */
		unsigned int							getNbClients() const;
		const std::map<int, Client *>			&getClientsMap() const;
		const std::string						&getPassword() const;
		const std::map<std::string, Channel *>	&getChannels() const;

		/* run is the main function of the server, it will create the socket,
		bind it, listen to it and then loop to accept new clients
		run can throw the following exceptions:
		- FailedToCreateSocket
		- FailedToBindSocket
		- FailedToListenSocket
		- FailedToPoll
		- FailedToAcceptClient */
		void	run( void );

		/* newClient will create a new client and add it to the clients map
		newClient can throw the following exceptions:
		- FailedToAcceptClient */
		void	newClient( void );

		/* removeClient will remove a client from the clients map */
		void	removeClient( int fd, int index );

		/* loop will loop to accept new clients and handle them
		loop can throw the following exceptions:
		- FailedToPoll
		- FailedToAcceptClient */
		void	loop( void );

		/* clear will clear the server */
		void	clear( void );

		/* clientAction will handle the client action */
		void	clientAction( int index );

		/* stop will stop the server */
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

	private:

		u_short							_port;
		std::string						_password;
		sockaddr_in						_addr;
		std::map< int, Client * >		_clients;
		std::vector< pollfd > 			_pollfds;
		std::map<std::string, Channel *>	_channels;

		static bool					_loop;
};

std::ostream &operator << (std::ostream &out, const Server &obj);

#endif
