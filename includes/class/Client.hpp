/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/09 18:28:58 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "tools.hpp"

class Client
{
	public:

		Client( void );
		Client( int serverSocket );
		Client( const Client &src );
		~Client( void );

		int					getFd( void ) const;
		const sockaddr_in	&getAddr( void ) const;
		const socklen_t		&getLenAddr( void ) const;

		Client	&operator=( const Client &src );

		class FailedToAcceptClient : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

	private:

		int 		_fd;
		sockaddr_in	_addr;
		socklen_t	_lenAddr;
};

#endif
