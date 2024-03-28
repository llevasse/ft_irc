/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/28 15:00:41 by eguelin          ###   ########.fr       */
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

		u_short								_port;
		sockaddr_in							_addr;
		std::string							_password;

		std::vector< Client * >				_clients;
		std::vector< pollfd > 				_pollfds;

		std::map< std::string, Client * >	_clientsNick;
		std::map< std::string, Channel * >	_channels;

		std::vector< std::string >			_usernames;

		static bool							_loop_flag;

		void	_loop( void );
		void	_clear( void );
		void	_clientRequest( size_t &index );
		void	_checkPort( const std::string &port );

	public:

		Server( const std::string &port, const std::string &password);
		~Server( void );

		Server	&operator=( const Server &src );

		const std::string	&getPassword() const;
		Client				*getClient( const std::string &nick ) const;
		Channel				*getChannel( const std::string &name ) const;

		void	run( void );

		void	newClient( void );
		void	removeClient( size_t index );

		void	newChannel( Client *client, const std::string &name , const std::string &password = "");
		void	removeChannel( const std::string &name );

		void	addClientNick( Client *client );
		void	changeClientNick( const std::string &oldNick, const std::string &newNick );

		void	addUsername( const std::string &username );
		bool	usernameExists( const std::string &username );

		static bool	isValidPasswordSyntax( const std::string &password );
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
