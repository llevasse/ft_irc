/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/10 16:58:56 by eguelin          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "tools.hpp"

class Client
{
	public:

		Client( int serverSocket );
		~Client( void );

		int					getFd( void ) const;
		const sockaddr_in	&getAddr( void ) const;
		const socklen_t		&getLenAddr( void ) const;

		/* receiveData will receive data from the client
		receiveData can throw the following exceptions:
		- FailedToReceiveData */
		std::string	receiveData( void ) const;

		/* sendData will send data to the client
		sendData can throw the following exceptions:
		- FailedToSendData */
		void		sendData( const std::string &data ) const;

		class FailedToAcceptClient : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToReceiveData : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FailedToSendData : public std::exception
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