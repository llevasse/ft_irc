/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/19 17:28:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		const std::string	&getNickname() const;
		const std::string	&getUsername() const;
		const std::string	&getPass() const;
		const std::string	&getChannel() const;
		bool				getPermission(const std::string &channel) const;

		void				setNickname(const std::string name);
		void				setUsername(const std::string name);
		void				setPermission(const std::string &channel, bool permission);
		void				setPass(const std::string pass);
		void				setChannel(const std::string name);
		void				removePermission(const std::string &channel);

		/* receiveData will receive data from the client
		receiveData can throw the following exceptions:
		- FailedToReceiveData */
		std::string	receiveData( void );

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
		std::string _nickname;
		std::string _username;
		std::string _data;
		std::string _pass;
		std::string _channel;
		std::map<std::string, bool> _permissions;
};

#endif
