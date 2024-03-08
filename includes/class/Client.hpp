/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/08 16:13:43 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "ft_irc.hpp"

class Client
{
	public:

		Client( int serverSocket );
		~Client( void );

		Client	&operator=( const Client &src );

	private:

		pollfd		_pollfd;
		sockaddr_in	_addr;
		socklen_t	_lenAddr;
};

std::ostream	&operator<<( std::ostream &o, const Client &src );

#endif
