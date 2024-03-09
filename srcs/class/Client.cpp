/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguelin <eguelin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:53 by eguelin           #+#    #+#             */
/*   Updated: 2024/03/09 18:18:27 by eguelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* ************************************************************************** */
/*                         Constructors & Destructors                         */
/* ************************************************************************** */

Client::Client( void )
{
	this->_fd = -1;
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_lenAddr = sizeof(this->_addr);
}

Client::Client( int serverSocket )
{
	this->_fd = accept(serverSocket, reinterpret_cast<sockaddr *>(&this->_addr), &this->_lenAddr);

	if (this->_fd == -1)
		throw Client::FailedToAcceptClient();
}

Client::Client( const Client &src )
{
	*this = src;
}

Client::~Client( void )
{
}

/* ************************************************************************** */
/*                              Operator overload                             */
/* ************************************************************************** */

Client	&Client::operator=( const Client &src )
{
	this->_fd = src._fd;
	memcpy(&this->_addr, &src._addr, sizeof(this->_addr));
	this->_lenAddr = src._lenAddr;

	return (*this);
}

/* ************************************************************************** */
/*                           Public member functions                          */
/* ************************************************************************** */

int	Client::getFd( void ) const {return (this->_fd);}

const sockaddr_in	&Client::getAddr( void ) const {return (this->_addr);}

const socklen_t		&Client::getLenAddr( void ) const {return (this->_lenAddr);}

/* ************************************************************************** */
/*                             Exceptions classes                             */
/* ************************************************************************** */

const char	*Client::FailedToAcceptClient::what() const throw()
{
	return ("Failed to accept client");
}
