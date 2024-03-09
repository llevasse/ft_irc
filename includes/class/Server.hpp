/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/09 18:28:50 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include "tools.hpp"
# include "Client.hpp"

class Server
{
	public:

		Server( u_short port, const std::string &password);
		~Server( void );

		Server	&operator=( const Server &src );

		void	run( void );
		void	newClient( void );
		void	removeClient( int fd, int index );
		void	loop( void );

	private:

		u_short					_port;
		std::string				_password;
		sockaddr_in				_addr;
		std::map< int, Client >	_clients;
		std::vector< pollfd > 	_pollfds;
};

#endif
