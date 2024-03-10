/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/10 22:39:12 by eguelin          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Client.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Client::Client( int serverSocket )
{
	std::cout << "Client constructor called" << std::endl;

	this->_lenAddr = sizeof(this->_addr);

	this->_fd = accept(serverSocket, reinterpret_cast<sockaddr *>(&this->_addr), &this->_lenAddr);

	if (this->_fd == -1)
		throw Client::FailedToAcceptClient();
}

Client::~Client( void )
{
	std::cout << "Client destructor called" << std::endl;

	close(this->_fd);
}

/* ************************************************************************** */
/*                                 Accessors                                  */
/* ************************************************************************** */

int	Client::getFd( void ) const {return (this->_fd);}

const sockaddr_in	&Client::getAddr( void ) const {return (this->_addr);}

const socklen_t		&Client::getLenAddr( void ) const {return (this->_lenAddr);}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

std::string	Client::receiveData( void ) const
{
	char		buffer[512];
	int			ret;

	ret = recv(this->_fd, buffer, 512, 0);

	if (ret == -1)
		throw Client::FailedToReceiveData();

	if (ret == 512)
	{
		buffer[510] = '\r';
		buffer[511] = '\n';
	}

	return (std::string(buffer, ret));
}

void	Client::sendData( const std::string &data ) const
{
	if (send(this->_fd, data.c_str(), data.size(), 0) == -1)
		throw Client::FailedToSendData();
}

/* ************************************************************************** */
/*                             Exceptions classes                             */
/* ************************************************************************** */

const char	*Client::FailedToAcceptClient::what() const throw()
{
	return ("Failed to accept client");
}

const char	*Client::FailedToReceiveData::what() const throw()
{
	return ("Failed to receive data");
}

const char	*Client::FailedToSendData::what() const throw()
{
	return ("Failed to send data");
}

