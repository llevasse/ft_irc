/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:50:47 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/08 15:40:29 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <map>
# include <vector>
# include "Client.hpp"
# include "ft_irc.hpp"

class Server
{
	public:

		Server( u_short port, const std::string &password);
		~Server( void );

		void	run( void );
		void	newClient( void );
		void	loop( void );

		Server	&operator=( const Server &src );



	private:

		u_short					_port;
		std::string				_password;
		sockaddr_in				_addr;
		std::map< int, Client >	_clients;
		std::vector< pollfd > 	_pollfds;
};

std::ostream	&operator<<( std::ostream &o, const Server &src );

#endif
